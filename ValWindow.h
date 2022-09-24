/*ValWindow.h   Please excuse the limited explanitory comments.  I tried to make the function names and arguments self explanitory. 
* handles windows and controls on those windows. 
  handles events on those windows
  



*/

#pragma once


// change this to false to skip blur on splashscreen for faster boot/testing
#define VW_splash_doblurout true  

#include<string>
#include<WinUser.h>
using namespace std;


LRESULT CALLBACK ValWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ValWindowPasswordControlWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
void VW_slpashscreen_msgloop_kill(void* a);
void VW_splashscreenthread(void* a);
void ValWindow_event_thread(void* a);
void ValWindow_render_thread(void* a);
void* __VWM_getdata(string name, string& type);
// evaluate a generic windows edit control 
string eval_edit_control(HWND hwnd) {
	int len = GetWindowTextLengthA(hwnd) + 1;
	char* a = new char[len];
	GetWindowTextA(hwnd, a, len);
	string ret = a;
	delete[] a;
	return ret;

}

//wndproc control creation constants   defunct for render thread control creation? 
#define VW_EDITCNTRL 0x0444
#define VW_PASSCNTRL 0x0544
#define VW_CREATE_WINDOW 0x0644
#define VW_CREATE_CONTROL 0x0654
#define VW_CREATE_WINDOW_MSG 0x0645

#include<Windows.h>
#include<WinUser.h>
#include<wingdi.h>
#include<commctrl.h>
#pragma comment(lib,"Comctl32.lib") 
#pragma comment(lib,"msimg32")
struct VRECT {
	int x, y, w, h;
};
string VRECTtostr(VRECT r){
	return "x=" + ctostr(r.x) + ",y=" + ctostr(r.y) + ",width=" + ctostr(r.w) + ",height=" + ctostr(r.h);
}
inline bool VRECT_collision(VRECT a, VRECT b) {
	return a.x<(b.x + b.w) && (a.x + a.w)>b.x && a.y<(b.y + b.h) && (a.y + a.h)>b.y;
}
inline bool dim_collision(int x, int y, int w, int h, int xx, int yy, int ww, int hh) {
	return x<(xx + ww) && (x + w)>xx && y<(yy + hh) && (y + h)>yy;
}
inline bool point_collision(int x, int y, int xx, int yy, int ww, int hh) {
	return x >= xx && x <= xx + ww && y >= yy && y <= yy + hh;
}
#include"valtimer.h"
#include"valtextcontrol.h"
#include"valgfx.h"
#include"ValControl.h"
#include"ValEventHandler.h"


//valwindow type constants
#define VW_transparent 0
#define VW_normal 1
#define VW_splash 2
#define VW_game 3


struct splashscreen_struct {
	string str;
	bool b;
	int time;
	int x, y, w, h;
	void* valwindptr;
};
splashscreen_struct* build_splashscreen_struct(string s, int time, int x = 0, int y = 0, int w = 0, int h = 0) {
	splashscreen_struct* ret= new splashscreen_struct;
	ret->str = s;
	ret->b = false;
	ret->time = time;
	ret->x = x;
	ret->y = y;
	ret->w = w;
	ret->h = h;
	ret->valwindptr = NULL;
	return ret;
}
void fill_splashscreen_struct(splashscreen_struct* ret, string s, int time, int x = 0, int y = 0, int w = 0, int h = 0) {
	
	ret->str = s;
	ret->b = false;
	ret->time = time;
	ret->x = x;
	ret->y = y;
	ret->w = w;
	ret->h = h;
	ret->valwindptr = NULL;
}
struct valwindow_create_struct {
	string name;
	int x, y, h, w;
	BYTE type;
};
void build_valwindow_create_struct(valwindow_create_struct* ret, string n, int x, int y, int w, int h, BYTE t){
	ret->name = n;
	ret->x = x;
	ret->y = y;
	ret->h = h;
	ret->w = w;
	ret->type = t;

}

#define VW_MOUSECAP_CLICK 1
#define VW_MOUSECAP_RCLICK 4
#define VW_MOUSECAP_LDOWN 2
#define VW_MOUSECAP_MOVE 3
struct mouse_capture_struct {
	BYTE type;
	int x, y;
};

class ValWindow { 
	/* included by ValWindowManager.h with cross dependancies. 
	// Depends on          
	//	          ValEventHandler->ValTimer
	//            ValGFX->ValTextControl
	//            ValControl->strlist.h
	//            (gdi comctrl windows)
	 Valwindow manages all aspects of GUI drawing and interaction for a window.
	 Create ValWindow variables by calling Create_Window from WindowMan Singlet global variable.
	 
	 utilize valWindowEditor.h to edit live windows and generate control code
	 in prep for valscript, register all external variables through WindowMan.
	 add controls to a ValWindow (currently 11/09/2020) by calling
	 AddControl(string datalist)
	 format: "title=title,text=label,type=VC_LABEL,x=#,y=#,w=#,h=#"
	 optional: 
	 ",numblurs=#"  number of times to blur the control after drawing (soften)
	 ",dataname=registeredvar"  associated data- button/listbox/global_stat types require this
	                            register properly typed data with WindowMan with registeredvar name first
	 ",transparent=true/false" white in control is transparent
	 ",textfont=Fontname"  see valtextcontrol for list of basic fontnames
	 ",nointeract=true/false  make this control non-interactive
	 ",nodraw=true/false  enable/disable draw on host window
	 ",background=imgfilename.jpg/png/bmp" sets and loads background img



	 **defunct**
	 add controls to a ValWindow (currently 10/31/2020) by calling  --- Depreciated but still implimented 11/9
	 add_control_ex for most standard ValControl's - button, label
	 add_editcontrol for standard windows edit control by HWND (I'm not ready to deal with that mess)
	 add_passwordcontrol for standard windows password control by HWND (see above)
	 create_listbox to create listbox control. 
	 add_global_stat_int to add a global variable watcher output .
	 eventually, will simplify all of these into a single(set of?) function call to windowman switching by type. 
	 eventually, will add a system to load window by an HTML esqu file, including function calls by varname. 
	 
	 once I get a working listbox, I'm relatively sure I can create a rudamentary form designer using my form designer. --alpha.01 edit@ 11/9/20
	 should be easy, but I'll probably have to use varlist which comes with a whole chain of dependancies that I need to clear up from 2009. -- fixed and implimented edit@11/9/20

	 I've been working on this system on and off now for nearly a month.  it's getting a little out of hand. I never meant for it to get this complicated.
	 . and now I can't stop adding to it. 
	 *********end defunct**************
	 add controls to window using wind += string or AddControl(string).  see AddControl for formatting.  use valWindowEditor to generate control info live


	 todo:
	 CODE CLEANUP for the whole stack. 


	*/
public:
    HWND myhwnd;  // HWND for my window
	HDC myhdc;  // DC to client area for my window
	short myUUID; //  UUID used by window manager to keep similar windows separate

    int clientwidth, clientheight;
	int Framecount;
	string windowname;
	string windowtitle;
	string windowclass;  // unimplemented-  for extended classes, template windows, meta controls and virtual windows
	
	short background_x, background_y;
	string background_fname="";
	ValGFX mygfx;      //window drawing layer
	ValGFX mygfxback;  // background layer
	ValGFX mygfxforg;  //forground layer  used for internal interacts.
	void load_background(string fname, int x, int y);

	ValEventHandler* events; // events handler for this window. 
	short register_event(string name, VRECT t, void* fn); // register a click event 

