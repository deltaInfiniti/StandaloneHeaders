
#pragma once
#include <string>
using namespace std;
#include"valtextcontrol.h" 
#include<olectl.h>
#include<ole2.h>
#include <chrono>
#ifndef VRGB 
#define VRGB COLORREF
#define VRGB_BLUE 16711680
#define VRGB_RED  255
#define VRGB_GREEN 64000
#define VRGB_WHITE 16777215
#define VRGB_BLACK 0

#define VRGB_PINK 13120200 //200,50,200
#define VRGB_PURPLE 16728192//128, 64, 255
#define VRGB_CYAN 16776960  //0,255,255
#define VRGB_YELLOW 65535  //255,255,0
#define VRGB_BROWN 15440  //80,60,0
#define VRGB_ORANGE 348341  //181,80,5
#define VRGB_GREEN_DARK 146456  //24,60,2
#define VRGB_GREEN_LIGHT 7405454  //142,255,112
#define VRGB_RED_DARK 2626  //66,10,0
#define VRGB_RED_LIGHT 1447616  //192,22,22
#define VRGB_BLUE_DARK 4259840  //0,0,65
#define VRGB_BLUE_LIGHT 11555116  //44,81,176
#define VRGB_GREY_DARK 2105376  //32,32,32
#define VRGB_GREY_LIGHT 6316128  //96,96,96
#define VRGB_GREY_VLIGHT 8421504 // 128,128,128
#define VRGB_GREY_VVLIGHT 12632256 //192...
#define VRGB_GREY 4210752  //64,64,64
#define RECT val_rect
#endif 
void Mandel_progress_callback(int);
static bool G_Mandel_color_LinearCats = true;

//Arbitrary Newton Derbail Root Organizer - ANDRO
static int G_Mandel_ANDRO_factorslist[300]; // initialize to zero
static int G_Mandel_ANDRO_factorslistlen = 0;
static double G_Mandel_ANDRO_rootslist[1000]; // holds roots associated with factorslist for newton fractal calculation
static int G_Mandel_ANDRO_rootslistlen = 0;
struct newton_fractal {
    double x, y;
    int its;
    int cat = 0;
};

void systemcall_ffmpeg_buildvideofromframeimages( string filemask = "frame%d.png", int fps = 60, int crf=18, string fileoutname="out.mp4", string pxfmt = "rgb24") {
    string call = "ffmpeg -r "+ctostr(fps)+ " - f image2 - s 1920x1080 - i "+filemask+" - vcodec libx264 - crf "+ctostr(crf)+" - pix_fmt "+pxfmt+" "+fileoutname;
    cout << call << "\n";
    system(call.c_str());
}
string G_FFMPEG_filemask = "frame%d.png", G_FFMPEG_pixfmt="rgb24", G_FFMPEG_fileout="out.mp4";
int G_FFMPEG_fps = 60, G_FFMPEG_crf = 18;
void FFMPEG_thread(void* a) {
    systemcall_ffmpeg_buildvideofromframeimages(G_FFMPEG_filemask, G_FFMPEG_fps, G_FFMPEG_crf, G_FFMPEG_fileout, G_FFMPEG_pixfmt);
}
void FFMPEG_dispatch_thread(string filemask = "frame%d.png", int fps = 60, int crf = 18, string fileoutname = "out.mp4", string pxfmt = "rgb24") {
    G_FFMPEG_filemask = filemask;
    G_FFMPEG_fps = fps;
    G_FFMPEG_crf = crf;
    G_FFMPEG_fileout = fileoutname;
    G_FFMPEG_pixfmt = pxfmt;
    _beginthread(FFMPEG_thread, 0, NULL);

}
#define mandel_factors_maxlen 1000;
#define foreach(a,b) for(int a=0; a < b; a++)

#define Mandelbrot_window_dims 2000
//this file needs serious refactoring, renaming, reducing.

int Linear_greyscale(int its, int maxits) {
    int maxp = 255 * 3;
    double div = (double)maxits / (double)maxp;
    its = its / div;
    int major = its / 3;
    int minor = its % 3;
    int r=major, g = major, b = major;
    if (minor)g++;
    minor--;
    if (minor > 0)b++;
    return RGB(r, g, b);
}

ValStopwatch G_Mandel_Stopwatch;
#define Mandel_number_cats 7
static int G_Mandel_colorizer_type = 0;
#define Mandel_colorizer_ex_maxcats 500
int G_Mandel_colorizer_ex_catagories[3000];  // 300 allows for 50 catagories... plenty. 
int G_Mandel_colorizer_ex_num_catagories = 0;
int linear_colorExproc(double ratio, unsigned int plc, int* catagories, int catlen) {
    unsigned char r, g, b;
    if (plc >= catlen)return 0;
    plc *= 6;
    r = catagories[plc] + (ratio * catagories[plc + 3]);
    g = catagories[plc + 1] + (ratio * catagories[plc + 4]);
    b = catagories[plc + 2] + (ratio * catagories[plc + 5]);

    return RGB(r, g, b);
}

int linear_colorEx(int its, int maxits) {
    
    if (G_Mandel_colorizer_ex_num_catagories == 0) {
        //cout << "Linear_colorEx error, no catagories defined\n";
        return -1;
    }
    int size = (maxits / G_Mandel_colorizer_ex_num_catagories);
    if (size == 0) {
        //cout << "Linear_colorEx error, size==0\n";
        return -1;
    }
    
    //double size = ((double)maxits / (double)G_Mandel_colorizer_ex_num_catagories);
    return linear_colorExproc( (double)(its%size) / (double)size, its/ size, G_Mandel_colorizer_ex_catagories, G_Mandel_colorizer_ex_num_catagories);
}

void Linear_colorEx_addCatagory(int rmin, int rmax, int gmin, int gmax, int bmin, int bmax) {
    int num_catagories = G_Mandel_colorizer_ex_num_catagories * 6;
    if (num_catagories > Mandel_colorizer_ex_maxcats - 6)return;
    G_Mandel_colorizer_ex_catagories[num_catagories] = rmin;
    G_Mandel_colorizer_ex_catagories[num_catagories + 1] = gmin;
    G_Mandel_colorizer_ex_catagories[num_catagories + 2] = bmin;
    G_Mandel_colorizer_ex_catagories[num_catagories + 3] = rmax - rmin;
    G_Mandel_colorizer_ex_catagories[num_catagories + 4] = gmax - gmin;
    G_Mandel_colorizer_ex_catagories[num_catagories + 5] = bmax - bmin;
    G_Mandel_colorizer_ex_num_catagories++;
}
void Linear_colorEx_addCatagoryb(int rmin, int gmin, int bmin, int rmax, int gmax, int bmax) {
    Linear_colorEx_addCatagory(rmin, rmax, gmin, gmax, bmin, bmax);
}
void Linear_colorEx_addRandCatagories(int howmany, valVeryRandom* vl) {
    unsigned long long int rval;
    unsigned char r, g, b, rr=255, gg=255, bb=255;
    rval = vl->next();
    rr = rval % 255; rval = rval >> 7;
    gg = rval % 255; rval = rval >> 7;
    bb = rval % 255; rval = rval >> 7;

    foreach(n, howmany) {
        //rval = vl->next();
        r = rr;// r = rval % 255; rval = rval >> 7;
        g = gg;// g = rval % 255; rval = rval >> 7;
        b = bb;// b = rval % 255; rval = rval >> 7;
        rval = vl->next();
        rr = rval % 255; rval = rval >> 7;
        gg = rval % 255; rval = rval >> 7;
        bb = rval % 255; rval = rval >> 7;
        Linear_colorEx_addCatagory(r, rr,g, gg,b, bb);
    }

}
valVeryRandom G_mandel_vlcolor;
string g_mandel_vlcolor_lastr = "";
void Linear_colorEx_fromstr(string seed,short count = 20) {
    if (g_mandel_vlcolor_lastr != seed) {
        G_mandel_vlcolor.build(seed);
        g_mandel_vlcolor_lastr = seed;
    }
    G_Mandel_colorizer_ex_num_catagories = 0;
    Linear_colorEx_addRandCatagories(count, &G_mandel_vlcolor);

}

