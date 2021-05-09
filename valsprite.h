#ifndef ValSprite_def
#define ValSprite_def
#define LOG(a) 

void valspritewriteBMPfile(HBITMAP bitmap, LPTSTR filename, HDC hDC) {  // coppied from examples.  works out of the box and isnt slow.
//  the best image loader is the one you dont have to write.
	BITMAP bmp;
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
	if (!GetObject(bitmap, sizeof(BITMAP), (LPSTR)&bmp)) {
		LOG("[ERROR] could not retrieve bitmap info");
		return;
	}
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);

//	cout << "cClrBits: " << cClrBits <<endl;
//	cout << "bmPlanes: " << bmp.bmPlanes  <<endl;
//	cout << "bmPixel: " << bmp.bmBitsPixel<<endl;
//	cout << "bmp.bmWidth: " << bmp.bmWidth  <<endl;
//	cout << "bmp.bmHeight: " << bmp.bmBitsPixel<<endl;

	if (cClrBits >24) cClrBits=32 ;
	else if (cClrBits != 1) cClrBits = (4*((((cClrBits/4)%1) + 1)));

	if (cClrBits != 24)
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
						sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
	else
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));
		pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
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
	if (!GetDIBits(hDC, HBITMAP(bitmap), 0, (WORD) pbih->biHeight, lpBits, pbmi, DIB_RGB_COLORS)) {
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
		LOG("[ERROR]could not write in to file");
		LOG(filename);
		return;
	}
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
	+ pbih->biClrUsed * sizeof (RGBQUAD),
	(LPDWORD) &dwTmp, ( NULL))){
		LOG("[ERROR]could not write in to file");
		return;
	}
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)){
		LOG("[ERROR]could not write into file");
		return;
	}
	if (!CloseHandle(hf)){
		LOG("could not close file");
		return;
	}
	GlobalFree((HGLOBAL)lpBits);
}
// representation of a single sprite
class ValSprite_s {
public:
	BYTE* field;
	int width;
	int height;
};



class ValSprite{

	
	public:
	BYTE* sprite_field;
	POINT sprite_loc[500];
	POINT sprite_siz[500];
	int sprite_fieldx,sprite_fieldy,sprite_fieldwidth,sprite_fieldheight;
	
	int sprite_list_size;
	
	ValSprite();
	ValSprite(string filetitle);
	


	void load_spritefield(string fname,string infofname);
	void write_spritefield(BYTE*& tobuf, int x, int y, int width, int height); 
	void save_spritefield(string ftitle);

	int new_sprite(int x, int y, int w, int h);
	void write_sprite(BYTE* tobuf, int x, int y, int yheight, int spritenum);
	void get_sprite_var(int num, ValSprite_s& v);
	void get_sprite_var_forfield(ValSprite_s& v);
	void write_sprite_var(BYTE* tobuf, int x, int y, int buffwidth, ValSprite_s& v);
	
	int get_listsize() { return sprite_list_size; };

	bool is_in_sprite(int x, int y);
	void get_sprite_bounds(int num, int& tx, int& ty, int& tw, int& th);
	