	// handles mouseover/click draw interactions on form- usually highlights controls that can be/are clicked.
	// but may be extended later to handle mouseover animations 
	BYTE control_interact_index;
	BYTE control_interact_count;
	short interact_index;
	short mousedown_index;
	void control_mouseover(short x, short y);
	void control_mousedown(short x, short y);


	//ValWindow(); // might want to add a version of this, move other constructor to peices. 
	//ValWindow(string name);
	//ValWindow(string name, int ww, int hh);
	bool is_closed = false;  // if the user has closed the window, set this.  can destroy this  maybe.  
	bool is_master = false;  // master windows call exit(0) when they're closed by user
	ValWindow(string name, int xx, int yy, int ww, int hh, BYTE type); // simple constructor


	bool TOPMOST;
	bool is_topmost() { return TOPMOST; }
	void set_topmost(bool a) { TOPMOST = (a ? Pdo_topmost() : 0); }
	void hide() {ShowWindow(myhwnd, SW_HIDE);}
	void show() { ShowWindow(myhwnd, SW_SHOW); full_render = true; }

	// currently number of controls are limited to 256 but this is arbitrary.  can choose to realloc this block if need more than 256.
	// hopefully, making the click functions pass x/y, metacontrols can be built in ValControl to limit control explosion.
	ValControl* controls[256];
	int controlslen;
	short add_control_ex(short type, string title, string text, VRECT vrect, void* fn, bool needs_parent = false);
	bool needs_control = false, needs_control_lock = false;
	short needs_control_index = -1;
	ValControl_struct ValControl_strct;
	short add_control_ex_ts(short type, string title, string text, VRECT vrect, void* fn, bool needs_parent, HWND parent = NULL);

	inline ValControl* GetControl(string name);
	inline short find_control(string title);
	inline short find_control_UUID(short uid);

	

	ValStopwatch rendertimer;  // ValTimer var used to track how often to render/limitedrender the window
	COLORREF transparent_color; // not implemented yet
	bool full_render; // force full re-render of window if this is set
	void limited_render(); // redraw only components that have needs_redraw set.
	void render_window(); // fully re-render window
	void GFXdraw(); // draws mygfx to client

	void* associated_data[10];// helpful to pass non-associated classes into event functions, possibly,  needs parent on valcontrol required
	string associated_name[10]; // helps to deliniate between associated data points
	short associated_len;
	short associate_data(void* what, string name);
	void* get_associated_data(string name);
	
	// probably could/should be private after testing is done.
	void Pcreate_window(int xx, int yy, int ww, int hh, BYTE type, bool show=true);  // does the actual window creation.
	bool pcreate_get_center = false;
	bool Pdo_topmost() { SetWindowPos(myhwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); return true; }

	void create_splashscreen(string name, int xx, int yy, int ww, int hh, int time);
	void create_clientwindow(int ww, int hh);
	void create_clientwindow(int xx, int yy, int ww, int hh); // called on creation with full constructor
	void create_transparentwindow(int ww, int hh);
	void create_transparentwindow(int xx, int yy, int ww, int hh);

/* 
* destroy_window
* clear_window  should really write the destructors for all other classes before trying to do this
* resize_window...  this one is going to be harder.  moving/spacing controls will have to be done on the fly as is
* move_window
* 
* text_input_wind  //template popout windows
* num_input_wind
* radio_input_wind
* yn_input_wind
* 
  create accessor functions to valcontrol here by name.  can use findcontrol_byname or something for ease
* hide_control();
* disable_control()
  read_control();
* set_control_text();
* set_control_color();
* set_control_boarder();
* 
* 
* 
*/

//   beta block. 
public:
	// when AddControl etc are finished, those should be the only ones called in maincode.
	// refactor and rename all other creation type functions to private and called by this.
	// string version takes argument string in, converts to varlist and sends to varlist constructor
	// input string should be as "type=VC_LABEL,title=mytitle,text=sometext,x=10,y=10,w=50,h=599"  
	//optional dataname for controls that need data  register data with WindowMan before calling. 
	//lots more options now- transparent, nointeract, fontname, nodraw, needsparent(buttons)
	ValControl* operator +=(string x) {
		return AddControl(x);
	}
	ValControl* AddControl(string controldata) {
		
		varlist vl;
		vl.fromcsl(controldata);
		return AddControl(vl);

	}
	// commas escaped as `1
	int AddControl_offsetx = 0;
	int AddControl_offsety = 0;
	void set_ACoffsetx(int x) { AddControl_offsetx = x; }
	void set_ACoffsety(int y) { AddControl_offsety = y; }

	ValControl* AddControl(varlist& controldata,bool load_extended=true) {
		int type = VC_str_toTYPE(controldata.valueof("type"));
		string title = controldata.valueof("title");
		if (GetControl(title) != NULL) {
			cout << "WARNING:{Valwindow::AddControl} control with name " << title << " already exists on window " << windowtitle << "\n";
		}
		string text = controldata.valueof("text");
		text= cslunformat(text);
		int x = ctoint(controldata.valueof("x"));
		x += AddControl_offsetx;
		int y = ctoint(controldata.valueof("y"));
		y += AddControl_offsety;
		int w = ctoint(controldata.valueof("w"));
		int h = ctoint(controldata.valueof("h"));
		bool bottom_aligned = false, right_aligned = false;
		if (y < 0) {
			y += clientheight;
			bottom_aligned = true;
		}
		if (x < 0) {
			x += clientwidth; 
			right_aligned = true;
		}

		string ttype, dataname,temp;
		stringlist* strl;
		void* gdat=NULL;
		ValControl* ret=NULL;
		bool np;

		switch (type) {
		case VC_LISTBOX:
			 ttype="";
			 dataname = controldata.valueof("dataname");
			 strl = (stringlist*)__VWM_getdata(dataname, ttype);
			if(strl==NULL){
			//if (AddControl_queuedata == NULL|| AddControl_datatype != typeid(stringlist*).name() ) {
				cout << "no stringlist named " << dataname << " registered with WindowMan\n";
				cout << "cannot create listbox without stringlist- call WindowMan.register_data or VWM_register_data first" << endl;
				return NULL;
			}
			ret = controls[create_listboxts(title, text, VRECT{ x,y,w,h }, strl)];
			temp = controldata.valueof("listboxfunc");
			if (temp != "") {
				ret->GLOBAL_POINTER = __VWM_getdata(temp, ttype);
				ret->listbox_function_name = temp;
			}
			ret->dataname = dataname;
			break;
		case VC_EDIT: // have to set wm controls here maybe
			ret = controls[add_editctrl_ts(title, VRECT{ x,y,w,h }, text)];
			if (controldata.isset("tabname")) {
				ret->tabname = controldata.valueof("tabname");
				//ret->tabhwnd = GetControl(ret->tabname)->windows_control;
				
				//if (ret->tabhwnd == NULL)cout << "Warning: edit control " + ret->title + " tab not linked- control not created yet?\n";
			}
			break;
		case VC_PASSWORD:
			if (text == "") {
				dataname = controldata.valueof("dataname");
				text = dataname;
			}
			ret = controls[add_passwordctrl_ts(title, VRECT{ x,y,w,h }, text)];
			break;
		case VC_GLOBAL_STAT_STRING:
		case VC_GLOBAL_STAT_INT:
		case VC_GLOBAL_STAT_BOOL:
			dataname = controldata.valueof("dataname");
			gdat = __VWM_getdata(dataname,ttype);
			if (gdat == NULL) {
				cout << "no data named " << dataname << " registered with WindowMan\n";
				cout << "cannot create global stat without data- call WindowMan.register_data or VWM_register_data first" << endl;
				return NULL;
			}
			add_global_stat_int(type, title, text, VRECT{ x,y,w,h },gdat );
			ret = controls[controlslen-1];
			ret->dataname = dataname;
			break;
		case VC_BUTTON:
			
			dataname = controldata.valueof("dataname");
			if (dataname == "VC_NOFUNC" || dataname=="")gdat = VC_NOFUNC;
			else gdat = __VWM_getdata(dataname, ttype);

			if (gdat == NULL) {
				cout << "no function named " << dataname << " registered with WindowMan\n";
				cout << "cannot create button without a function- call WindowMan.register_data or VWM_register_data first" << endl;
				return NULL;
			}
			
			np = controldata.valueof("needsparent")=="true";
			
			ret = controls[add_control_ex_ts(type, title, text, VRECT{ x,y,w,h }, gdat, np, myhwnd)];
			ret->dataname = dataname;
			break;
		default:
			np = controldata.valueof("needsparent") == "true";
			ret = controls[add_control_ex_ts(type, title, text, VRECT{ x,y,w,h }, VC_NOFUNC, np, myhwnd)];
			break;
		}

		auto glambdai = [&controldata](string str, auto& data) { if (controldata.isset(str))data = ctoint(controldata.valueof(str)); };
		auto glambdasc = [&controldata](string str, auto& data) { if (controldata.isset(str))data = controldata.valueof(str).c_str(); };
		if (ret != NULL) {
			ret->parent = myhwnd;
			//ret->dataname = dataname;
			//if (controldata.isset("numblurs"))ret->numblurs = ctoint(controldata.valueof("numblurs"));
			if (load_extended) {
				glambdai("numblurs", ret->numblurs);
				if (controldata.isset("textfont"))ret->SetFont(controldata.valueof("textfont"));
				if (controldata.isset("transparent"))ret->IS_TRANSP = (controldata.valueof("transparent") == "true" ? true : false);
				if (controldata.isset("nodraw"))ret->NO_draw = (controldata.valueof("nodraw") == "true" ? true : false);
				if (controldata.isset("nointeract"))ret->NO_interact = (controldata.valueof("nointeract") == "true" ? true : false);;
				if (controldata.isset("background")&& ret->background_fname=="")ret->load_background(controldata.valueof("background"));
			
			}
			if (bottom_aligned) 
				ret->bottom_align = y - clientheight;
	
			if (right_aligned) 
				ret->right_align = x - clientwidth;
			
			//ret->needs_repaint = true;
			ret->drawtogfx();
			ret->needs_redraw = true;
		}
		return ret;

	}


