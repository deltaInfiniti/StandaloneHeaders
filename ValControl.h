/* ValControl.h
* class for window controls
* 
*/



#pragma once
// user changeable constants. could be variables 
#define listbox_cellheight 18 
#define LISTBOX_ARROWHEIGHT 15

#include<string>
#include"valgfx.h"
#include"strlist.h"
#include"varlist.h"
#include<mutex>
using namespace std;
string str_replace(string a, string b, string c) {
	string ret = a;
	int plc = 0;
	while ((plc = ret.find(b, (size_t)plc)) != string::npos) {
		ret.replace(plc, b.length(), c);
		plc += (c.length() - b.length()) + 1;
	}
	return ret;
}
int VC_random(int max, int min = 0) {
	return (rand() % max) + min;
}
// used to deliniate a functionless interactable object
#define VC_NOFUNC (void*)&NoFunction

// list of acceptable ValControl types
//  commented ones not implimented yet
#define VC_BUTTON 0
#define VC_CHECKBOX 1
#define VC_LABEL 2
#define VC_EDIT 3
#define VC_EDITML 300
#define VC_GHOST 4 // supposed to be transp. frame... Not as easy as I thought.
#define VC_DEAD_AREA 5// technically used to selectively remove interactability
#define VC_GLOBAL_STAT_INT 6
#define VC_GLOBAL_STAT_STRING 7
#define VC_GLOBAL_STAT_BOOL 8
#define VC_PASSWORD 9
#define VC_IMAGE 10
#define VC_DROPDOWN 11// temporary listbox?? 
#define VC_LISTBOX 12
#define VC_LOADINGBAR 13
#define VC_SLIDER 14
#define VC_LABELML 15


#define M_VC_TYPE_tostr_M(a) case a: return #a;
string VC_TYPE_tostr(int type) {
	switch (type){
		M_VC_TYPE_tostr_M(VC_BUTTON);
		M_VC_TYPE_tostr_M(VC_CHECKBOX);
		M_VC_TYPE_tostr_M(VC_LABEL);
		M_VC_TYPE_tostr_M(VC_EDIT);
		M_VC_TYPE_tostr_M(VC_EDITML);
		M_VC_TYPE_tostr_M(VC_GHOST);
		M_VC_TYPE_tostr_M(VC_DEAD_AREA);
		M_VC_TYPE_tostr_M(VC_PASSWORD);
		M_VC_TYPE_tostr_M(VC_IMAGE);
		M_VC_TYPE_tostr_M(VC_DROPDOWN);
		M_VC_TYPE_tostr_M(VC_LISTBOX);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_INT);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_STRING);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_BOOL);
		M_VC_TYPE_tostr_M(VC_LOADINGBAR);
		M_VC_TYPE_tostr_M(VC_SLIDER);
		M_VC_TYPE_tostr_M(VC_LABELML);
	}

}
//BAD FORM BUT MAKES FOR EASY COPY PASTE
#define M_VC_TYPE_tostr_M(a) if(type== #a) return a;
int VC_str_toTYPE(string type) {
	
		M_VC_TYPE_tostr_M(VC_BUTTON);
		M_VC_TYPE_tostr_M(VC_CHECKBOX);
		M_VC_TYPE_tostr_M(VC_LABEL);
		M_VC_TYPE_tostr_M(VC_EDIT);
		M_VC_TYPE_tostr_M(VC_EDITML);
		M_VC_TYPE_tostr_M(VC_GHOST);
		M_VC_TYPE_tostr_M(VC_DEAD_AREA);
		M_VC_TYPE_tostr_M(VC_PASSWORD);
		M_VC_TYPE_tostr_M(VC_IMAGE);
		M_VC_TYPE_tostr_M(VC_DROPDOWN);
		M_VC_TYPE_tostr_M(VC_LISTBOX);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_INT);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_STRING);
		M_VC_TYPE_tostr_M(VC_GLOBAL_STAT_BOOL);
		M_VC_TYPE_tostr_M(VC_LOADINGBAR);
		M_VC_TYPE_tostr_M(VC_SLIDER);
		M_VC_TYPE_tostr_M(VC_LABELML);
}
#undef M_VC_TYPE_tostr_M
struct ValControl_struct {
	BYTE type;
	string name;
	string label;
	VRECT vrect;
	void* funct;
	bool needs_parent;
	HWND parent;
};