	void findsprites();
	void fix_sprite_bounds(int num);
	/*  todo list:

	mouse_define_new_sprite_in_field();// MAYBE IN VALSCREEN 
	
	add a valsprite to valscreen as member //done
	test all functions through valscreen for easy screen buffer drawing.// done
	add sprite identifyer to valscreen // done
	add sprite drawing function // done

	add sprite shuffle system to move idenifyers
	add sequence system to group like sprites
	add sprite field re-draw system to redraw bitmap with sequence sprites in order 
	add binary info only spritefield import/export function just headers (sprite h/w data) and rgba info + sequence info
	
	*/
	HDC mHDC, hdcg;
	HBITMAP HBMP, newbitmap;

		
	
};
void ValSprite::get_sprite_var_forfield(ValSprite_s& v) {
	v.field = sprite_field;
	v.height = sprite_fieldwidth;
	v.width= sprite_fieldheight;
}
void ValSprite::findsprites() {//finds unbound sprites in sprites and binds them
	//need to fix my naming convention here
	BYTE* b = sprite_field;
	int w = sprite_fieldwidth, h = sprite_fieldheight;
	cout << "testing w h:  " << w << ":" << h << endl;
	int lh = 0;
	for (int i = 0; i < h; i++) {
		for (int n = 0; n < w; n++) {

			b = sprite_field + ((((i)*w) + n) * 4);
			if (is_in_sprite(n, i)) continue;

			if (*b == 255 && *(b + 1) == 255 && *(b + 2) == 255) {
				b += 4;
				continue;
			}
			b += 4;
			//cout << "found nonwhite pixel atx,y " << n << ": " << i << endl;
			//pause();
			BYTE* c = b;
			int ty = i;
			int tx = n, tw = 5, th = 0;
			// trace down and left to find x,y.  

			c = sprite_field + ((ty * w) + tx) * 4;
			//tx,ty should be top left corner of sprite; c=tx,ty

			//trace rows to find width- sliding, do rows +2 to -1, then do 0,1,max-1,max outside
			int ttx = tx, tty = ty;
			bool nw = false;
			BYTE* d = c + (w * 4); // move down 1 row;
			int itt = 1, nwloop = 0;
			while (1) {
				nw = false;
				for (int txi = 1; txi < tw || bp_nowhite(d); txi++) {
					if (bp_nowhite(d)) nw = true;
					tw = (tw > txi ? tw : txi);
					d += 4;
				}
				itt++;
				d = c + (w * 4 * itt);
				int hind = d - sprite_field;
				//cout << "field index: " << hind << " xy: "<< (hind% (w*4))/4<< ":"<<(hind/w)/4 <<endl;
				th++;
				if (!nw)nwloop++;
				else nwloop = 0;
				if (nwloop == 5)break; // if all were white up to tw 

			}
			c = sprite_field + ((ty * w) + tx) * 4;
			for (int iy = 0; iy < th; iy++) {
				while (bp_nowhite(c)) {
					tx--;
					tw++;
					c -= 4;
				}
				c += w * 4;
			}

			// th and tw should now be height and width.
			b += (tw * 4) + ((n - tx) * 4);
			n += tw;
			th -= 5;
			//SHOW(tx);
			//SHOW(ty);
			//SHOW(tw);
			//SHOW(th);
			int nnn = new_sprite(tx, ty, tw, th);
			fix_sprite_bounds(nnn);
			get_sprite_bounds(nnn, tx, ty, tw, th);


			if (th > lh)lh = th;

			//Sleep(1000);
		}
		//i+=lh;
		lh = 0;
	}
	cout << "out of loop" << endl;

}
void ValSprite::get_sprite_var(int num, ValSprite_s& v) {
	int size = sprite_siz[num].x * sprite_siz[num].y;
	v.width = sprite_siz[num].x;
	v.height = sprite_siz[num].y;
	//cout << "sprite size: " << size << endl;
	//cout << "sprite dims: " << v.width << ":" << v.height << endl;

	v.field = new BYTE[size*4];
	BYTE* hold = sprite_field;
	hold += ((sprite_loc[num].y * sprite_fieldwidth) + sprite_loc[num].x) * 4;
	BYTE* tohold = v.field;
	for (int n = 0; n < sprite_siz[num].y; n++) {
		for (int i = 0; i < sprite_siz[num].x; i++) {
			*tohold = *hold; tohold++; hold++;
			*tohold = *hold; tohold++; hold++;
			*tohold = *hold; tohold++; hold++;
			*tohold = *hold; tohold++; hold++;

		}
		hold = sprite_field;
		hold+= (((sprite_loc[num].y+n+1) * sprite_fieldwidth) + sprite_loc[num].x) * 4;
	}


}
bool ValSprite::is_in_sprite(int x, int y){
	for(int i =0 ; i< sprite_list_size;i++){
	
		if(x>=sprite_loc[i].x && y>=sprite_loc[i].y && x<= sprite_loc[i].x+sprite_siz[i].x && y<=sprite_loc[i].y+sprite_siz[i].y){
			//cout << x << ":" << y << " is in sprite \n";
			return true;
		}
	}
	return false;
	
}

