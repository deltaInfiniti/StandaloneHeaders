// valwindowmanager.h
/*
ValWindowManager is a class for supervising valwindow variables in a single program complex.
should be the only header in the valwindow suite that needs to be included in user programs

important notes: 
string loader has escape system for commas.  `1 is escape string for now. hoping to change to something more 
   intuitive at a later date.  maybe %1 as html coding or \1 or something.
RESERVED_ functions in classes MUST be called by a persistent thread- Mainthread preferred. 
absolutely must use void __VWM_msgpump() in main thread.

   ******************features of valsuite:
   * **************[]== not yet finished


standard controls: 
labels, buttons, statisticlabels, checkboxs, single-selection listbox
image, slider, loadingbar(modified slider), 
features:
mouseover/mousedown indicator drawing -interact, 
load image into most contexts, 
all drawn and handled by valsuite/GDI/direct BITMAP twiddling

Full 1-line* string style loading functionality.  * most controls are 1 line. some controls require
   associated data- global_stat, listbox, button REQUIRE associated data pointers to opperate.  
   these variables/functions must be registered by name with windowman using VWM_register_data
   extended style variable control by stringtype/listtype constructor - more to add but it's there



windows controls:
edit, edit multiline, password
features: full tab control between edits, press target button by name on enter(password boxes only currently)



Window manager:
1 line create standard, []tooltype, transparent, and splashscreen windows
1 line splash-screen implimentation with associated optional loading proceedure.
   optoinal animated blurrout 
windows may exist with same name and same named controls without collisions(when passing parent to button functions properly)



live form editor-  much to come here -valwindoweditor.h
[x] target any window currently open in WindowMan
[x] open new target window
[x] change all integral variable data live for any control
[] error protection -- some
[x] add new control of any type to target window
[x] export string/c++source code to produce last processed control
[x] accessibility tweaks-
[x] highlight target control on control listbox click
[x][x] controlbox filter
[x][x] auto-target on listbox click
[x][x] 2 data box sets- target/new w/ copy button for each target box  -> to new
[x][x][x] copy button for all fields except title
[x][x][x] process button sets control listbox to new control
[][] check on 'add new' if control with that name exists
[x]export full window string to file
[x]import full window string from file


[x]mouse capture target window 
[x][x]highlight section ( cannot capture under edit controls yet. must make transp first)
[x][x][x] shift to toggle highlight, noshift to just highlight section
[x][x][x] shiftclick to toggle highlight on single control
[x][x]move l/r/u/d highlighted section buttons
[x][x] editboxes for dimensions of highlighted sections 
[x][x][x]copy button-> copy dims to new control area 
[x][x][x]export code button-> exports code for highlighted controls
-- can be used to write games! check valbreakout.h
-- my goal--
[]script runner
[][] register script as control function




*/


#pragma once
string hwnd_name__(HWND hWnd);
void hwnd_clear_interact__(HWND hWnd);
bool neo_loginfunc(string uname, string pw, string** status);
#include"varlist.h"

#include"ValWindow.h"
#include"ValDataRegister.h"
struct valwindowinfo {
	int x, y;
	string title;
	string name;
};


class ValWindowManager {
	// global multiwindow manager for wndproc determination.
	//  change input routine to add hwnd to queue with point
	//  change eventhandlerthread to take windowmanager and find target when nessesary. 
	//  should always be only one global windowmanager... singleton

	// this is the first input stack level where virtual windows drawn on one window background
	// should be possible.  will need to impliment a titlebar sytem for all virtual windows
	// and handle drag for these types of events. 

	
public:
	HWND msgpump_hwnd = NULL;
	DWORD create_window_threadid = -1;
	ValWindow* windows[256]; // these each hold all vars that should be nessesary for this class.
	int windowslen=0;
	ValCrypt locker;
	
	
	splashscreen_struct splash_s;
	bool Needs_create = false, lock_create = false; // switch to mutex??
	valwindow_create_struct vcs_struct;
	BYTE newly_created_window = 0;
	bool is_started = false;
	bool HyperVisor_login_success = false;

	
	ValWindowManager() {
		RESERVED_GLOBAL_VALDATANODE_BANK_FILL();
		if (dataregistry == NULL)dataregistry = new ValDataRegistry();
	}
	/*******************register data block- use this before using AddControl on ValWindow**********/
	// attempt will be made to make this arbitrary length. 
#define VWM_register_data(dat) WindowMan.register_data((void*)&dat,typeid(&dat).name(),#dat)
#define VWM_register_datan(dat,namez) WindowMan.register_data((void*)dat,typeid(dat).name(),namez)
#define VWM_register_datar(dat,namez) WindowMan.remove_registered_data(namez)
	ValDataRegistry* dataregistry=NULL;
	void register_data(void* dat, string type, string name) {
		dataregistry->add_genericdata(name, dat, VDNtype_NOTSET);
	}
	void* find_registered_data(string name, string& type) {

		return dataregistry->get_data(name);
	}
	void remove_registered_data(string name) {
		dataregistry->remove_data(name);
	}