class ValControl {

/* ValControl 
* included directly by ValWindow, which is included by ValWindowManager.h
* depends on 
   valgfx.h (gdi32, ole2)
   valtextcontrol.h
   strlist.h
   

* class for handling drawing and interactions for on-window controls
* see define list above for list of implimented types
* handles all drawing for all controls except edit type
* handles drawing for interact events (mousedown, mouseover) 
* handles some click events (listbox/metacontrols) fully
* 
* 
* todo:
* destructor
* code reorganization/cleanup
* dropdown selection
* slider control
* color picker
* file selector (use wm version...)
*/

public:
	ValControl(BYTE t, int xx, int yy, int ww, int hh, string l, string ti);
	ValControl(BYTE t, int xx, int yy, int ww, int hh, string l, HWND& pa, string ti);
	//ValControl(string fname, BYTE t, int xx, int yy, int ww, int hh);
	//ValControl(ValGFX& source, int sx, int sy, int ww, int hh, int dx, int dy);

	~ValControl() {} //kill all pointers

	void set_defaults(BYTE t, int xx, int yy, int ww, int hh, string l, string ti);
	void start_gfx(int ww, int hh);

	

	// integral values-copy these 
	BYTE type;
	string title;
	string label;
	short x, y, width, height;
	string dataname;

	bool ISGLOBAL, NO_interact, NO_draw, NO_text, NEEDSPARENT;
	bool IS_TRANSP;
	bool drawunder = false; // draw the background under this control before copying. only used when transparent&globalstat
	short numblurs;
	bool is_multiarea = false; // true for listboxes only currently.
	int highlight_values[6];// 0,1 2,3 4,5 domains for changing highlights  use VRGB values

	int bottom_align = 0; // denotes negative initial x/y values for export
	int right_align = 0;
	string tabname = ""; // name of control focus goes to when tab is hit, for export
	
	
									   
/*reusable index values
	listbox 0 - list selection index  1-is arrow mouseover
	checkbox 0- checkbox evaluation 
	*/
	int value[10];


	//transient values- set on runtime
	bool do_highlight = false;
	HWND parent, windows_control;
	HWND tabhwnd = NULL;
	ValGFX* mygfx;       // graphics handlers
	ValGFX* interact;    // transparent mouseover/generic interact layer
	ValGFX* mousedowngfx;// transparent mousedown interact layer for interactable controls
	ValGFX* backgroundgfx=NULL;  // background layer.  instead of makewhite 

	short UUID = 0; // filled by valwindow, determines priority.
	ValTextControl* textformat;  // options may need copying if not default

	bool GOLOBAL_B; // current value of 
	string GLOBAL_S;// global var to avoid
	int GLOBAL_I;   //cross-thread collisions

//globals. need pointer at runtime
	void* GLOBAL_POINTER; //when loading these will have to be set somehow...
	string GLOBAL_POINTER_VARNAME = ""; // use these for loading/saving to registered variables class
	string GLOBAL_POINTER_VARTYPE = "";// notes-write variable pointer registering class

	//volatile values- changes during runtime based on window state
	bool is_interacted;
	short interact_count;
	bool is_mousedown;
	bool needs_redraw;
	bool needs_repaint;
	bool drawn_aux;
	string sval; // listbox current value and more soon
	short multiareax = 0, multiareay = 0; // multiarea selection value
	short highlight_index = 0; // may change this to [3] to go with highlight_values
	std::mutex drawmutex;

	//type specific vars
	short LISTDATA_OFFSET = 0; // what index should be first displayed  should make this value[3] instead
	strlist* listdata = NULL;//  will have to build this or load this after control load.
	string listbox_function_name = "";

	void drawtogfx(); // runonce to set up windows vars-- draw for type. 
	void draw();  // run after drawtogfx to redraw VC components
	bool has_drawn;
	void draw_highlight(); // draw and remove mouseover highlight
	void remove_highlight();
	
	void draw_interact(); // draw and remove interact animation
	void remove_interact();

	


	void clipimage(ValGFX& source, int sx, int sy, int ww, int hh, int dx, int dy);  
	void drawme(ValGFX& gfx);
	void setlabel(string l);
	//void clicked();


	// wanted: 
	void to_varlist_data();
	void from_varlist_data();
	string generate_quickcode(); // both of these may make more since in valwindow
	string parse_quickcode();  // generate/interpret control specific string for quick control creation.

	// beta section. or needs work:



	void mouseover(bool tf, short xx, short yy);
	void SetFont(string font);
	void clicked(int xx, int yy);
	void mousedown(bool tf, short xx, short yy);