	string eval_edit(string name) {
		for (int i = 0; i < controlslen; i++) {
			if (controls[i]->title == name) return eval_edit_control(controls[i]->windows_control);
		}
		return "";
	}
	int evaluate_controli(string title, int& type) {// should be capital I
		ValControl* vc;
		short index = find_control(title);
		if (index == -1) { cout << "no control: \"" << title << "\"found" << endl; type = -1; return-1; }
		type = controls[index]->type;
		return controls[index]->value[0];
	}
	bool evaluate_controlb(string title, int& type) { // should be capital B
		return (bool)evaluate_controli(title, type);
	}
	string evaluate_controls(string title, int& type) {//should be capital S
		
		short index = find_control(title);
		if (index == -1) { cout << "no control: \"" << title << "\"found" << endl; type = -1; return""; }
		type = controls[index]->type;
		return controls[index]->sval;
	}
	string evaluate_listbox(string title) {
		int a = 0;
		return evaluate_controls(title, a);
	}
	//string eval_listbox(string name) {
	//	return GetControl(name)->sval;
	//}
	bool evaluate_checkbox(string title) {
		return GetControl(title)->value[0] != 0;
	}

	void set_control_label(string title, string label) {
		short index = find_control(title);
		if (index == -1) { cout << "no control: \"" << title << "\"found" << endl; return; }
		controls[index]->setlabel(label);

	}
	void set_editctrl_text(string name, string text) {

		SetWindowTextA(controls[find_control(name)]->windows_control, text.c_str());
	}
	void press_button_byname(string name) {
		short ind = find_control(name);
		if (ind == -1) {
			cout << "no control found by : " << name << endl;
			return;
		}
		ValControl* vc = controls[ind];
		cout << "press_button_byname control found- name: " << name << "  :  " << vc->title << endl;
		short x = vc->x + (vc->width / 2);
		short y = vc->y + (vc->height / 2);
		events->throw_event_thread(x, y);
	}
	void press_button_byid(short id) {
		short ind = find_control_UUID(id);
		ValControl* vc = controls[ind];
		short x = vc->x + (vc->width / 2);
		short y = vc->y + (vc->height / 2);
		events->throw_event_thread(x, y);
	}

	void add_global_stat_int(short type, string title, string text, VRECT vrect, void* gptr) { // works for int/string/bool globals
		int i = add_control_ex_ts(type, title, text, vrect, (void*)&NoFunction,0);
		controls[i]->GLOBAL_POINTER = gptr;
		controls[i]->ISGLOBAL = true;
		controls[i]->check_global();

	}
	// calculate the automatic tab order for edit/password controls
	// tab order is creation order by default. assumes arg is newest added editctrl
	void calculate_tabs(ValControl* hold) {
		bool hasdone = false;
		ValControl* targ = NULL;
		for (int i = 0; i < controlslen; i++) {
			if (controls[i]->type == VC_EDIT || controls[i]->type == VC_PASSWORD) {
				if (hasdone) {
					targ = controls[i];
				}
				else {
					hold->tabhwnd = controls[i]->windows_control;
					targ = controls[i];
					hasdone = true;
				}
			}
		}
		if(targ!=NULL)targ->tabhwnd = hold->windows_control;
	}

	short  add_editctrl(string name, VRECT vrect, string value="") {
		ValControl* hold = new ValControl(VC_EDIT, vrect.x, vrect.y, vrect.w, vrect.h, name, this->myhwnd,value);
		hold->parent = myhwnd;
		hold->NO_interact = true;
		//hold->NO_draw = true;
		hold->IS_TRANSP = true;
		hold->title = name;
		//calculate_tabs(hold);

		//hold->label = value;
		controls[controlslen] = hold;

		return controlslen++;
	}
	short add_editctrl_ts(string name, VRECT vrect, string value = "") {
		short ind = add_control_ex_ts(VC_EDIT, name, value, vrect, VC_NOFUNC, 1);
		ValControl* hold = controls[ind];
		hold->parent = myhwnd;
		hold->NO_interact = true;
		//hold->NO_draw = true;
		hold->title = name;
		//hold->label = value;
		//controls[controlslen] = hold;
		//return controlslen++;
		return ind;
	}

