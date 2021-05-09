#ifndef ValScreen_def
#define ValScreen_def
#define bp_nowhite(b) !(*b==255 && *(b+1)==255 && *(b+2)==255)
#define bp_white(b) (*b==255 && *(b+1)==255 && *(b+2)==255)
	HWND DRAW_HWND=NULL;	
void destroy_drawing();  

#define RECT val_rect
struct val_rect{
    int X; 
    int Y;
    int Width;
    int Height;
};
int get_y_from_parabola(int a, int b, int c, int d,int x, int yzero, int ytop,bool invert);
// parses (ax^2)/d + bx +c .  returns values between yzero and ytop.  invert to invert plain 0=ytop (inverted is standard bottom left ==0,0)
#include "valsprite.h"
class ValScreen{

    public:
    char *bits;
	char* copybuf;

    HDC hdc;
    HDC condc;
    HWND enum_HWND;
    ValSprite sprites;
	LPRECT WindowRect;
	bool DO_EDIT_GETPIX;
    // creation and variables
    ValScreen();
    ValScreen(val_rect rect);
    ValScreen(int x, int y, int w, int h);
    ~ValScreen();
    void Set(int x, int y, int w, int h);
    void SetX(int x);
    void SetY(int y);
    void SetWidth(int w);
    void SetHeight(int h);
    void SetRECT(RECT rect);
    
	void reset_bounds();
    void start_vars();
    void outinfo();
    
    // file handling
    void write_file(string a);
	void write_file_std(LPTSTR fname);
    void buf_load_file_bmp(string fname);
    
    // screen and window recording
	int get_screen();
    int get_hwnd_screen(HWND hwnd,int x,int y,int w,int h);
	COLORREF Get_Pixel(int x, int y);
	int buf_Get_Pixel(int x, int y);
	int buf_xyindex(int x, int y);
	
    // console and transparent window drawing
	void console_draw();
	void bufconsole_draw(); 
	void bufconsole_draw(int w, int h);
	void bufwin_draw();
	void bufwin_draw(int x,int y);
	
	// HWND target generation/agragate 
    HWND create_drawing_console(int xx, int yy, int ww, int hh);
    HWND find_Window(string title,int &x, int &y, int &w, int &h);
    HWND create_transparent_window(int xx, int yy, int ww, int hh);
	HWND create_transparent_window2(int xx, int yy, int ww, int hh);
    
	
	
    // buffer handlers
    void get_buffer(HBITMAP &hbmp,int &w, int &h);
	void get_buffer();
    int buf_editpix(int x, int y, int plc);
    int buf_editrgb(int x, int y,BYTE r, BYTE g, BYTE b, int plc);
    void white_buffer(int alpha);
	void black_buffer(int alpha);
	void white_buffer_sect(int x, int y, int w, int h, int alpha );  //alpha=0

    // shapes and lines
	void buf_drawbox(int x, int y, int w, int h);
    void buf_drawbox2(int x, int y, int w, int h, char r, char g, char b);
    
    void buf_drawrect(int tx, int ty, int tw, int th);
	void buf_draw_boarder(int width);
    
	void buf_drawline(int x, int y, int xy,bool horizontal, int width);
    void buf_drawlinefrom(int x, int y, int xx, int yy, int width);
    void buf_drawlinefrom2(int x, int y, int xx, int yy, int width);
    
 	void buf__drawslopex(int x, int y, int ydir, double a, int itt); // ydir can be -1|1 
 	void buf__drawslopey(int x, int y, int xdir, double a, int itt); // xdir can be -1|1 
 	void buf_drawlinefrom_slope(int x, int y, int xx, int yy, int width);
	void buf_drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width);
    void draw_curve(int a, int b, int c,int d, int xzero, int xtop, int yzero, int ytop,bool invert);
    void draw_curve2(int a, int b, int c,int d, int xzero, int xtop, int yzero, int ytop,bool invert);
        
    void buf_drawcircle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width);
    void buf_draw_circle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width);
	
	void buf_drawtext(int x, int y, int w, int h, string text); // uses GDI textout function
    
	void vsprite_findsprites();
    
	void delete_buf();
	void copy_buf();
	void paste_buf();


	void buf_whitefix_pix(char* pix);
	void buf_whitefix();
    
    
    int buf_width, buf_height;
    long int buffer_size;
    val_rect r;
    POINT p;
    HDC m_HDC;
    HBITMAP bmp;
    HDC bufhdc;
	HBITMAP newbitmap;
	bool IS_BUFFER, vsfound_window;
    HDC hdcg;
	HBITMAP Selectdump;
	private:
    
};
void ValScreen::buf_whitefix_pix(char* pix) {
	char* hold = pix;
	BYTE a, b, c;
	a = *pix; b = *(pix + 1); c = *(pix + 2);
	if (a > 200 && b > 200 && c > 200 ){//&& a<230 && b<230 &&c<230){
		if (abs(a - b) + abs(b - c) + abs(c - a) < 25) {
			*pix = 255; pix++;
			*pix = 255; pix++;
			*pix = 255; pix++;
			*pix = 200; 
			
		}

	}
	pix = hold;
}
void ValScreen::buf_whitefix() {
	char* hold = bits;
	for (int n = 0; n < buf_height; n++) {
		for (int i = 0; i < buf_width; i++) {
			buf_whitefix_pix(hold);
			hold += 4;
		}
	}

}
void ValScreen::copy_buf() {
	if (copybuf != NULL) {
		delete[] copybuf;
	}
	copybuf = new char[buf_width * buf_height * 4];
	memcpy(copybuf, bits, buf_width * buf_height * 4);

}
void ValScreen::paste_buf() {
	memcpy( bits,copybuf , buf_width * buf_height * 4);

}

void ValScreen::delete_buf() {
	ReleaseDC(NULL,hdcg);
	DeleteObject(newbitmap);
	//delete[] bits;
	DeleteDC(hdcg);
}

void ValScreen::vsprite_findsprites() {
	sprites.findsprites();
	int nnn = sprites.get_listsize();
	int tx, ty, tw, th;
	for (int i = 0; i < nnn; i++) {
		sprites.get_sprite_bounds(i, tx, ty, tw, th);
		buf_drawrect(tx, ty, tw, th);
	}
	bufconsole_draw();
}


void ValScreen::buf_drawrect(int tx, int ty, int tw, int th){
	buf_drawline(tx,ty,tw,1,3);
	buf_drawline(tx,ty+th,tw,1,3);
	
	buf_drawline(tx,ty,th,0,3);
	buf_drawline(tx+tw,ty,th,0,3);	
		
}
int circle_getyfromXR(double x, int r, bool &f){
	double xx = x*x;
	double rr = r*r;
	xx=rr-xx;
	
	if(xx<0){
	  f=false;
	  return -1;
	}
	f=true;
	if(xx==0)return 0;
	//if(xx<2)return 1;
	return sqrt(xx);
}
int get_y_from_parabola(int a, int b, int c, int d,int x, int yzero, int ytop,bool invert=true){
		
		int y=0,ym=0,ly=0,ytoph=0;
		y= a*x;
		y=y*y;
		y+= b*x;
		
		y/=d;
		y+=c;
		
		
		
		
		if(ly!=0) ym = (y-ly);
		//else ym=1;
		if(ym<0) ym*=-1;
		ym+=2;
		if(invert)ytoph=ytop-(y+ym);
		else ytoph=y+ym;
		//cout << "ytop: " << ytop << "  ytoph:" << ytoph << "\n";
		if(ytoph<yzero) ytoph=  -2;
		if(ytoph>ytop) ytoph= -4;
		return ytoph;
	}