	varlist globaldata;
	varlist ownerdata;
	//ValCrypt VCrypt; 
	/*  create new window block.  After testing, most of these will be private and 
	    a full wrapper function 'new_window()' will be overloaded to handle all needs*/
	//working but needs more testing on threads without message pump...
	ValWindow* new_window(string name, int xx, int yy, int ww, int hh, BYTE type) {
		if (create_window_threadid != -1)return create_new_windowts(name, xx, yy, ww, hh, type);
		else create_new_window(name, xx, yy, ww, hh, type);
	}

	ValWindow* RESERVED_create_new_window() {
		return create_new_window(vcs_struct.name, vcs_struct.x, vcs_struct.y, vcs_struct.w, vcs_struct.h, vcs_struct.type);
	}
	ValWindow* create_new_windowex(string name, int xx, int yy, int ww, int hh, BYTE type) {
		return create_new_windowts(name, xx, yy, ww, hh, type);

		/* depreciated. used whole cpu in msgpump. 
		while (Needs_create || lock_create)Sleep(1);
		lock_create = true;
		build_valwindow_create_struct(&vcs_struct, name, xx, yy, ww, hh, type);
		Needs_create = true;
		while (Needs_create)Sleep(1);
		int index = newly_created_window;
		cout << "new create_new_window index: " << index << endl;
		//Needs_create = false;
		lock_create = false;
		return windows[index];
		*/
	}

	ValWindow* create_new_windowts(string name, int xx, int yy, int ww, int hh, BYTE type) {
		while (Needs_create || lock_create)Sleep(1);
		lock_create = true;
		build_valwindow_create_struct(&vcs_struct, name, xx, yy, ww, hh, type);
		Needs_create = true;
		PostThreadMessage(create_window_threadid, VW_CREATE_WINDOW_MSG, NULL, NULL);
		while (Needs_create)Sleep(1);
		int index = newly_created_window;
		cout << "new create_new_window index: " << index << endl;
		//Needs_create = false;
		lock_create = false;
		return windows[index];
	}

	ValWindow* create_new_window(string name, int xx, int yy, int ww, int hh, BYTE type) {
		windows[windowslen] = new ValWindow(name, xx, yy, ww, hh, type);
		//windows[windowslen] = new ValWindow(vcs_struct.name, vcs_struct.x, vcs_struct.y, vcs_struct.w, vcs_struct.h, vcs_struct.type);
		windows[windowslen]->myUUID = windowslen;

		//is_hidden[windowslen] = 0;
		windowslen++;
		return windows[windowslen - 1];

	}
	//window variable accessor function by hwnd
	ValWindow* fromHWND(HWND hw) {
		for (int i = 0; i < windowslen; i++)
			if (windows[i]->myhwnd == hw)return windows[i];
		return NULL;
	}
	//window variable accessor function by title
	ValWindow* fromName(string name) {
		for (int i = 0; i < windowslen; i++)
			if (windows[i]->windowtitle ==name)return windows[i];
		return NULL;
	}

	bool splashed = false;
	void create_splash(string imgfile_name, int ms_onscreen_min, int xx=0, int yy = 0, int ww=0, int hh=0) {
		splashed = true;
		fill_splashscreen_struct(&splash_s,imgfile_name, ms_onscreen_min, xx, yy, ww, hh);
		_beginthread(VW_splashscreenthread, 0, (void*)&splash_s);	
	}
	bool is_splashing() {
		if (!splashed)return false;
		return !splash_s.b;
	}
	void wait_for_splash() {
		while (is_splashing())Sleep(100);
	}