	short  add_passwordctrl(string name, VRECT vrect, string buttonname = "") {
		ValControl* hold = new ValControl(VC_PASSWORD, vrect.x, vrect.y, vrect.w, vrect.h, name, this->myhwnd,buttonname);
		//ValControl* hold = controls[add_control_ex_ts(VC_PASSWORD, name, buttonname, vrect, VC_NOFUNC, 1)];
		hold->title = buttonname;
		hold->parent = myhwnd;
		hold->NO_interact = true;
		//hold->NO_draw = true;
		hold->title = name;
		hold->label = buttonname;
		//calculate_tabs(hold);
		controls[controlslen] = hold;
		while (hold->windows_control == NULL)Sleep(1);
		//hold->UUID = random(60000);
		cout << "password control for " << name << " UUID is " << hold->UUID << endl;

		//SetWindowSubclass(hold->windows_control, ValWindowPasswordControlWndProc, hold->UUID, (DWORD_PTR)this);  //beta  seems to work, but not fast...
		return controlslen++;
	}
	short  add_passwordctrl_ts(string name, VRECT vrect, string buttonname="") {
		short ret = add_control_ex_ts(VC_PASSWORD, name, buttonname, vrect, VC_NOFUNC, 1);
		ValControl* hold = controls[ret];
		cout << "password control named: " << hold->title << endl;
		cout << "password control buttonnamed: " << hold->label << endl;
		hold->title = name;
		hold->label = buttonname;
		return ret;
	}

	
	short reserved_add_control_ex(ValControl_struct* st) {
		return add_control_ex(st->type, st->name, st->label, st->vrect, st->funct, st->needs_parent);
	}
	short reserved_add_control_ex_wm(ValControl_struct* st) {
		if(st->type==VC_PASSWORD)
		return add_passwordctrl( st->name, st->vrect, st->label);
		if (st->type == VC_EDIT)
		return add_editctrl(st->name, st->vrect, st->label);
	}
	
	short create_listbox(string title, string text, VRECT vrect, strlist* list) {
		
		ValControl* hold = new ValControl(VC_LISTBOX, vrect.x, vrect.y, vrect.w, vrect.h, text);
		hold->listdata = list;
		hold->drawtogfx();
		hold->title = title;
		hold->parent = myhwnd;
		events->register_control(title, controlslen, vrect.x, vrect.y, vrect.w, vrect.h);
		controls[controlslen] = hold;
		controls[controlslen]->needs_redraw = true;
		return controlslen++;
	}
	short create_listboxts(string title, string text, VRECT vrect, strlist* list) {
		short ind = add_control_ex_ts(VC_LISTBOX, title, text, vrect, VC_NOFUNC, false);
		controls[ind]->listdata = list;
		controls[ind]->drawtogfx();
		controls[ind]->needs_redraw = true;
		return ind;
	}

	mouse_capture_struct* mouse_cap;
	bool IS_MOUSE_CAPTURED = false;
	void* capture_callback = NULL;
	// callb must be a function call to a void func(void*a) where a is ValWindow* to captured window where mouse_cap can be extracted
	bool capture_mouse(mouse_capture_struct * mcs, void* callb) {
		// implimentation is in event thread
		mouse_cap = mcs;
		IS_MOUSE_CAPTURED = true;
		capture_callback = callb;
		return true; // eventually, check to see if already captured and return false if already captured.  add bool overwrite
	}
	void release_mouse() {
		IS_MOUSE_CAPTURED = false;

	}
	void read_mousecap(int& x, int& y, BYTE& type) {
		if (!IS_MOUSE_CAPTURED)return;

		x = mouse_cap->x;
		y = mouse_cap->y;
		type = mouse_cap->type;

	}
	void set_mousecap(int x, int y, BYTE type) {
		if (!IS_MOUSE_CAPTURED)return;

		mouse_cap->x = x;
		mouse_cap->y = y;
		mouse_cap->type = type;

	}
	void unhighlight_all() {
		for (int i = 0; i < controlslen; i++) {
			controls[i]->set_highlight(false);
			controls[i]->needs_repaint=true;
			controls[i]->needs_redraw = true;
		}
	}
	// highlight all controls in rect(x,y,w,h) by collision 
	void highlight_selection(int x, int y, int w, int h) {
		ValControl* vc;
		for (int i = 0; i < controlslen; i++) {
			vc = controls[i];
			if (dim_collision(x, y, w, h, vc->x, vc->y, vc->width, vc->height)) {
				vc->toggle_highlight();
				vc->needs_repaint = true;
				vc->needs_redraw = true;
			}

		}
	}
	int last_collision_query_index = 0;
	// find a control on this window by collision. xxx returns controls index of found control or 0
	string control_nameat_c(int x, int y, int* xxx=NULL) {
		if (xxx == NULL)xxx = &last_collision_query_index;
		ValControl* vc;
		*xxx = -1;
		for (int i = 0; i < controlslen; i++) {
			vc = controls[i];
			if (point_collision(x, y, vc->x, vc->y, vc->width, vc->height)) {
				*xxx = i;
				return vc->title;
			}
		}
		return "";
	}
	// calculate all unset edit control tabs into a loop. 
	void calculate_edit_ctrl_tabs() {
		ValControl* vc, * first=NULL, * last = NULL;
		bool doneone = false;
		for (int i = 0; i < controlslen; i++) {
			vc = controls[i];
			if ((vc->type == VC_EDIT || vc->type == VC_PASSWORD) &&vc->tabname=="" && vc->tabhwnd == NULL) {
				if (!doneone) {
					first = vc;
					last = vc;
					doneone = true;
				}
				else {
					last->tabhwnd = vc->windows_control;
					last->tabname = vc->title;
					last = vc;
				}
			}
			else if (vc->tabname != "") {
				vc->tabhwnd = GetControl(vc->tabname)->windows_control;
				if (vc->tabhwnd == NULL)cout << "Warning: caculate_edit_ctrl_tabs set NULL hwnd for control " + vc->tabname + ".\n";
			}

		}
		if (last != NULL) {
			last->tabhwnd = first->windows_control;
			last->tabname = first->title;
		}

	}
	// assert highlighed Edit/password controls into a tab loop
	void calculate_edit_ctrl_tabs_highlight() {
		ValControl* vc, * first=NULL, * last = NULL;
		bool doneone = false;
		for (int i = 0; i < controlslen; i++) {
			vc = controls[i];
			if (vc->do_highlight && (vc->type == VC_EDIT || vc->type == VC_PASSWORD)) {
				if (!doneone) {
					first = vc;
					last = vc;
					doneone = true;
				}
				else {
					last->tabhwnd = vc->windows_control;
					last->tabname = vc->title;
					last = vc;
				}
			}
		}
		if (last != NULL) {
			last->tabhwnd = first->windows_control;
			last->tabname = first->title;
		}

	}

	string export_markup() {
		LPRECT lr= new RECT;
		GetWindowRect(myhwnd, lr);
		string ret = "type=WINDOW,title=" + windowname + ",x=" + ctostr(lr->left) + ",y=" + ctostr(lr->top) + ",w=" + ctostr(clientwidth) + ",h=" + ctostr(clientheight);
		if (background_fname != "")ret += ",backround=" + background_fname;
		ret += "\n";
		for (int i = 0; i < controlslen; i++) {
			ret += controls[i]->export_markup_string(true)+"\n";
		}
		delete lr;
		return ret;
	}
	
	
	/*********************************************end beta block*****************************************************/
	
};

ValWindow::ValWindow(string name, int xx, int yy, int ww, int hh, BYTE type) {
	myUUID = -1;
	myhwnd = NULL;
	interact_index = -1;
	mousedown_index = -1;
	pcreate_get_center = false;
	Framecount = 0;
	associated_len = 0;
	full_render = false;
	windowname = name;
	windowtitle = name;
	TOPMOST = true;
	clientwidth = ww;
	clientheight = hh;
	IS_MOUSE_CAPTURED = false;
	transparent_color = RGB(255, 255, 255);
	events = new ValEventHandler(ww, hh);
	//mygfx.set(ww, hh);
	mygfx.Get_blank_buffer(ww, hh);
	mygfxback.Get_blank_buffer(ww, hh);
	mygfxforg.Get_blank_buffer(ww, hh);

	if (type == VW_normal) create_clientwindow(xx, yy, ww, hh);
	if (type == VW_transparent) create_transparentwindow(xx, yy, ww, hh);
	if (type == VW_splash) {
		create_splashscreen(name, xx, yy, ww, hh, 6000); return;
	}
	controlslen = 0;
	_beginthread(ValWindow_event_thread, 0, (void*)this);
	_beginthread(ValWindow_render_thread, 0, (void*)this);

}