int Linear_color(int its, int maxits) {
    // attempt to colorize mandelbrot image, can be more generalized to a int-> rainbow system 
    // maxits is your total color space from re->green->blue->pink
    // its is a relative (arbitrary, linear) place in that color space. 
    //1530 different outputs possible when maxints is multiple of 3060
    if (its == maxits)return 0;// 16777215; // white
    if (G_Mandel_colorizer_type == 3)return Linear_greyscale(its, maxits);
    if (G_Mandel_colorizer_type == 4)return linear_colorEx(its, maxits);
    int catsize = (maxits / Mandel_number_cats);  // the size of the hardcoded catagories in the total
    if (catsize < 1)catsize = 1;
                                                  //short jump = its / catsize; // what catagory will we be in- for switch
    short jump;
    if (G_Mandel_colorizer_type == 0) jump = its / catsize;
    else jump = (its) % Mandel_number_cats; // what catagory will we be in- for switch  2022 change to make grades very steep
    //  else jump = (its) % catsize;  weird results but cool. 
    double itc = (its % catsize);
    itc /= (float)catsize;
    itc *= 510;// actual weighted value of the itteration count -- should be between 0-510
    double itr = 0; // for sine wave style transition
    double itrb = 1; //for non-branching flow
    if (itc > 255) {
        itr = 1;
        itrb = 0;
        itc -= 255;
    }
    //if (itc <1)return RGB(255,255,255);
    double r, g, b;
    switch (jump) {// from itc==0  itr==1  itr==1&&itc==255
    case 0:// red  from 64,0,0 -> 255,0,0 ->192,128,0
        r = (itrb * (64 + (itc * .75))) + (itr * (255 - (itc / 4)));
        g = (itr * (itc / 2));
        return RGB(r, g, 0);
        break;
    case 1:// 192,128,0  -> 255,255,0 -> 128,192,0 orange to yellow to green
        r = (itrb * (192 + (itc / 4))) + (itr * (255 - (itc / 2)));
        g = (itrb * (128 + (itc / 2))) + (itr * (255 - (itc / 4)));
        return RGB(r, g, 0);
        break;
    case 2:// 128,192,0  -> 0,255,0 -> 0,192,128   green to very green to teal green
        r = (itrb * (128 - (itc / 2)));
        g = (itrb * (192 + (itc / 4))) + (itr * (255 - (itc / 4)));
        b = (itr * (itc / 2));
        return (int)RGB(r, g, b);
        break;
    case 3:// 0,192,128 -> 0, 192, 192 -> 0,128,192  // blue transition 1
        g = (itrb * 192) + (itr * (192 - (itc / 4)));
        b = (itrb * (128 + (itc / 4))) + (itr * 192);
        return (int)RGB(0, g, b);
        break;
    case 4:// 0,128,192 -> 0, 64, 192 -> 0,0,255 // blue transition 2
        g = (itrb * (128 - (itc / 4))) + (itr * (64 - (itc / 4)));
        b = (itrb * 192) + (itr * (192 + (itc / 4)));
        return (int)RGB(0, g, b);
        break;
    case 5:// 0,0,255 -> 64, 0, 192 -> 128,0,192 // blue to purple
        r = (itrb * (itc / 4)) + (itr * (64 + (itc / 4)));
        b = (itrb * (255 - (itc / 4))) + (itr * 192);
        return (int)RGB(r, 0, b);
        break;
    case 6:// 128,0,192 -> 192,0,192 -> 255,0,255 // purple to pink
        r = (itrb * (128 + (itc / 4))) + (itr * (192 + (itc / 4)));
        b = (itrb * (192)) + (itr * (192 + (itc / 4)));
        return (int)RGB(r, 0, b);
        break;
    }

}

#include"valComplexMath.h"
#include"valFractal_ANDRO.h"
#include"valFractalIterators.h"  
#include"valFractal.h"