void ValSprite::fix_sprite_bounds(int num){ // devtool
	//for each sprite in field, check to make sure tx,ty,tw,th don't go through a sprite//done
	// make sure bounding box has no white padding. -- just -=3 each field and rerun till change
	BYTE* hold = sprite_field;
	int tx, ty, tw, th;
	tx = sprite_loc[num].x;
	ty = sprite_loc[num].y;
	tw = sprite_siz[num].x;
	th = sprite_siz[num].y;
	int ww = sprite_fieldwidth;
	hold += ((ty * tw) + tx) * 4;
	for (int i = 0; i < tw; i++) {
		if (bp_nowhite(hold)) {
			ty--;
			th++;
			i = 0;
			hold = sprite_field;
			hold+= ((ty * ww) + tx) * 4;
			//cout << "fixbounds moved ty" << endl;
			continue;

		}
		hold += 4;
	}
	hold = sprite_field;
	hold += ((ty * ww) + (tx + tw)) * 4;
	//should be at tx+tw,ty
	for (int i = 0; i < th; i++) {
		if (bp_nowhite(hold)) {
			tw++;
			i = 0;
			hold = sprite_field;
			hold += ((ty * ww) + (tx+tw)) * 4;
			//cout << "fixbounds moved tw" << endl;
			continue;
		}
		hold += ww*4;
	}
	hold = sprite_field;
	hold += (((ty + th) * ww) + (tx+tw)) * 4;
	//should be at tx+tw,ty+th
	for (int i = 0; i < tw; i++) {
     		if (bp_nowhite(hold)) {
			th++;
			i = 0;
			hold = sprite_field;
			hold += (((ty+th) * ww) + (tx+tw)) * 4;
			//cout << "fixbounds moved th" << endl;
			continue;
		}
		hold -= 4;
	}
	
	//should be at tx,ty+th
	hold = sprite_field;
	hold+= (((ty+th) * ww) + tx ) * 4;

	for (int i = 0; i < th; i++) {
		if (bp_nowhite(hold)) {
			tx--;
			tw++;
			i = 0;
			hold = sprite_field;
			hold += (((ty+th) * ww) + tx ) * 4;
			//cout << "fixbounds moved tx" << endl;
			continue;
		}
		hold -= ww * 4;
	}
	if (tx != sprite_loc[num].x || ty != sprite_loc[num].y || tw != sprite_siz[num].x || th != sprite_siz[num].y) {
		sprite_loc[num].x=tx;
		sprite_loc[num].y=ty;
		sprite_siz[num].x=tw;
		sprite_siz[num].y=th;
		//cout << "fixbounds looped" << endl;
		//pause();
		//Sleep(300);
		fix_sprite_bounds(num);
	}
	
	
}
void ValSprite::save_spritefield(string ftitle){ 
	string bmpname = ftitle+".bmp", txtname = ftitle+".txt";
	mHDC = GetDC(NULL);
	SelectObject(mHDC,newbitmap);
	
	valspritewriteBMPfile(newbitmap,(LPTSTR)bmpname.c_str(),mHDC);
	ofstream ofile(txtname, ofstream::binary);
	POINT* loc = sprite_loc;
	POINT* siz = sprite_siz;
	ofile << sprite_list_size;
	for(int i = 0; i < sprite_list_size;i++){
		
			
			ofile << loc->x <<loc->y<<siz->x<<siz->y;
			loc++;siz++;
		
	}
	ofile.close();
		
}

// width and height of target buffer for bounding purposes.