short ValWindow::add_control_ex(short type, string title, string text, VRECT vrect, void* fn, bool needs_parent/*=false*/) {

	ValControl* hold = new ValControl(type, vrect.x, vrect.y, vrect.w, vrect.h, text);
	hold->title = title;
	hold->parent = myhwnd;
	hold->NEEDSPARENT = needs_parent;
	controls[controlslen] = hold;
	short s = register_event(title, vrect, fn);
	if (needs_parent)events->parents[s] = myhwnd;
	events->control_id[s] = controlslen;

	controls[controlslen]->needs_redraw = true;

	return controlslen++;

}
short ValWindow::add_control_ex_ts(short type, string title, string text, VRECT vrect, void* fn, bool needs_parent, HWND parent /*= NULL*/) {
	ValControl_struct st;
	st.type = type;
	st.name = title;
	st.label = text;
	st.vrect = vrect;
	st.funct = fn;
	st.needs_parent = needs_parent;
	st.parent = parent;
	while (needs_control || needs_control_lock)Sleep(1);
	needs_control_lock = true;
	ValControl_strct = st;
	needs_control = true;
	while (needs_control)Sleep(1);
	short ret = needs_control_index;
	needs_control_index = -1;
	needs_control_lock = false;
	return ret;
}
inline ValControl* ValWindow::GetControl(string name) {
	short h = find_control(name);
	if (h == -1) return NULL;
	return controls[h];
}

inline short ValWindow::find_control(string title) {
	for (int i = 0; i < controlslen; i++) {
		if (title == controls[i]->title) return i;
	}
	return -1;
}
inline short  ValWindow::find_control_UUID(short uid) {
	for (int i = 0; i < controlslen; i++) {
		if (uid == controls[i]->UUID) return i;
	}
	return -1;
}
short ValWindow::register_event(string name, VRECT t, void* fn) {
	short r = events->register_function(name, fn);
	events->add_event(t.x, t.y, t.w, t.h, r);
	return r;
}

short ValWindow::associate_data(void* what, string name) {
	associated_data[associated_len] = what;
	associated_name[associated_len] = name;
	return associated_len++;
}

void* ValWindow::get_associated_data(string name) {
	for (int i = 0; i < associated_len; i++) {
		if (name == associated_name[i]) return associated_data[i];
	}
	cout << " no associated data named -" << name << "- in window " << windowtitle << endl;
	return NULL;
}

void ValWindow::limited_render() {
	bool didathing = false;
	for (int i = 0; i < controlslen; i++) {
		controls[i]->check_global();

		if (controls[i]->needs_redraw) {
			if (controls[i]->drawunder || controls[i]->IS_TRANSP) {
				//if(mygfxback.bits!=NULL)
				mygfx.color_section(controls[i]->x, controls[i]->y, controls[i]->width, controls[i]->height, VRGB_BLACK);
			}
			controls[i]->drawme(mygfx);
			controls[i]->needs_redraw = false;
			didathing = true;
		}
	}
	if (didathing) {
		mygfxforg.transCopyToGFX(mygfx, 0, 0);
		GFXdraw();
	}
}
void ValWindow::load_background(string fname,int x=0, int y=0) {
	mygfxback.Get_blank_buffer(clientwidth,clientheight);
	background_fname = fname;
	mygfxback.load_image(fname);
	background_x = x;
	background_y = y;
	mygfxback.CopyToGFX(mygfx, x, y);
}
void ValWindow::render_window() {
	mygfx.makeblack();
	mygfxback.CopyToGFX(mygfx,0,0);
	for (int i = 0; i < controlslen; i++) {
		controls[i]->drawme(mygfx);
	}
	mygfxforg.transCopyToGFX(mygfx, 0, 0);
	GFXdraw();

}



void ValWindow::control_mouseover(short x, short y) {
	//cout << "in control_mouseover x,y: " << x << " , " << y << "\n";

	short index = -1;
	if (y != -1) index = events->control_at(x, y);
	if (index >= controlslen)return;
	if (interact_index != index && interact_index > -1 && controls[interact_index] != NULL) {

		controls[interact_index]->mouseover(false, x, y);
	}
	interact_index = index;
	if (index < 0) return;

	controls[index]->mouseover(true, x, y);
}
void ValWindow::control_mousedown(short x, short y) {
	short index = events->control_at(x, y);
	//if (index == -1)return;
	if (mousedown_index != index && mousedown_index != -1 && controls[mousedown_index]!=NULL) {
		controls[mousedown_index]->mousedown(false,x,y);
		cout << "mousedown_index:" << interact_index << endl;
	}

	mousedown_index = index;
	if (index == -1) return;
	controls[index]->mousedown(true,x,y);
}


void ValWindow::GFXdraw(){
	HDC dc = GetDC(myhwnd);
	mygfx.blt(dc, 0, 0);
	DeleteDC(dc);
}


void ValWindow::create_transparentwindow(int ww, int hh) {
	Pcreate_window(0, 0, ww, hh, 0);
}
void ValWindow::create_transparentwindow(int xx, int yy, int ww, int hh) {
	Pcreate_window(xx, yy, ww, hh, 0);
}
void ValWindow::create_clientwindow(int ww, int hh) {
    Pcreate_window(0, 0, ww, hh,1);
}
void ValWindow::create_clientwindow(int xx, int yy, int ww, int hh) {
	Pcreate_window(xx, yy, ww, hh, 1);
}
void ValWindow::create_splashscreen(string name,int xx, int yy, int ww, int hh, int time) {
	
	
	//cout << "starting splashscreen vars: " << name << " " << xx << " " << yy << " " << ww << " " << hh << " " << time << endl;
	mygfx.load_image(name);
	if (ww == 0) ww = mygfx.width;
	if (hh == 0) hh = mygfx.height;
	clientwidth = ww;
	clientheight = hh;
	//cout << " ww:hh   " << ww << ":" << hh << endl;
	pcreate_get_center = true;
	Pcreate_window( xx, yy, ww, hh, 0);
	//mygfx.blt(myhdc, 0, 0);
	//mygfx.blur();
	GFXdraw();

	
}
void ValWindow::Pcreate_window(int xx, int yy, int ww, int hh, BYTE type,bool show/*=true*/) {
	HWND hWnd;
	WNDCLASSA wnd = { };
	wnd.lpfnWndProc = ValWindowWndProc;
	//wnd.hInstance = hInstance;
	wnd.hInstance = NULL;
	wnd.lpszClassName = windowname.c_str();
	if (pcreate_get_center) {
		xx = (GetSystemMetrics(SM_CXSCREEN) / 2) - (ww/2);
		yy = (GetSystemMetrics(SM_CYSCREEN) / 2) - (hh/2);
	}
	//Register window class
	RegisterClassA(&wnd);
	DWORD ws_ex = 0;
	DWORD style = CS_OWNDC | DFCS_CAPTIONCLOSE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN;
	if (type == VW_transparent) {
		ws_ex = WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW;
		style = 0;
	}
	else if (type == VW_splash) {
		ws_ex = WS_EX_TOOLWINDOW | WS_EX_LAYERED;
		style = CS_OWNDC;
	}
	else ws_ex = WS_EX_APPWINDOW;
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = ww;
	rect.bottom = hh;
	::AdjustWindowRect(&rect, style, false);
	cout << "adjust client area: " <<rect.right - rect.left << ": " << rect.bottom - rect.top << endl;
	ww = rect.right - rect.left;
	hh = rect.bottom - rect.top;
	hWnd = CreateWindowExA(
		ws_ex, windowname.c_str(), windowtitle.c_str() ,
		style,
		xx,yy,ww,hh,
		NULL,NULL,NULL,NULL);

	if (hWnd == NULL) {
		cout << "createwindowex failed e=" << GetLastError() << endl;
		pause();
		return ;
	}


	if (type == VW_transparent || type == VW_splash) {
		SetLayeredWindowAttributes(hWnd, transparent_color, 255, LWA_COLORKEY);
		//SetWindowLong(hWnd, GWL_STYLE, 0);
		SetWindowLong(hWnd, GWL_STYLE, WS_BORDER|WS_THICKFRAME);
		SetWindowLong(hWnd, GWL_STYLE, 0);
		SetWindowPos(hWnd,0, xx, yy, ww, hh, SWP_FRAMECHANGED);
	}
	else { 

		SetClassLong(hWnd, -14/*GCL_HICON*/, (LONG)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(101)));
	}
	if(show || type == VW_splash)ShowWindow(hWnd, SW_SHOW);

	//SetWindowPos(hWnd, HWND_TOPMOST, xx, yy, ww, hh, SWP_SHOWWINDOW);


	myhdc = GetDC(hWnd);
	myhwnd = hWnd;


}
/**************************************end ValWindow window creation block******************************************************/
/******************************************** begin splashscreen block******************************************************/