//given opposing corners of a box, makes x,y top left corner, xx,yy bottom right
inline void box_dims_highlow(int& x, int& y, int& xx, int& yy) {
    int t = 0;
    if (x > xx) { t = x; x = xx; xx = t; }
    if (y > yy) { t = y; y = yy; yy = t; }
}
HBITMAP OLELoadImage(char* FileName) // loads jpgs and pngs into hbitmap context.  
{  // stolen from ancient forum post... shlould credit better
    // Use IPicture stuff to use JPG / GIF files
    IPicture* p;
    IStream* s;
    IPersistStream* ps;
    HGLOBAL hG;
    void* pp;
    FILE* fp;

    fp = fopen(FileName, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    int fs = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    hG = GlobalAlloc(GPTR, fs);
    if (!hG){
        fclose(fp);
        return NULL;
    }
    pp = (void*)hG;
    fread(pp, 1, fs, fp);
    fclose(fp);

    // Create an IStream so IPicture can
    CreateStreamOnHGlobal(hG,false,&s);
    if (!s){
        GlobalFree(hG);
        return NULL;
    }

    OleLoadPicture(s, 0, false, IID_IPicture, (void**)&p);

    if (!p){
        s->Release();
        GlobalFree(hG);
        return NULL;
    }
    s->Release();
    GlobalFree(hG);

    HBITMAP hB = 0;
    p->get_Handle((unsigned int*)&hB);
    HBITMAP hBB = (HBITMAP)CopyImage(hB, IMAGE_BITMAP, 0, 0,LR_COPYRETURNORG);
    p->Release();
    return hBB;
}

#define VRGB COLORREF
#define VRGB_BLUE 16711680
#define VRGB_RED  255
#define VRGB_GREEN 64000
#define VRGB_WHITE 16777215
#define VRGB_BLACK 0

#define VRGB_111 65793 // 1,1,1 - for modifying greys
#define VRGB_PINK 13120200 //200,50,200
#define VRGB_PURPLE 16728192//128, 64, 255
#define VRGB_CYAN 16776960  //0,255,255
#define VRGB_YELLOW 65535  //255,255,0
#define VRGB_BROWN 15440  //80,60,0
#define VRGB_ORANGE 348341  //181,80,5
#define VRGB_GREEN_DARK 146456  //24,60,2
#define VRGB_GREEN_LIGHT 7405454  //142,255,112
#define VRGB_RED_DARK 2626  //66,10,0
#define VRGB_RED_LIGHT 1447616  //192,22,22
#define VRGB_BLUE_DARK 4259840  //0,0,65
#define VRGB_BLUE_LIGHT 11555116  //44,81,176
#define VRGB_GREY_DARK 2105376  //32,32,32
#define VRGB_GREY_LIGHT 6316128  //96,96,96
#define VRGB_GREY_VLIGHT 8421504 // 128,128,128
#define VRGB_GREY_VVLIGHT 12632256 //192...
#define VRGB_GREY 4210752  //64,64,64
//#define VRGB_RAND (((rand()<<16)+rand())%16777215)
#define VRGB_RAND G_VS_Rand3(16777215)
class ValGFX {
public:
	ValGFX();
    ~ValGFX();
    void clearmem();

	HDC hdcDesktop;
	HBITMAP hbmp, Selectdump;
    BITMAPINFO mybmi;
	char* bits;
    int width, height;
    char* copybuf;
    int copywidth, copyheight;
    void set(int w, int h) { width = w; height = h; }; // this is borked
    
	void Get_blank_buffer(int w, int h);

    void blt(HDC hdc, int x, int y);
    void transblt(HDC hdc, int x, int y);
    void bltsect(HDC hdc, int x, int y, int w, int h, int xx, int yy,bool copytome=false);

    void create_default_BMI(int w, int h, BITMAPINFO& myBmi);
    void create_BMI(BITMAPINFO& myBmi) { create_default_BMI(width, height, mybmi); }
    
    bool load_image(string fname);
    bool OLE_load(string fname);
    bool GDIP_load(string fname);

    void save_image(string fname);

    void editpixel(int x, int y, COLORREF rgb);
    char* buf_at_xy(int x, int y) {return bits + (((y * width) + x) * 4);}
    void copy_buf();
    void paste_buf();
    //DIBdraw(HDC comdc, HBITMAP& bmp);
    void do_DIB(HBITMAP& a, BITMAP& b);
    void HDCdraw(HDC comdc, HBITMAP& target, int x, int y);
    void CopySectionToGFX(ValGFX& gfx, int x, int y, int w, int h, int xx, int yy);
    void CopyToGFX(ValGFX& gfx, int x, int y); // seems to be working now mor etesting needed
    /*  edit/draw to buffer functions*/
    void makewhite(int alpha);
    void makeblack(int alpha);
    void color_section(int x, int y, int w, int h, VRGB color, int alpha);
    void makecolor(VRGB color, int alpha );
    void draw_boarder(int wide  /*=3*/, int offset /*= 1*/, VRGB color /*= VRGB{ 0,0,255 }*/);
    void draw_boarder2(int wide  /*=3*/, int offset /*= 1*/, VRGB color /*= VRGB{ 0,0,255 }*/);
    void drawline(int x, int y, int xy, bool horizontal, int width, VRGB color);
    void drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width);
    void drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width, VRGB color);
    void draw_box2(int x, int y, int xx, int yy, int wide, int offset, VRGB color);//this is better
    void drawline2(int x, int y, int xy, bool horizontal, int width, VRGB color);
    void draw_box3(int x, int y, int xx, int yy, int wide, int offset, VRGB color);//this is better. absolute bounds
    void draw_square(int x, int y, int xx, int yy, VRGB color /*= (VRGB)255*/);
    void buf__drawslopex(int x, int y, int xdir, double a, int itt, VRGB clr);
    void buf__drawslopey(int x, int y, int xdir, double a, int itt, VRGB clr);
    void drawline_slope(int x, int y, int xx, int yy, int width, VRGB clr);

    // alpha block(untested or known bugs):
    void draw_box(int x, int y, int xx, int yy, int wide , int offset, VRGB color );
    void transCopyToGFX(ValGFX& gfx, int x, int y);
    void CopyfromHBMP(HDC hdc, HBITMAP& bmp, int x, int y, int w, int h); // some bug here.  needs testing.
    void CopyToHBMP(HDC hdc, HBITMAP bmp, int x, int y, int w, int h);

    

    //void draw_boarder(int width, int offset , VRGB color /*= VRGB{ 0,0,255 }*/);
    // doesnt blur straight lines separating complimentary colors....... maybe useful. 
    void blurtocopy();  // basic, slow, very slight result.  best antialias.

    void blurtocopy2();// erratic static
    void blurtocopy3();// slightly smoother
    void blurtocopy4();// slightly smoother
    void blurtocopy5();
    void blurtocopy6();
    void blurtocopy7();// smooth but very fast and heavy.. 
    void blurtocopy8();// far far better
    void blurtocopy9();// still good but slower
    void blurtocopy10();// attempt at faster... Creates weird fractals.
    void blurtocopy11();
    void blur() { blurtocopy8(); paste_buf(); }

    void clip_hbmp(HBITMAP& h);
    void draw_circle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width, VRGB clr /*= (VRGB)VRGB_RED*/);

    //if ww or hh are 0, copy to my full buffer.  must already have buffer.  
    bool load_image_sect(string fname,int xdst, int ydst, int ww=0, int hh=0, int xsrc=0, int ysrc=0) {
        if (ww == 0||ww>width)ww = width;
        if (hh == 0||hh>height)hh = height;

        string extens = extension(fname);
        
        //if (hbmp)DeleteObject(hbmp);// can remove if statement 
        HBITMAP hbmpt;
            if (extens != ".bmp") hbmpt =OLELoadImage((char*)fname.c_str());
            else hbmpt = (HBITMAP)LoadImageA(NULL, fname.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); //maybe xsrc ysrc instead of 0,0
            
        BITMAP wrbmp;
        if (!GetObject(hbmpt, sizeof(BITMAP), (LPSTR)&wrbmp)) {
            //LOG("[ERROR] could not retrieve bitmap info");
            cout << "getObject failed" << endl;
            return false;
        }
        if (ww > wrbmp.bmWidth)ww = wrbmp.bmWidth;
        if (hh > wrbmp.bmHeight)hh = wrbmp.bmHeight;
        cout << "loading image w,h: " << ww << " , " << hh << "\n";

        HDC tempdc = CreateCompatibleDC(hdcDesktop);
        SelectObject(tempdc,hbmpt);
        bltsect(tempdc, xdst, ydst, ww, hh, xsrc, ysrc,true); // maybe 0,0 instead of src
        //do_DIB(hbmpt, wrbmp);

        SelectObject(tempdc, Selectdump);
        ReleaseDC(NULL,tempdc);
        DeleteDC(tempdc);
        DeleteObject(hbmpt);
        return true;

    }



   /*
    
   int mandcolor2(int its, int maxits){
   //start at white
   //red+
   //green+
   //red-
   //blue+
   //green-
   //red+
   }
   */
#define Mandel_number_cats 7
    int get_mand_color(int its, int maxits) {
        // attempt to colorize mandelbrot image, can be more generalized to a int-> rainbow system 
        // maxits is your total color space from re->green->blue->pink
        // its is a relative (arbitrary, linear) place in that color space. 
        //1530 different outputs possible when maxints is multiple of 3060
        return Linear_color(its, maxits);  // defaults to global linear_color function with global options
         
        if (its == maxits)return 0;// 16777215; // white
        if (G_Mandel_colorizer_type == 3)return Linear_greyscale(its, maxits);
        int catsize = (maxits / Mandel_number_cats);  // the size of the hardcoded catagories in the total
        //short jump = its / catsize; // what catagory will we be in- for switch
        short jump;
        if(G_Mandel_colorizer_type == 0) jump = its / catsize;
        else jump= (its) % Mandel_number_cats; // what catagory will we be in- for switch  2022 change to make grades very steep
        //  else jump = (its) % catsize;  weird results but cool. 
        double itc = (its % catsize);
        itc /= (float)catsize;
        itc *= 510;// actual weighted value of the itteration count -- should be between 0-510
        double itr = 0; // for sine wave style transition
        double itrb = 1; //for non-branching flow
        if (itc > 255) {
            itr = 1;
            itrb = 0;
            itc -= 255;
        }
        //if (itc <1)return RGB(255,255,255);
        double r, g, b;
        switch (jump) {// from itc==0  itr==1  itr==1&&itc==255
        case 0:// red  from 64,0,0 -> 255,0,0 ->192,128,0
            r = (itrb * (64 + (itc * .75))) + (itr * (255 - (itc / 4)));
            g = (itr * (itc / 2));
            return RGB(r, g, 0);
            break;
        case 1:// 192,128,0  -> 255,255,0 -> 128,192,0 orange to yellow to green
            r = (itrb * (192 + (itc / 4))) + (itr * (255 - (itc / 2)));
            g = (itrb * (128 + (itc / 2))) + (itr * (255 - (itc / 4)));
            return RGB(r, g, 0);
            break;
        case 2:// 128,192,0  -> 0,255,0 -> 0,192,128   green to very green to teal green
            r = (itrb * (128 - (itc / 2)));
            g = (itrb * (192 + (itc / 4))) + (itr * (255 - (itc / 4)));
            b = (itr * (itc / 2));
            return (int)RGB(r, g, b);
            break;
        case 3:// 0,192,128 -> 0, 192, 192 -> 0,128,192  // blue transition 1
            g = (itrb * 192) + (itr * (192 - (itc / 4)));
            b = (itrb * (128 + (itc / 4))) + (itr * 192);
            return (int)RGB(0, g, b);
            break;
        case 4:// 0,128,192 -> 0, 64, 192 -> 0,0,255 // blue transition 2
            g = (itrb * (128 - (itc / 4))) + (itr * (64 - (itc / 4)));
            b = (itrb * 192) + (itr * (192 + (itc / 4)));
            return (int)RGB(0, g, b);
            break;
        case 5:// 0,0,255 -> 64, 0, 192 -> 128,0,192 // blue to purple
            r = (itrb * (itc / 4)) + (itr * (64 + (itc / 4)));
            b = (itrb * (255 - (itc / 4))) + (itr * 192);
            return (int)RGB(r, 0, b);
            break;
        case 6:// 128,0,192 -> 192,0,192 -> 255,0,255 // purple to pink
            r = (itrb * (128 + (itc / 4))) + (itr * (192 + (itc / 4)));
            b = (itrb * (192)) + (itr * (192 + (itc / 4)));
            return (int)RGB(r, 0, b);
            break;
        }

    }
    void fractal_buffer_render(int* inpBuf,int max, int w, int h) {
        if (w != width) {
            cout << "fractal_buffer_render warning- width != inputWidth\n";
        }
        if (h != height) {
            cout << "fractal_buffer_render warning- height != inputHeight\n";
        }
        copy_buf();
        int color;
        BYTE* hold = (BYTE*)copybuf;
        int* inbuf = inpBuf;
        for (int n = 0; n < h; n++) {
            for (int i = 0; i < w; i++) {
                color = get_mand_color(*inbuf, max); inbuf++;
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
            }
        }

    }
    void mandel_buffer_render(int inpBuf[][2000],int max) {
        copy_buf();
        int color;
        BYTE* hold = (BYTE*)copybuf;
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                color = get_mand_color(inpBuf[n][i], max);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
            }
        }
    }

    

    
    void OmniMandel_thread(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims], int rebuild = 0, double bailout = 4.0, int type = 0) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;
        BYTE* hold = (BYTE*)copybuf;
        SHOW(x);
        SHOW(y);
        SHOW(type);
        SHOW(maxits);
        Dispatch_workerthread_job(x, y, w, h, cx, cy, maxits, Mcallback, inpBuf, rebuild, bailout, type, copybuf, this->width, this->height, 12, Mandel_progress_callback);
        cout << "dispatched worker threads\n";
        while (G_mandel_workerthread_info.running)Sleep(60);
        cout << "threads finished itterating, returning to renderer\n";

    }
    void OmniMandel(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims], int rebuild = 0, double bailout = 4.0, int type = 0)
    {
        OmniMandel_thread(x, y, w, h, cx, cy, maxits, Mcallback, inpBuf, rebuild, bailout, type);
    }



}; 
ValGFX::ValGFX() {
    hdcDesktop = GetDC(GetDesktopWindow());
    width = 0;
    height = 0;
    copywidth = 0;
    copyheight = 0;
    bits = NULL;
    copybuf = NULL;

}
void ValGFX::clearmem() {
    
    if (copybuf != NULL)delete[]copybuf;
    copybuf = NULL;
    DeleteObject(hbmp);

}
ValGFX::~ValGFX() {//used to be... very leaky
    DeleteDC(hdcDesktop);
    clearmem();
                   //if (bits != NULL)delete[](BYTE*)bits;
}