	//create a valwindow from a markup string. more details to come later
	//markup string has similar form to ValControl Markup
	// already generated ValWindow variables can produce their own markup string through export_markup
	// markup export may not properly export your functions/data if not produced by add_control
	//this may need to be checked by hand untill further notice, when using other control generators
	// remember to register your data with windowman before calling import functions
	void import_markup(string& str) {
		int ind = findnext(str, "\n", 0);
		string hold = getbetween(str, 0, ind);
		cout << "creating window string: " << hold << endl;
		
		varlist vst;
		vst.fromcsl(hold);
		if (vst.valueof("type") != "WINDOW") {
			cout << "ValWindow importmarkup firstline type not window\n";
			return;
		}
		string title = vst.valueof("title");
		string xx = vst["x"];
		string yy = vst["y"];
		string ww = vst["w"];
		string hh = vst["h"];
		ValWindow* vw = create_new_windowts(title, ctoint(xx), ctoint(yy), ctoint(ww), ctoint(hh), 1);
		Sleep(50);
		int nextind = ind;
		while (1) {
			/*nextind= findnext(str, "\n", nextind+1 );
			cout << "ind nextind" << ind << "," << nextind << endl;
			if (nextind == -1) break;
			hold = getbetween(str, ind + 1, nextind);
			*/
			hold = getbetween(str, nextind+1, "\n");
			cout << "adding control: " << hold << "\n";
			cout << "afterstr" << str << endl;
			if (hold == "")break;
			cout << "indbefore" << nextind << endl;
			nextind += hold.length()+1;
			cout << "indafter" << nextind << endl;
			
			vw->AddControl(hold);
			ind = nextind;
		}
		vw->calculate_edit_ctrl_tabs();
		cout << "finished creating new window by markup string";
	}
	void import_markup_file(string fname) {
		string data = file_contents(fname);
		import_markup(data);
	}



	


	

}WindowMan;

