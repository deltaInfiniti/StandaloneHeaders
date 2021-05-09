#pragma once
#include<string>
#include<windows.h>
using namespace std;
class ValTextControl {
public:
	LOGFONTA fontdat;
	COLORREF color,undocolor;
	HDC bufhdc;
	HBITMAP Selectdump;
	HFONT myfont=NULL;
	HFONT fontselectdump;
	string content;
	string fontname;
	RECT lastbounds;
	int x, y, w, h;
	ValTextControl();
	ValTextControl(string what);
	ValTextControl(string fntname, int xx, int yy, int ww, int hh, string what="");

	void SetFont(LOGFONT copy);
	ValTextControl& SetFont(string fontnamez);//check
	ValTextControl& SetColor(COLORREF copy);// check
	ValTextControl& DIBdraw(HDC comdc,HBITMAP& target);
	int getrealtwidth();
	bool IS_TRANSP;
	HFONT get_HFONT() {
		if (myfont == NULL)myfont = CreateFontIndirectA(&fontdat);
		return myfont;
	}
};
int ValTextControl::getrealtwidth() {
	bufhdc = CreateCompatibleDC(NULL);
	//HFONT fnt = CreateFontIndirectA(&fontdat);
	if (myfont == NULL)myfont = CreateFontIndirectA(&fontdat);

	SelectObject(bufhdc, myfont);
	RECT a = { 0,0,0,0 };
	DrawTextA(bufhdc, content.c_str(), content.length(), &a, DT_CALCRECT);
	SelectObject(bufhdc, fontselectdump);
	//DeleteObject(fnt);
	ReleaseDC(NULL, bufhdc);
	DeleteDC(bufhdc);
	return a.right;
}
ValTextControl& ValTextControl::DIBdraw(HDC comdc,HBITMAP& target) {
	bufhdc = CreateCompatibleDC(comdc);
	if(myfont==NULL)myfont = CreateFontIndirectA(&fontdat);
	SelectObject(bufhdc, target);
	SelectObject(bufhdc, myfont );
	SetTextColor(bufhdc, color);
	RECT a = { x,y,x+141,y+100 };//x+141,y+100 };
	//	RECTb(a, x, y, x+w,y+h);
		//BeginPath(bufhdc);
	if (IS_TRANSP) SetBkMode(bufhdc, TRANSPARENT);
	DrawTextA(bufhdc, content.c_str(), content.length(), &a, DT_NOCLIP|DT_SINGLELINE|DT_INTERNAL);
	a = { 0,0,0,0 };
	DrawTextA(bufhdc, content.c_str(), content.length(), &a, DT_CALCRECT);
	lastbounds = a;

	//TextOutA(bufhdc, x, y, content.c_str(), content.length());
	//EndPath(bufhdc);
	//cout << "draw length was " << a.right - a.left << endl;

	SelectObject(bufhdc, fontselectdump);
	SelectObject(bufhdc, Selectdump);
	//DeleteObject(fnt);
	ReleaseDC(NULL, bufhdc);
	DeleteDC(bufhdc);
	return *this;
}
ValTextControl::ValTextControl() {
	ValTextControl("Arial", 0, 0, 0, 0);
}
ValTextControl::ValTextControl(string what) {
	ValTextControl(what, 0, 0, 0, 0);
}
ValTextControl::ValTextControl(string fntname, int xx, int yy, int ww, int hh,string what) {
	content = what;
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	IS_TRANSP = true;
	SetFont(fntname);
}
ValTextControl& ValTextControl::SetColor(COLORREF copy) {
	color = copy;
	return *this;

}

ValTextControl& ValTextControl::SetFont(string fontnamez) {
	fontname = fontnamez;
	if (myfont != NULL) {
		DeleteObject(myfont);
		myfont = NULL;
	}

	fontdat.lfHeight = 16;
	fontdat.lfWidth = 0;
	fontdat.lfEscapement = 0;
	fontdat.lfOrientation =0;
	fontdat.lfWeight = 500;
	fontdat.lfItalic = 0;
	fontdat.lfUnderline = 0;
	fontdat.lfStrikeOut = 0;
	fontdat.lfCharSet = DEFAULT_CHARSET;
	fontdat.lfOutPrecision =  OUT_TT_ONLY_PRECIS;// OUT_DEFAULT_PRECIS; //
	fontdat.lfClipPrecision = CLIP_DEFAULT_PRECIS;// CLIP_STROKE_PRECIS;//
	fontdat.lfQuality = DEFAULT_QUALITY;// CLEARTYPE_QUALITY;
	fontdat.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	//fontdat.lfFaceName = "Arial";
	memcpy(fontdat.lfFaceName, fontnamez.c_str(), fontnamez.length());
	for (int i = fontnamez.length(); i < 32; i++)fontdat.lfFaceName[i] = '\0';

	//	int i = 0;
//	for (; i < (fontname.length() > 32 ? 31 : fontname.length()); i++) {
//		fontdat.lfFaceName[i] = fontname[i];
//	}
//	fontdat.lfFaceName[i] = '\n';
	return *this;
}