	void toggle_highlight() { do_highlight = !do_highlight; }
	void set_highlight(bool a) { do_highlight = a; }

	void set_listbox_function(void* fn, string name) {
		GLOBAL_POINTER = fn; listbox_function_name = name;
	}
	void check_global() {
		if (ISGLOBAL) {
			switch (type) {
			case VC_GLOBAL_STAT_INT:
				if (*(int*)GLOBAL_POINTER != GLOBAL_I) {
					GLOBAL_I = *(int*)GLOBAL_POINTER;
					drawtogfx();
					needs_redraw = true;
				}
			break;
			case VC_GLOBAL_STAT_STRING:
				if (*(string*)GLOBAL_POINTER != GLOBAL_S) {
					GLOBAL_S = *(string*)GLOBAL_POINTER;
					drawtogfx();
					needs_redraw = true;
				}
				break;

			}
		}
	}
	void resize(int ww, int hh);
	void RESERVED_resize(int ww, int hh);
	void move(int xx, int yy, int ww, int hh, bool abs);
	

	//  beta:
	string background_fname="";
	void load_background(string fname) {
		if (backgroundgfx->bits == NULL) {
			
			backgroundgfx->Get_blank_buffer(width, height);
			backgroundgfx->copy_buf();
		}
		cout << "loading background image: " << fname << "\n";
		backgroundgfx->load_image_sect(fname, 0, 0);
		//drawtogfx();
		background_fname = fname;
		needs_repaint = true;
		needs_redraw = true;
	}
#define VC_NUMBLURS_DEFAULT 2
#define VC_TEXTCOLOR_DEFAULT RGB(140, 20, 50);
#define VC_NODRAW_DEFAULT false
#define VC_ISTRANSP_DEFAULT false
#define VC_NOINTERACT_DEFAULT false
#define VC_FONTNAME_DEFAULT "Consolas"
#define VC_NOTEXT_DEFAULT false

	string export_markup_string(bool export_extended) {

		string temp = label;
		//if (type == VC_SLIDER)temp = sval;
		if (type == VC_SLIDER)temp =temp+":"+ sval;
		if (temp[0] == 0)temp = "";
		if(temp!="")cslformat(temp);
		int xx = x, yy = y;
		if (bottom_align != 0)yy = bottom_align;
		if (right_align != 0)xx = right_align;
		//cout << "markuptemp: *" << temp << "*"<<(int)temp[0]<<"\n";
		string ret =  "title=" + title + ",type=" + VC_TYPE_tostr(type)+",text=" + temp.c_str() +",x=" + ctostr(xx) + ",y=" + ctostr(yy) + ",w=" + ctostr(width) + ",h=" + ctostr(height);
		if (listbox_function_name != "") ret += ",listboxfunc=" + listbox_function_name;
		switch (type) {
		case VC_LISTBOX:
		case VC_EDIT:
		case VC_PASSWORD:
		case VC_BUTTON:
		case VC_GLOBAL_STAT_STRING:
		case VC_GLOBAL_STAT_INT:
		case VC_GLOBAL_STAT_BOOL:
			if (dataname != "")ret += ",dataname=" + dataname;
			break;
		}
		if (export_extended) {
			if(numblurs!=VC_NUMBLURS_DEFAULT)ret += ",numblurs=" + ctostr(numblurs);
			
			if (textformat->fontname != VC_FONTNAME_DEFAULT) {
				ret += ",textfont=";
				ret += textformat->fontdat.lfFaceName;
			}
			if (textformat->fontdat.lfHeight != VTC_DEFAULT_TEXT_HEIGHT) ret += ",textfontsize=" + ctostr(textformat->fontdat.lfHeight);
			if (IS_TRANSP != VC_ISTRANSP_DEFAULT)ret += (IS_TRANSP ? ",transparent=true" : ",transparent=false");
			if (NO_draw != VC_NODRAW_DEFAULT) ret += ",nodraw=" + ctostr(NO_draw);// ? "true" : "false");
			if (NO_interact != VC_NOINTERACT_DEFAULT)ret += ",nointeract=" + ctostr(NO_interact);
			if (NEEDSPARENT)ret += ",needsparent=true";
			if (background_fname != "") ret += ",background=" + background_fname;
			if (tabname != "")ret += ",tabname=" + tabname;
			
		}

		return ret;
	}
};