void ValGFX::copy_buf() {
    if (copybuf == NULL || copywidth!=width || copyheight != height) {
        
        delete[] (BYTE*)copybuf;
        copybuf = new char[width * height * 4];
        copywidth = width;
        copyheight = height;
        //cout << "inside copy_buf create" << endl;

    }
    if(copybuf==NULL)copybuf = new char[width * height * 4];
    //cout << "before copy memcopy" << endl;
    memcpy(copybuf, bits, width * height * 4);
    //cout << "after  copy memcopy" << endl << endl;

}
void ValGFX::paste_buf() {
    if (copybuf == NULL)return;
    memcpy(bits, copybuf, width * height * 4);

}
string extension(string a);

void ValGFX::do_DIB(HBITMAP& hbmpt, BITMAP& wrbmp) {
    create_default_BMI(wrbmp.bmWidth, wrbmp.bmHeight, mybmi);
    if (width == 0)width = wrbmp.bmWidth;
    if (height == 0)height = wrbmp.bmHeight;

    hbmp = CreateDIBSection(hdcDesktop, &mybmi, DIB_RGB_COLORS, (VOID**)&bits, 0, 0);
    int result = GetDIBits(hdcDesktop, hbmpt, 0, (wrbmp.bmHeight), bits, (BITMAPINFO*)&mybmi, DIB_RGB_COLORS);
    cout << "loaded dib height: " << mybmi.bmiHeader.biHeight << endl;
    height = mybmi.bmiHeader.biHeight * -1;
    if (!result) {
        cout << "getDiBits" << endl; return ;
    }

}
void gdiLoadHbitmapPNG(HBITMAP& membit, string fname)
{
    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    {
        Gdiplus::Bitmap bitmap(ctolpwstr(fname), true);
        
        const Color c = Color(255, 0, 0);
        bitmap.GetHBITMAP(c, &membit);

    }

    GdiplusShutdown(gdiplusToken);
}

bool ValGFX::GDIP_load(string fname) {
    if (hbmp)DeleteObject(hbmp);// can remove if statement 
    HBITMAP hbmpt;
    gdiLoadHbitmapPNG(hbmpt,(char*)fname.c_str());
    BITMAP wrbmp;
    if (!GetObject(hbmpt, sizeof(BITMAP), (LPSTR)&wrbmp)) {
        //LOG("[ERROR] could not retrieve bitmap info");
        cout << "getObject failed" << endl;
        return false;
    }
    do_DIB(hbmpt, wrbmp);
    DeleteObject(hbmpt);
    return true;

}

bool ValGFX::load_image(string fname) {
    string extens = extension(fname);
    if (extens != ".bmp") {
     
        if(extens == ".jpg") return OLE_load(fname);
        if (extens == ".png") return GDIP_load(fname);
    }
    if (hbmp)DeleteObject(hbmp);// can remove if statement 
    HBITMAP hbmpt = (HBITMAP)LoadImageA(NULL, fname.c_str() , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    BITMAP wrbmp;
    if (!GetObject(hbmpt, sizeof(BITMAP), (LPSTR)&wrbmp)) {
        //LOG("[ERROR] could not retrieve bitmap info");
        cout << "getObject failed" << endl;
        return false;
    }
    do_DIB(hbmpt, wrbmp);
    DeleteObject(hbmpt);
    return true;

}


bool ValGFX::OLE_load(string fname) {
    if (hbmp)DeleteObject(hbmp);// can remove if statement 
    HBITMAP hbmpt = (HBITMAP)OLELoadImage((char*)fname.c_str());
    BITMAP wrbmp;
    if (!GetObject(hbmpt, sizeof(BITMAP), (LPSTR)&wrbmp)) {
        //LOG("[ERROR] could not retrieve bitmap info");
        cout << "getObject failed" << endl;
        return false;
    }
    do_DIB(hbmpt, wrbmp);
    DeleteObject(hbmpt);
    return true;

}
#define LOG(a) cout << a<<"\n"
void ValGFX::save_image(string fname) {
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
    BYTE* hp; // byte pointer
    DWORD dwTmp;
    if (!GetObject(this->hbmp, sizeof(BITMAP), (LPSTR)&wrbmp)) {
        LOG("[ERROR] could not retrieve bitmap info");
        return;
    }
    cClrBits = (WORD)(wrbmp.bmPlanes * wrbmp.bmBitsPixel);

    //	cout << "cClrBits: " << cClrBits <<endl;
    //	cout << "bmPlanes: " << wrbmp.bmPlanes  <<endl;
    //	cout << "bmPixel: " << wrbmp.bmBitsPixel<<endl;
    //	cout << "bmp.bmWidth: " << wrbmp.bmWidth  <<endl;
    //	cout << "bmp.bmHeight: " << wrbmp.bmBitsPixel<<endl;

    if (cClrBits > 24) cClrBits = 32;
    else if (cClrBits != 1) cClrBits = (4 * ((((cClrBits / 4) % 1) + 1)));

    if (cClrBits != 24)
        pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
            sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits));
    else
        pbmi = (PBITMAPINFO)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = wrbmp.bmWidth;
    pbmi->bmiHeader.biHeight = wrbmp.bmHeight;
    pbmi->bmiHeader.biPlanes = wrbmp.bmPlanes;
    pbmi->bmiHeader.biBitCount = wrbmp.bmBitsPixel;
    if (cClrBits < 24)
        pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
    pbmi->bmiHeader.biCompression = BI_RGB;
    pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * cClrBits;
    pbmi->bmiHeader.biClrImportant = 0;
    pbih = (PBITMAPINFOHEADER)pbmi;
    lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
    if (!lpBits) {
        LOG("[ERROR] could not allocate memory");
        return;
    }
    if (!GetDIBits(hdcDesktop, HBITMAP(this->hbmp), 0, (WORD)pbih->biHeight, lpBits, pbmi, DIB_RGB_COLORS)) {
        LOG("GetDIB error");
        return;
    }
    hf = CreateFileA(fname.c_str(), GENERIC_READ | GENERIC_WRITE, (DWORD)0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
        (HANDLE)NULL);
    if (hf == INVALID_HANDLE_VALUE) {
        LOG("[ERROR]could not create file for writing");
        return;
    }
    hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M"
    hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage);
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;

    hdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD);

    if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER), (LPDWORD)&dwTmp, NULL)) {
        LOG("[ERROR]could not write headers to file");
//        LOG(filename);
        return;
    }
    if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
        + pbih->biClrUsed * sizeof(RGBQUAD),
        (LPDWORD)&dwTmp, (NULL))) {
        LOG("[ERROR]could not write info to file");
        return;
    }
    dwTotal = cb = pbih->biSizeImage;
    hp = lpBits;
    if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) {
        LOG("[ERROR]could not write data bits to file");
        return;
    }
    if (!CloseHandle(hf)) {
        LOG("could not close file");
        return;
    }
    GlobalFree((HGLOBAL)lpBits);
}
void ValGFX::create_default_BMI(int w, int h, BITMAPINFO& myBmi) {
    myBmi.bmiHeader.biSize = sizeof(myBmi);
    myBmi.bmiHeader.biWidth = w;
    myBmi.bmiHeader.biHeight = h * -1;
    myBmi.bmiHeader.biPlanes = 1;
    myBmi.bmiHeader.biBitCount = 32;
    myBmi.bmiHeader.biCompression = BI_RGB;
    myBmi.bmiHeader.biSizeImage = (w * (4) + 3) * h;	//& -4)  ??  this was in example
}