#ifdef VW_HAS_SPLASHSCREEN_LOAD
void SPLASHSCREEN_LOAD();
#endif

void VW_slpashscreen_msgloop_kill(void* a) {
	splashscreen_struct* info = (splashscreen_struct*)a;
	
	// put global loading stuff in here instead of sleep
	// start all global threads here, timer_calibrate comes to mind
	// this method will be a required function like main for end users
	// can be called without splash screen, inline if desired. 
#ifdef VW_HAS_SPLASHSCREEN_LOAD // define this before including valwindowmanager to define your own loading process
	SPLASHSCREEN_LOAD();
#else
	_beginthread(calibrate_timer_thread, 0, NULL);
#endif 
	
	ValWindow* vw = (ValWindow*)info->valwindptr;
	if (vw == NULL)cout << "VW_slpashscreen_msgloop_kill splashscreen vwptr didn't translate" << endl;
	// beta portion replaces sleep with loading bar
	//vw->add_control_ex_ts(VC_LOADINGBAR, "loading", "1", VRECT{ 50,50,200,30 },VC_NOFUNC,false);
	
	////cout << "added control" << endl;
	//vw->limited_render();
	////cout << "rendered window" << endl;

	ValControl* h = vw->GetControl("loading");
	int time = info->time /100;
	for (int i = 2; i < 101; i++) {
		Sleep(time);
		h->sval= ctostr(i);
		h->drawtogfx();
		h->needs_redraw = true;
		vw->limited_render();

	}
	//cout << "past loop" << endl;

	//Sleep((info->time) - (30 * 30));

	if (info->valwindptr != NULL && VW_splash_doblurout) {
		
		((ValWindow*)(info->valwindptr))->mygfx.copy_buf();
		
		for (int i = 0; i < 30; i++) {
			//((ValWindow*)(info->valwindptr))->mygfx.blurtocopy10();
			//((ValWindow*)(info->valwindptr))->mygfx.paste_buf();
			//((ValWindow*)(info->valwindptr))->mygfx.blurtocopy10();
			//((ValWindow*)(info->valwindptr))->mygfx.paste_buf();
			//((ValWindow*)(info->valwindptr))->mygfx.blurtocopy10();
			//((ValWindow*)(info->valwindptr))->mygfx.paste_buf();
			((ValWindow*)(info->valwindptr))->mygfx.blurtocopy9();
			((ValWindow*)(info->valwindptr))->mygfx.paste_buf();
			((ValWindow*)(info->valwindptr))->GFXdraw();
			Sleep(10);
		}
		for (int i = 0; i < 30; i++) {
			((ValWindow*)(info->valwindptr))->mygfx.blurtocopy3();//6 white and pink  // 5 is cool
			((ValWindow*)(info->valwindptr))->mygfx.paste_buf(); // 4 is nice too colorful fractals
			((ValWindow*)(info->valwindptr))->GFXdraw();
			Sleep(12);
		}
	}
	else cout << "valwindow not translated" << endl;
	
	info->b = true; // kill splash screen
	
}

