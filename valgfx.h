
#pragma once
#include <string>
using namespace std;
#include"valtextcontrol.h" 
#include<olectl.h>
#include<ole2.h>
#include <chrono>

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

#define mandel_factors_maxlen 1000;
#define foreach(a,b) for(int a=0; a < b; a++)

#define Mandelbrot_window_dims 2000
//this file needs serious refactoring, renaming, reducing.

/*#include<wincodec.h>
#include<wincodecsdk.h>
#pragma comment(lib,"Windowscodecs")
#pragma comment(lib,"Windowscodecssdk")

void codecSaveImage(char* FileName, int width, int height, BYTE* bt) {
    IWICImagingFactory* fact;
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&fact);// IID_PPV_ARGS(&fact));
    IWICBitmap* btc;
    HPALETTE hp;
    fact->CreateBitmapFromMemory(width, height, GUID_WICPixelFormat32bppBGRA, 0, width * height * 4, bt, &btc);
    //btc->CopyPixels(NULL, (UINT)width, (UINT)size, bt);
    IStream* s;
    

    HGLOBAL hG = GlobalAlloc(GPTR, size);
    memcpy(hG,bt,)
}


stolen from:
https://stackoverflow.com/questions/5511849/how-to-save-hbitmap-as-jpg-using-win32-imaging-api-windows-mobile-6
OLE2 image save to file for png,bmp,gif,jpg. 
HRESULT Imaging_SaveToFile(HBITMAP handle, LPTSTR filename, LPCTSTR format){
HRESULT res;

res = CoInitializeEx(NULL, COINIT_MULTITHREADED);
if ((res == S_OK) || (res == S_FALSE)) {
    IImagingFactory* factory=NULL;
    if (CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IImagingFactory, (void**)&factory) == S_OK) {
        UINT count;
        ImageCodecInfo* imageCodecInfo=NULL;
        if (factory->GetInstalledEncoders(&count, &imageCodecInfo) == S_OK) {
            // Get the particular encoder to use
            LPTSTR formatString;
            if (wcscmp(format, L"png") == 0) {
                formatString = _T("image/png");
            } else if (wcscmp(format, L"jpg") == 0) {
                formatString = _T("image/jpeg");
            } else if (wcscmp(format, L"gif") == 0) {
                formatString = _T("image/gif");
            } else if (wcscmp(format, L"bmp") == 0) {
                formatString = _T("image/bmp");
            } else {
                CoUninitialize();
                return S_FALSE;
            }
            CLSID encoderClassId;
            if (count == 0) {
                CoUninitialize();
                return S_FALSE;
            }
            for(int i=0; i < (int)count; i++) {
                if (wcscmp(imageCodecInfo[i].MimeType, formatString) == 0) {
                    encoderClassId= imageCodecInfo[i].Clsid;
                    free(imageCodecInfo);
                    break;
                } else {
                    continue;
                }
                CoUninitialize();
                return S_FALSE;
            }
            IImageEncoder* imageEncoder=NULL;
            if (factory->CreateImageEncoderToFile(&encoderClassId, filename, &imageEncoder) == S_OK) {
                IImageSink* imageSink = NULL;
                res = imageEncoder->GetEncodeSink(&imageSink);

                if (res != S_OK) {
                    CoUninitialize();
                    return res;
                }

                BITMAP bm;
                GetObject (handle, sizeof(BITMAP), &bm);
                PixelFormatID pixelFormat;
                switch (bm.bmBitsPixel) {
                    case 1: {
                        pixelFormat = PixelFormat1bppIndexed;
                        break;
                    }
                    case 4: {
                        pixelFormat = PixelFormat4bppIndexed;
                        break;
                    }
                    case 8: {
                        pixelFormat = PixelFormat8bppIndexed;
                        break;
                    }
                    case 24: {
                        pixelFormat = PixelFormat24bppRGB;
                        break;
                    }
                    default: {
                        pixelFormat = PixelFormat32bppARGB;
                        break;
                    }
                }

                BitmapData* bmData = new BitmapData();
                bmData->Height = bm.bmHeight;
                bmData->Width = bm.bmWidth;
                bmData->Scan0 = bm.bmBits;
                bmData->PixelFormat = pixelFormat;

                UINT bitsPerLine = bm.bmWidth * bm.bmBitsPixel;
                UINT bitAlignment = sizeof(LONG) * 8;
                UINT bitStride = bitAlignment * (bitsPerLine / bitAlignment);   // The image buffer is always padded to LONG boundaries
                if ((bitsPerLine % bitAlignment) != 0) bitStride += bitAlignment; // Add a bit more for the leftover values
                bmData->Stride = (bitStride / 8);

                IBitmapImage* pBitmap;
                factory->CreateBitmapFromBuffer(bmData, &pBitmap);
                IImage* pImage;
                pBitmap->QueryInterface(IID_IImage, (void**)&pImage);
                res = pImage->PushIntoSink(imageSink);
                if (res != S_OK) {
                    CoUninitialize();
                    return res;
                }

                pBitmap->Release();
                pImage->Release();
                imageSink->Release();
                imageEncoder->TerminateEncoder();
                imageEncoder->Release();
            }
        }
    }
    CoUninitialize();
} else {
    return res;
}

return res;
}
*/
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
int Linear_color(int its, int maxits) {
    // attempt to colorize mandelbrot image, can be more generalized to a int-> rainbow system 
    // maxits is your total color space from re->green->blue->pink
    // its is a relative (arbitrary, linear) place in that color space. 
    //1530 different outputs possible when maxints is multiple of 3060
    if (its == maxits)return 0;// 16777215; // white
    if (G_Mandel_colorizer_type == 3)return Linear_greyscale(its, maxits);
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
#define vabs(a) (a<0?a*-1.0:a)

void VS_complex_div(double a, double b, double c, double d, double& rr, double& ii) {
    double h = ((c * c) + (d * d));
    if (h == 0) {
        cout << "complex division by zero, returning 0 error\n";
        rr = 0; ii = 0; return;
    }
    rr = ((a * c) + (b * d)) / h;
    ii = ((b * c) - (a * d)) / h;
}

void VS_complex_mul(double a, double b, double c, double d, double& rr, double& ii) {
    rr = (a * c) - (b * d);
    ii = (b * c) + (a * d);
}

void VS_complex_sin(double& r, double& i) {
    //sin(z) = sin(x + iy) = sin(x)cosh(y) + isinh(y)cos(x) https://math.stackexchange.com/questions/2738852/coding-the-complex-exp-sin-and-cos-function
    double rr = sin(r) * cosh(i);
    double ii = sinh(i) * cos(r);
    r = rr;
    i = ii;
}
void VS_complex_cos(double& r, double& i) {
    double rr = cos(r) * cosh(i);
    double ii = sinh(i) * sin(r);
    r = rr;
    i = ii;
}
void VS_complex_tan(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_sin(a, b);
    VS_complex_cos(c, d);
    VS_complex_div(a, b, c, d, r, i);
}
void VS_complex_square(double& r, double& i) {
    double rr = r*r;
    double ii = i*i;
    i = (2*r*i);
    r = (rr-ii);
}
void VS_complex_exp(double a, double b, int e, double& rr, double& ii) {
    rr = a; ii = b;
    double cc, ccc;
    if (e == 2) {   
        VS_complex_square( rr, ii);
        return;
    }
    for (int i = 2; i <= e; i++) {
        VS_complex_mul(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_E_Exponent(double x, double y, double& rx, double& ry) {
    double ex = exp(x);
    rx = ex * cos(y);
    ry = ex * sin(y);
}

void VS_complex_R_Exponent(double r, double x, double y, double& rx, double& ry) {
    r = vabs(r); // r cannot be negative or 0 technically.
    double a = log(r);
    double ex = pow(r,x);
    rx = ex * cos(a*y);
    ry = ex * sin(a*y);

}
bool VS_complex_rangecomp(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs((xx - x)) < swing && vabs((yy - y)) < swing);

}
bool VS_complex_rangecompw2(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs(xx - x) < swing && vabs(yy - y) < swing);

}
bool VS_complex_rangecompw(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs(x - xx) < swing && vabs(y - yy) < swing);

}
void VS_complex_mulLD(long double a, long  double b, long  double c, long  double d, long  double& rr, long  double& ii) {
    rr = (a * c) - (b * d);
    ii = (b * c) + (a * d);
}
void VS_complex_squareLD(long double& r, long  double& i) {
    long double rr = r * r;
    long double ii = i * i;
    i = (2 * r * i);
    r = (rr - ii);
}
void VS_complex_expLD(long double a, long  double b, int e, long  double& rr, long  double& ii) {
    rr = a; ii = b;
    long double cc, ccc;
    if (e == 2) {
        VS_complex_squareLD(rr, ii);
        return;
    }
    for (int i = 2; i <= e; i++) {
        VS_complex_mulLD(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_exp_dumb(double a, double b, int e, double& rr, double& ii) {
    rr = a; ii = b;
    double cc, ccc;
    while (e != 1) {
        e--;
        VS_complex_mul(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_bigexp(double a, double b, int e, double& rr, double& ii) {
    double hr=a, hi=b;
    while (e != 1) {
        while (e % 2 == 0) {
            e /= 2;
            VS_complex_square(a, b);
        }
        if (e == 1)break;
        VS_complex_mul(hr, hi, a, b, hr, hi);
        e -= 1;
    }
    VS_complex_mul(hr, hi, a, b, rr, ii);
    //while (exp.comp(BWONE) != 0) {

    //    while (exp.mod2() == 0) {
    //        exp = exp.half();
    //        hold = hold.squared();
    //        //hold2=hold2.mulbeta2(this);
    //    }
    //    if (exp.comp(BWONE) == 0)break;
    //    hold3 = hold3.mulbeta2(hold);
    //    exp.minus1();

    //}
    //return hold.mulbeta2(hold3);//.mulbeta2(hold2);
}

void VS_complex_cotan(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_cos(a, b);
    VS_complex_sin(c, d);
    VS_complex_div(a, b, c, d, r, i);
}
void VS_complex_divwrong(double a, double b, double c, double d, double& rr, double& ii) {
    double h = ((c * c) + (d * d));
    if (h == 0) {
        rr = 0; ii = 0; return;
    }
    rr = a * c + b * d / h;
    ii = b * c - a * d / h;
}
void VS_complex_tanwrong(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_sin(a, b);
    VS_complex_cos(c, d);
    VS_complex_divwrong(a, b, c, d, r, i);
}
void VS_complex_cotanwrong(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_cos(a, b);
    VS_complex_sin(c, d);
    VS_complex_divwrong(a, b, c, d, r, i);
}
void VS_COMPLEX_Sqrt(long double& xr, long double& ir) {
    long double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    long double xs = x * x, is = i * i;
    long double zabsz = sqrt(xs + is);
    long double r = sqrt((zabsz + x) / 2);
    long double ii = sqrt((zabsz - x) / 2);
    if (i < 0)ii *= -1;
    xr = r;
    ir = ii;
}
void VS_COMPLEX_Sqrt(double& xr,double& ir) {
    double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    double xs = x * x, is = i * i;
    double zabsz = sqrt(xs + is);
    double r = sqrt((zabsz + x) / 2);
    double ii = sqrt((zabsz - x) / 2);
    if (i < 0)ii *= -1;
    xr = r;
    ir = ii;
}
int VS_COMPLEX_SqrtSafe2(long double& xr, long double& ir) {
    long double h = xr, hh = ir;
    long double xrd, ird;
    VS_COMPLEX_Sqrt(h, hh);
    long double xh = h, ih = hh;
    long double t = h, tt = hh;
    xrd = h; ird = hh;
    for (int i = -6; i < 6; i++) {

        for (int n = -30; n < 30; n++) {
            t = h + (.00000000000000001 * i);
            tt = hh + (.00000000000000001 * n);
            xrd = t; ird = tt;
            VS_complex_squareLD(t, tt);
            if (t == xr && tt == ir) {
                xr = xrd; ir = ird;
                return i + 7;
            }
        }
    }
    xr = xh;
    ir = ih;
    return 0;
}
/******************************************end VS_COMPLEX math block*************************************************************/
/******************************************Start ANDRO newton system*************************************************************/

void newton_derbail_itteratemf(double x, double y, int* factors, int factorslen, double& rx, double& ry) {
    if (x == 0 && y == 0)return;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int xe, xf;
    double xntot = 0, yntot = 0, xdtot = 0, ydtot = 0;
    bool neg = false;
    bool needsconstnegone = true;
    // loop through factorslen, factors[x*2]=xf [+1]=xe
    foreach(i, factorslen) {
        xf = factors[i * 3];
        xe = factors[(i * 3) + 1];
        neg = factors[(i * 3) + 2] == 1;
        if (xe == 0) {
            if (!neg)xntot += xf;
            else xntot -= xf;
            needsconstnegone = false;
            continue;
        }
        if (xe == -1) { // negative xe means const i
            if (!neg)yntot += xf;
            else yntot -= xf;
            continue;
        }
        VS_complex_exp(zx, zy, xe, zxcopy, zycopy);
        zxcopy *= xf;
        //zxcopy -= 1;
        if (!neg) {
            xntot += zxcopy;
            yntot += zycopy;
        }
        else {
            xntot -= zxcopy;
            yntot -= zycopy;
        }
        VS_complex_exp(zx, zy, xe - 1, xx, yy);
        xx *= (xe - 1) * xf; // might need to change that.
        yy *= (xe - 1) * xf;
        if (!neg) {
            xdtot += xx;
            ydtot += yy;
        }
        else {
            xdtot -= xx;
            ydtot -= yy;
        }
    }
    if (needsconstnegone)xntot -= 1;// assumed ((qz^n, qqz^n-1...)(- 1)) constant
    VS_complex_div(xntot, yntot, xdtot, ydtot, xx, yy);

    rx = zx - xx;
    ry = zy - yy;

}
newton_fractal arbitrary_newton_derbail_root_process_mf(double x, double y, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);

        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.000000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 1;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int ANDRO_addtoarray(double x, double y, double* arr, int& len) {


    if (vabs(x) < .000000001)x = 0;
    if (vabs(y) < .000000001)y = 0;
    double* harr = arr;
    if (len > 1000) {
        cout << "len too long" << endl;
        pause();
    }
    foreach(i, len) {
        if (VS_complex_rangecomp(x, y, *harr, *(harr + 1), 0.00001))return i;
        if (*harr == x && *(harr + 1) == y)return i;
        harr += 2;
    }
    *harr = x;
    harr++;
    *harr = y;
    len++;
    return len;
}
int arbitrary_newton_derbail_roots_mf(int* factors, int factorslen, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    for (double n = -3.0; n < 3.0; n += .002) {
        val = arbitrary_newton_derbail_root_process_mf(n, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(0, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(n, 0, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);
        
        val = arbitrary_newton_derbail_root_process_mf(n, -n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(n, sin(n), factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(cos(n), n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}

newton_fractal arbitrary_newton_nova_derbail_root_process_mf(double x, double y, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);
        zxcopy += x;
        zxcopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 0;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int arbitrary_newton_nova_derbail_roots_mf(int* factors, int factorslen, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    cout << "into nova roots process\n";
    for (double n = -3.0; n < 3.0; n += .002) {
        val = arbitrary_newton_nova_derbail_root_process_mf(n, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(0, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, 0, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, -n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, sin(n), factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(cos(n), n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}
newton_fractal arbitrary_newton_julia_derbail_root_process_mf(double x, double y, double cx, double cy, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);
        zxcopy += cx;
        zxcopy += cy;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.0000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 1;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int arbitrary_newton_julia_derbail_roots_mf(int* factors, int factorslen, double cx, double cy, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    cout << "into julia roots process\n";
    for (double n = -3.0; n < 3.0; n += .001) {
        val = arbitrary_newton_julia_derbail_root_process_mf(n, n,cx,cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(0, n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, 0, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, -n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, sin(n), cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(cos(n), n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(cos(n), sin(n), cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}

string arbitrary_newton_derbail_roots_outputmf(int* factors, int factorslen, int maxits, double bail) {
    double arr[2000];
    foreach(i, 2000)arr[i] = 0.0;
    int arrlen = 0;
    arrlen = arbitrary_newton_derbail_roots_mf(factors, factorslen, maxits, bail, (double*)arr, arrlen);
    cout << arrlen << " roots detected\n";
    int a, b;
    foreach(i, arrlen) {
        a = arr[i * 2];
        b = arr[(i * 2) + 1];
        //if (vabs(a) < .000000001)a = 0;
        //if (vabs(b) < .000000001)b = 0;
        cout << "if(VS_complex_rangecomp(zxcopy, zycopy," << a << ", " << b << ", 0.00001))return ((its*its) % (spaces*3))+(spaces*" << ((i + 1) % 5) << "); \n";
    }

    return "done";
}

void ANDRO_factors_removeExp(int xe, int* factors, int& factorslen) {
    foreach(i, factorslen) {
        if (factors[(i * 3) + 1] == xe) {
            factorslen--;
            if (i == factorslen) return;
            factors[(i * 3)] = factors[(factorslen * 3)];
            factors[(i * 3) + 1] = factors[(factorslen * 3) + 1];
            factors[(i * 3) + 2] = factors[(factorslen * 3) + 2];
        }
    }

}

string ANDRO_factors_str(int* factors, int factorslen) {

    int xe, xf;
    bool neg = false;
    // loop through factorslen, factors[x*2]=xf [+1]=xe
    string ret = "F(x)=";
    foreach(i, factorslen) {
        xf = factors[i * 3];
        xe = factors[(i * 3) + 1];
        if (factors[(i * 3) + 2] == 1)ret += "-";
        else if (i != 0) ret += "+";
        if (xe == -1) ret += " (" + ctostr(xf) + "i) ";
        else if (xe == 0) ret += " (" + ctostr(xf) + ") ";
        else ret += " (" + (xf == 1 ? "" : ctostr(xf)) + "z^" + ctostr(xe) + ") ";
    }

    return ret;

}
string ANDRO_Equation() {
    return ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
string ANDROctostr(double a) {
    if (a == 1.0)return "1";
    if (vabs(a) < 0.0000001) return "0";
    char buff[25];
    sprintf(buff, "%2.6f", a);
    return string(buff);
}
string ANDRO_roots_str(double* roots, int rootslen) {
    string ret = "";
    foreach(i, rootslen) {
        ret += "(" + ANDROctostr(roots[i * 2]) + "," + ANDROctostr(roots[1 + (i * 2)]) + ") ";
        if (i != rootslen - 1)ret += ",";
    }
    return ret;
}
string ANDRO_Roots() {
    return ANDRO_roots_str(G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);

}
void ANDRO_factorlist_alter(int xf, int xe, bool neg, int* factors, int& factorslen) {
    int xff;
    foreach(i, factorslen) {
        xff = factors[i * 3];
        if (xe == factors[(i * 3) + 1]) {
            if (neg != (factors[(i * 3) + 2]==1 ) ) factors[i * 3] -= xf;
            else factors[i * 3] += xf;
            if (factors[i * 3] == 0)ANDRO_factors_removeExp(xe, factors, factorslen);
            return;
        }
    }
    factors[factorslen * 3] = xf;
    factors[(factorslen * 3) + 1] = xe;
    factors[(factorslen * 3) + 2] = (neg ? 1 : 0);
    factorslen++;
}

int calc_ANDRO(double x, double y, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy);

        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {
            
            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            
        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_nova(double x, double y, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novajulia(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy);
        zxcopy += cx;
        zycopy += cy;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}


int calc_mandle_julia_Euler(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}

int calc_mandle_julia_sqrt(double x, double y,double cx ,double cy, int maxits,int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy,3,zx,zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt(double x, double y, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt2(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 3, zx, zy);
        zx += cx;
        zy += cy;
        VS_COMPLEX_Sqrt(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt2(double x, double y, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 3, zx, zy);
        zx += x;
        zy += y;
        VS_COMPLEX_Sqrt(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt3(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt3(double x, double y, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt4(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt4(double x, double y, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt5(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
 
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt5(double x, double y, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
 
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler(double x, double y, int maxits, double bail=4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler2(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        VS_complex_E_Exponent(zx, zy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler3(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        VS_complex_E_Exponent(zx, zy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler4(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy,3,zx,zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler5(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx -= x;
        zy -= y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler6(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_tan(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler7(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_sin(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler8(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_cos(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler9(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_tanwrong(zx, zy); 
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler10(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
 
        VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_tanwrong(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler11(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler12(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double halfpi = 1.57079632679;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy*halfpi, zx, zy);
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler13(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double halfpi = 1.57079632679;
    while (its < maxits) {

        VS_complex_E_Exponent(zx , zy * halfpi*2, zx, zy);
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_derbail(double x, double y, int maxits = 1000,double bail=4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX=0, derbY=0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        if (vabs(derbX) + vabs(derbY) > bail)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_derbail2(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2*zx;
        derbY += 2*zy;
        if (vabs((derbX + derbY)) > bail)return its;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_derbail3(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        if (vabs((derbX + derbY)) > (vabs((zx+zy)))*(bail))return its;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_derbail4(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        if (vabs((derbX + derbY)) > (vabs(zxcopy) + vabs(zycopy)) * (bail))return its;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        its++;
    }
    return its;
}




int calc_mandle(double x, double y, int maxits = 1000) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong(double x, double y, int maxits = 1000) {
    // 3 arms of oddity
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        zy = (2 * zx * zy) + x;
        zx = (zxcopy - zycopy) + y;
        xh = zy;
        zy = zx;
        zx = xh;
        its++;
    }
    return its;
}
int calc_mandle_wrong2(double x, double y, int maxits = 1000) {
    // swiped mandelbrot set
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) + y;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx = (zxcopy - zycopy) - x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong3(double x, double y, int maxits = 1000) {
    // swiped mandelbrot set correct direction
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) - y;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx = (zxcopy - zycopy) + x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong4(double x, double y, int maxits = 1000) {
    // flatback with rainbow spirals
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) + zy;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx += (zxcopy - zycopy) - x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong5(double x, double y, int maxits = 1000) {
    //  Whoah!...  

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx + y;
        zycopy = zy * zy + x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) - y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) - x;
        its++;
    }
    return its;
}
int calc_mandle_wrong6(double x, double y, int maxits = 1000) {
    //  Whoah !...  but correct orientation

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx - y;
        zycopy = zy * zy - x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong7(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx + y;
        zycopy = zy * zy + x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong8(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 8.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zycopy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong9(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zx = (2 * zxcopy * zycopy) + y;
        //zx = zxcopy - zycopy + y;
        zy = (zx - zy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong10(double x, double y, int maxits = 1000) {
    //weird mandle-boodah triangle 128 itts shows the magic hands
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zx = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zy = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong11(double x, double y, int maxits = 1000) {
    //The fumkin mandelbrot-butterfly.  I found it.
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + (y * y / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x * x / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong12(double x, double y, int maxits = 1000) {
    //odd splitup
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) - (zy / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (zx / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong13(double x, double y, int maxits = 1000) {
    //starry claw2
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + (zy / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (zx / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong14(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x)-y;// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong15(double x, double y, int maxits = 1000) {
    int its = 1;
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        zy = (2 * zx * zy) + x;
        zx = (zxcopy - zycopy) + y;
        its++;
    }
    return its;
}
int calc_mandle_wrong16(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x);// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong17(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + x;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (y)+(y+x / its);// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong18(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy;
    while (its < maxits) {
        if (vabs(zx*zx) + vabs(zy*zy) > 16) return its;
        VS_complex_square(zx, zy);
        zx += x; zy += y;
        its++;
    }
    return its;
}
#define JULIASET_Y 2100
#define JULIASET_X 2100
#define VPNLRF Vals_parameterized_nonlinear_recursive_function

int Vals_parameterized_nonlinear_recursive_function(double &x, double &y, double &cx, double &cy, int& depth, int maxdepth = 100, int Rvalue = 1) {
    if (depth >= maxdepth) {
        return maxdepth;
    }
    depth++;
    double n = x * cx;
    double t = y * cy;
    double c = (double)depth / (double)maxdepth;

    if ((vabs(n) + vabs(t))*c > Rvalue)return depth;
    VS_complex_square(n, t);
    if (n < t) n *= -1;
    else if (t < n)t *= -1;
    if (x > n && y > t) {
         Vals_parameterized_nonlinear_recursive_function(x, y, n, t, depth, maxdepth, Rvalue*2);
    }
    else if (x < n && y < t) {
        int d2 = depth/2;
        Vals_parameterized_nonlinear_recursive_function(n, t,cx,cy, d2, maxdepth, Rvalue/2);
        depth += d2 / c;
    }
    else {
        x = n;
        cy = t;
        VS_complex_sin(n, t);
        depth++;
        cx = n;
        y = t;
    }
    return Vals_parameterized_nonlinear_recursive_function(x, y, cx, cy, depth, maxdepth, Rvalue);
}

int calc_julia2(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cx;
        x = (xcopy - ycopy) + cy;

        its++;
    }

    return its;
}
int calc_julia(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia3(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 - vabs(x / its) * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia4(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        x = (2 * x * y) + cy;
        y = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia5(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * xcopy * y) + cy;
        x = (x - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia6(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * ycopy) + cy;
        x = (xcopy - y) + cx;

        its++;
    }

    return its;
}
int calc_julia7(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        cx = y;
        cy = x;
        its++;
    }

    return its;
}
int calc_julia_tan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy=x, ycopy=y;
    while (its < maxits) {
        
        VS_complex_tan(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_tanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_tanwrong(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cotanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cotanwrong(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cotan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cotan(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cos(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cos(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin_tan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(cx, ycopy);
        VS_complex_tan(xcopy, cy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin_tanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(cx, ycopy);
        VS_complex_tanwrong(xcopy, cy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_exp_exp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_square(x, ycopy);
        VS_complex_square(xcopy, y);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp_exp_exp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_square(x, ycopy);
        VS_complex_square(cx, y);
        VS_complex_square(xcopy, cy);
        VS_complex_square(xcopy, y);
        if (xcopy + ycopy > Rvalue)return its;
//        xcopy += cx;
//       ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_threexp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_exp(xcopy, ycopy,4,xcopy,ycopy);
        
        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_threexpLD(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    long double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_expLD(xcopy, ycopy, 4, xcopy, ycopy);

        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp7(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 6400) {

    int its = 1;
    double xcopy = x, ycopy = y;
    double rr, ii;
    while (its < maxits) {
        VS_complex_bigexp(xcopy, ycopy, 7, rr, ii);
        xcopy = rr;
        ycopy = ii;

        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp127(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 6400) {

    int its = 1;
    double xcopy = x, ycopy = y;
    double rr, ii;
    while (its < maxits) {
        VS_complex_bigexp(xcopy, ycopy, 127, rr, ii);
        xcopy = rr;
        ycopy = ii;

        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}

int calc_Newton_e3m1(double x, double y, int maxits = 1000, double bailout = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zxcopy, zycopy);
        //zxcopy -= 1;
        zxcopy += x;
        zycopy += y;
        hold = vabs(zxcopy) + vabs(zycopy);
        if (hold == 0)return maxits-its;// return its;// *-1;
        if (hold> bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return its;
}

int calc_Newton_e3m1_2(double x, double y, int maxits = 1000, double bailout = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    while (its < (maxits/6)) {
        VS_complex_exp(zx, zy, 4, zxcopy, zycopy);
        zxcopy -= 1;
        //zxcopy += x;
        //zycopy += y;
        hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy,1,0,0.0001))return its * 3;
        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.0001))return its * 4;
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0001))return its * 5;
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0001))return its * 6;
        if (hold > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    if (its == maxits / 6)return maxits;

    if (its < maxits / 6)its %= maxits / 5;
    else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_3(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7)+1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        //VS_complex_exp(zx, zy, 3, xx, yy);
        //VS_complex_mul(xx, yy, 3, 0, xx, yy);
        //VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
//        zxcopy = xx;
 //       zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00005))return (spaces * 2);

        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.00005))return  (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.00005))return (spaces * 5);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.00005))return (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
//    if (its < maxits / 6)its %= maxits / 5;
  //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e4m1_db(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
        zxcopy = xx;
        zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecompw(zxcopy, zycopy, 1, 0, 0.00005))return (its%spaces)+(spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, -1, 0, 0.00005))return  (its % spaces) + (spaces * 4);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces) + (spaces * 5);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e4m1_db_b(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
        zxcopy = xx;
        zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00005))return (its % spaces) + (spaces * 2);
        //if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.00005))return  (its % spaces) + (spaces * 4);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces) + (spaces * 5);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces) + (spaces * 6);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx, cy, 0.0000001))return its +(spaces);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx * -1, cy, 0.0000001))return its + (spaces * 3);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx, cy * -1, 0.0000001))return its + (spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx * -1, cy * -1, 0.0000001))return its + (spaces * 4);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy= zx - xx;
        zycopy= zy - yy;
        //zxcopy = xx;
        //zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.0000000001))return (its % spaces*2);// +(spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.0000000001))return  (its % spaces * 2) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces * 2) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces * 2) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_2E4M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy *= 2;
        zycopy *= 2;
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 6;
        yy *= 6;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;

        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -0.840896, 0.00001))return (its % spaces );// +(spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.840896, 0, 0.00001))return  (its % spaces ) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.840896, 0, 0.00001))return (its % spaces ) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 0.840896, 0.00001))return (its % spaces ) + (spaces * 6);
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_trueE3M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 3, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 2, xx, yy);
        xx *= 2;
        yy *= 2;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.5, -0.866025, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.5, 0.866025, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_E13M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 13, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 12, xx, yy);
        xx *= 12;
        yy *= 12;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.748511, -0.663123, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.120537, -0.992709, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.748511, 0.663123, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.120537, 0.992709, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 0);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.354605, -0.935016, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.885456, 0.464723, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.885456, -0.464723, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.970942, -0.239316, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.568065, -0.822984, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 0);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.354605, 0.935016, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.970942, 0.239316, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.568065, 0.822984, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4c(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx * 3, zy * 3, 3, xx, yy);
        //xx *= 3;
        //yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        //zxcopy = xx;
        //zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecompw(zxcopy, zycopy, 1, 0, 0.0000000001))return (its % spaces * 2);// +(spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, -1, 0, 0.0000000001))return  (its % spaces * 2) + (spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces * 2) + (spaces * 4);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces * 2) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4b(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx, cy, 0.0001))return its +(spaces);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx*-1, cy, 0.0001))return its + (spaces * 3);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx, cy*-1, 0.0001))return its + (spaces * 2);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx*-1, cy*-1, 0.0001))return its + (spaces * 4);

        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}

/******************************************end hardcoded newton rendering types***************************************/
/******************************************start mandelbuddah itterators section***************************************/
int calc_mandle_buddah(double x, double y, int maxits,double bail, double* trackbuff) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return its;
}


/******************************************start arbitrary fractal threading system***********************************/

struct Mandel_workerthread_info {
    int place = 0;
    int maxthreads = 0;
    mutex job_mut;
    double cx, cy;
    int maxits;
    double bailout;
    double basex;
    double basey;
    double stepx;
    double stepy;
    int totalstepsx;
    int totalstepsy;
    void* buffer;
    void* function;
    int* itsbuf;
    int type;
    int finished;
    double rebuild;

    int progress[20];
    int threadsinpool = 0;
    int threadsidle = 0;
    bool running=false;
    int global_threadlock = 64;
};

Mandel_workerthread_info G_mandel_workerthread_info;
string G_Mandel_threadstat = "";
bool G_Mandel_Buddahbrot_renderpause = false;
int G_Mandel_Buddahbrot_samplecount = 0, G_Mandel_Buddahbrot_HitcountTotal=0;
/********heart and soul of the threaded renderer.***********/
int mandel_worker_thread_process(double xh, double yh, double cx, double cy, int maxits, double bailout, void* Mcallback, int type) {
    int ret = 0;

    switch (type) {
    
    case 0:
        ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
        break;
    case 1: // Jset_brot calculation
        ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (cx, cy, xh, yh, maxits, bailout);
        break;
    case 2:
        ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (0, yh, cx + xh, cy, maxits, bailout);
        break;
    case 3:
        ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (yh, 0, cx + xh, cy, maxits, bailout);
        break;
    default:
    case 300: // arbitrary newton same callback as brot with bail
    case 302: // newton nova filler
        ret = ((int(__cdecl*)(double, double, int,double ))(Mcallback)) (xh, yh, maxits,bailout);
        break;
    case 301: // arbitrary newton same callback as brot with bail
    case 303: // arbitrary newton same callback as brot with bail but roots calculated without cx/cy contribution.
        ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
        break;
    case 100: // regular brot types
        ret = ((int(__cdecl*)(double, double, int))(Mcallback)) (xh, yh, maxits);
        break;    
    case 101: // regular brot types with bail
        ret = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits,bailout);
        break;
    case 200: // newton fractal
        ret = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits, bailout);
        break;
    case 201: // newton fractal
        ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
        break;
    

    }


        

    return ret;
}
double vs_rand_double() {
    double a = G_VS_Rand3(1000000000), b = G_VS_Rand3(1000000000);
    if (a < b) return a / b;
    return b / a;
}

int mandel_buddah_thread_process_step(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data,double xmin, double xmax, double ymin, double ymax, double xstep, double ystep,int numerator,int denominator) {
    double n = x,  i = y;
    int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits*numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double *tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (n <= xmin || n >= xmax || i <= ymin || i >= ymax) continue;
            int xx = ((n - xmin) / xstep);
            int yy = ((i - ymin) / ystep);
            myhit_data[xx + (yy * 2000)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}
static bool G_Mandel_threading_halt = false;
void mandel_buddah_thread_process(int* itsbuf, mutex &workmut, double xmin, double ymin, double xmax, double ymax, int maxits,double bail,int samples,void* function,int& progress,int numer, int denom ) {
    workmut.lock();
    auto myhit_data = new int[2000*2000];

    bool isdone = false;
    foreach(i, 2000) { foreach(n, 2000) { myhit_data[i+(n*2000)] = 0;  } }
    workmut.unlock();
    double* trackbuff = new double[maxits*5];

    double* tb_h = trackbuff;
    double n, i;
    double xwid = xmax - xmin, ywid = ymax - ymin;
    double xstep = xwid / 2000, ystep = ywid / 2000;
    int xx, yy;
    int ctch = 0;
    while (samples >0) {
        //generate 2 random doubles. n,i
        workmut.lock();
        n = (vs_rand_double()*xwid)+xmin;
        i = (vs_rand_double()*ywid)+ymin;
        workmut.unlock();

        if (G_Mandel_threading_halt)break;
        
        ctch+=mandel_buddah_thread_process_step(n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep,numer,denom);
        ctch += mandel_buddah_thread_process_step(-n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(-n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(-i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        ctch += mandel_buddah_thread_process_step(-i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom);
        

        progress++;
        samples--;
    }
    
    int* itsh = itsbuf;
    workmut.lock();
    foreach(i, 2000) { foreach(n, 2000) { *itsh += myhit_data[n + (i * 2000)]; itsh++;   } }//myhit_data[n][i];
    G_Mandel_Buddahbrot_samplecount += ctch;
    workmut.unlock();

    delete[] trackbuff;
    delete[] myhit_data;
}
void mandel_buddah_thread_renderer(int* itsbuf) {

}


static int G_Mandel_buddahbrot_samples = 500;
void Mandel_workerthread(void* a) {

    int myplace = 0;
    int maxthreads = 0;
    double cx, cy;
    int maxits;
    double bailout;
    double basex;
    double basey;
    double stepx;
    double stepy;
    BYTE* buffer;
    int tstepsx;
    int tstepsy;
    void* function;
    int* itsbuf,*itsbufbase;
    int itsbuf_jump;
    int type;
    //int its;
    double rebuild;
    int color;
    double xx, yy;
    int y_stepcount = 0, x_stepcount = 0;;

    // mandelbuddah vars:
    // int* buddahbuffer;
    // int* bbufferhold;


    G_mandel_workerthread_info.job_mut.lock();
    G_mandel_workerthread_info.threadsinpool++;
    G_mandel_workerthread_info.threadsidle++;
    G_mandel_workerthread_info.job_mut.unlock();
    while (1) {
        while (G_mandel_workerthread_info.maxthreads == 0 || G_mandel_workerthread_info.place >= G_mandel_workerthread_info.maxthreads)Sleep(100);
        G_mandel_workerthread_info.job_mut.lock();
        //cout << "thread awoke\n";
        if (G_mandel_workerthread_info.maxthreads == 0)continue;
        if (G_mandel_workerthread_info.place >= G_mandel_workerthread_info.maxthreads) {
            //G_mandel_workerthread_info.maxthreads = 0;.
            G_mandel_workerthread_info.job_mut.unlock();
            continue;
        }
        maxthreads = G_mandel_workerthread_info.maxthreads;
        myplace = G_mandel_workerthread_info.place;
        
        G_mandel_workerthread_info.place++;
        G_mandel_workerthread_info.threadsidle--;
        stepx = G_mandel_workerthread_info.stepx;
        stepy = G_mandel_workerthread_info.stepy;

        buffer = (BYTE*)G_mandel_workerthread_info.buffer;
        basex = G_mandel_workerthread_info.basex;
        basey = G_mandel_workerthread_info.basey;
        tstepsx = G_mandel_workerthread_info.totalstepsx;
        tstepsy = G_mandel_workerthread_info.totalstepsy;
        buffer += (tstepsx * myplace*4);
        function = G_mandel_workerthread_info.function;
        type = G_mandel_workerthread_info.type;
        itsbuf = G_mandel_workerthread_info.itsbuf;
        itsbufbase = itsbuf;
        itsbuf += tstepsx * myplace; //*4?
        itsbuf_jump = maxthreads * tstepsx;
        cx = G_mandel_workerthread_info.cx;
        cy = G_mandel_workerthread_info.cy;
        maxits = G_mandel_workerthread_info.maxits;
        bailout = G_mandel_workerthread_info.bailout;
        rebuild = G_mandel_workerthread_info.rebuild;
        y_stepcount = 0;
        x_stepcount = 0;
        yy = basey + (stepy * myplace);
        stepy *= (maxthreads);
        G_mandel_workerthread_info.job_mut.unlock();
        double xwid= basex + (tstepsx * stepx), ywid= basey + (tstepsy * (stepy/maxthreads));

        //cout << "thread " << myplace << " started with type=" << type << "tstepsy: " << tstepsy << "\n";
        switch (type) {
        case 400:
        case 401:
            //Note: must clear iterationsBuffer before iterating here. 
            //this is for mandelbudah rendering
            mandel_buddah_thread_process(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid,ywid, maxits, bailout, G_Mandel_buddahbrot_samples,function, G_mandel_workerthread_info.progress[myplace],9,10);
            break;
        case 402:
            //Note: must clear iterationsBuffer before iterating here. 
            //this is for mandelbudah rendering
            mandel_buddah_thread_process(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, G_mandel_workerthread_info.progress[myplace], cx, cy);
            break;

        default:
            for (int y = myplace; y < tstepsy - 1; y += maxthreads) {
                xx = basex;
                for (int x = 0; x < tstepsx; x++) {
                    if (G_Mandel_threading_halt) { y = tstepsy; break; }
                    if (!rebuild || (rebuild && rebuild == (*itsbuf))) {
                        (*itsbuf) = mandel_worker_thread_process(xx, yy, cx, cy, maxits, bailout, function, type);
                        color = Linear_color((*itsbuf), maxits);
                        *buffer = GetBValue((COLORREF)color); buffer++;
                        *buffer = GetGValue((COLORREF)color); buffer++;
                        *buffer = GetRValue((COLORREF)color); buffer += 2;
                    }
                    else buffer += 4;
                    itsbuf++;
                    xx += stepx;
                    x_stepcount++;
                    G_mandel_workerthread_info.progress[myplace]++;
                }
                buffer += (tstepsx * (maxthreads - 1) * 4);
                itsbuf += (tstepsx * (maxthreads - 1));
                y_stepcount++;
                yy += stepy;
                
            }
            break;
        }
        G_mandel_workerthread_info.job_mut.lock();
        G_mandel_workerthread_info.finished++;
        G_mandel_workerthread_info.threadsidle++;
        //cout << "thread " << myplace << " ended stepcounts x,y: " << x_stepcount<<","<<y_stepcount<<"\n";
        G_mandel_workerthread_info.job_mut.unlock();
    }

}

string ctostr(unsigned long long i) {
    char a[38];
    _ui64toa(i, a, 10);
    //_itoa_s(i, a, 10);
    return a;

}

void Dispatch_workerthread_job (double x, double y, double w, double h, double cx, double cy,
                               int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims],
                               int rebuild , double bailout , int type ,char* buffer,int cwid,int chit, int maxthreads, void* progCallback) {
    unsigned long long time = 0;
    if (G_mandel_workerthread_info.running) {
        if (G_mandel_workerthread_info.finished != G_mandel_workerthread_info.maxthreads) {
            cout << "last threaded render is not complete. please wait\n";
            return;
        }

    }
    if (type > 299 && type < 400) {
        cout << "starting to process ANDRO roots\n";
        G_Mandel_ANDRO_rootslistlen = 0;
        int roots = 0;
        if(type == 300||type==303)roots=arbitrary_newton_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
        if(type == 302)roots = arbitrary_newton_nova_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
        if (type == 301)roots = arbitrary_newton_julia_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen,cx,cy, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);

        

        double a, b;
        if (roots < 1) {
            cout << "no roots found with method specific root detection method, finding non-normalized roots\n";
            roots = arbitrary_newton_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
            if (roots < 1) {
                cout << "no roots found for current arbitrary equation\n";
                return;
            }

        }
        cout << roots << " roots found \n";
        foreach(i, G_Mandel_ANDRO_rootslistlen) {
            a = G_Mandel_ANDRO_rootslist[i * 2];
            b = G_Mandel_ANDRO_rootslist[(i * 2) + 1];
            if (vabs(a) < .00000001)a = 0;
            if (vabs(b) < .00000001)b = 0;
            cout << "if(VS_complex_rangecomp(zxcopy, zycopy," << a << ", " << b << ", 0.00001))return ((its*its) % (spaces*3))+(spaces*" << ((i + 1) % 5) << "); \n";
        }
        cout << "out of roots processing\n";
    }

    if (G_mandel_workerthread_info.global_threadlock < maxthreads) maxthreads = G_mandel_workerthread_info.global_threadlock;
    long int maxprogress = cwid*chit;
    if (type >= 400 && type < 500) {
        maxprogress = G_Mandel_buddahbrot_samples * maxthreads;
        if (!rebuild) {
            cout << "resetting input iteration buffer to 0s\n";
            G_Mandel_Buddahbrot_samplecount = 0;
            foreach(xxx, Mandelbrot_window_dims) {
                foreach(yyy, Mandelbrot_window_dims) {
                    inpBuf[xxx][yyy] = 0;
                }
            }
        }
        
    }

//    cout << "dispatching threads now\n";
    G_Mandel_threadstat = "dispatching";
    G_mandel_workerthread_info.rebuild = rebuild;
    G_mandel_workerthread_info.running = true;
    G_mandel_workerthread_info.place = 0;
    G_mandel_workerthread_info.cx = cx;
    G_mandel_workerthread_info.cy=cy; 
    G_mandel_workerthread_info.maxits=maxits;
    G_mandel_workerthread_info.bailout=bailout;
    G_mandel_workerthread_info.basex=x;
    G_mandel_workerthread_info.basey=y; 
    G_mandel_workerthread_info.stepx = w/cwid;
    G_mandel_workerthread_info.stepy= h/chit;
    G_mandel_workerthread_info.totalstepsx=cwid;
    G_mandel_workerthread_info.totalstepsy=chit;
    G_mandel_workerthread_info.buffer=buffer;
    G_mandel_workerthread_info.function=Mcallback;
    G_mandel_workerthread_info.itsbuf=(int*)inpBuf;
    G_mandel_workerthread_info.type = type;
    G_mandel_workerthread_info.finished=0;
    //G_Mandel_Stopwatch.Restart();
    //G_Mandel_Stopwatch.Start();
    foreach(bbb, 20)G_mandel_workerthread_info.progress[bbb] = 0;
    time = chrono_micro();
    
    G_mandel_workerthread_info.maxthreads = maxthreads; // this line causes the threads in the worker pool to awaken. Do all setup before this line
    //cout << "threads messaged\n";
//    Sleep(5);
    //cout << "threads rendering: " <<(G_mandel_workerthread_info.threadsinpool - G_mandel_workerthread_info.threadsidle) << "\n";
    unsigned long long int totalprogress = 0;
    unsigned long long int progr;
    while (G_mandel_workerthread_info.finished != G_mandel_workerthread_info.maxthreads) {
        
        totalprogress = 0;
        foreach(bbb, 20) totalprogress += G_mandel_workerthread_info.progress[bbb];
        progr = (totalprogress*100)/maxprogress;
        G_Mandel_threadstat = ctostr(G_mandel_workerthread_info.threadsinpool - G_mandel_workerthread_info.threadsidle) + " rendering | " + ctostr(totalprogress)+":"+ctostr(maxprogress);
        
        ((void(__cdecl*)(int))(progCallback))(progr );

        Sleep(66);
    }
    if (!G_Mandel_threading_halt) {
        ((void(__cdecl*)(int))(progCallback))(100);
    }

    if (type >= 400 && type < 500) {
        cout << "into buddahbrot greyscale image renderer\n";
        int maxv = 0, minv = 10000000;
        int* itsbufh = (int*)inpBuf;
        unsigned long int total = 0;
        foreach(i, 2000) { 
            foreach(n, 2000) { 
            if (*itsbufh > maxv)maxv = *itsbufh; 
            if (*itsbufh < minv)minv = *itsbufh;
            total+= *itsbufh;
            itsbufh++;
            } 
        }
        G_Mandel_Buddahbrot_HitcountTotal = total;
        cout << maxv << ":max " << minv << ":min    "<<total <<":total  " << G_Mandel_Buddahbrot_samplecount <<" samples rendered \n";
        maxv -= minv;
        int tot = 765;
        int temp,tt;
        double dtemp;
        itsbufh = (int*)inpBuf;
        char r, g, b;
        char* bufh = buffer;
        if (maxv > maxits)maxv = maxits;
        if (type!=401 ) {
            foreach(i, 2000) {
                foreach(n, 2000) {
                    temp = (*itsbufh) - minv;
                    temp = Linear_color(temp,maxv);// maxv
                    *bufh = GetBValue(temp); bufh++;
                    *bufh = GetGValue(temp); bufh++;
                    *bufh = GetRValue(temp); bufh++; bufh++;
                    itsbufh++;
                }
            }
        }
        else {
            foreach(i, 2000) {
                foreach(n, 2000) {
                    temp = (*itsbufh) - minv;
                    itsbufh++;
                    if ((*itsbufh) != 0) {

                        dtemp = (double)maxv / (double)(temp);
                        dtemp = tot * dtemp;
                        temp = dtemp;
                        tt = temp / 3;
                        temp = temp % 3;
                    }
                    else {
                        tt = 0; temp = 0; 
                    }
                    r = tt + (temp > 0 ? 1 : 0);
                    g = tt + (temp > 1 ? 1 : 0);
                    b = tt;
                    *bufh = b; bufh++;
                    *bufh = g; bufh++;
                    *bufh = r; bufh++; bufh++;
                }
            }
        }
        /*
        foreach(i, 2000) {
            foreach(n, 2000) {
                temp = (*itsbufh) - minv;
                itsbufh++;
                if ((*itsbufh) != 0) {
                    
                    dtemp = (double)maxv / (double)(temp);
                    dtemp = tot * dtemp;
                    temp = dtemp;
                    tt = temp / 3;
                    temp = temp % 3;
                }
                else {
                    tt = 0; temp = 0;
                }
                r = tt+ (temp>0?1:0);
                g = tt + (temp > 1 ? 1 : 0);
                b = tt;
                *bufh = b; bufh++;
                *bufh = g; bufh++;
                *bufh = r; bufh++; bufh++;
            }
        }
        */
    }

    unsigned long long ms;
    //G_Mandel_Stopwatch.End(lp, ms);
    ms=G_Mandel_Stopwatch.Stop();
    string rt = "render time: " + ctostr(chrono_micro() - time) + "micros";
    G_Mandel_threadstat = rt;
    cout << rt << "\n";
    G_mandel_workerthread_info.maxthreads = 0;
    G_mandel_workerthread_info.running = false;
    cout << "finished threaded rendering\n";

}

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

    
    void OmniMandel_b(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims], int rebuild = 0, double bailout = 4.0, int type=0) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int  color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        //G_Mandel_Stopwatch.Restart();
        //G_Mandel_Stopwatch.Start();
        unsigned long long time = chrono_micro();
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                if (rebuild && inpBuf[n][i] != rebuild) {
                    hold += 4;
                    xh += x_jump;
                    continue;
                }
                switch (type) {
                case 0:
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
                    break;
                case 1: // Jset_brot calculation
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) ( cx, cy, xh, yh, maxits, bailout);
                    break;
                case 2:
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (0, yh, cx+xh, cy, maxits, bailout);
                    break;
                case 3:
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) ( yh,0, cx + xh, cy, maxits, bailout);
                    break;
                case 100: // regular brot types
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, int))(Mcallback)) (xh, yh, maxits);
                    break;
                case 200: // newton fractal
                    inpBuf[n][i] = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits, bailout);
                    break;
                case 201: // newton fractal
                    inpBuf[n][i] = ((int(__cdecl*)(double, double,double,double, int, double))(Mcallback)) (xh, yh,cx,cy, maxits, bailout);
                    break;
                
                }
                

                color = get_mand_color(inpBuf[n][i], ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }
        //unsigned long long  ms;
        //ms=G_Mandel_Stopwatch.Stop();
        time = chrono_micro() - time;
        cout << "render complete, time: " <<  time << "micros\n";

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
    void multiJset(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims], int rebuild=0,double bailout=4.0) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int  color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                if (rebuild && inpBuf[n][i] != rebuild) {
                    hold += 4;
                    xh += x_jump;
                    continue;
                }
                inpBuf[n][i] = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);

                color = get_mand_color(inpBuf[n][i], ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    //int calc_mandle(double x, double y, int maxits = 1000) {
    //    int its = 1;
    //    //double abs = vabs(x) + vabs(y);
    //    long double zx = x, zy = y;
    //    long double zxcopy, zycopy;
    //    while (its < maxits) {
    //        zxcopy = zx * zx;
    //        zycopy = zy * zy;
    //        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
    //        //zy = 2 * zx * zy + x;
    //        zy = (2 * zx * zy) + y;
    //        //zx = zxcopy - zycopy + y;
    //        zx = (zxcopy - zycopy) + x;
    //        its++;
    //    }
    //    return its;
    //}


//#include <stdio.h>
//#include <tgmath.h>
//#include <winbgim.h>


//

    void draw_jset_tocopy(double x, double y, double w, double h, int maxits) {
    //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();
        int ww = 3, hh = 3;
        double xplc = -1.5;

        long double x_jump = ww / (double)this->width;
        long double y_jump = hh / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = xplc, yh = -1.5;
        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                itts = calc_julia(xh, yh,x,y, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = xplc;
            yh += y_jump;;
        }

    }
    void multiJset(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {

                itts = ((int(__cdecl*)(double, double, double, double, int,int))(Mcallback)) (xh, yh, cx, cy, maxits,4);
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void multiJset_brot(double x, double y, double w, double h, double cx, double cy, int maxits, void* Mcallback) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {

                itts = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) ( cx, cy, xh, yh, maxits, 4);
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
//    int Vals_parameterized_nonlinear_recursive_function(double& x, double& y, double& cx, double& cy, int& depth, int maxdepth = 100, int Rvalue = 4) {

        void draw_Vset_tocopy(double x, double y, double w, double h, double cx, double cy, int maxits,int bailout=4) {
            //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
            copy_buf();

            long double x_jump = w / (double)this->width;
            long double y_jump = h / (double)this->height;
            cout << "xj yj: " << x_jump << ":" << y_jump << endl;
            double xh = x, yh = y;

            BYTE* hold = (BYTE*)copybuf;
            int itts, color;
            int ittops = maxits;// 1 + (maxits / 4) * (3);
            int depth = 0;
            for (int n = 0; n < height; n++) {
                for (int i = 0; i < width; i++) {
                    //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                    //itts = calc_mandle_wrong15(xh, yh, maxits);
                    itts = Vals_parameterized_nonlinear_recursive_function(xh, yh, cx, cy,depth, maxits,bailout);
                    //itts = calc_julia(cx, cy, xh, yh, maxits);
                    //cout << "mand its: " << itts << "\n";
                    color = get_mand_color(itts, ittops);
                    *hold = GetBValue((COLORREF)color); hold++;
                    *hold = GetGValue((COLORREF)color); hold++;
                    *hold = GetRValue((COLORREF)color); hold += 2;
                    xh += x_jump;
                }
                xh = x;
                yh += y_jump;;
            }

        }
    void draw_jset_tocopy(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia(cx, cy, xh, yh, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong(double x, double y, double w, double h,double cx,double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();
        
        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                itts = calc_julia(cx, cy, xh, yh, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong2(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                 itts = calc_julia2(xh, yh, cx, cy, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }

    void draw_jset_tocopy_wrong3(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                itts = calc_julia(0, yh, cx+xh, cy, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong4(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                itts = calc_julia2(0, yh, cx + xh, cy, maxits,64);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong5(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                itts = calc_julia2(yh, 0, cx + xh, cy, maxits, 64);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong6(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                itts = calc_julia(yh, 0, cx + xh, cy, maxits,4);// maxits*maxits
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_jset_tocopy_wrong7(double x, double y, double w, double h, double cx, double cy, int maxits) {
        //void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h, int maxits) {
        copy_buf();

        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;

        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        int ittops = maxits;// 1 + (maxits / 4) * (3);
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, cx, cy, maxits);
                //itts = calc_julia2(cx, cy, xh, yh, maxits);
                itts = calc_julia3(xh, yh, cx, cy, maxits, 512);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, ittops);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void multimandelbrot(double x, double y, double w, double h, int maxits, void* Mcallback) {
        copy_buf();
        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;
        BYTE* hold = (BYTE*)copybuf;
        int itts, color;

        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                //itts = calc_mandle_wrong15(xh, yh, maxits);
                itts= ((int(__cdecl*)(double,double,int))(Mcallback)) (xh,yh,maxits);
                //itts = calc_julia(xh, yh, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, maxits);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }

    void draw_mandelbrot_tocopy_wrong(double x, double y, double w, double h,int maxits) {
        copy_buf();
        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh = x, yh = y;
        BYTE* hold = (BYTE*)copybuf;
        int itts, color;

        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                itts = calc_mandle_wrong15(xh, yh, maxits);
                //itts = calc_julia(xh, yh, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, maxits);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
        }

    }
    void draw_mandelbrot_tocopy(double x, double y, double w, double h,int maxits=512) {
        copy_buf();
        long double x_jump = w / (double)this->width;
        long double y_jump = h / (double)this->height;
        cout << "xj yj: " << x_jump << ":" << y_jump << endl;
        long double xh=x, yh=y;
        BYTE* hold = (BYTE*)copybuf;
        int itts, color;
        for (int n = 0; n < height; n++) {
            for (int i = 0; i < width; i++) {
                //cout << "passing in x,y: " << xh << " , " << yh << "\n";
                itts = calc_mandle(xh, yh, maxits);
                //cout << "mand its: " << itts << "\n";
                color = get_mand_color(itts, maxits);
                *hold = GetBValue((COLORREF)color); hold++;
                *hold = GetGValue((COLORREF)color); hold++;
                *hold = GetRValue((COLORREF)color); hold += 2;
                xh += x_jump;
            }
            xh = x;
            yh += y_jump;;
            //cout << "moved y value: " <<y << "        \r";
            //if((int)y % 5 ==0) 
        }
        //get x and y field size 
        //get x and y pixel jump
        // setup copy pointer walker
        //loop through all pixels and run mandelbrot_calc for each 
        // call colorizer
        // set pixel in copy


        // calling process pastes buf and draws gfx.

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
bool ValGFX::load_image(string fname) {
    string extens = extension(fname);
    if (extens != ".bmp") return OLE_load(fname);
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