void ValGFX::transblt(HDC hdc, int x, int y) {
    HDC bufhdc = CreateCompatibleDC(hdc);
    SelectObject(bufhdc, hbmp);
    TransparentBlt(hdc, x, y, width, height, bufhdc, 0, 0, width,height,RGB(0, 0, 0));  // SRCCOPY);

    SelectObject(bufhdc, Selectdump);
    ReleaseDC(NULL, bufhdc);
    DeleteDC(bufhdc);
}

void ValGFX::blt(HDC hdc,int x,int y) {    
        HDC bufhdc = CreateCompatibleDC(hdc);
        SelectObject(bufhdc, hbmp);
        BitBlt(hdc, x, y, width, height, bufhdc, 0, 0, SRCCOPY);

        SelectObject(bufhdc, Selectdump);
        ReleaseDC(NULL, bufhdc);
        DeleteDC(bufhdc);
}

void ValGFX::bltsect(HDC hdc, int x, int y, int w, int h, int xx, int yy, bool copytome/*=false*/) {
    HDC bufhdc = CreateCompatibleDC(hdc);
    SelectObject(bufhdc, hbmp);
    if(copytome) BitBlt(bufhdc, x, y, w, h, hdc, xx, yy, SRCCOPY);
    else BitBlt(hdc, x, y, w, h, bufhdc, xx, yy, SRCCOPY);

    SelectObject(bufhdc, Selectdump);
    ReleaseDC(NULL, bufhdc);
    DeleteDC(bufhdc);
}
void ValGFX::CopySectionToGFX(ValGFX& gfx, int x, int y, int w, int h, int xx, int yy) {
    HDC tempdc = CreateCompatibleDC(hdcDesktop);
    SelectObject(tempdc, gfx.hbmp);
    bltsect(tempdc, x, y, w, h, xx, yy);
    ReleaseDC(NULL, tempdc);
    DeleteDC(tempdc);

}


void ValGFX::HDCdraw(HDC comdc, HBITMAP& target, int x, int y) {
    
    HDC bufhdc = CreateCompatibleDC(comdc);
    SelectObject(bufhdc, target);
    HDC myhdc = CreateCompatibleDC(comdc);
    SelectObject(myhdc, hbmp);

    BitBlt(bufhdc,x,y,width,height,myhdc,0,0,SRCCOPY );
    SelectObject(bufhdc, Selectdump);
    ReleaseDC(NULL, bufhdc);
    DeleteDC(bufhdc);
    SelectObject(myhdc, Selectdump);
    ReleaseDC(NULL, myhdc);
    DeleteDC(myhdc);
}
void ValGFX::Get_blank_buffer(int w, int h) {
    if (hbmp) DeleteObject(hbmp);
    if (w == 0 && h == 0) {
        w = width; h = height;
    }
    else {
        width = w; height = h;
    }
    mybmi.bmiHeader.biSize = sizeof(mybmi);
    mybmi.bmiHeader.biWidth = w;
    mybmi.bmiHeader.biHeight = h * -1;
    mybmi.bmiHeader.biPlanes = 1;
    mybmi.bmiHeader.biBitCount = 32;
    mybmi.bmiHeader.biCompression = BI_RGB;
    mybmi.bmiHeader.biSizeImage = (w * (mybmi.bmiHeader.biBitCount / 8) + 3) * h;
    hbmp= CreateDIBSection(hdcDesktop, &mybmi, DIB_RGB_COLORS, (VOID**)&bits, NULL, 0);
}

void ValGFX::CopyfromHBMP(HDC hdc, HBITMAP &bmp,int x, int y, int w, int h) {
    if (w > width || h > height)DeleteObject(hbmp);
    if (!hbmp)Get_blank_buffer(w, h);

    HDC bufhdc = hdcDesktop;
    SelectObject(bufhdc, hbmp);
    HBITMAP old=(HBITMAP)SelectObject(hdc, bmp);
    //BitBlt(hdc, 0, 0, w, h, bufhdc, x, y, SRCCOPY);
    BitBlt(bufhdc, 0, 0, w, h, hdc, x, y, SRCCOPY);

    SelectObject(bufhdc, Selectdump);
    SelectObject(hdc, old);
    ReleaseDC(NULL, bufhdc);
    DeleteDC(bufhdc);

}
void ValGFX::CopyToHBMP(HDC hdc, HBITMAP bmp, int x, int y, int w, int h) {
    if (w > width)w = width;
    if (h > height)h = height;
    if (!hbmp)Get_blank_buffer(w, h);

    HDC bufhdc = hdcDesktop;
    SelectObject(bufhdc, hbmp);
    HBITMAP old = (HBITMAP)SelectObject(hdc, bmp);
    BitBlt(hdc, x, y, w, h, bufhdc, 0, 0, SRCCOPY);


    SelectObject(bufhdc, Selectdump);
    SelectObject(hdc, old);
    ReleaseDC(NULL, bufhdc);
    DeleteDC(bufhdc);

}
void ValGFX::CopyToGFX(ValGFX& gfx, int x, int y) {
    HDC tempdc = CreateCompatibleDC(hdcDesktop);
    SelectObject(tempdc, gfx.hbmp);
    blt(tempdc, x, y);
    ReleaseDC(NULL, tempdc);
    DeleteDC(tempdc);

}
void ValGFX::transCopyToGFX(ValGFX& gfx, int x, int y) {
    HDC tempdc = CreateCompatibleDC(hdcDesktop);
    SelectObject(tempdc, gfx.hbmp);
    transblt(tempdc, x, y);
    ReleaseDC(NULL, tempdc);
    DeleteDC(tempdc);

}
/***************************************** buffer editing/drawing ********************************/

void ValGFX::editpixel(int x, int y, COLORREF rgb) {
    char* hold = buf_at_xy(x, y);
    *hold = GetGValue(rgb); hold++;
    *hold = GetBValue(rgb); hold++;
    *hold = GetRValue(rgb); hold++;
}
void ValGFX::makewhite(int alpha = 0) {
    BYTE* bytes = (BYTE*)bits;
    int plc = 0;
    for (int n = 0; n < height; n++) {
        for (int i = 0; i < width; i++) {
            *bytes = 255; bytes++;
            *bytes = 255; bytes++;
            *bytes = 255; bytes++;
            *bytes = alpha; bytes++;
        }
    }
}
void ValGFX::makeblack(int alpha = 0) {
    BYTE* bytes = (BYTE*)bits;
    int plc = 0;
    for (int n = 0; n < height; n++) {
        for (int i = 0; i < width; i++) {
            *bytes = 0; bytes++;
            *bytes = 0; bytes++;
            *bytes = 0; bytes++;
            *bytes = alpha; bytes++;
        }
    }
}
void ValGFX::makecolor(VRGB color,int alpha = 0) {
    BYTE* bytes = (BYTE*)bits;
    BYTE r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);
    int plc = 0;
    for (int n = 0; n < height; n++) {
        for (int i = 0; i < width; i++) {
            *bytes = b; bytes++;
            *bytes = g; bytes++;
            *bytes = r; bytes++;
            *bytes = alpha; bytes++;
        }
    }
}
void ValGFX::color_section(int x, int y, int w, int h,VRGB color, int alpha = 0) {
    char* bytes = bits;
    bytes += ((y * width) + x) * 4;
    int nlen = y + h, ilen = x + w;
    BYTE r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);
    for (int n = y; n < nlen && n < height; n++) {
        for (int i = x; i < ilen && i < width; i++) {
            *bytes = b; bytes++;
            *bytes = g; bytes++;
            *bytes = r; bytes++;

            *bytes = alpha; bytes++;
        }
        bytes += (width - w) * 4;
    }
}
/*********************************alpha block***************************************************/
/******************** all functions considered untested or have known bugs*************************/