void ValScreen::buf_draw_boarder(int width){
	buf_drawline(0,0,r.Height-1,false,width);
	buf_drawline(0,0,r.Width-1,true,width);
	
	buf_drawline(r.Width-1,r.Height-1,r.Height-1,false,width);
	buf_drawline(r.Width-1,r.Height-1,r.Width-1,true,width);
}
	
	

void ValScreen::buf_drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width){
	buf_drawlinefrom_slope(x,y,xx,yy,width);
	buf_drawlinefrom_slope(x,y,xxx,yyy,width);
	buf_drawlinefrom_slope(xxx,yyy,xx,yy,width);
		
}
void ValScreen::buf_draw_circle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width){		
	width /=3;
	bool flag=false;
	int xcp=0, ycp=0, xcm=0, ycm=0, rtest= radius- (sqrt(radius));
	float sway=.5;
	for(double i = 0; i <= radius; i+=sway){
		if(i==rtest)sway=.02;
		//if(i==radius-1)sway=.01;
		int y = circle_getyfromXR(i,radius,flag);
		if(!flag)continue;
		xcp = xcenter+i;
		ycp = ycenter+y;
		xcm = xcenter-i;
		ycm = ycenter-y;
		for(int w = width*-1; w < width; w++){
			// +/- plane
			buf_editpix(xcp+w,ycp,0);
			buf_editpix(xcp,ycp+w,0);
			
			// +/+ plane
			buf_editpix(xcp+w,ycm,0);
			buf_editpix(xcp,ycm+w,0);
			
			// -/- plane:
			buf_editpix(xcm+w,ycp,0);
			buf_editpix(xcm,ycp+w,0);
			
			// -/+ plane:
			buf_editpix(xcm+w,ycm,0);
			buf_editpix(xcm,ycm+w,0);
		}
	}
}
	
void ValScreen::buf_drawcircle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width){		
	width /=3;
	bool flag=false;
	for(int i = radius*-1; i < radius; i++){
		int y = circle_getyfromXR(i,radius,flag);
		if(!flag)continue;
		buf_editpix(xcenter+i,ycenter+y,0);
		buf_editpix(xcenter+i,ycenter+y*-1,0);
		for(int w = 0; w < width; w++){
			buf_editpix(xcenter+i+w,ycenter+y,0);
			buf_editpix(xcenter+i+w,ycenter+y*-1,0);
			buf_editpix(xcenter+i,ycenter+y+w,0);
			buf_editpix(xcenter+i,(ycenter+y*-1)+w,0);
			
			buf_editpix(xcenter+i-w,ycenter+y,0);
			buf_editpix(xcenter+i-w,ycenter+y*-1,0);
			buf_editpix(xcenter+i,ycenter+y-w,0);
			buf_editpix(xcenter+i,(ycenter+y*-1)-w,0);

		}
			
	}
	for(double i = 0; i < 40; i++){
		int y = circle_getyfromXR(radius-(i/20),radius,flag);
		if(!flag)continue;
		buf_editpix(1+(xcenter-radius)+(i/20),ycenter+y,0);
		buf_editpix(1+(xcenter-radius)+(i/20),ycenter-y,0);
		//buf_editpix(((xcenter-radius)+(i/20))-1,ycenter-y,0);
		buf_editpix((xcenter+radius)-(i/20)-1,ycenter+y,0);
		buf_editpix((xcenter+radius)-(i/20)-1,ycenter-y,0);
		//buf_editpix(((xcenter+radius)-(i/20))-1,ycenter-y,0);
				
		buf_editpix((xcenter-radius)+(i/20),ycenter+y,0);
		buf_editpix((xcenter-radius)+(i/20),ycenter-y,0);
		buf_editpix((xcenter-radius)+(i/20),ycenter-(y*-1),0);
		buf_editpix((xcenter-radius)+(i/20),ycenter+(y*-1),0);
		
		buf_editpix((xcenter+radius)-(i/20),ycenter+y,0);
		buf_editpix((xcenter+radius)-(i/20),ycenter-y,0);
		buf_editpix((xcenter+radius)-(i/20),ycenter-(y*-1),0);
		buf_editpix((xcenter+radius)-(i/20),ycenter+(y*-1),0);
		
		/*y = circle_getyfromXR(radius+(i/30),radius,flag);
		if(!flag)continue;
		buf_editpix(xcenter+radius,ycenter+y,0);
		buf_editpix(xcenter+radius,ycenter-y,0);
		buf_editpix(xcenter+radius,(ycenter-y)*-1,0);
		buf_editpix(xcenter+radius,(ycenter+y)*-1,0);
		*/
	}
		
}


void ValScreen::console_draw(){
	BitBlt(condc,100,100,r.Width,r.Height,hdc,0,0,SRCCOPY);	
	
}
void ValScreen::bufwin_draw(int x,int y){
	bufhdc=CreateCompatibleDC(condc);
	SelectObject(bufhdc,newbitmap);
	BitBlt(condc,x,y,r.Width,r.Height,bufhdc,0,0,SRCCOPY);	
    

	SelectObject(bufhdc, Selectdump);
	ReleaseDC(NULL,bufhdc);
	DeleteDC(bufhdc);
	
}
void ValScreen::bufwin_draw(){
	bufhdc=CreateCompatibleDC(condc);
	SelectObject(bufhdc,newbitmap);
	BitBlt(condc,5,5,r.Width,r.Height,bufhdc,0,0,SRCCOPY);	
    
	SelectObject(bufhdc, Selectdump);
	ReleaseDC(NULL,bufhdc);
	DeleteDC(bufhdc);
	
}
void ValScreen::bufconsole_draw(){
	bufhdc=CreateCompatibleDC(condc);
	SelectObject(bufhdc,newbitmap);
	BitBlt(condc,100,50,r.Width,r.Height,bufhdc,0,0,SRCCOPY);	
    

	SelectObject(bufhdc, Selectdump);
	ReleaseDC(NULL,bufhdc);
	DeleteDC(bufhdc);
	
}
void ValScreen::bufconsole_draw(int w, int h){
	bufhdc=CreateCompatibleDC(condc);
	SelectObject(bufhdc,newbitmap);
	BitBlt(condc,100,50,w,h,bufhdc,0,0,SRCCOPY);	
    

	SelectObject(bufhdc, Selectdump);
	ReleaseDC(NULL,bufhdc);
	DeleteDC(bufhdc);
	
}