void ValControl::set_defaults(BYTE t, int xx, int yy, int ww, int hh, string l, string ti = "") {
	label = l;
	title = ti;
	type = t;
	x = xx;
	y = yy;
	width = ww;
	height = hh;
	value[0] = 0;
	textformat->content = l;
	NO_draw = VC_NODRAW_DEFAULT;
	interact_count = 0;
	NO_interact = VC_NOINTERACT_DEFAULT;
	NO_text = VC_NOTEXT_DEFAULT;

	ISGLOBAL = false;
	IS_TRANSP = VC_ISTRANSP_DEFAULT;
	GLOBAL_POINTER = NULL;
	windows_control = NULL;
	
	needs_redraw = false;
	has_drawn = false;
	drawn_aux = false;
	UUID = VC_random(20000);
	NEEDSPARENT = false;

	tabhwnd = NULL;
}
void ValControl::start_gfx(int ww, int hh) {
	textformat = new ValTextControl(VC_FONTNAME_DEFAULT, 0, 0, ww, hh);
	textformat->color = VC_TEXTCOLOR_DEFAULT;

	mygfx = new ValGFX();
	mygfx->Get_blank_buffer(ww, hh);
	mygfx->copy_buf();
	interact = new ValGFX();
	interact->Get_blank_buffer(ww, hh);
	interact->makeblack();

	mousedowngfx = new ValGFX();
	mousedowngfx->Get_blank_buffer(ww, hh);
	mousedowngfx->makeblack();
	
	backgroundgfx = new ValGFX();

	numblurs = VC_NUMBLURS_DEFAULT;
}

ValControl::ValControl(BYTE t, int xx, int yy, int ww, int hh, string l, HWND &pa, string ti="") {
	parent = pa;
	start_gfx(ww, hh);
	set_defaults(t, xx, yy, ww, hh, l, ti);
	drawtogfx();
	
}

ValControl::ValControl(BYTE t, int xx, int yy, int ww, int hh, string l, string ti="") {
	start_gfx(ww, hh);
	set_defaults(t, xx, yy, ww, hh, l, ti);
	
	
	drawtogfx();
}

void ValControl::setlabel(string l) {
	if (type == VC_LOADINGBAR) {
		sval = l;
		needs_repaint = true;
		needs_redraw = true;
		return;
	}
	label = l;
	textformat->content = l;
	drawtogfx();
	needs_redraw = true;
}
void ValControl::SetFont(string font) {
	textformat->SetFont(font);
}
void ValControl::resize(int ww, int hh) {
	RESERVED_resize(ww, hh);  // reserved version no longer needs to be reserved. remove reserved version
}
/***************************************************************end constructor/setter/checker block*********************************************/
/***************************************************************start graphics block*****************************************************/


void ValControl::drawme(ValGFX& gfx) {
	if (needs_repaint) {
		drawtogfx();
		needs_repaint = false;
	}
	if (NO_draw)return;
	if (IS_TRANSP){
		drawmutex.lock();
		mygfx->transCopyToGFX(gfx, x, y);
		drawmutex.unlock();
		return;
    }
	drawmutex.lock();
	mygfx->CopyToGFX(gfx, x, y);
	drawmutex.unlock();
	//mygfx->HDCdraw(mygfx->hdcDesktop, gfx.hbmp, x, y);
	//if(interactcount>0)interact->HDCdraw(interact->hdcDesktop,gfx.hbmp,x,y);

}