void ValGFX::clip_hbmp(HBITMAP& h) {
    CopyfromHBMP(hdcDesktop,h,0,0,width,height);

}
void ValGFX::draw_boarder2(int wide = 2, int offset = 1, VRGB color = (VRGB)255) {
/*    cout << 1;
    drawline2(offset, offset, height - ((offset)), false, wide, color);
    cout << 1;
    drawline2(offset, offset, width - (offset ), true, wide, color);
    cout << 1;
    drawline2(width - (offset + wide), offset, (height - (offset + 2)), false, wide, color);
    cout << 1;
    drawline2(width - (offset + 1), height - (offset + wide),(width - (offset )) * -1, true, wide, color);
    */
    draw_box2(0, 0, width - wide, height - wide, wide, offset, color);
}
void ValGFX::draw_boarder(int wide = 2, int offset = 1, VRGB color = (VRGB)255 ) {
    drawline(0, 0, height - 2, false, wide, color);
    drawline(0, 0, width - 2, true, wide, color);
    drawline(width - 1, 0, (height - 2), false, wide, color);
    drawline(width - 1, height - 1, (width - 2)*-1, true, wide, color);
}
void ValGFX::draw_box(int x, int y, int xx, int yy, int wide = 2, int offset = 1, VRGB color = (VRGB)255) {
    int wi = (abs(xx - x)), hi = (abs(yy - y));

    drawline(x, y, wi, true, wide, color);
    drawline(x, y, hi, false, wide, color);
    drawline(x, yy, wi, true, wide, color);
    drawline(xx, y, hi, false, wide, color);
}

#define VC_setpix(h,r,g,b) *h=b;h++;*h=g;h++;*h=r;h+=2;
void ValGFX::drawline(int x, int y, int xy, bool horizontal, int wide, VRGB color) {
    BYTE r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);
    if (xy < 0) {
        if (horizontal)x += xy;
        else y += xy;
        xy = abs(xy);
    }
    
    short holdpjump = (wide / 2) * 4;
    char* hold = buf_at_xy(x, y), *holdp;
    for (int i = 0; i < xy; i++) {
        holdp = hold;// -holdpjump;
        for (int n = 0; n < wide; n++) {
            VC_setpix(holdp, r, g, b);
            holdp += (horizontal ? 0: width  ) * 4;
        }
        hold += (horizontal ? 1 : width ) *4;
    }
}
void ValGFX::draw_box2(int x, int y, int xx, int yy, int wide = 2, int offset = 1, VRGB color = (VRGB)255) {
    int t;
    if (x > xx) { t = x; x = xx; xx = t; }
    if (y > yy) { t = y; y = yy; yy = t; }

    int wi = (abs(xx - x)), hi = (abs(yy - y));

    drawline2(x, y, wi, true, wide, color);
    drawline2(x, y, hi, false, wide, color);
    drawline2(x, yy, wi+wide, true, wide, color);
    drawline2(xx, y, hi, false, wide, color);


}
void ValGFX::draw_box3(int x, int y, int xx, int yy, int wide = 2, int offset = 1, VRGB color = (VRGB)255) {
    int t;
    if (x > xx) { t = x; x = xx; xx = t; }
    if (y > yy) { t = y; y = yy; yy = t; }

    int wi = (abs(xx - x)), hi = (abs(yy - y));

    drawline2(x, y, wi-wide, true, wide, color);
    drawline2(x, y+wide, hi-wide, false, wide, color);
    drawline2(x+wide, yy-wide, wi-wide , true, wide, color);
    drawline2(xx-wide, y, hi, false, wide, color);


}

void ValGFX::draw_square(int x, int y, int xx, int yy, VRGB color = (VRGB)255) {
    color_section(x, y, xx - x, yy - y, color);
}
void ValGFX::drawline2(int x, int y, int xy, bool horizontal, int wide, VRGB color) {
    BYTE r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);
    if (xy < 0) {
        if (horizontal)x += xy;
        else y += xy;
        xy = abs(xy);
    }

    short holdpjump = (wide / 2) * 4;
    char* hold = buf_at_xy(x, y), * holdp;
    for (int i = 0; i < xy; i++) {
        holdp = hold;// -holdpjump;
        for (int n = 0; n < wide; n++) {
            VC_setpix(holdp, r, g, b);
            holdp += (horizontal ? width-1 : 0) * 4;
        }
        hold += (horizontal ? 1 : width) * 4;
    }
}
void ValGFX::buf__drawslopex(int x, int y, int ydir, double a, int itt, VRGB clr = (VRGB)VRGB_RED) { // ydir can be -1|1 
    double vl = 0, len = 0, vll = 0;
    int nx;
    for (int i = 0; i <= itt; i++) {
        len = abs(vl) - abs(vll);
        for (int n = 0; n < len; n++) {
            nx = n;
            if (a < 0)nx *= -1;
            editpixel(floor(vll) + x + nx, y,clr);
        }
        y += ydir;
        vll = vl;
        vl += a;
    }
}
void ValGFX::buf__drawslopey(int x, int y, int xdir, double a, int itt, VRGB clr = (VRGB)VRGB_RED) { // ydir can be -1|1 	 	
    double vl = 0, len = 0, vll = 0;
    int nx;
    for (int i = 0; i <= itt; i++) {
        len = abs(vl) - abs(vll);
        for (int n = 0; n < len; n++) {
            nx = n;
            if (a < 0)nx *= -1;
            editpixel(x, floor(vll) + y + nx,clr);
        }
        x += xdir;
        vll = vl;
        vl += a;
    }
}