ValWindow* VW_from_hwnd(HWND hWnd) {
	return WindowMan.fromHWND(hWnd);
}
string hwnd_name__(HWND hWnd) {
	 return WindowMan.fromHWND(hWnd)->windowtitle;
}
void hwnd_clear_interact__(HWND hWnd) {
	WindowMan.fromHWND(hWnd)->control_mouseover(0, -1);

}
void* __VWM_getdata(string name, string& type) {
	return WindowMan.find_registered_data(name, type);


}
void __VWM_msgpump() {
	MSG msg;
	WindowMan.create_window_threadid = GetCurrentThreadId();
	cout << "main thread id located: " << WindowMan.create_window_threadid << endl;
	while (1) {
		
		GetMessageA(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		
		DispatchMessageA(&msg);
		if (msg.message == VW_CREATE_WINDOW_MSG) {
			ValWindow* wind = WindowMan.RESERVED_create_new_window();
			WindowMan.newly_created_window = wind->myUUID;
			WindowMan.Needs_create = false;
		}
	}

}
void VWM_handle_create_window_msg(valwindow_create_struct* s) {
	WindowMan.RESERVED_create_new_window();
}

void WindMan_event_thread() {// moved to valwindow
	if (WindowMan.is_started)return;
	WindowMan.is_started = true;
	while (1) {



		Sleep(1);
	}


}

/***************************************Hypervisor block ****************************************************************/
// this is a catchall loader system to get a login password token for local encryption
// also a great place to put firstrun warnings/terms agreements etc. 


void Hypervisor_firstrun_button(void* a) {
	//get hypervisor window var
	ValWindow* wind = WindowMan.fromName("HyperVisor");
	//eval terms and notify if not checked
	bool term=wind->evaluate_checkbox("terms_checkbox");
	if (!term) {
		cout << "terms not accepted\n";
		wind->AddControl("type=VC_LABEL,title=passwordnclabel,text=please accept the terms of use,x=50,y=360,w=400,h=30,numblurs=1,transparent=true");
		//wind->AddControl("")  // add warning and return
		return;
	}
	//eval username and password
	string uname, pw;
	uname = wind->eval_edit("username_box");
	pw = wind->eval_edit("password_box");
	if (uname == "" || pw.length() < 4) {
		cout << " uname is blank or pw is less than 4 chars\n";
		wind->AddControl("type=VC_LABEL,title=passwordnclabel,text=error: username blank or password less than 4 characters.,x=50,y=380,w=400,h=30,numblurs=1,transparent=true");
		//wind->AddControl("")  // add warning and return
		return;
	}
	// build varlist data for user
	// add 'LocAlPasSwOrd=CoRrEct' to the list and check for that on login for PW check
	varlist outlist;
	outlist.set("LocAlPasSwOrd", "CoRrEct");
	outlist.set("termsv01", "true");
	outlist.set("Valsuite_owner", uname);
	ValCrypt rc(pw, 1346);//build vcrypt var with pass
	//save globaldata from username.di with vcrypt
	varlist_enc_save(outlist, rc, uname +".di");
	//load back into temp var to check integrity
	outlist.clear();
	varlist_dec_load(outlist, rc, uname + ".di");
	if (outlist.valueof("LocAlPasSwOrd") != "CoRrEct") {
		// add warning and return
		return;
	}
	
	//write basic.di
	outlist.clear();
	outlist.set("termsv01", "true");
	outlist.set("Valsuite_owner", uname);
	outlist.save("basic.txt");
	// at the end of this, exit program. or add exit  prompt.
	wind->AddControl("type=VC_LABEL,title=frdonelabel,text=user credentials created. please close and reopen ValSuite,x=50,y=400,w=400,h=30,numblurs=1,transparent=true");

	// want all good runs to start with regular start.
}

void Hypervisor_username_manager(void* login_func);
void Hypervisor_login_button(void* a) {
	//get hypervisor window var
	ValWindow* wind = WindowMan.fromName("HyperVisor");
	//eval password
	//eval username (from globaldata?)
	string uname, pw;
	uname = WindowMan.globaldata.valueof("Valsuite_owner");//wind->eval_edit("username_box");
	pw = wind->eval_edit("password_box");
	//build vcrypt var with pass
	WindowMan.locker.start( pw,1346);
	//  WindowMan.loker.backup();
	varlist_dec_load(WindowMan.ownerdata, WindowMan.locker, uname + ".di");
	if (WindowMan.ownerdata.valueof("LocAlPasSwOrd") != "CoRrEct") {
		cout << "password incorrect" << endl;
		wind->AddControl("type=VC_LABEL,title=passwordnclabel,text=password was not correct.,x=50,y=260,w=400,h=30,numblurs=1,transparent=true");
		// if not clear password box, add 'wrong pass' label, clear globaldata, reload globaldata from basic
		// add warning and return
		return;
	}
	
	//open username manager or call injection function somehow... register?
	WindowMan.HyperVisor_login_success = true;
	WindowMan.remove_registered_data("Hypervisor_login_button");
	WindowMan.remove_registered_data("Hypervisor_firstrun_button");
	//wind->GetControl("loginbut")->disable  // no disable function yet...
	wind->AddControl("type=VC_LABEL,title=welcomebacklabel,text=Welcome back. Password accepted.,x=50,y=260,w=400,h=30,numblurs=1,transparent=true");
	Sleep(3000);
	Hypervisor_username_manager(neo_loginfunc);
	wind->hide();
}
void* hypervisor_loginfunc = NULL;
void open_VS_hypervisor_window_(void* injection_function) {
	hypervisor_loginfunc = injection_function;
	//still need a good background pic.
	//still need a readme file.
	bool firstrun = false;
	string ownername = "";
	WindowMan.register_data(Hypervisor_firstrun_button, "buttonfunction", "Hypervisor_firstrun_button");
	WindowMan.register_data(Hypervisor_login_button, "buttonfunction", "Hypervisor_login_button");
	WindowMan.create_splash("splash.jpg", 3000);
	WindowMan.wait_for_splash();
	if (file_exists("basic.txt")) {
		WindowMan.globaldata.load("basic.txt");// contains username, some basic config info.
		if (WindowMan.globaldata.valueof("termsv01") != "true")firstrun = true;
		if ((ownername = WindowMan.globaldata.valueof("Valsuite_owner")) == "")firstrun = true;
		if (!file_exists(ownername + ".di"))firstrun = true;
	}
	else {
		firstrun = true;
	}

	ValWindow* wind = WindowMan.create_new_windowts("HyperVisor", 300, 300, 500, 500, 1);
	
	if (firstrun) {

		wind->AddControl("type=VC_LABEL,title=readmelabel1,text=Please read the whole readme file before continuing,x=10,y=10,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->AddControl("type=VC_LABEL,title=readmelabel2,text=the readme contains extended  operating information,x=10,y=30,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->AddControl("type=VC_LABEL,title=readmelabel3,text=Welcome to ValSuite. We've noticed this is your first time ,x=10,y=80,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->AddControl("type=VC_LABEL,title=readmelabel4,text=Please enter an owner name and password to begin. *Local encryption Only ,x=10,y=100,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->AddControl("type=VC_LABEL,title=readmelabel5,text=Don't use your forum/game login information here. ,x=10,y=120,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->set_ACoffsety(100);
		wind->AddControl("type=VC_LABEL,title=welcomelabel,text=Welcome to ValSuite. Please create login credentials,x=80,y=120,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		wind->AddControl("type=VC_CHECKBOX,title=terms_checkbox,text=I agree to the terms in ReadMe.txt,x=10,y=140,w=480,h=40");
		wind->AddControl("type=VC_BUTTON,title=firstrunbut,text=submit,x=340,y=185,w=80,h=60,needsparent=true,dataname=Hypervisor_firstrun_button");

		

	}
	else {
		wind->AddControl("type=VC_BUTTON,title=loginbut,text=login,x=340,y=185,w=80,h=60,needsparent=true,dataname=Hypervisor_login_button");
		wind->AddControl("type=VC_LABEL,title=welcomelabel,text=Welcome back to ValSuite. Please login to continue,x=80,y=120,w=480,h=20,numblurs=1,textfont=Modern,transparent=true");
		//wind->add_control_ex_ts(VC_BUTTON, "login", "Login", rct, (void*)Hypervisor_login_button, true, wind->myhwnd);
		//enter password button
	}
	
	wind->AddControl("type=VC_EDIT,title=username_box,text="+ownername+",x=100,y=185,w=180,h=22,dataname=,nointeract=true");
	wind->AddControl("type=VC_LABEL,title=usernamelabel,text=Ownername:,x=3,y=185,w=80,h=30,numblurs=1,transparent=true");
	wind->AddControl("type=VC_LABEL,title=passwordlabel,text=Password:,x=3,y=225,w=80,h=30,numblurs=1,transparent=true");
	wind->AddControl("type=VC_PASSWORD,title=password_box,text=loginbut,x=100,y=225,w=180,h=22,dataname=,nointeract=true");
	
	//*wind += "type=VC_PASSWORD,title=password_box,text=,x=100,y=225,w=180,h=30,dataname=,nodraw=true,nointeract=true";
	wind->set_ACoffsety(0);


}


void hypervisor_verifybut() {
	
	ValWindow* vw = WindowMan.fromName("UsernameManager");
	string n = vw->eval_edit("usernamebox");
	string p = vw->eval_edit("passwordbox");
	if (hypervisor_loginfunc == NULL) {
		cout << "no login function\n";
		return;
	}
	//if (neo_loginfunc(n, p,(string**)&(vw->GetControl("newaccstatus")->GLOBAL_POINTER))) {
	// evil void* function voodoo 
	bool test = ((bool(__cdecl*)(string,string,string**)) hypervisor_loginfunc) (n, p, (string**)&(vw->GetControl("newaccstatus")->GLOBAL_POINTER));
	if (test) {
		cout << "login success" << endl;
		// import new username into username list
		// import new username into global userdata usernamelist
		// import uname.pw.=pw to global userdata
	}
	else {
		cout << "login failed" << endl;
	}
}
//loginfunc must be a bool function(string username, string password, string**status);
string hypernewaccstatus="", hypertargaccstatus="";
void Hypervisor_username_manager(void* login_func) {
	//parse usernames out of ownerdata into global or held strlist.
	//register strlist
	//funcs and buts for - add username, 
	//listbox with unames
	//hypervisor_loginfunc = login_func;
	string s = "valusernameman.diw";
	cout << "started markup\n";
	VWM_register_datan(hypervisor_verifybut, "hypervisor_verifybut");
	//VWM_register_datan(, "");
	VWM_register_datan(&hypernewaccstatus, "hypernewaccstatus");
	VWM_register_datan(&hypertargaccstatus, "hypertargaccstatus");
	WindowMan.import_markup_file(s);
	cout << "ended markup\n";
	//while (1)Sleep(3000);
	//hold thread forever... 
	/*
	type=WINDOW,title=UsernameManager,x=1823,y=395,w=500,h=500
	title=usernames_lst,type=VC_LISTBOX,text=nd,x=38,y=39,w=146,h=388,dataname=windowlist,numblurs=0,textfont=Modern
	title=usernamelabal,type=VC_LABEL,text=Username,x=214,y=48,w=63,h=21,numblurs=1,textfont=Modern,transparent=true
	title=passwrodlabal,type=VC_LABEL,text=password:,x=214,y=73,w=63,h=21,numblurs=1,textfont=Modern,transparent=true
	title=passwordbox,type=VC_PASSWORD,text=,x=287,y=72,w=136,h=19,numblurs=0,textfont=Modern,nointeract=true
	title=usernamebox,type=VC_EDIT,text=,x=287,y=49,w=136,h=19,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=passwordbox
	title=verifybut,type=VC_BUTTON,text=Verify,x=223,y=285,w=190,h=43,textfont=Modern
	title=mulecheck,type=VC_CHECKBOX,text= mule account,x=221,y=104,w=199,h=22,textfont=Modern
	title=proxylabel,type=VC_LABEL,text=Proxy:,x=229,y=136,w=68,h=21,numblurs=1,textfont=Modern,transparent=true
	title=portlabel,type=VC_LABEL,text=Port:,x=232,y=160,w=68,h=21,numblurs=1,textfont=Modern,transparent=true
	title=proxybox,type=VC_EDIT,text=,x=286,y=138,w=136,h=19,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=portbox
	title=portbox,type=VC_EDIT,text=,x=285,y=161,w=136,h=19,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=proxybox
	title=useproxycheck,type=VC_CHECKBOX,text=save proxy ,x=213,y=188,w=199,h=22,textfont=Modern
	title=newaccountlabel,type=VC_LABEL,text=New Account Info:,x=221,y=19,w=196,h=20,numblurs=1,transparent=true
	title=targetaccountlabel,type=VC_LABEL,text=target account:,x=221,y=348,w=242,h=21,numblurs=1,transparent=true
	title=targetaccountbox,type=VC_EDIT,text=,x=221,y=370,w=236,h=22,numblurs=0,transparent=true,nointeract=true
	title=autologcheck,type=VC_CHECKBOX,text=auto login on select,x=37,y=435,w=146,h=18,textfont=Modern
	title=newaccstatus,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=203,y=256,w=235,h=21,dataname=status,textfont=Modern
	title=targetaccstatus,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=201,y=399,w=227,h=20,dataname=status,textfont=Modern
	title=safetyslider,type=VC_SLIDER,text=safety:72,x=215,y=215,w=196,h=20,numblurs=0
	*/
}


/*depreciated block
	//void* registered_variables[255];
	//string registered_vartypes[255];
	//string registered_varnames[255];
	//int registered_varlen = 0;


	//void register_data(void* dat, string type, string name) {
	//	registered_variables[registered_varlen]=dat;
	//	registered_vartypes[registered_varlen]=type;
	//	registered_varnames[registered_varlen]=name;
	//	registered_varlen++;
	//}
	//void* find_registered_data(string name,string&type) {
	//	for (int i = 0; i < registered_varlen; i++) {
	//		if (registered_varnames[i] == name) {
	//			type = registered_vartypes[i];
	//			return registered_variables[i];
	//		}
	//	}
	//	return NULL;
	//}
	//void remove_registered_data(string name) {
	//	for (int i = 0; i < registered_varlen; i++) {
	//		if (registered_varnames[i] == name) {
	//			registered_varlen--;
	//			registered_varnames[i] = registered_varnames[registered_varlen ];
	//			registered_vartypes[i] = registered_vartypes[registered_varlen];
	//			registered_variables[i] = registered_variables[registered_varlen];
	//			registered_varnames[registered_varlen]="";
	//			registered_vartypes[registered_varlen] = "";
	//			registered_variables[registered_varlen]=NULL;
	//			return;
	//		}
	//	}
	//}
*/