/*usable fontnames.  case sensitive 
* Ink Free
* Unispace
* Segoe Script
* 
System
8514oem
Fixedsys
Terminal
Modern
Roman
Script
Courier
MS Serif
MS Sans Serif
Small Fonts
TeamViewer15
Marlett
Arial
Arabic Transparent
Arial Baltic
Arial CE
Arial CYR
Arial Greek
Arial TUR
Arial Black
Bahnschrift Light
Bahnschrift SemiLight
Bahnschrift
Bahnschrift SemiBold
Bahnschrift Light SemiCondensed
Bahnschrift SemiLight SemiConde
Bahnschrift SemiCondensed
Bahnschrift SemiBold SemiConden
Bahnschrift Light Condensed
Bahnschrift SemiLight Condensed
Bahnschrift Condensed
Bahnschrift SemiBold Condensed
Calibri
Calibri Light
Cambria
Cambria Math
Candara
Candara Light
Comic Sans MS
Consolas
Constantia
Corbel
Corbel Light
Courier New
Courier New Baltic
Courier New CE
Courier New CYR
Courier New Greek
Courier New TUR
Ebrima
Franklin Gothic Medium
Gabriola
Gadugi
Georgia
Impact

Javanese Text
Leelawadee UI
Leelawadee UI Semilight
Lucida Console
Lucida Sans Unicode
Malgun Gothic
@Malgun Gothic
Malgun Gothic Semilight
@Malgun Gothic Semilight
Microsoft Himalaya
Microsoft JhengHei
@Microsoft JhengHei
Microsoft JhengHei UI
@Microsoft JhengHei UI
Microsoft JhengHei Light
@Microsoft JhengHei Light
Microsoft JhengHei UI Light
@Microsoft JhengHei UI Light
Microsoft New Tai Lue
Microsoft PhagsPa
Microsoft Sans Serif
Microsoft Tai Le
Microsoft YaHei
@Microsoft YaHei
Microsoft YaHei UI
@Microsoft YaHei UI
Microsoft YaHei Light
@Microsoft YaHei Light
Microsoft YaHei UI Light
@Microsoft YaHei UI Light
Microsoft Yi Baiti
MingLiU-ExtB
@MingLiU-ExtB
PMingLiU-ExtB
@PMingLiU-ExtB
MingLiU_HKSCS-ExtB
@MingLiU_HKSCS-ExtB
Mongolian Baiti
MS Gothic
@MS Gothic
MS UI Gothic
@MS UI Gothic
MS PGothic
@MS PGothic
MV Boli
Myanmar Text
Nirmala UI
Nirmala UI Semilight
Palatino Linotype
Segoe MDL2 Assets
Segoe Print

Segoe UI
Segoe UI Black
Segoe UI Emoji
Segoe UI Historic
Segoe UI Light
Segoe UI Semibold
Segoe UI Semilight
Segoe UI Symbol
SimSun
@SimSun
NSimSun
@NSimSun
SimSun-ExtB
@SimSun-ExtB
Sitka Small
Sitka Text
Sitka Subheading
Sitka Heading
Sitka Display
Sitka Banner
Sylfaen
Symbol
Tahoma
Times New Roman
Times New Roman Baltic
Times New Roman CE
Times New Roman CYR
Times New Roman Greek
Times New Roman TUR
Trebuchet MS
Verdana
Webdings
Wingdings
Yu Gothic
@Yu Gothic
Yu Gothic UI
@Yu Gothic UI
Yu Gothic UI Semibold
@Yu Gothic UI Semibold
Yu Gothic Light
@Yu Gothic Light
Yu Gothic UI Light
@Yu Gothic UI Light
Yu Gothic Medium
@Yu Gothic Medium
Yu Gothic UI Semilight
@Yu Gothic UI Semilight
HoloLens MDL2 Assets

*/