void ValScreen::buf_drawtext(int x, int y, int w, int h, string text ) { // working
	bufhdc = CreateCompatibleDC(condc);
	SelectObject(bufhdc, newbitmap);
//	RECT a;
//	RECTb(a, x, y, x+w,y+h);
	//BeginPath(bufhdc);
	//DrawTextA(bufhdc, text, text.length(), &a, DT_EDITCONTROL);
	TextOutA(bufhdc, x, y, text.c_str(), text.length());
	//EndPath(bufhdc);
	SelectObject(bufhdc, Selectdump);
	ReleaseDC(NULL, bufhdc);
	DeleteDC(bufhdc);

}
void ValScreen::outinfo(){
		BITMAP wrbmp;
	if (!GetObject(this->bmp, sizeof(BITMAP), (LPSTR)&wrbmp)) {
		//LOG("[ERROR] could not retrieve bitmap info");
		return;
	}

	cout << "bmp.bmWidth: " << wrbmp.bmWidth  <<endl;
	cout << "bmp.bmHeight: " << wrbmp.bmHeight<<endl;
	SHOW(r.Width);
	SHOW(r.Height);
	
}

COLORREF ValScreen::Get_Pixel(int x, int y){
	//if(IS_BUFFER) buf_editpix(x,y,0);
	//if(IS_BUFFER) buf_drawbox(x,y,3,3);
	if(DO_EDIT_GETPIX)buf_editpix(x, y, 0);
	return GetPixel(hdc,x,y);
	//  set flag to auto-edit checked pixels in buf if IS_BUF 
	
}
int ValScreen::buf_Get_Pixel(int x, int y) {

	

	char* hold = bits;
	hold+= (((y * r.Width) + x) * 4);
	char a, b, c;
	a = *hold; hold++;
	b = *hold; hold++;
	c = *hold; hold++;
	return (int)RGB(c, b, a);

	int ret = *hold;
	hold++;
	ret += (((int)(*hold)) << 8);
	hold++;
	ret += (((int)(*hold)) << 16);
	return ret;

}
ValScreen::~ValScreen(){
	DeleteObject(bmp);
	ReleaseDC(NULL,hdc);
	ReleaseDC(NULL,m_HDC);
	IS_BUFFER=false;
	buf_width=0;  buf_height=0;
	DO_EDIT_GETPIX = true;
}
void ValScreen::start_vars(){	
    m_HDC = GetDC(GetDesktopWindow());
    hdc=CreateCompatibleDC(m_HDC);
	bmp = CreateCompatibleBitmap(m_HDC, r.Width,r.Height);
	condc = GetDC(GetConsoleHwnd());
	buffer_size = r.Width*r.Height*4;
	DO_EDIT_GETPIX = true;
}

ValScreen::ValScreen(int x, int y, int w, int h){
	r.X=x;
	r.Y=y;
	
    r.Width=w ;
    r.Height=h;
	copybuf = NULL;
    start_vars();
	
}
ValScreen::ValScreen(val_rect rect){
	r=rect;
	start_vars();
}
ValScreen::ValScreen(){
	r.X=0;
	r.Y=0;
	
    r.Width=GetSystemMetrics(SM_CXSCREEN);
    r.Height=GetSystemMetrics(SM_CYSCREEN);
	start_vars();	
	
}
void ValScreen::Set(int x, int y, int w, int h){
	r.X=x;
	r.Y=y;
	
    r.Width=w ;
    r.Height=h;
    reset_bounds();
}
void ValScreen::reset_bounds(){
		DeleteDC(hdc);
		DeleteObject(bmp);
    	hdc=NULL; bmp=NULL;
    	buffer_size = r.Width*r.Height*4;
    	
}
void ValScreen::SetX(int x){
	if(r.X != x){
		r.X= x; 
		reset_bounds();
	}
}
void ValScreen::SetY(int y){
	if(r.Y != y){
		r.Y = y;
		reset_bounds();
	}	
}
void ValScreen::SetWidth(int w){
	if(r.Width != w){
		r.Width = w;
		reset_bounds();
	}
	
}
void ValScreen::SetHeight(int h){
	if(r.Height != h){
		r.Height = h;
		reset_bounds();
	}
	
}
void ValScreen::SetRECT(val_rect rect){
	reset_bounds();
	r = rect;
}