void ValSprite::write_spritefield(BYTE*& tobuf, int x, int y, int width, int height){
	int w = width, h = height;
	int ww = w - x,hh=h-y;
	bool jumptype =0;
	if(ww>sprite_fieldwidth-x){
		jumptype=1;
		ww=sprite_fieldwidth-x;
	}
	if(hh>sprite_fieldheight-y)hh=sprite_fieldheight-y;

	BYTE* field_hold = sprite_field;
	BYTE* tobuf_hold = tobuf;
	//field_hold++;
	//tobuf_hold++;

	tobuf+= ((x*height)+y)*4;
	//cout << "writing "<<ww<<"*"<<hh<<" bytes"<<endl;
	for(int n = 0; n < hh;n++){
		for(int i = 0; i < ww;i++){
		
			//cout << "itstart";
			*tobuf_hold=*field_hold; tobuf_hold++; field_hold++;
			*tobuf_hold=*field_hold; tobuf_hold++; field_hold++;
			//cout << "itmid";
			*tobuf_hold=*field_hold; tobuf_hold++; field_hold++;
			*tobuf_hold=*field_hold; tobuf_hold++; field_hold++;
//			tobuf=field_hold; *tobuf++; *field_hold++;
//			tobuf=field_hold; *tobuf++; *field_hold++;
			//cout << "itend\n";
		}
		//cout << "loop"<<n <<endl;
		if(jumptype==1)tobuf_hold+= (width-ww)*4;
		else field_hold+= (sprite_fieldwidth-ww)*4;
		// write better later. needs to either buffer depending on which is smaller.
	} 
	//tobuf=tobuf_hold;
	
}
void ValSprite::write_sprite_var(BYTE* tobuf,int x, int y,int buffwidth, ValSprite_s& v) {
	BYTE* thold = tobuf;
	BYTE* vhold = v.field;
	thold += ((y  * buffwidth) + x) * 4;
	int hh = v.height;
	int ww = v.width;

	for (int n = 0; n < hh; n++) {
		for (int i = 0; i < ww; i++) {

			//cout << "itstart";
			*thold = *vhold; thold++; vhold++;
			*thold = *vhold; thold++; vhold++;
			*thold = *vhold; thold++; vhold++;
			*thold = *vhold; thold++; vhold++;
		}
		thold = tobuf;
		thold += (((y + n + 1) * buffwidth) + x) * 4;
	}


}
void ValSprite::write_sprite(BYTE* tobuf, int x, int y, int yheight, int spritenum){ // yheight is width...
	BYTE* field_hold= sprite_field;
	field_hold  += ((sprite_loc[spritenum].y*sprite_fieldwidth)+sprite_loc[spritenum].x)*4;
	
	
	BYTE** tobuf_hold = &tobuf;
	tobuf+=  ((y*yheight)+x)*4;
	
	
	int bjump = (yheight- sprite_siz[spritenum].x  )*4;
	int sjump = (sprite_fieldwidth -sprite_siz[spritenum].x)*4;
	
	for(int n = 0; n < sprite_siz[spritenum].y;n++){
		for(int i = 0; i < sprite_siz[spritenum].x;i++){
		
			*tobuf=*field_hold; tobuf++; field_hold++;
			*tobuf=*field_hold; tobuf++; field_hold++;
			*tobuf=*field_hold; tobuf++; field_hold++;
			*tobuf=*field_hold; tobuf++; field_hold++;
		}
		tobuf+=bjump; field_hold+=sjump;
	}
	tobuf=*tobuf_hold;
	
}
int ValSprite::new_sprite(int x, int y, int w, int h){
	int a = sprite_list_size;
	sprite_loc[a].x =x;
	sprite_loc[a].y =y;
	sprite_siz[a].x =w;
	sprite_siz[a].y =h;
	sprite_list_size++;
	return a;
}
void ValSprite::get_sprite_bounds(int num,int &tx, int& ty, int& tw, int& th) {
	tx = sprite_loc[num].x;
	ty = sprite_loc[num].y;
	tw = sprite_siz[num].x;
	th = sprite_siz[num].y;
}
ValSprite::ValSprite(){
	sprite_list_size=0;	
	
	
}
ValSprite::ValSprite(string filetitle){
	sprite_list_size=0;	
	load_spritefield(filetitle+".bmp",filetitle+".txt");
	
	
}

void ValSprite::load_spritefield(string fname,string infofname){
	HBMP = (HBITMAP) LoadImage( NULL, (LPCWSTR)ctolpwstr(fname), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	int w, h;
	BITMAP wrbmp;
	if (!GetObject(HBMP, sizeof(BITMAP), (LPSTR)&wrbmp)) {
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
        sprite_fieldwidth=wrbmp.bmWidth;
		sprite_fieldheight=wrbmp.bmHeight;
		cout << "loaded sprite dims: " << sprite_fieldwidth << ":" << sprite_fieldheight << endl;
		//w=wrbmp.bmWidth;
        //buf_width=w;
        //h=wrbmp.bmHeight;
        //buf_height=h;
        //cout <<"get_buffer(hbitmap) width: "<<wrbmp.bmWidth<<endl;
        //cout <<"get_buffer(hbitmap) height: "<<wrbmp.bmHeight<<endl;
        mybmi.bmiHeader.biPlanes = 1;
        mybmi.bmiHeader.biBitCount = 32;
        mybmi.bmiHeader.biCompression = BI_RGB;
        mybmi.bmiHeader.biSizeImage = (wrbmp.bmWidth * (mybmi.bmiHeader.biBitCount / 8) + 3) * wrbmp.bmHeight;	//& -4)  ??  this was in example
    //    SelectObject(hdcg,hbmp);
    DeleteObject(newbitmap);
	newbitmap =CreateDIBSection(hdcg, &mybmi, DIB_RGB_COLORS,(VOID **)&sprite_field, 0, 0);
	if(!newbitmap)  {cout <<"CreateDIBSection"<<endl;  return ;}
	int result = GetDIBits(hdcg, HBMP, 0, (wrbmp.bmHeight),sprite_field, (BITMAPINFO *)&mybmi, DIB_RGB_COLORS);
	if (!result)  cout <<"getDiBits"<<endl;  
	
	// load sprite data here.  
	ifstream ifile(infofname, ifstream::binary);
	POINT* loc = sprite_loc;
	POINT* siz = sprite_siz;
	ifile>>sprite_list_size;
	for(int i = 0; i < sprite_list_size;i++){
			ifile >> loc->x>>loc->y>>siz->x>>siz->y;
			loc++;siz++;
		
	}
	ifile.close();
		

}
	
	


#endif