void VW_splashscreenthread(void* a) {
	
	splashscreen_struct* info = (splashscreen_struct*)a;
	//if (info->x < 1)info->x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (info->w );
	//if (info->y < 1)info->y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (info->h );
	
	//cout << "in splashscreenthread past metrics" << endl;;
	ValWindow splashsc(info->str, info->x, info->y, info->w, info->h, VW_splash);
	splashsc.set_topmost(1);
	//splashsc.add_control_ex(VC_LOADINGBAR, "loading", "1", VRECT{ 50,50,200,30 }, VC_NOFUNC, false);
	//still not entirely sure why ^^ doesn't work. causes butterfly errors all over the place. vv works...
	cout << "splashscreen client data iw,w,h: " <<info->w<<","<< splashsc.clientwidth << "," << splashsc.clientheight << endl;
	ValControl* loadingbar = new ValControl(VC_LOADINGBAR, 50, splashsc.clientheight - 50, splashsc.clientwidth -100, 30, "1", "loading");
	splashsc.controls[0] = loadingbar;
	splashsc.controlslen = 1;
	splashsc.controls[0]->needs_redraw = true;
	splashsc.limited_render();
	info->valwindptr = (void*)&splashsc;
	//string mar = "mario.bmp";
	//ValWindow splashsc(mar,500,500,500,500, VW_splash);
	//cout << "in splashscreenthread past constructor" << endl;;
	//Sleep(3000);
	info->b = false;
	
	_beginthread(VW_slpashscreen_msgloop_kill, 0, (void*)info);
	//cout << "in splashscreenthread past kill start" << endl;;
	MSG msg;
	while (1) {
		//cout << "in msg thread" << endl;
		if (PeekMessageA((LPMSG)&msg, splashsc.myhwnd, 0, 0, PM_NOREMOVE)) {
			GetMessageA(&msg, NULL, 0, 0);
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		if (info->b==true)break;
		//Sleep(1);
	}
	//cout << "after msg thread" << endl;
	ShowWindow(splashsc.myhwnd, SW_HIDE);
}
/******************************************** end splashscreen block******************************************************/
/********************************************begin helper thread block******************************************************/



void ValWindow_render_thread(void* a) {
	ValWindow* wind = (ValWindow*)a;
	while (1) {
		if (wind->rendertimer.read_ms_nolap() > 30) {
			wind->Framecount++;
			//cout << "framecount: " << wind->Framecount << endl;
			if (!wind->full_render)wind->limited_render();
			else {
				wind->render_window();
				wind->full_render = false;
			}
			wind->rendertimer.Lap();
		}
		if (wind->needs_control) {
			if (wind->ValControl_strct.type == VC_PASSWORD) {
				wind->needs_control_index = wind->reserved_add_control_ex_wm(&(wind->ValControl_strct));
				while (wind->controls[wind->needs_control_index]->windows_control == NULL)Sleep(3);
				//SetWindowSubclass(wind->controls[wind->needs_control_index]->windows_control, ValWindowPasswordControlWndProc, wind->controls[wind->needs_control_index]->UUID, (DWORD_PTR)wind);
			}
			else if (wind->ValControl_strct.type == VC_EDIT) {
				wind->needs_control_index = wind->reserved_add_control_ex_wm(&(wind->ValControl_strct));
				while (wind->controls[wind->needs_control_index]->windows_control == NULL)Sleep(3);
				//SetWindowSubclass(wind->controls[wind->needs_control_index]->windows_control, ValWindowPasswordControlWndProc, wind->controls[wind->needs_control_index]->UUID, (DWORD_PTR)wind);
			}
			else
				wind->needs_control_index = wind->reserved_add_control_ex(&(wind->ValControl_strct));
			wind->needs_control = false;
			Sleep(1);
			continue;
		}

		Sleep(22);
	}

}

// global variables for mouse events. if they ever invent multiple pointers this will have to be classified.
POINT ptclick;
POINT ptrclick; // new in 2022
POINT ptmousemove;
POINT ptmousedown;
//BYTE mousemove_ind; 
bool G_ismousedown = false;
bool G_was_master = false; // was the last closed window a master window
bool G_is_ok_toclose = false; // 
bool window_xbutton_clicked = false;
HWND pthwnd=NULL;
HWND hwnd_mouseover_clear = NULL;
#define VW_EVENT_THREAD_SLEEP 20


void ValWindow_event_thread(void* a) {  // handles mouse events for a valwindow
	ValWindow* wind = (ValWindow*)a;
	short hold;
	int lastmouse_ind = 0;

	while (1) {
		if (ptrclick.x != 0 && pthwnd == wind->myhwnd) {
			if (wind->IS_MOUSE_CAPTURED) {
				wind->mouse_cap->x = ptrclick.x;
				wind->mouse_cap->y = ptrclick.y;
				wind->mouse_cap->type = VW_MOUSECAP_RCLICK;
				((void(__cdecl*)(void*))(wind->capture_callback))((void*)wind); // call the call_back assigned when capture_mouse is called
				//_beginthread((_beginthread_proc_type)wind->capture_callback, 0, (void*)wind);
			}
			ptrclick = { 0,0 };
		}
		if (ptclick.x != 0 && pthwnd == wind->myhwnd) {
			//wind->events->throw_event_inline(ptclick.x, ptclick.y);
			if (wind->IS_MOUSE_CAPTURED) {
				wind->mouse_cap->x = ptclick.x;
				wind->mouse_cap->y = ptclick.y;
				wind->mouse_cap->type = VW_MOUSECAP_CLICK;
				((void(__cdecl*)(void*))(wind->capture_callback))((void*)wind); // call the call_back assigned when capture_mouse is called
				//_beginthread((_beginthread_proc_type)wind->capture_callback, 0, (void*)wind);
			}
			else {
				hold = wind->events->throw_event_thread(ptclick.x, ptclick.y);
				if (hold != -1) wind->controls[hold]->clicked(ptclick.x, ptclick.y);
			}
			ptclick = { 0,0 };
			//pthwnd = NULL;
		}
		if (ptmousemove.x != 0&&ptmousemove.y!=-1 && pthwnd == wind->myhwnd) {
			if (wind->IS_MOUSE_CAPTURED) {
				
				wind->mouse_cap->x = ptmousemove.x;
				wind->mouse_cap->y = ptmousemove.y;
				wind->mouse_cap->type = VW_MOUSECAP_MOVE;
				if (G_ismousedown) {
					wind->mouse_cap->type = VW_MOUSECAP_LDOWN;
					//cout << "captured mousedown caught" << endl;
				}
				((void(__cdecl*)(void*))(wind->capture_callback))((void*)wind);
				//_beginthread((_beginthread_proc_type)wind->capture_callback, 0, (void*)wind);
			}
			else {
				if (G_ismousedown)wind->control_mousedown(ptmousemove.x, ptmousemove.y);
				else wind->control_mouseover(ptmousemove.x, ptmousemove.y);
			}
			ptmousemove.x = 0;
		} 
		if (hwnd_mouseover_clear == wind->myhwnd) {
			wind->control_mouseover(0, -1);
			ptmousemove.x = 0;
			ptmousemove.y = 0;
			hwnd_mouseover_clear = NULL;
		}

		//if (ptmousedown.x != 0 && pthwnd == wind->myhwnd) {
		//	wind->control_mousedown(ptmousedown.x, ptmousedown.y);
		//	
		//	
		//}
		if (window_xbutton_clicked && pthwnd == wind->myhwnd) {
			wind->is_closed = true;
			//CloseWindow(pthwnd); // this actually minimizes window
			DestroyWindow(pthwnd);
			window_xbutton_clicked = false;
			G_was_master = wind->is_master;
			G_is_ok_toclose = true;
			SendMessage(pthwnd, WM_CLOSE, 0, 0);

			//pthwnd = NULL;
		}
		Sleep(VW_EVENT_THREAD_SLEEP);

	}

}

/********************************************end helper thread block******************************************************/
/******************************************** begin callback block******************************************************/



//callback function for generic edit boxes
LRESULT CALLBACK ValWindoweditControlWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
	ValWindow* vwp = (ValWindow*)dwRefData;
	switch (msg)
	{
		//case WM_KEYDOWN:
	case WM_CHAR:

		if (wParam == VK_TAB || wParam == VK_RETURN) {
			cout << "caught tab/return" << endl;
			short controlId = vwp->find_control_UUID(uIdSubclass);
			if (controlId != -1) {
				HWND hold = vwp->controls[controlId]->tabhwnd;
				if (hold != NULL) {
					SetFocus(hold);
				}
				else {
					if (hold == NULL)cout << "hold is null" << endl;

					if (controlId == -1)cout << "controlId==-1" << endl;
					else cout << "controlID title: " << vwp->controls[controlId]->title << endl;
				}
			}
			
			return 0;
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)return 0;
		if (wParam == VK_TAB)return 0;
		break;



	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);


}