void ValControl::drawtogfx() {  // this version may be redraw. remove edit and other windows handled components.
	
	drawmutex.lock();

	if (backgroundgfx->bits != NULL) {
		//cout << "drew background" << endl;
		mygfx->makewhite();
		backgroundgfx->transCopyToGFX(*mygfx, 0, 0);
		//backgroundgfx->CopyToGFX(*mygfx, 0, 0);
	}
	else { mygfx->makewhite(); }
	string temp;
	switch (type) {

	case VC_BUTTON:
		//draw box around edge of gfx 
		if (backgroundgfx->bits == NULL) mygfx->makecolor(VRGB_GREY_VVLIGHT);
		mygfx->draw_boarder2(1, 0, VRGB_GREY_LIGHT);
		//mygfx->draw_boarder2(1, 1, VRGB_GREY_LIGHT);
		mygfx->draw_boarder2(2, 2, VRGB_GREY);
		if (!drawn_aux) {
			interact->draw_box(3, 3, width - 3, height - 3, 2, 1, (VRGB)VRGB_GREEN);
			mousedowngfx->draw_box(4, 4, width - 4, height - 4, 4, 1, (VRGB)VRGB_BLUE);
		}

		//set textx,y to  left align or center

		//textformat->x = 20;
		textformat->content = label;
		textformat->x = (width / 2) - (textformat->getrealtwidth() / 2);
		textformat->y = (height / 2) - (textformat->getrealtheight() / 2);//10;
		break;
	case VC_CHECKBOX:
		mygfx->draw_boarder();
		mygfx->draw_box(7, height / 3, 25, (height / 3) * 2, 2, 0, (VRGB)VRGB_RED);
		if (value[0] != 0) {
			mygfx->drawline_slope(7, height / 3, 25, (height / 3) * 2, 5, (VRGB)VRGB_RED);
			//mygfx->draw_box(9, height / 3+2, 23,((height / 3) * 2)-2,2, 0, (VRGB)VRGB_RED);
		}
		if (!drawn_aux) {
			interact->draw_box(3, 3, width - 3, height - 3, 2, 1, (VRGB)VRGB_GREEN);
			mousedowngfx->draw_box(4, 4, width - 4, height - 4, 4, 1, (VRGB)VRGB_BLUE);
		}
		//set textx,y to  left align or center
		textformat->content = label;
		textformat->x = 30;
		textformat->y = (height / 3) - 3;
		// draw checkbox
		// draw x state
		// set textxy to just past box
		break;
	case VC_LABEL:
		textformat->content = label;
		textformat->x = 0;
		textformat->y = (height / 3) - 5;
		mygfx->makeblack();
		IS_TRANSP = true;
		numblurs = 1;
		// set textxy to left align
		break;
	case VC_LISTBOX:
		numblurs = 0;
		if (!drawn_aux) {
			is_multiarea = true;
			interact->draw_box2(3, 2, width - 6, listbox_cellheight - 3, 2, 1, (VRGB)VRGB_PURPLE);
			mousedowngfx->draw_box2(3, 2, width - 6, listbox_cellheight - 3, 3, 1, (VRGB)VRGB_BLUE_LIGHT);
			highlight_values[0] = VRGB_CYAN;
			highlight_values[1] = VRGB_GREEN;
			highlight_index = 0;
			value[1] = 0;
		}
		if (listdata != NULL) {


			textformat->x = 5;
			int indexes = (height - (LISTBOX_ARROWHEIGHT * 2)) / listbox_cellheight;
			//indexes--;
			short listlen = listdata->length();

			indexes = (indexes < listlen ? indexes : listlen);
			for (int i = 0; i < indexes; i++) {

				//textformat->content = (*listdata)[i];
				textformat->content = listdata->ITT(i + LISTDATA_OFFSET);
				textformat->y = ((listbox_cellheight * i)) + LISTBOX_ARROWHEIGHT;
				if (value[0] == i) {
					sval = textformat->content;
					//mygfx->drawline(0, (listbox_cellheight * (i + 1)) + 8, width, true, 3, VRGB_BLUE);//selected line
					mygfx->color_section(0, textformat->y, width - 2, listbox_cellheight, (VRGB)VRGB_YELLOW);
				}
				textformat->DIBdraw(mygfx->hdcDesktop, mygfx->hbmp);
				//cout << "listbox drawtogfx loop i: " << i << "tf->y: " << textformat->y << "\n";
				mygfx->draw_box(0, textformat->y, width - 2, textformat->y + (listbox_cellheight), 2, 1, (VRGB)VRGB_RED);
				//cout << "2listbox drawtogfx\n";// loop tf->y: " << textformat->y << "\n";



			}
			textformat->y = 0;
			textformat->x = 0;
			value[8] = (value[0] + LISTDATA_OFFSET);
			if (LISTDATA_OFFSET != 0&& listlen!=0) value[8] %= listlen;

			textformat->content = ctostr(LISTDATA_OFFSET) + ":" + ctostr(listlen) + ":" + ctostr(value[8]);
			value[1] = indexes * listbox_cellheight + LISTBOX_ARROWHEIGHT;

			//mygfx->draw_box(0, 1, width - 2, 10, 2, 1, (VRGB)VRGB_RED_DARK);
			//draw scroll buttons w/ highlight

			//mygfx->color_section(0, 0, width - 1, 10, (VRGB)highlight_values[highlight_index]);
			mygfx->color_section(0, 0, width - 1, LISTBOX_ARROWHEIGHT, (VRGB)highlight_values[highlight_index]);
			short wit = width / 2;
			mygfx->drawtriangle(wit - 7, 9, wit, 2, wit + 7, 9, 3, (VRGB)VRGB_BLACK);
			//mygfx->draw_box(0, height-11, width - 2, height-1, 2, 1, (VRGB)VRGB_RED_DARK);

			//mygfx->color_section(0, height - 11, width - 2, 10, (VRGB)highlight_values[highlight_index]);
			mygfx->color_section(0, height - (LISTBOX_ARROWHEIGHT + 1), width - 2, LISTBOX_ARROWHEIGHT, (VRGB)highlight_values[highlight_index]);
			mygfx->drawtriangle(wit - 7, height - 9, wit, height - 2, wit + 7, height - 9, 3, (VRGB)VRGB_BLACK);
		}
		break;
	case VC_EDITML:
	case VC_EDIT:  // actually uses wm_edit
		if (windows_control == NULL) {
			LPARAM lp = 0;
			if (type == VC_EDITML)lp = 1;
			SendMessage(parent, VW_EDITCNTRL, (WPARAM)this, lp);
			while (windows_control == NULL)Sleep(1);
			has_drawn = true;
			//textformat->getrealtwidth();
			textformat->get_HFONT();
			SendMessage(windows_control, WM_SETFONT, (WPARAM)textformat->myfont, (LPARAM)1);//(WPARAM)font
			Sleep(10);
			SetWindowTextA(windows_control, title.c_str());
			temp = title;
			title = label;
			label = temp;
			numblurs = 0;


		}
		if (!do_highlight)mygfx->draw_boarder2(3, 0, VRGB_GREY_LIGHT);
		needs_redraw = true;
		//cout << "out of vcedit\n";
		// windows handles drawing the whole text box console
		// set text of control 
		// reset bkgfx bounds to text area
		// if firstdraw, create windows edit control hwnd here
		// fill windows_control hwnd member for access
		break;
	case VC_PASSWORD:
		if (windows_control == NULL) {
			//cout << "threw message\n";
			//UUID = VC_random(6000);
			SendMessage(parent, VW_PASSCNTRL, (WPARAM)this, (LPARAM)0);

			numblurs = 0;
		}
		if (!do_highlight)mygfx->draw_boarder2(3, 0, VRGB_GREY_LIGHT);
		needs_redraw = true;
		break;
	case VC_GLOBAL_STAT_INT:
		mygfx->makeblack();
		textformat->content = str_replace(label, "*I", ctostr(GLOBAL_I));
		textformat->IS_TRANSP = false;
		IS_TRANSP = false;
		break;
	case VC_GLOBAL_STAT_STRING:
		mygfx->makeblack();
		textformat->content = str_replace(label, "*S", GLOBAL_S);
		textformat->IS_TRANSP = false;
		IS_TRANSP = false;
		break;
	case VC_IMAGE:
		if (!drawn_aux) {
			NO_text = true;
			cout << "loading image: " << label << endl;
			//mygfx->load_image_sect(label,0,0);
			load_background(label);
			NO_interact = true;
		}
		break;
	case VC_SLIDER:
		if (!drawn_aux) {
			breakarg(label, label, sval, ':');
			if (sval == "")sval = "0";
			//sval = label;
			//label = "0";
			is_multiarea = true;
		}
	case VC_LOADINGBAR:
		if (!drawn_aux) {
			
			textformat->x = (width / 2) - (textformat->getrealtwidth() / 2);
			textformat->y = (height / 2) - 10;
			numblurs = 0;
			if (type == VC_LOADINGBAR)NO_interact = true;
		}
		mygfx->makecolor(VRGB_GREY_VLIGHT);
		mygfx->draw_boarder2(0, 0, VRGB_GREY_LIGHT);
		//mygfx->draw_boarder2(1, 1, VRGB_GREY_LIGHT);
		mygfx->draw_boarder2(1, 2, VRGB_GREY);



		value[0] = ctoint(sval);
		if(type==VC_LOADINGBAR)textformat->content = "LOADING:"+sval+"%";
		else textformat->content = label+ ":"+ sval + "%";
		//cout << "1drew loadingbar at " << value[2] << "wide  val1: " << value[1]<<"\n";
#define GVC_LOADINGBARSIZE 8
		//if (value[0] != value[1]) {
		mygfx->color_section(GVC_LOADINGBARSIZE, GVC_LOADINGBARSIZE, width - (GVC_LOADINGBARSIZE * 2), height - (GVC_LOADINGBARSIZE * 2), VRGB_GREY_VVLIGHT);
		if (value[0] > 0) {
			if (value[0] == 100)value[2] = (width - (GVC_LOADINGBARSIZE * 2));
			else value[2] = ((width - (GVC_LOADINGBARSIZE * 2)) * value[0]) / 100;
			//cout << "2drew loadingbar at " << value[2] << "wide\n";
			mygfx->color_section(GVC_LOADINGBARSIZE, GVC_LOADINGBARSIZE, value[2], height - (GVC_LOADINGBARSIZE * 2), VRGB_BLUE_DARK);
		}
		value[1] = value[0];
		//}
		break;
	}
	//print label at textxy
	drawn_aux = true;
	if(!NO_text)textformat->DIBdraw(mygfx->hdcDesktop, mygfx->hbmp);

	if (numblurs > 0)
		for (int i = 0; i < numblurs; i++)mygfx->blur();
	if (do_highlight)mygfx->draw_boarder2(2, 1, VRGB_PURPLE);
	drawmutex.unlock();
}
/********************************************** end graphics block*******************************************/
/********************************************** start interaction block***************************************/