void ValScreen::buf_load_file_bmp(string fname){
	HBITMAP hBMP = (HBITMAP) LoadImage( NULL, (LPCWSTR)fname.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	int w, h;
	get_buffer(hBMP,w,h);    
	SetWidth(w); 
	SetHeight(h); 		
	
}
void ValScreen::get_buffer(HBITMAP &hbmp, int &w, int &h){
	BITMAP wrbmp;
	if (!GetObject(hbmp, sizeof(BITMAP), (LPSTR)&wrbmp)) {
		//LOG("[ERROR] could not retrieve bitmap info");
		cout << "getObject failed"<<endl;
		return;
	}	
	DeleteDC(hdcg);
	hdcg =GetDC(GetDesktopWindow());
	BITMAPINFO mybmi;
	mybmi.bmiHeader.biSize = sizeof(mybmi);
        mybmi.bmiHeader.biWidth = wrbmp.bmWidth;
        mybmi.bmiHeader.biHeight =  wrbmp.bmHeight*-1;
        w=wrbmp.bmWidth;
        buf_width=w;
        h=wrbmp.bmHeight;
        buf_height=h;
        //cout <<"get_buffer(hbitmap) width: "<<wrbmp.bmWidth<<endl;
        //cout <<"get_buffer(hbitmap) height: "<<wrbmp.bmHeight<<endl;
        mybmi.bmiHeader.biPlanes = 1;
        mybmi.bmiHeader.biBitCount = 32;
        mybmi.bmiHeader.biCompression = BI_RGB;
        mybmi.bmiHeader.biSizeImage = (wrbmp.bmWidth * (mybmi.bmiHeader.biBitCount / 8) + 3) * wrbmp.bmHeight;	//& -4)  ??  this was in example
    //    SelectObject(hdcg,hbmp);
    if(IS_BUFFER) DeleteObject(newbitmap);
	newbitmap =CreateDIBSection(hdcg, &mybmi, DIB_RGB_COLORS,(VOID **)&bits, 0, 0);
	if(!newbitmap)  {cout <<"CreateDIBSection"<<endl;  return ;}
	int result = GetDIBits(hdcg, hbmp, 0, (wrbmp.bmHeight), bits, (BITMAPINFO *)&mybmi, DIB_RGB_COLORS);
	if (!result)  {cout <<"getDiBits"<<endl;  return;}
	IS_BUFFER = true;
	
}


void ValScreen::get_buffer(){	

	if(!bmp)get_screen();
	if(!bmp){
		cout << "valscreen::get_buffer failed, cannot get screen data"<<endl;
		return;
	}
	BITMAPINFO mybmi;
	mybmi.bmiHeader.biSize = sizeof(mybmi);
        mybmi.bmiHeader.biWidth =r.Width ;
        buf_width=r.Width;
        mybmi.bmiHeader.biHeight = r.Height*-1;
        buf_height=r.Height;
        mybmi.bmiHeader.biPlanes = 1;
        mybmi.bmiHeader.biBitCount = 32;
        mybmi.bmiHeader.biCompression = BI_RGB;
        mybmi.bmiHeader.biSizeImage = (r.Width * (mybmi.bmiHeader.biBitCount / 8) + 3) * r.Height;	//& -4)  ??  this was in example
    if(IS_BUFFER){
		DeleteObject(newbitmap);
		
      //delete[] bits;  //**************************
	  
	}
	DeleteObject(newbitmap);
	newbitmap =CreateDIBSection(hdc, &mybmi, DIB_RGB_COLORS,(VOID **)&bits, NULL, 0);
	if(!newbitmap)  {cout <<"CreateDIBSection"<<endl;  return ;}
	int result = GetDIBits(hdc, bmp, 0, (r.Height*-1), bits, (BITMAPINFO *)&mybmi, DIB_RGB_COLORS);
	if (!result)  {cout <<"getDiBits"<<endl;  return;}
	IS_BUFFER=true;
	//After createdibsection bits holds direct access to bitmap in hdc.
}
void ValScreen::white_buffer(int alpha=0){
	BYTE* bytes = (BYTE*)bits;
	int plc=0;
	for(int n = 0; n < buf_height; n++){
		for(int i =0; i<buf_width; i++){
			*bytes = 255;bytes++;
			
			*bytes =255;bytes++;
			*bytes = 255;bytes++;
			*bytes = alpha;bytes++;
//			bits[plc]=255;
//			bits[plc+1]=255;
//			bits[plc+2]=255;
//			bits[plc+3]=alpha;
//			plc+=4;
		}
	}
	//cout << "white_buffer overwrote: "<<plc<<endl;
	//cout << "buf dims: "<< buf_height << ":"<<buf_width<<endl;

}
void ValScreen::black_buffer(int alpha = 0) {
	BYTE* bytes = (BYTE*)bits;
	int plc = 0;
	for (int n = 0; n < buf_height; n++) {
		for (int i = 0; i < buf_width; i++) {
			*bytes = 0; bytes++;

			*bytes = 0; bytes++;
			*bytes = 0; bytes++;
			*bytes = alpha; bytes++;
			//			bits[plc]=255;
			//			bits[plc+1]=255;
			//			bits[plc+2]=255;
			//			bits[plc+3]=alpha;
			//			plc+=4;
		}
	}
	//cout << "white_buffer overwrote: "<<plc<<endl;
	//cout << "buf dims: "<< buf_height << ":"<<buf_width<<endl;

}
void ValScreen::white_buffer_sect(int x, int y, int w, int h, int alpha = 0) {
	char* bytes = bits;
	bytes += ((y * buf_width) + x) * 4;
		int nlen = y + h, ilen = x + w;
	for (int n = y; n < nlen && n < buf_height; n++) {
		for (int i = x; i < ilen && i < buf_width; i++) {
			*bytes = 255; bytes++;
			*bytes = 255; bytes++;
			*bytes = 255; bytes++;
			*bytes = alpha; bytes++;
		}
		bytes += (buf_width - w) * 4;
	}
}
	
void ValScreen::buf_drawbox(int x, int y, int w, int h){
	if(!IS_BUFFER)get_buffer();
	int plc=0;
	for(int i = x; i < x+w && i < r.Width; i++){
			for(int n = y; n < y+h && n <r.Height  ; n++){
				plc =(((n * r.Width )+i)* 4);
				bits[ plc ] = 0x00;
				bits[ plc + 1 ] = 0X01;//0xFF;
				bits[ plc + 2 ] = 0XFF;//;0xFF;
			}
		}
}
void ValScreen::buf_drawbox2(int x, int y, int w, int h, char re, char gr, char bl){
	if(!IS_BUFFER)get_buffer();
	int plc=0;
	for(int i = x; i < x+w && i < r.Width; i++){
			for(int n = y; n < y+h && n <r.Height  ; n++){
				plc =(((n * r.Width )+i)* 4);
				bits[ plc ] = bl;
				bits[ plc + 1 ] = gr;//0xFF;
				bits[ plc + 2 ] = re;//;0xFF;
			}
		}
}
// draw a straight,cardinal line on buffer starting at x,y, going to xy (x if horizontal, y if not), width pixels thick
// width must be odd.
void ValScreen::buf_drawline(int x, int y, int xy,bool horizontal, int width){
	if (xy < 0) {
		if (horizontal)x += xy;
		else y += xy;
		xy = abs(xy);
	}
	if(width%2==0) width-=1;
	int wide = width/2;
	if(!IS_BUFFER)get_buffer();
	int plc=0,plc2=0,plc3=0;
	int w = (horizontal?x+xy:x);
	int h = (!horizontal?y+xy:y);
	int reset = 0,bsize=r.Width*r.Height*4;
	for(int i = x; i <= w && i < r.Width; i++){
			for(int n = y; n <= h && n <r.Height  ; n++){
				plc =(((n * r.Width )+i)* 4);
				bits[ plc ] = 0x00;
				bits[ plc + 1 ] = 0X01;//0xFF;
				bits[ plc + 2 ] = 0XFF;//;0xFF;
				reset++;
				for(int b = 1; b <= wide; b++){
					if(!horizontal){
						plc2=plc+(4*b);
						plc3= plc-(4*b);
					}
					else{
					    plc2= plc+(r.Width*4*b);
						plc3= plc-(r.Width*4*b);
					}
					if (plc2 > bsize || plc2<0)continue;
					bits[ plc2 ] = 0x00;
					bits[ plc2 + 1 ] = 0X01;//0xFF;
					bits[ plc2 + 2 ] = 0XFF;
					if (plc3 > bsize || plc3 < 0)continue;
					bits[ plc3 ] = 0x00;
					bits[ plc3 + 1 ] = 0X01;//0xFF;
					bits[ plc3 + 2 ] = 0XFF;
					reset+=2;
				}
				
					 
			}
		}
		//SHOW(reset);
		
}
int ValScreen::buf_xyindex(int x, int y){
	return (((y*r.Width)+x)*4);
}
int ValScreen::buf_editpix(int x, int y, int plc=0){
	//if(x < 0 || y < 0 || x>r.Width || y > r.Height) return 0;
	
	if(plc==0) plc = (((y*r.Width)+x)*4);
	if(plc<0 || plc>buffer_size || x>r.Width)return 0;  
	bits[plc] = 0x00;
	bits[plc+1] = 0x00;
	bits[plc+2] = 0xFF;
	return plc;
}
int ValScreen::buf_editrgb(int x, int y,BYTE re, BYTE gr, BYTE bl, int plc=0){
	//if(x < 0 || y < 0 || x>r.Width || y > r.Height) return 0;
	
	if(plc==0) plc = (((y*r.Width)+x)*4);
	if(plc<0 || plc>buffer_size || x>r.Width)return 0;  
	bits[plc] = bl;
	bits[plc+1] = gr;
	bits[plc+2] = re;
	return plc;
}
/*
// creates 'sprite' section file for loading 
void DIB_save_section((string fname,int x, int y, int xx, int yy)

//int ValScreen::buf_save_section_mask(string fname,int x, int y, int xx, int yy){     //   , COLREF mask){
	
	ofstream ofile(ctocp(fname,ios::out | ios::binary));
	ofile << r.Width << r.Height;
	if(!IS_BUFF) get_buffer();
	int ind = buf_xyindex(x,y);
	int indi= ind;
	int w = xx-x;
	//int h = yy-y;
	
	for(;y<yy;y++){
		//for(;x<xx;x++){
			//if(colcomp(get_cref(x,y),mask)) ofile<<
			//ofile << bits[ind]<<bits[ind+1]<<bits[ind+2];
			//ind+=4;
			ofile.write(bits+ind,(xx-x)*4);
		//}
		ind+=w;
		//ind=indi;
	}
		
	ofile.close();
}
void ValScreen::get_sprite_buf(x,y){
// make vars and createdibsection into spritebuf;

}
int ValScreen::load_section_mask(string fname,COLREF mask){
	ifstream ifile(ctocp(fname,ios::out | ios::binary));
	
	ifile >> spritew>>spriteh;
	if(!SPRITE_BUFF)get_sprite_buf(spritew,spriteh);
	ifile.read(spritebuf,spritew*spriteh*4);
	ifile.close();
}
	
		
void ValScreen::sprite_tblt(int x,int y, int xx=0, int yy=0){
	TransparentBlt(hdc,x,y,spritew,spriteh,spritehdc,xx,yy,spritew,spriteh,RGB(0,0,0));

}
COLORREF ValScreen::Get_Pixel2(int x, int y){
	if(IS_BUFF) buf_editpix(x,y);
	return GetPixel(hdc,x,y);
	//  set flag to auto-edit checked pixels in buf if IS_BUF 
	
}
	*/

void ValScreen::draw_curve2(int a, int b, int c, int d, int xzero, int xtop, int yzero, int ytop,bool invert=true){
	int y;
	for(int x=xzero; x<xtop; x++){
		y = get_y_from_parabola(a,b,c,d,x,yzero,ytop,invert);
		if(y==-1)continue;
		buf_editpix(x-xzero,y);
	}
}
void ValScreen::draw_curve(int a, int b, int c, int d, int xzero, int xtop, int yzero, int ytop,bool invert=true){
	
	int y=0,ym,ly=0,ytoph;
	
	for(int x=xzero; x<xtop; x++){
		//for(int y=yzero; y<ytop; y++){
		y= a*x;
		y=y*y;
		y+= b*x;
		
		y/=d;
		y+=c;
		
		
		if(y<yzero) continue;
		if(y>ytop) continue;
		
		if(ly!=0) ym = (y-ly);
		else ym=1;
		if(ym<0) ym*=-1;
		ym+=2;
		for(int i = 0; i < ym; i++){
			if(invert)ytoph=ytop-(y+i);
			else ytoph=y+i;
			buf_editpix(x-xzero,ytoph);
			buf_editpix(1+ x - xzero, ytoph);
			buf_editpix(x - xzero, ytoph+1);
		}
		ly=y;
	}
}

// finally a successful, reasonably fast, reasonably readable diagonal line section that accurately draws the line

void ValScreen::buf__drawslopex(int x, int y, int ydir, double a, int itt){ // ydir can be -1|1 
	double vl=0, len=0,vll=0;
	int nx;
	for(int i = 0; i <= itt; i++){
	len = abs(vl)-abs(vll);
		for(int n = 0; n < len; n++){
			nx=n;
			if(a < 0)nx*=-1; 
			buf_editpix(floor(vll)+x+nx, y);
		}
		y+=ydir;
		vll=vl;
		vl+=a;
	}
}
void ValScreen::buf__drawslopey(int x, int y, int xdir, double a, int itt){ // ydir can be -1|1 	 	
	double vl=0, len=0,vll=0;
	int nx;
	for(int i = 0; i <= itt; i++){
	len = abs(vl)-abs(vll);
		for(int n = 0; n < len; n++){
			nx=n;
			if(a < 0)nx*=-1;
			buf_editpix(x, floor(vll)+y+nx);
		}
		x+=xdir;
		vll=vl;
		vl+=a;
	}
}
void ValScreen::buf_drawlinefrom_slope(int x, int y, int xx, int yy, int width){
	//cout << "drawing slope for x,y,xx,yy: " << x<<":"<< y<<":"<< xx<<":"<< yy<<endl;
	int wide = width/2;
	if (x == xx) {
		buf_drawline(x, y, yy - y, false, wide);
		return;
	}
	if (y == yy) {
		buf_drawline(x, y, xx - x, true, wide);
		return;
	}
	long double xxx =abs(xx-x);
	long double yyy = (yy-y)/xxx;  // yslope (y per x)
	if(abs(yyy)>=1){
		//cout << "drawing slopey " <<xxx << ":"<<yyy<<endl;
		buf__drawslopey(x,y,(xx-x>-1?1:-1),yyy,xxx);
		for(int i = 0; i<wide;i++){
			buf__drawslopey(x+i,y,(xx-x>-1?1:-1),yyy,xxx);
			buf__drawslopey(x-i,y,(xx-x>-1?1:-1),yyy,xxx);
		}
		return;
	}else{
		yyy = abs(yy-y);
		xxx= (xx-x)/yyy;
		//cout << "drawing slopex " <<xxx << ":"<<yyy<<endl;
		buf__drawslopex(x,y,(yy-y>-1?1:-1),xxx,yyy);
		for(int i = 0; i<wide;i++){
			buf__drawslopex(x,y+i,(yy-y>-1?1:-1),xxx,yyy);
			buf__drawslopex(x,y-i,(yy-y>-1?1:-1),xxx,yyy);
		}
	}
}
	 
	
	
// heavily depreciated.  attempt at int math only diagonal line
void ValScreen::buf_drawlinefrom2(int x, int y, int xx, int yy, int width){
	if(width%2==0) width-=1;
	int wide = width/2, itt;;
	long double yslope;
	long double xslope;
	long double xxx = xx-x;
	long double yyy = yy-y;
	bool stype = 0;
	if(xxx==0 ){
		if(yyy<0)buf_drawline(x, y+yyy ,abs(yyy),true,width);
		else buf_drawline(x,y,yyy,true,width);
	}
	if(yyy==0 ){
		if(xxx<0)buf_drawline(x+xxx, y ,abs(xxx),false,width);
		else buf_drawline(x,y,xxx,false,width);
	}
	if(yyy>xxx){
		yslope=1* (yyy>-1?1:-1);;
		xslope= yyy/xxx;
		xslope=abs(xslope)* (xxx>-1?1:-1);
		itt = yyy;
		stype=1;
	}else if (xxx>yyy){
		xslope = 1 * (xxx>-1?1:-1);;
		yslope = xxx/yyy;
		yslope=abs(yslope)* (yyy>-1?1:-1);
		itt = xxx;
		
	}else{ // xxx==yyy
		yslope=1 * (yyy>-1?1:-1);
		xslope=1* (xxx>-1?1:-1);
		itt=xxx;
	}
	bool hoz = abs(yslope)==1;
	
	long double xxxx=0, yyyy=0;
	int xlast = 0;
	int ylast = 0;
	int xlen, ylen;
	int xinc, yinc;
	for(int	 i = 0; i < itt; i++){
		xlen = abs(floor(xxxx))-abs(xlast);
		ylen =abs(floor(yyyy))-abs(ylast);
		
		for(int ix = 0; ix<xlen; ix++){
			xinc = ix* (xxx>-1?1:-1);
			
			for(int iy = 0; iy<ylen; iy++){
				yinc = iy*(yyy>-1?1:-1);
				//editpix(xlast+xinc,ylast+yinc);
				if(hoz)buf_drawline(xlast+xinc-wide,ylast+yinc,width,hoz,1);
				else buf_drawline(xlast+xinc,ylast+yinc-wide,width,hoz,1);
			}
			
		}
		ylast+= ylen*(yyy>-1?1:-1);
		xlast += xlen*(xxx>-1?1:-1);;
		xxxx+=xxx;
		yyyy+=yyy;
		
	}
}
	/*
	
	
	if(stype){ // step= y*1
		for(int	 i = 0; i < itt; i++){
			xitt = Floor((xxxx+xslope)-xlast);
			for(int	 ix = 0; ix < xitt; ix++){
				editpix(xlast,ylast);
				xlast++;
			}
			ylast++;
		}
	}
	else{
		for(int	 i = 0; i < itt; i++){
			xitt = Floor((yyyy+yyy)-ylast);
			for(int	 ix = 0; ix < xitt; ix++){
				editpix(xlast,ylast);
				xlast++;
			}
			ylast++
		}
	}
			xnext = 
	int len
	for(int	 i = (stype?y:x); i < itt; i++){
		len = 


*/
// void ValScreen::buf_drawlinefromx
// void ValScreen::buf_drawlinefromy
// void ValScreen::buf_draw_45
//void ValScreen::buf_drawlinefrom2(int x, int y, int xx, int yy, int width)

// void ValScreen::buf_drawlinefromx(int x, int y, int xx, int yy, int width)
// void ValScreen::buf_drawlinefromy(int x, int y, int xx, int yy, int width)
// void ValScreen::buf_draw_45
//void ValScreen::buf_drawlinefrom2(int x, int y, int xx, int yy, int width){
//	long double xxx = xx-x;
//	long double yyy = yy-y;
// if(xxx>yyy) buf_drawlinefromx
// else if( yyy>xxx) buf_drawlinefromy
// else if yyy==xxx) buf_draw_45
   
//	long double yslope = yyy/xxx; 
//	long double xslope = yslope/yyy;
	
//	for( int ix = 0; ix < xslope;ix++){
//   	for( int iy = 0; iy < yslope;iy++){
//			buf_editpix(xplc+ix,yplc+iy);
//		}
		
//		
// 
	
// attempts to draw diagonal line 
// depreciated.  attempts to use only integers... Dunno what I was thinking that day.. obviously not about math.

void ValScreen::buf_drawlinefrom(int x, int y, int xx, int yy, int width){
	bool wxy;
	int h = 0;
	int wide = (width-1)/2; // set Wide for later use
	// set direction vars
	int xdir =1, ydir=1;
	if(xx<x) xdir = -1;
	if(yy<y) ydir = -1;
	wxy = (xdir == ydir) ; // set form value for width
	
	// distances to travel in x,y
	int xxx = (xx>x?xx-x:x-xx);
	int yyy = (yy>y?yy-y:y-yy);
	//SHOW(xxx);
	//SHOW(yyy);
	// default to straight cardinal line if possible
	if(xxx==0){
		buf_drawline(x,y,yy,0,width);
		return;
	}
	if(yyy==0){
		buf_drawline(x,y,xx,1,width);
		return;
	}
	///  if larger number is more than 2x smaller number, larger/=2 largerdir*=2 (or larger/smaller instead of 2)
	// check if diagonal perturbations exist and set their interval (?mod)(mo) and variable Direction determiner(?horizontal)( ho)
	int xsiz=1,ysiz=1,yex=1,xex=1,tmp;
	bool ho= (xxx<yyy);  // horizontal/vertical determiner
	if(ho && xxx !=0){  // ratio control section
		tmp=yyy/xxx;    // step ratio must not be more than 2:1 or mod steps will have to happen more than
		if(tmp >1){     // once per full step
			
		   ysiz*= tmp;
		   yex = yyy%(tmp);
		   yyy/= (tmp);
		}
	}else if(yyy!=0){
		tmp = xxx/yyy;
		if(tmp >1){
			
		   xsiz*= tmp;
		   yex = xxx%(tmp); 
		   xxx/= (tmp);
		}
	}
	int bo;
	if(ho) bo=yyy-xxx;
	else bo=xxx-yyy;
	
	//if(yex>1)yex++;
	bo+=yex;
	
	int bg = (ho? yyy:xxx);
	float mo,mobase;
	if(bo!=0){
		mo= (float)bg/(float)bo;
	}
	else mo=bg+1;
	mobase=mo;
	int imo = mo;
	if(wide==0)wide=1;
	//wide*= xsiz*ysiz;
	//wide++;
	
	int place = 0, add=0, ad=0,xa=0,ya=0;
	int tmpt =((xsiz*ysiz)/2);
	if(tmpt>wide*2) wide=wide*2; //  changed here
	else if(tmpt>wide)wide=tmpt;
	
	while ((x!=xx || y!=yy) && place < 1000){
		place++;
		
		for ( int p = wide*-1; p < wide; p++){ // make wide section of line segment  
			ad = p - (p/2);
			add = p/2;

			//if(xsiz>1 || ysiz>1){
			for(int sizj = tmpt*-1; sizj <= tmpt; sizj++){ 
				if(xsiz>1) xa=sizj;
				if(ysiz>1) ya=sizj;
				if(wxy)buf_editpix(x+ad+xa,y+(add)+ya);           
				else buf_editpix(x+(add)+xa,y+ad+ya);
			}
		} 
		if(place == imo){// do mod jumps
			mo+=mobase;
			imo=mo;
			if(!ho) x+=xdir*xsiz;
			else y+=ydir*xsiz;
			continue;
		}

		if(x<xx){ // increment 
			x+=xsiz;
			if(x>xx)x=xx;	
		}else if(x>xx){
		   x-=xsiz;
		   if(x<xx)x=xx;
		} 
		
		
		if(y<yy){
		    y+=ysiz;
		    if(y>yy)y=yy;  
		}else if(y>yy){
		 	y-=ysiz;
		 	if(y<yy)y=yy;
		}

	}
	
}		 
	
	

/*
		
// attempts to draw diagonal line 
void ValScreen::buf_drawlinefrom(int x, int y, int xx, int yy, int width){
	bool wxy;
	int h = 0;
	int wide = (width-1)/2; // set Wide for later use
	// set direction vars
	int xdir =1, ydir=1;
	if(xx<x) xdir = -1;
	if(yy<y) ydir = -1;
	wxy = (xdir == ydir) ; // set form value for width
	
	// distances to travel in x,y
	int xxx = (xx>x?xx-x:x-xx);
	int yyy = (yy>y?yy-y:y-yy);
	SHOW(xxx);
	SHOW(yyy);
	// default to straight cardinal line if possible
	if(xxx==0){
		buf_drawline(x,y,yy,0,width);
		return;
	}
	if(yyy==0){
		buf_drawline(x,y,xx,1,width);
		return;
	}
	///  if larger number is more than 2x smaller number, larger/=2 largerdir*=2 (or larger/smaller instead of 2)
	// check if diagonal perturbations exist and set their interval (?mod)(mo) and variable order determiner(?horizontal)( ho)
	int xsiz=1,ysiz=1,yex=1,xex=1;
	bool ho= (xxx<yyy);
	if(ho){
		if(yyy/xxx >1){
		   ysiz*= yyy/xxx;
		   yex = yyy%(yyy/xxx);
		   yyy/= (yyy/xxx);
		}
	}else{
		if(xxx/yyy >1){
		   xsiz*= xxx/yyy;
		   yex = xxx%(xxx/yyy); 
		   xxx/= (xxx/yyy);
		}
	}
	int bo;
	if(ho) bo=yyy-xxx;
	else bo=xxx-yyy;
	if(yex>1)yex++;
	bo+=yex;
	
	int bg = (ho? yyy:xxx), hh =0;
	float mo,mobase;
	if(bo!=0){
		//hh=mo%bo;
		mo= (float)bg/(float)bo;
	}
	else mo=bg+1;
	mobase=mo;
	int imo = mo;
	//mo++;
	//hh=bo-(bg/mo);
	//if(hh!=0)hh=bg/hh;
	//else hh = bg+1;
	SHOW(xxx);
	SHOW(yyy);
	SHOW(xsiz);
	SHOW(ysiz);
	SHOW(ho);
	SHOW(bo);
	SHOW(mo);
	SHOW(hh);
	SHOW(bg);
	// loop 
	if(wide==0)wide=1;
	wide*= xsiz*ysiz;
	
	int place = 0, add=0, ad=0,cdown=bo;
	bool cxy=0;
	while ((x!=xx || y!=yy) && place < 1000){
		place++;
		//cdown--;
	//	cout << place << "place    cdown:" << cdown<<"             \r";
		
		for ( int p = wide*-1; p < wide; p++){ // make wide section of line segment  
			ad = p - (p/2);
			add = p/2;
			
			if(wxy)buf_editpix(x+ad,y+(add));//*ydir))           
			else buf_editpix(x+(add),y+ad);              
		} 
		// bg--;
		//if(place%mo==0 || place%hh==0){
		//if(cdown==0){
		//	if(bo==0)cdown=bg+1000;
		//	else {
		//		cdown=((bg/bo));
		//		if(bg%bo>bo/2)cdown++;
		//    	bo--;
		//    }
		if(place == imo){
			mo+=mobase;
			imo=mo;
			if(!ho) x+=xdir*xsiz;
			else y+=ydir*xsiz;
			continue;
		}
		//if(place<bg){
			if(x<xx){
				x+=xsiz;
				if(x>xx)x=xx;	
			}else if(x>xx){
			   x-=xsiz;
			   if(x<xx)x=xx;
			} 
			if(y<yy){
			    y+=ysiz;
			    if(y>yy)y=yy;
			    
			}else if(y>yy){
			 	y-=ysiz;
			 	if(y<yy)y=yy;
			}
		//}
		/*else{
			if(x<xx)x++;
			else if(x>xx) x--;
			if(y<yy)y++;
			else if(y>yy) y--;
//	 		if(x!=xx)x+= xdir;
//			if(y!=yy)y+= ydir;
		}
	
	}
	
}		 
	
	


*/
int ValScreen::get_hwnd_screen(HWND hwnd,int x,int y,int w,int h){
	IS_BUFFER=false;
    HDC m_HDC = GetDC(hwnd);
    if(!hdc)hdc=CreateCompatibleDC(m_HDC);//(GetDC(GetDesktopWindow()));//

	//if(!bmp)bmp = CreateCompatibleBitmap(m_HDC, w,h);
	if(!bmp)bmp = CreateCompatibleBitmap(m_HDC, r.Width,r.Height);
	SelectObject(m_HDC,bmp);

    if (bmp) {
        HBITMAP old = (HBITMAP) SelectObject(hdc,bmp);
		//BitBlt(hdc, 0,0,w,h , m_HDC, x,y, SRCCOPY);
		//SetStretchBltMode(hdc,COLORONCOLOR);
		//SetStretchBltMode(m_HDC,COLORONCOLOR);
		StretchBlt(hdc,0,0,r.Width,r.Height,m_HDC,x,y,w,h,SRCCOPY);
		GetObject(hdc,sizeof(BITMAP), old);
		ReleaseDC(NULL, m_HDC);

//	    WriteBMPFile(bmp, "out.bmp", hdc);
		return 1;
       
    }
    else{ cout << "couldn't get memory" << endl;
        pause();
    }
    ReleaseDC(NULL, m_HDC);

    return -1;
	
}

int ValScreen::get_screen(){
	IS_BUFFER=false;

    HDC m_HDC = GetDC(GetDesktopWindow());
    if(!hdc)hdc=CreateCompatibleDC(m_HDC);

	if(!bmp)bmp = CreateCompatibleBitmap(m_HDC, r.Width,r.Height);
	SelectObject(m_HDC,bmp);

    if (bmp) {
        HBITMAP old = (HBITMAP) SelectObject(hdc,bmp);
		BitBlt(hdc, 0,0,r.Width, r.Height , m_HDC, r.X, r.Y, SRCCOPY);
		GetObject(hdc,sizeof(BITMAP), old);
		ReleaseDC(NULL, m_HDC);

//	    WriteBMPFile(bmp, "out.bmp", hdc);
		return 1;
       
    }
    else{ cout << "couldn't get memory" << endl;
        pause();
    }
    ReleaseDC(NULL, m_HDC);

    return -1;
}
	
#define LOG(a) cout << a << endl;
void ValScreen::write_file(string a){
	//LPTSTR b = (LPTSTR)a.c_str(); //= ctocp(a);
	write_file_std(ctolpwstr(a));
}

void ValScreen::write_file_std(LPTSTR filename) {
	//HBITMAP bitmap = bmp;
	BITMAP wrbmp;
	PBITMAPINFO pbmi;
	WORD cClrBits;
	HANDLE hf; // file handle
	BITMAPFILEHEADER hdr; // bitmap file-header
	PBITMAPINFOHEADER pbih; // bitmap info-header
	LPBYTE lpBits; // memory pointer
	DWORD dwTotal; // total count of bytes
	DWORD cb; // incremental count of bytes
	BYTE *hp; // byte pointer
	DWORD dwTmp;
	if (!GetObject(this->bmp, sizeof(BITMAP), (LPSTR)&wrbmp)) {
		LOG("[ERROR] could not retrieve bitmap info");
		return;
	}
	cClrBits = (WORD)(wrbmp.bmPlanes * wrbmp.bmBitsPixel);

//	cout << "cClrBits: " << cClrBits <<endl;
//	cout << "bmPlanes: " << wrbmp.bmPlanes  <<endl;
//	cout << "bmPixel: " << wrbmp.bmBitsPixel<<endl;
//	cout << "bmp.bmWidth: " << wrbmp.bmWidth  <<endl;
//	cout << "bmp.bmHeight: " << wrbmp.bmBitsPixel<<endl;

	if (cClrBits >24) cClrBits=32 ;
	else if (cClrBits != 1) cClrBits = (4*((((cClrBits/4)%1) + 1)));

	if (cClrBits != 24)
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
						sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
	else
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));
		pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = wrbmp.bmWidth;
	pbmi->bmiHeader.biHeight = wrbmp.bmHeight;
	pbmi->bmiHeader.biPlanes = wrbmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = wrbmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1<<cClrBits);
		pbmi->bmiHeader.biCompression = BI_RGB;
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) /8 * pbmi->bmiHeader.biHeight * cClrBits;
	pbmi->bmiHeader.biClrImportant = 0;
	pbih = (PBITMAPINFOHEADER) pbmi;
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	if (!lpBits) {
		LOG("[ERROR] could not allocate memory");
		return;
	}
	if (!GetDIBits(hdc, HBITMAP(this->bmp), 0, (WORD) pbih->biHeight, lpBits, pbmi, DIB_RGB_COLORS)) {
		LOG("GetDIB error");
		return;
	}
	hf = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, (DWORD) 0,
	NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
	(HANDLE) NULL);
	if (hf == INVALID_HANDLE_VALUE){
		LOG("[ERROR]could not create file for writing");
		return;
	}
	hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M"
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed  * sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD);

	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp, NULL)) {
		LOG("[ERROR]could not write headers to file");
		LOG(filename);
		return;
	}
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
	+ pbih->biClrUsed * sizeof (RGBQUAD),
	(LPDWORD) &dwTmp, ( NULL))){
		LOG("[ERROR]could not write info to file");
		return;
	}
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)){
		LOG("[ERROR]could not write data bits to file");
		return;
	}
	if (!CloseHandle(hf)){
		LOG("could not close file");
		return;
	}
	GlobalFree((HGLOBAL)lpBits);
}
#undef RECT
HWND ValScreen::find_Window(string title,int &x, int &y, int &w, int &h){
    // MINErect=new RECT;
	if (!WindowRect)WindowRect = new RECT;
    
    enum_HWND = NULL;
    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
	{   

	    if (!IsWindowVisible(hwnd))
	        continue;
	
	    int length = GetWindowTextLength(hwnd);
	    if (length == 0)
	        continue;
	
	    //char* title2 = new char[length+1];
		LPWSTR title2= new WCHAR[length+1];
	    GetWindowText(hwnd, title2, length+1);
		wcout << L"found window title: " << title2<<endl;
	    //if (title2 == title){
		if(wcscmp(title2,ctolpwstr(title))==0){
    		GetWindowRect(enum_HWND, WindowRect);
    		x = WindowRect->left;
			y = WindowRect->top;
			w = WindowRect->right - x;
			h = WindowRect->bottom - y;
 			enum_HWND=hwnd;
			delete[] title2;
			return hwnd;
		}
		delete[] title2;

	}	
	return NULL;
}	
	