void ValGFX::drawline_slope(int x, int y, int xx, int yy, int width,VRGB clr = (VRGB)VRGB_RED) {
    //cout << "drawing slope for x,y,xx,yy: " << x<<":"<< y<<":"<< xx<<":"<< yy<<endl;
    int wide = width / 2;
    if (x == xx) {
        drawline(x, y, yy - y, false, wide,clr);
        return;
    }
    if (y == yy) {
        drawline(x, y, xx - x, true, wide,clr);
        return;
    }
    long double xxx = abs(xx - x);
    long double yyy = (yy - y) / xxx;  // yslope (y per x)
    if (abs(yyy) >= 1) {
        //cout << "drawing slopey " <<xxx << ":"<<yyy<<endl;
        buf__drawslopey(x, y, (xx - x > -1 ? 1 : -1), yyy, xxx,clr);
        for (int i = 0; i < wide; i++) {
            buf__drawslopey(x + i, y, (xx - x > -1 ? 1 : -1), yyy, xxx,clr);
            buf__drawslopey(x - i, y, (xx - x > -1 ? 1 : -1), yyy, xxx,clr);
        }
        return;
    }
    else {
        yyy = abs(yy - y);
        xxx = (xx - x) / yyy;
        //cout << "drawing slopex " <<xxx << ":"<<yyy<<endl;
        buf__drawslopex(x, y, (yy - y > -1 ? 1 : -1), xxx, yyy,clr);
        for (int i = 0; i < wide; i++) {
            buf__drawslopex(x, y + i, (yy - y > -1 ? 1 : -1), xxx, yyy,clr);
            buf__drawslopex(x, y - i, (yy - y > -1 ? 1 : -1), xxx, yyy,clr);
        }
    }
}
void ValGFX::drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width) {
    drawline_slope(x, y, xx, yy, width);
    drawline_slope(x, y, xxx, yyy, width);
    drawline_slope(xxx, yyy, xx, yy, width);

}
void ValGFX::drawtriangle(int x, int y, int xx, int yy, int xxx, int yyy, int width,VRGB color) {
    drawline_slope(x, y, xx, yy, width,color);
    drawline_slope(x, y, xxx, yyy, width, color);
    drawline_slope(xxx, yyy, xx, yy, width, color);

}
int circle_getyfromXR(double x, int r, bool& f) {
    double xx = x * x;
    double rr = r * r;
    xx = rr - xx;

    if (xx < 0) {
        f = false;
        return -1;
    }
    f = true;
    if (xx == 0)return 0;
    //if(xx<2)return 1;
    return sqrt(xx);
}
void ValGFX::draw_circle(int xcenter, int ycenter, int radius, int xmin, int xmax, int ymin, int ymax, int width, VRGB clr = (VRGB)VRGB_RED) {
    width /= 3;
    bool flag = false;
    int xcp = 0, ycp = 0, xcm = 0, ycm = 0, rtest = radius - (sqrt(radius));
    float sway = .5;
    for (double i = 0; i <= radius; i += sway) {
        if (i == rtest)sway = .02;
        //if(i==radius-1)sway=.01;
        int y = circle_getyfromXR(i, radius, flag);
        if (!flag)continue;
        xcp = xcenter + i;
        ycp = ycenter + y;
        xcm = xcenter - i;
        ycm = ycenter - y;
        for (int w = width * -1; w < width; w++) {
            // +/- plane
            editpixel(xcp + w, ycp, clr);
            editpixel(xcp, ycp + w, clr);

            // +/+ plane
            editpixel(xcp + w, ycm, clr);
            editpixel(xcp, ycm + w, clr);

            // -/- plane:
            editpixel(xcm + w, ycp, clr);
            editpixel(xcm, ycp + w, clr);

            // -/+ plane:
            editpixel(xcm + w, ycm, clr);
            editpixel(xcm, ycm + w, clr);
        }
    }
}
 // should make a 2nd version of this that skips copy pixels that aren't 'background' colored.
//for speed and  asthetics 
void ValGFX::blurtocopy() {  // very very very simple antialiasing/blurring 
    copy_buf();
    int widt = (width) * 4;
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + (widt +4);

    //char val;
    char* back = hold - 4;
    char* forward = hold + 4;
    char* above = hold - widt;
    char* below = hold + widt;
    char* uplef = (hold - widt) - 4;
    char* uprig = (hold - widt) + 4;
    char* dnlef = (hold + widt) - 4;
    char* dnrig = (hold + widt) + 4;
    short r, g, b;  // can probably be bytes
    for (int i = 1; i < height-2; i++) {
        for (int n = 1; n < width-2; n++) {
            /*b = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            g = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            r = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            */
            b = *back;b+= *forward + *above + *below;
            back++; forward++; above++; below++;
            g = *back; g += *forward + *above + *below;
            back++; forward++; above++; below++;
            r = *back; r += *forward + *above + *below;
            back++; forward++; above++; below++;
            b /= 3; g /= 3; r /= 3;
            b += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 16;
            uplef++; uprig++; dnlef++; dnrig++;
            g += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 16;
            uplef++; uprig++; dnlef++; dnrig++;
            r += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 16;
            uplef++; uprig++; dnlef++; dnrig++;

            b += *hold *21; hold++;
            g += *hold *21; hold++;
            r += *hold *21; hold++;
            b /= 20; g /= 20; r /= 20;
            *place = (BYTE)b; place++;
            *place = (BYTE)g; place++;
            *place = (BYTE)r; place++;
            place++; hold++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++; // pass alpha
        }
        uplef += 12; uprig += 12; dnlef += 12; dnrig += 12; back += 12; forward += 12; above += 12; below += 12;
        place += 12; hold += 12; // += 3 pixels to skip boarders and misaligned boxes.

    }
    //will have to call pastebuf to get result
}
void ValGFX::blurtocopy2() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    BYTE v;
    short hh = (height - 2) ;
    short ww = (width - 2) * 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 8);
            //v += ((*hold) < 64 ? 1 : 0);
            //v += ((*hold) % 8 || (*hold) < 32 ? 1 : 0);
            *place += ((*hold) / 8);
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (width*4)) += v;
            *(place + (width *4)) += v;

            *(place - ((width * 4) + 4)) += v;
            *(place - ((width * 4) - 4)) += v;
            *(place + ((width * 4) + 4)) += v;
            *(place + ((width * 4) - 4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy3() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    BYTE v;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 8);
            v += ((*hold) < 64 ? 1 : 0);
            v += ((*hold) % 8 || (*hold) < 32 ? 1 : 0);
            *place += ((*hold) / 8);
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (width * 4)) += v;
            *(place + (width * 4)) += v;

            *(place - ((width * 4) + 4)) += v;
            *(place - ((width * 4) - 4)) += v;
            *(place + ((width * 4) + 4)) += v;
            *(place + ((width * 4) - 4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy4() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    BYTE v;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 8);
            v -= ((*hold) < 64 ? 1 : 0);
            v -= ((*hold) % 8 || (*hold) < 32 ? 1 : -1);
            *place += ((*hold) / 8);
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (width * 4)) += v;
            *(place + (width * 4)) += v;

            *(place - ((width * 4) + 4)) += v;
            *(place - ((width * 4) - 4)) += v;
            *(place + ((width * 4) + 4)) += v;
            *(place + ((width * 4) - 4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy5() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    short v;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 15);
            v -= ((*hold) < 64 ? 1 : 0);
            v += ((*hold) % 8 || (*hold) < 32 ? 1 : -1);
            v += ((*hold) % 4 ? 1 : 0);
            *place += ((*hold) / 16);
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (width * 4)) += v;
            *(place + (width * 4)) += v;

            *(place - ((width * 4) + 4)) += v;
            *(place - ((width * 4) - 4)) += v;
            *(place + ((width * 4) + 4)) += v;
            *(place + ((width * 4) - 4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy6() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    short v;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    short wf = width * 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 6);//+ ((*hold) % 8);
            //v -= ((*hold) < 64 ? 1 : 0);
            //v += ((*hold) % 8 || (*hold) < 32 ? 1 : -1);
            //v += (((*hold) % 16) - 3 > 3 ? 1 : 0);
            *place += ((*hold) / 9)-1;
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (wf)) += v;
            *(place + (wf)) += v;
            v /= 2;
            *(place - ((wf) + 4)) += v;
            *(place - ((wf) - 4)) += v;
            *(place + ((wf) + 4)) += v;
            *(place + ((wf) - 4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy7() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + ((width + 1) * 4);
    short v,t;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    short wf = width * 4;
    int maths;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 24);//+ ((*hold) % 8);
            //v -= ((*hold) < 64 ? 1 : 0);
            v += ((*hold) % 24? 1 : 0);
            
            //v += (((*hold) % 16) - 3 > 3 ? 1 : 0);
            t = (((float)(*hold) / 4.0) * 3);
            maths = (int)(*hold) * 10000;
            maths /= 12308;
            if (maths > 0)maths -= 1;
            //if (t == 0)t++;
            *place += t -1;
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (wf)) += v;
            *(place + (wf)) += v;
            v /= 2;
            *(place - ((wf)+4)) += v;
            *(place - ((wf)-4)) += v;
            *(place + ((wf)+4)) += v;
            *(place + ((wf)-4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy9() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    BYTE* hold = (BYTE*)buf_at_xy(1, 1);
    BYTE* place = (BYTE*)copybuf + ((width + 1) * 4);
    short v, t;
    short hh = (height - 2);
    short ww = (width - 2) * 4;
    short wf = width * 4;
    int maths;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //cout << "i:" << i << " n:" << n << "         \r";
            v = ((*hold) / 32);//+ ((*hold) % 8);
            //v -= ((*hold) < 64 ? 1 : 0);
            v += ((*hold) % 32 ? 1 : 0);

            //v += (((*hold) % 16) - 3 > 3 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            maths = (int)(*hold) * 10000;
            maths /= 12308;
            if (maths > 0)maths -= 1;
            if (t == 0)t++;
            *place += t - 1;
            *(place - 4) += v;
            *(place + 4) += v;
            *(place - (wf)) += v;
            *(place + (wf)) += v;
            v /= 2;
            *(place - ((wf)+4)) += v;
            *(place - ((wf)-4)) += v;
            *(place + ((wf)+4)) += v;
            *(place + ((wf)-4)) += v;
            hold++; place++;
        }
        //hold += 4; place += 4;
    }
}
void ValGFX::blurtocopy8() {  // very very very simple antialiasing/blurring 

    copy_buf();
    int widt = (width) * 4;
    BYTE* hold = (BYTE*)buf_at_xy(1, 1);
    BYTE* place = (BYTE*)(copybuf + (widt + 4));

    //char val;
    BYTE* back = hold - 4;
    BYTE* forward = hold + 4;
    BYTE* above = hold - widt;
    BYTE* below = hold + widt;
    BYTE* uplef = (hold - widt) - 4;
    BYTE* uprig = (hold - widt) + 4;
    BYTE* dnlef = (hold + widt) - 4;
    BYTE* dnrig = (hold + widt) + 4;
    unsigned int r, g, b;  // can probably be bytes
    for (int i = 1; i < height - 3; i++) {
        for (int n = 1; n < width - 1; n++) {
            /*b = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            g = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            r = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            */
            b = 0;
            b += *back; b += *forward; b += *above; b += *below;
            back++; forward++; above++; below++;
            g = 0;
            g += *back; g += *forward; g += *above; g += *below;
            back++; forward++; above++; below++;
            r = 0;
            r += *back; r += *forward; r += *above; r += *below;
            back++; forward++; above++; below++;
            //b /= 128; g /= 128; r /= 128;
            b /= 31; g /= 31; r /= 31;
            b += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 65;
            uplef++; uprig++; dnlef++; dnrig++;
            g += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 65;
            uplef++; uprig++; dnlef++; dnrig++;
            r += ((short)(*uplef + *uprig) + (short)(*dnlef + *dnrig)) / 65;
            uplef++; uprig++; dnlef++; dnrig++;
            //if (b > 46)cout << "b overflow2 " << b << endl;
            //if (g > 46)cout << "g overflow2 " << g << endl;
            //if (r > 46)cout << "r overflow2 " << r << endl;
            b += ((((int)*hold) * 10001)/12308); hold++;
            g += ((((int)*hold) * 10001) / 12308); hold++;
            r += ((((int)*hold) * 10001) / 12308); hold++;
            //if (b > 255)cout << "b overflow " << b << endl;
            //if (g > 255)cout << "g overflow " << g << endl;
            //if (r > 255)cout << "r overflow " << r << endl;
            //b /= 20; g /= 20; r /= 20;
            *place = (BYTE)b; place++;
            *place = (BYTE)g; place++;
            *place = (BYTE)r; place++;
            place++; hold++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++; // pass alpha
        }
        uplef += 8; uprig += 8; dnlef += 8; dnrig += 8; back += 8; forward += 8; above += 8; below += 8;
        place += 8; hold += 8; // += 3 pixels to skip boarders and misaligned boxes.

    }
    //will have to call pastebuf to get result
}