void ValControl::mouseover(bool tf, short xx, short yy) {
	if (NO_interact)return;
	xx -= x;
	yy -= y;
	bool ml_redraw = false;
	if (is_multiarea) {// listbox only currently, maybe will add more multiarea controls later.
		short hy;
		hy = (((yy - (LISTBOX_ARROWHEIGHT+5)) / listbox_cellheight) * listbox_cellheight) + LISTBOX_ARROWHEIGHT;
		if (hy == multiareay && is_interacted == tf && !(yy<LISTBOX_ARROWHEIGHT || yy>height - LISTBOX_ARROWHEIGHT)) {
			
			return;
		}
		else {
			ml_redraw = true;
			
		}
		multiareay = hy;
	}
	else if (is_interacted == tf || NO_interact)return;
	//cout << "\nmouseover " << label <<  "val: " << tf<< " xx,yy: "<<xx<<" , "<<yy<< endl;
	is_interacted = tf;
	switch (type) {
	case VC_LISTBOX:
		if (tf) {
			//drawtogfx();
			if ((yy<LISTBOX_ARROWHEIGHT || yy>height - LISTBOX_ARROWHEIGHT) && tf) {
				highlight_index = 3;
				highlight_values[3] = VRGB_RAND;

				multiareay = 0;
				//drawtogfx();
				needs_repaint = true;
				break;
			}
			highlight_index = 0;
			//
			if(ml_redraw)drawtogfx();
			//needs_repaint = true;
			if (multiareay < value[1]) {
				//drawmutex.lock();
				interact->transCopyToGFX(*mygfx, 0, multiareay);
				//drawmutex.unlock();
			}
		}
		else {
			highlight_index = 0;
			//drawtogfx();
			needs_repaint = true;
		}
		break;
	default:
		if (tf) {
			drawmutex.lock();
			interact->transCopyToGFX(*mygfx, 0, 0);
			drawmutex.unlock();
		}
		else needs_repaint = true;// drawtogfx();
		break;

	}

	needs_redraw = true;
}