HWND ValScreen::create_drawing_console(int xx=820,int yy=50,int ww=800,int hh=500 ){
	int x,y,w,h;
	cout << "getting drawing window"<<endl;
    while(find_Window("drawing",x,y,w,h)==NULL){
		system("start drawing.exe");
		cout << "opening drawing.exe"<<endl;
		pause();
	}
	
	SetWindowPos(enum_HWND ,HWND_TOPMOST,xx,yy,ww,hh,SWP_SHOWWINDOW );
	
	condc= GetDC(enum_HWND);
	cout << "found and set drawing window\n";
	DRAW_HWND=enum_HWND;
	atexit(destroy_drawing);
	
	return enum_HWND;
	
}
LRESULT CALLBACK vsWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND ValScreen::create_transparent_window(int xx = 820, int yy = 50, int ww = 800, int hh = 500) {

	LPCWSTR windowName = LPCWSTR("w");
	HWND hWnd;
	WNDCLASS wnd = { };
	wnd.lpfnWndProc = vsWndProc;
	//wnd.hInstance = hInstance;
	wnd.hInstance = NULL;
	wnd.lpszClassName = windowName;

	//Register window class
	RegisterClass(&wnd);

	//Create window
	//! This returns NULL
	hWnd = CreateWindowEx(
		WS_EX_TRANSPARENT|WS_EX_LAYERED| WS_EX_TOOLWINDOW , //   |WS_EX_LAYERED
		windowName,
		LPCWSTR("drawing also"),
		0,//WS_EX_DLGMODALFRAME |WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_EX_APPWINDOW, //WS_OVERLAPPEDWINDOW,
		xx,
		yy,
		ww,
		hh,
		NULL,
		NULL,
		NULL,//hInstance,
		NULL
	);
	if (hWnd == NULL) {
		cout << "createwindowex failed e=" << GetLastError() << endl;
		pause();
		return NULL;
	}
	SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 255, LWA_COLORKEY);
	SetWindowLong(hWnd, GWL_STYLE, 0);
	//ShowWindow(hWnd, SW_SHOW);

	SetWindowPos(hWnd, HWND_TOPMOST, xx, yy, ww, hh, SWP_SHOWWINDOW);


	condc = GetDC(hWnd);
	enum_HWND = hWnd;

	//    Set(xx,yy,ww,hh);
	//    get_screen();
	//    get_buffer();
	//    white_buffer();
	//    bufwin_draw();
	//    
	return hWnd;
}
HWND ValScreen::create_transparent_window2(int xx=820,int yy=50,int ww=800,int hh=500 ){
	 
	LPCWSTR windowName = L"drawingalso"; 
	HWND hWnd;
    WNDCLASS wnd={ };
    wnd.lpfnWndProc = vsWndProc;
    //wnd.hInstance = hInstance;
    wnd.hInstance = NULL;
    wnd.lpszClassName = windowName;

    //Register window class
    RegisterClass(&wnd);

    //Create window
    //! This returns NULL
    hWnd = CreateWindow(
		//WS_EX_TRANSPARENT,//WS_EX_TRANSPARENT|WS_EX_LAYERED| WS_EX_TOOLWINDOW , //   |WS_EX_LAYERED
        windowName, 
       L"drawing also",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN,//WS_CAPTION|WS_POPUP,//WS_EX_DLGMODALFRAME |WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_EX_APPWINDOW, //WS_OVERLAPPEDWINDOW,
        xx,
        yy,
        ww,
        hh,
        NULL,
        NULL,
        NULL,//hInstance,
        NULL
        );
    if(hWnd == NULL) {
        cout << "createwindowex failed e=" <<GetLastError()<< endl;
        pause();
        return NULL;
    }
    //SetLayeredWindowAttributes(hWnd,RGB(255,255,255),255,LWA_COLORKEY);
    //SetWindowLong(hWnd, GWL_STYLE, 0 );    
    ShowWindow(hWnd, SW_SHOW);
	
    //SetWindowPos(hWnd ,HWND_TOPMOST,xx,yy,ww,hh,SWP_SHOWWINDOW );
    
   
    condc=GetDC(hWnd);
    enum_HWND=hWnd;
    
//    Set(xx,yy,ww,hh);
//    get_screen();
//    get_buffer();
//    white_buffer();
//    bufwin_draw();
//    
    return hWnd;
}

//WndProc function
#define GET_X_LPARAM(lp) ((int)(lp>>16))
#define GET_Y_LPARAM(lp) ((int)((lp<<16)>>16))
LRESULT CALLBACK vsWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//return 0;
    switch(msg) {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDc = BeginPaint(hWnd, &ps);

            //FillRect(hDc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

            EndPaint(hWnd, &ps);

            return 0;
        }
	case WM_LBUTTONDOWN:
	
		cout<<lParam<<":"<<GET_X_LPARAM(lParam) <<":"<< GET_Y_LPARAM(lParam)<<"    \r";
	
		return 0;
	break;
    case WM_DESTROY:
        {
            PostQuitMessage(0);
			exit(0);
            return 0;
        }
    }
	//return 0;
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
	
void destroy_drawing(){
	if(DRAW_HWND!=NULL)PostMessage(DRAW_HWND, WM_CLOSE, 0, 0);//DestroyWindow(DRAW_HWND);
 
}
//#define RECT RECT
	#endif