void ValGFX::blurtocopy10() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    BYTE* hold = (BYTE*)buf_at_xy(1, 1);
    BYTE* place = (BYTE*)copybuf + ((width + 1) * 4);
    short v, t;
    short hh = (height - 2);
    short ww = (width - 2) ;
    short widt = width * 4;
    BYTE* back = hold - 4;
    BYTE* forward = hold + 4;
    BYTE* above = hold - widt;
    BYTE* below = hold + widt;
    BYTE* uplef = (hold - widt) - 4;
    BYTE* uprig = (hold - widt) + 4;
    BYTE* dnlef = (hold + widt) - 4;
    BYTE* dnrig = (hold + widt) + 4;
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //b             
            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back+= v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            uplef += v;
            uprig += v;
            dnlef += v;
            dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            //g
            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back += v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            uplef += v;
            uprig += v;
            dnlef += v;
            dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            //r
            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back += v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            uplef += v;
            uprig += v;
            dnlef += v;
            dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            //a
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;

        }
        //hold += 4; place += 4;
        uplef += 8; uprig += 8; dnlef += 8; dnrig += 8; back += 8; forward += 8; above += 8; below += 8;
        place += 8; hold += 8;
    }
}
void ValGFX::blurtocopy11() {
    //copy_buf();
    ZeroMemory(copybuf, width * height * 4);
    BYTE* hold = (BYTE*)buf_at_xy(1, 1);
    BYTE* place = (BYTE*)(copybuf + ((width + 1) * 4));
    short v, t;
    short hh = (height - 2);
    short ww = (width - 3);
    short widt = width * 4;
    BYTE* back = place - 4;
    BYTE* forward = hold + 4;
    BYTE* above = place - widt;
    BYTE* below = place + widt;
    BYTE* uplef = (place - widt) - 4;
    BYTE* uprig = (place - widt) + 4;
    BYTE* dnlef = (hold + widt) - 4;
    BYTE* dnrig = (place + widt) + 4;
    //ww *= 4;
#define skip 16
    for (int i = 1; i < hh; i++) {
        for (int n = 1; n < ww; n++) {
            //b             
            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back += v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            *uplef += v;
            *uprig += v;
            *dnlef += v;
            *dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back += v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            *uplef += v;
            *uprig += v;
            *dnlef += v;
            *dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;

            v = ((*hold) / 32);//+ ((*hold) % 8);
            v += ((*hold) % 32 ? 1 : 0);
            t = (((float)(*hold) / 5.05) * 4);
            if (t == 0)t++;
            *place += t - 1;
            *back += v;
            *forward += v;
            *above += v;
            *below += v;
            v /= 2;
            *uplef += v;
            *uprig += v;
            *dnlef += v;
            *dnrig += v;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            hold++; place++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;


        }
        //hold += 4; place += 4;
        uplef += skip; uprig += skip; dnlef += skip; dnrig += skip; back += skip; forward += skip; above += skip; below += skip;
        place += skip; hold += skip;
        //uplef += 8; uprig += 8; dnlef += 8; dnrig += 8; back += 8; forward += 8; above += 8; below += 8;
        //place += 8; hold += 8;
    }
}
#undef skip 
// proof of concept optioned blur/aliasing system.  needs testing. can be done with far fewer vars and some math
/*
void ValGFX::blurtocopyex(BYTE cweight=1, BYTE sweight=2, BYTE eweight=3, bool bo) {  // very very very simple antialiasing/blurring 
    // prob going to scrap for different version with hold filling work array any copying back to copybuf where copybuf is bkrnd
    copy_buf();
    char* hold = buf_at_xy(1, 1);
    char* place = copybuf + (width + 1);

    char val;
    char* back = hold - 4;
    char* forward = hold + 4;
    char* above = hold - width;
    char* below = hold + width;
    char* uplef = (hold - width) - 4;
    char* uprig = (hold - width) + 4;
    char* dnlef = (hold + width) - 4;
    char* dnrig = (hold + width) + 4;
    short r, g, b;  // can probably be bytes
    for (int i = 1; i < height - 2; i++) {
        for (int n = 1; n < width - 2; n++) {
            if (bo && VRGB(*place) != RGB(0, 0, 0))continue;// sketchy cast from char* array to colorref. check for errors.
            b = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            g = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            r = ((*uplef + *uprig + *dnlef + *dnrig) / 12) + ((*back + *forward + *above + *below) / 6);
            uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++;
            b += *hold; hold++;
            g += *hold; hold++;
            r += *hold; hold++;
            b /= 2; g /= 2; r /= 2;
            *place = (BYTE)b; place++;
            *place = (BYTE)g; place++;
            *place = (BYTE)r; place++;
            place++; hold++; uplef++; uprig++; dnlef++; dnrig++; back++; forward++; above++; below++; // pass alpha
        }
        uplef += 12; uprig += 12; dnlef += 12; dnrig += 12; back += 12; forward += 12; above += 12; below += 12;
        place += 12; hold += 12; // += 3 pixels to skip boarders and misaligned boxes.

    }
    //will have to call pastebuf to get result
}
*/