void ValControl::mousedown(bool tf, short xx, short yy) {
	xx -= x;
	yy -= y;
	if (!is_multiarea && (is_mousedown == tf || NO_interact))return;
//	cout << "\nmousedown " << label << "val: " << " xx,yy: " << xx << " , " << yy << endl;
	is_mousedown = tf;
	
	switch (type) {
	case VC_SLIDER:
		value[7] = static_cast<int>(static_cast<float>(xx) / (static_cast<float>(width- (GVC_LOADINGBARSIZE)) / 100.0));
		if (value[7] > 100)value[7] = 100;
		if (value[7] < 0)value[7] = 00;
		sval = ctostr(value[7] );
		//cout << "caught mousedown slider event" << endl;
		drawtogfx();
		break;
	case VC_LISTBOX:
		if (tf) {
			drawtogfx();
			if (yy<LISTBOX_ARROWHEIGHT || yy>height - LISTBOX_ARROWHEIGHT)break;
			drawmutex.lock();
			mousedowngfx->transCopyToGFX(*mygfx, 0, (((yy - (LISTBOX_ARROWHEIGHT+5)) / listbox_cellheight) * listbox_cellheight) + LISTBOX_ARROWHEIGHT);
			drawmutex.unlock();
		}
		else drawtogfx();
		break;
	default:

		if (tf) {
			drawmutex.lock();
			mousedowngfx->transCopyToGFX(*mygfx, 0, 0);
			drawmutex.unlock();
		}
		else drawtogfx();
		
		break;

	}
	//drawmutex.unlock();
	needs_redraw = true;
}