// callback function for password boxes
LRESULT CALLBACK ValWindowPasswordControlWndProc(HWND hWnd, UINT msg,WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass,DWORD_PTR dwRefData){
	ValWindow* vwp = (ValWindow*)dwRefData;
	switch (msg)
	{
	//case WM_KEYDOWN:
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			cout << "ValWindowEditControlWndProc called at: " << vwp->windowtitle << " at ID: " << uIdSubclass<<endl;

			short controlId = vwp->find_control_UUID(uIdSubclass);
			if (controlId != -1) {
				cout << "found button to press after password enter{label,title}: " << vwp->controls[controlId]->label << " : " << vwp->controls[controlId]->title;
				vwp->press_button_byname(vwp->controls[controlId]->label);
				SetFocus(vwp->myhwnd);
			}
			// associate button/function with enter press when target control is password.
			//may need a 2nd for edits that finds tabs when nessesary.
			return 0;
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)return 0;
		break;
		
	
		
	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);
	
	
}
// extracted from windowsx.h
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
ValStopwatch GLOBAL_WINDOW_MOUSEPOS_TIMER;
HWND hwnd_hasmouse = NULL;
//int hitcounter_vwwp = 0;
ValWindow* VW_from_hwnd(HWND hWnd);
void VWM_handle_create_window_msg(valwindow_create_struct*);
// valwindowwndproc window proceedure class function for non-splash ValWindows 
LRESULT CALLBACK ValWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    //return 0;
	ValControl* ctr;
	ValWindow* Vw;
	switch (msg) {
    //case WM_KEYDOWN:
	case VW_CREATE_WINDOW:
		//WindowMan.create_new_window((valwindow_create_struct*)wParam);
		VWM_handle_create_window_msg((valwindow_create_struct*)wParam);
	break;
	case  VW_CREATE_CONTROL:
		 ((ValWindow*)wParam)->reserved_add_control_ex((ValControl_struct*)lParam);
	break;
	case VW_PASSCNTRL:
		ctr = (ValControl*)wParam;
		ctr->windows_control = CreateWindowExA(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE 
			| ES_LEFT | ES_PASSWORD,
			ctr->x+2, ctr->y+2, ctr->width-4, ctr->height-4, hWnd, NULL, NULL, NULL);
		SetWindowSubclass(ctr->windows_control, ValWindowPasswordControlWndProc, ctr->UUID, (DWORD_PTR)VW_from_hwnd(hWnd));  //beta  seems to work, but not fast...
		//cout << "created edit control" << endl;
		return 0;
	break;
	case VW_EDITCNTRL:
		//cout << "in edit control wndproc\n";
		 ctr = (ValControl*)wParam;
		ctr->windows_control = CreateWindowExA(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE 
			| ES_LEFT  | (lParam==1? ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL : ES_AUTOHSCROLL) ,
			ctr->x+2, ctr->y+2,ctr->width-4, ctr->height-4, hWnd, NULL, NULL, NULL);
		SetWindowSubclass(ctr->windows_control, ValWindoweditControlWndProc, ctr->UUID, (DWORD_PTR)VW_from_hwnd(hWnd));  //beta  seems to work, but not fast...
		
		//cout << "created edit control" << endl;
		return 0;
	break;
	case WM_COMMAND:
		//if (wParam = IDOK) {
			//cout << "enter key hit at wparam:" << wParam << " lparam:" << lParam << endl;
		//}
	break;
	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return TRUE;
		}
		break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps); // needed or windows goes absolutely bonkers.
        return 0;
    }
	case WM_LBUTTONDOWN:
		// add xy to event handler list. 
		//cout<<"window found mousedown" << lParam << ":" << GET_X_LPARAM(lParam) << ":" << GET_Y_LPARAM(lParam) << "    \r";
		ptmousedown = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
		G_ismousedown = true;
		pthwnd = hWnd;
		return 0;
		break;

	case WM_LBUTTONUP:
        // add xy to event handler list. 
        //cout<<"window found click" << lParam << ":" << GET_X_LPARAM(lParam) << ":" << GET_Y_LPARAM(lParam) << "    \r";
		//if (G_ismousedown == false)return 0;
		//ptclick = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
		//G_ismousedown = false;
		//pthwnd = hWnd;
  //      return 0;
  //      break;
#ifdef VAL_MINESWEEPER_FAST_MOUSE
		Vw = VW_from_hwnd(hWnd);
		if (Vw->IS_MOUSE_CAPTURED) {
			Vw->mouse_cap->x = GET_X_LPARAM(lParam);
			Vw->mouse_cap->y = GET_Y_LPARAM(lParam);
			Vw->mouse_cap->type = VW_MOUSECAP_CLICK;
			((void(__cdecl*)(void*))(Vw->capture_callback))((void*)Vw);
		}
#else
		if (G_ismousedown == false)return 0;
		ptclick = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
		G_ismousedown = false;
		pthwnd = hWnd;
#endif
		break;

	case WM_RBUTTONUP:
		// add xy to event handler list. 
		//cout<<"window found click" << lParam << ":" << GET_X_LPARAM(lParam) << ":" << GET_Y_LPARAM(lParam) << "    \r";
		//if (G_ismousedown == false)return 0;
		ptrclick = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
		//G_ismousedown = false;
		pthwnd = hWnd;
		return 0;
		break;


	case WM_MOUSEMOVE:
		if (GLOBAL_WINDOW_MOUSEPOS_TIMER.read_ms_nolap() > 1) {
			//cout << "window mouse move" << lParam << ":" << GET_X_LPARAM(lParam) << ":" << GET_Y_LPARAM(lParam) << "    \r";
			GLOBAL_WINDOW_MOUSEPOS_TIMER.Lap();
			pthwnd = hWnd;
			ptmousemove = { GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			if (hwnd_hasmouse != hWnd) {
				//cout << hitcounter_vwwp++ << "threw trackmouse event" << hwnd_name__(hWnd) << endl;
				hwnd_hasmouse = hWnd;
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_LEAVE;
				tme.hwndTrack = hWnd;
				if (!_TrackMouseEvent(&tme))cout << "trackmouseevent failed " << endl;
				
			}
			//SetCursor(LoadCursor(NULL, IDC_ARROW));
		}

	break;
	case WM_MOUSELEAVE:
		//G_ismousedown = false;
		//pthwnd = hWnd;
		pthwnd = NULL;
		//cout << hitcounter_vwwp++<< "mouseleave hit " <<hwnd_name__(hWnd)<< "  lp:wp " << lParam << " : " << wParam<< endl;
		//ptmousemove = {1,-1 };
		hwnd_hasmouse = NULL;
		hwnd_clear_interact__(hWnd);
		return 0;
	break;
	case WM_KEYDOWN:
		//wparam=vk code
		//lparam= extended
		break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
		//DestroyWindow(hWnd);
        //exit(0);
        //return 0;
    }
	case WM_CLOSE:
		// put hwnd event close here.
		if( G_was_master) exit(0);
		if (G_is_ok_toclose) {
			G_is_ok_toclose = false; break;
		}
		window_xbutton_clicked = true;
		pthwnd = hWnd;
		return 0;
    }
    //return 0;
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}



/*

apparantly this is how I should be capturing enter keys on the edit/password controls.  
should be useful for metacontrols since editable metacontrols will have to spin up temporary edit controls.
maybe temp edit controls over labels could be a good way to move forward.

long FAR PASCAL SubProc(HWND hWnd, WORD wMessage,WORD wParam,LONG
                           lParam)
   {

       switch (wMessage)
        {

             case WM_GETDLGCODE:
               return (DLGC_WANTALLKEYS |
                       CallWindowProc(lpOldProc, hWnd, wMessage,
                                      wParam, lParam));

             case WM_CHAR:
             //Process this message to avoid message beeps.
            if ((wParam == VK_RETURN) || (wParam == VK_TAB))
              return 0;
               else
              return (CallWindowProc(lpOldProc, hWnd,
                                        wMessage, wParam, lParam));

          case WM_KEYDOWN:
               if ((wParam == VK_RETURN) || (wParam == VK_TAB)) {
                 PostMessage (ghDlg, WM_NEXTDLGCTL, 0, 0L);
                 return FALSE;
               }

            return (CallWindowProc(lpOldProc, hWnd, wMessage,
                                      wParam, lParam));
            break ;

          default:
               break;

		} /* end switch */


		/* depreciated
void pump_and_control_mainthread(void* a) { // a pump and WM control creator system 
	// *a is valwindow.  add create_control struct/vars and flag for this MSG loop. 
	MSG msg;
	while (1) {
		GetMessageA(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		//TranslateAcceleratorA(&msg);
		DispatchMessageA(&msg);
		//if(!needs_control) create_wm_control();
	}

}
*/