void ValControl::clicked(int xx, int yy) {
	bool temp = false;
	switch (type) {
	case VC_SLIDER:

		break;
	case VC_CHECKBOX:
		if (value[0] == 0)value[0] = 1;
		else value[0] = 0;
		//cout << "toggled value to " << (bool)value[0] << endl;
		drawtogfx();
		needs_redraw = true;
		break;

	case VC_LISTBOX:

		xx -= x;
		yy -= y;
		
		if (yy > height - LISTBOX_ARROWHEIGHT) {
			LISTDATA_OFFSET++;
			if (LISTDATA_OFFSET >= listdata->length()) {
				LISTDATA_OFFSET = 0;
			}
			value[0]--;
			if (value[0] < 0)value[0] = listdata->length() - 1;
		}
		else if (yy < LISTBOX_ARROWHEIGHT) {
			LISTDATA_OFFSET--;
			if (LISTDATA_OFFSET < 0)LISTDATA_OFFSET = listdata->length() - 1;
			value[0]++;
			if (value[0] > listdata->length() - 1)value[0] = 0;
		}
		else {
			value[0] = (yy - (5+LISTBOX_ARROWHEIGHT)) / listbox_cellheight;
			temp = true;
			//cout << "listbox clicked, set value[0] (clicked index) to " << value[0] << endl;
		}
		drawtogfx();
		needs_redraw = true;
		if (temp && GLOBAL_POINTER != NULL && listbox_function_name !="") {  // && has_listbox_function bool or something
			cout << "threw event thread from listbox: " << listbox_function_name << endl;
			_beginthread((_beginthread_proc_type)GLOBAL_POINTER, 0, parent);
		}
		break;
		//cout << "processed clicks for " << label << endl;
	}
}
void ValControl::move(int xx, int yy, int ww, int hh, bool abs) {
	int xxx, yyy;
	if (abs) {
		xxx = x + xx;
		yyy = y + yy;
		if (xxx<0 || xxx>ww || yyy<0 || yyy>hh)return;
		xx = xxx; yy = yyy;
	}
	else if (xx == x && yy == y) return;
//	cout << "vc_switch move: " << xx << ": " << yy << endl;
	switch (type) {
	case VC_EDIT:
	case VC_EDITML:
	case VC_PASSWORD:
		SetWindowPos(windows_control, 0, xx + 2, yy + 2, (width)-4, (height)-4, SWP_DRAWFRAME);
	default:
		x = xx;
		y = yy;
		needs_redraw = true;
		needs_repaint = true;
		break;
	}
}
//no longer needs to be reserved.
void ValControl::RESERVED_resize(int ww, int hh) {
	//wm controlls can just call windowresize
	//normal controls have to reset gfx sizes too.
	if (ww == width && hh == height)return;
	switch (type) {

	case VC_IMAGE:
		backgroundgfx->clearmem();
		backgroundgfx->Get_blank_buffer(ww, hh);
		width = ww;
		height = hh;
		drawn_aux = false;
		mygfx->clearmem();
		mygfx->Get_blank_buffer(ww, hh);
		mygfx->copy_buf();
		//load_background(background_fname);
		break;

	case VC_EDIT:
	case VC_EDITML:
	case VC_PASSWORD:
		SetWindowPos(windows_control, 0, x + 2, y + 2, (ww) - 4, (hh) - 4, SWP_DRAWFRAME);
	default:
		drawn_aux = false;
		mygfx->clearmem();
		mygfx->Get_blank_buffer(ww, hh);
		mygfx->copy_buf();

		interact->clearmem();
		interact->Get_blank_buffer(ww, hh);
		interact->makeblack();

		mousedowngfx->clearmem();
		mousedowngfx->Get_blank_buffer(ww, hh);
		mousedowngfx->makeblack();
		break;
	}
	width = ww;
	height = hh;
	drawtogfx();
	needs_redraw = true;
}

void listbox_selectstring(ValControl* lb, string whatstr) {
	stringlist* data = lb->listdata;
	int index = -1;
	foreach(i, data->length()) {
		if (data->index(i) == whatstr) {
			index = i; break;
		}
	}
	if (index != -1) {
		lb->LISTDATA_OFFSET = index;
		lb->value[0] = 0;
		lb->drawtogfx();
		lb->needs_redraw = true;
	}
	else {
		cout << "could not find *" << whatstr << "* in listbox list\n";
	}

}
