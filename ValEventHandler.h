#pragma once


void NoFunction() {} // 
void* NoFunc = (void*)&NoFunction;

class ValEventHandler {  // when adding scriptor in, event handler will have to be able to call script functions aswell.  add deliniation for script class
public:
	ValEventHandler(int x, int y);
	~ValEventHandler();
	// global eventhandler callback location.
	short* collision_table; // stored as short[y][x]
	int width, height;
	//_beginthread_proc_type functions[255];
	bool disabled[256];
	BYTE types[256];
	short control_id[256];
	HWND parents[256];
	//ValControl *hcontrol[256]; // type=2 valcontrol throws function
	//short register_control(ValControl *VC,
	//int script_info[256];
	int functions_len;
	void(*funcs[256])();
	string names[256];
	short register_function(void* a);// all registered functions must have NO arguments. 
	short register_function(string name, void* a);
	short add_event(int x, int y, int w, int h, short funcn);
	short throw_event_inline(int x, int y);
	short throw_event_thread(int x, int y);
	void output_coltable();
	void disable(short fn) { disabled[fn] = true; }
	void enable(short fn) { disabled[fn] = false; }
	

	short register_control(string name, BYTE id, int x, int y, int w, int h);
	short register_controlex(string name, BYTE id, int x, int y, int w, int h, void* a);
	short control_at(short x, short y);

	/***************mousecapture stuff**********************/
	//should probably be in valwindow instead
	int* capx, *capy;
	bool is_captured = false;
	void* capfunc;
	bool capture_mouse(void* capfc, int* capxx, int* capyy);// func should be (BYTE,x,y) BYTE is 0 for over, 1 for mousedown, 2 for mouseup
	void release_mouse();

	bool is_disabled = false;
	void disable_all_throws() { is_disabled = true; }
	void restart_all_throws(){ is_disabled = false; }
	string control_nameat(int x, int y);
};
/**********************toplevel functions************************************/


/**********************member functions************************************/
ValEventHandler::ValEventHandler(int x, int y) {

	width = x; height = y;
	collision_table = (short*)malloc(x * y * sizeof(short));
	ZeroMemory(collision_table, x * y * sizeof(short));
	functions_len = 1;
	ZeroMemory(disabled, 256 * sizeof(bool));
	ZeroMemory(control_id, 256*sizeof(short));
	ZeroMemory(parents, sizeof(HWND)*256);

}
ValEventHandler::~ValEventHandler() {
	free(collision_table);
}
short ValEventHandler::register_function(void* a) {
	funcs[functions_len] = (void(__cdecl*)(void))a;
	return functions_len++;
}
short ValEventHandler::register_function(string name, void* a) {
	funcs[functions_len] = (void(__cdecl*)(void))a;
	names[functions_len] = name;
	control_id[functions_len] = -1;
	return functions_len++;
}
short ValEventHandler::control_at(short x, short y) {
	if (y >= height || x >= width)return -1;
	if (functions_len == 1)return -1;
	short* hold = collision_table;
	hold += (y * width) + x;
	//cout << "control index found: " << *hold << " control id: " << (int)control_id[*hold] << " name: " <<names[*hold]<<endl;
	if (*hold == 0)return -1;
	return control_id[*hold];
}
string ValEventHandler::control_nameat(int x, int y) {
	if (y >= height || x >= width)return "";
	if (functions_len == 1)return "";
	short* hold = collision_table;
	hold += (y * width) + x;
	//cout << "control index found: " << *hold << " control id: " << (int)control_id[*hold] << " name: " <<names[*hold]<<endl;
	if (*hold == 0)return "";
	return names[*hold];
}

short ValEventHandler::register_controlex(string name, BYTE id, int x, int y, int w, int h, void* a) {
	names[functions_len] = name;
	control_id[functions_len] = id;

	add_event(x, y, w, h, functions_len);
	funcs[functions_len] = (void(__cdecl*)(void)) & a;
	return functions_len++;
}
short ValEventHandler::register_control(string name, BYTE id, int x, int y, int w, int h) {
	names[functions_len] = name;
	control_id[functions_len] = id;
	add_event(x, y, w, h, functions_len);
	funcs[functions_len] = (void(__cdecl*)(void))&NoFunction;
	return functions_len++;
}
short ValEventHandler::add_event(int x, int y, int w, int h, short funcn) {
	short* hold = collision_table;
	hold += (y * width) + x;
	int ww = x + w, hh = y + h;
	short ret = 0;
	for (int i = y; 1; ) {
		for (int n = x; n < ww; n++) {
			*hold = funcn; hold++;
			ret++;
		}
		if (++i == hh)break;
		hold = collision_table+((i*width)+x) ;
	}
	return ret;
}

short ValEventHandler::throw_event_inline(int x, int y) {
	if (is_disabled)return -1;

	cout << "attempted to throw event: " << x << ":" << y;

	
	short* hold = collision_table;
	short ret = *hold;
	hold += (y * width) + x;
    ret = *hold;
	if (disabled[ret])return 0;

	//cout << "found event: " << ret << endl;
	if (*hold == 0) {
		cout << endl; return 0;
	}
	cout << names[ret] << endl;
	
	((void(__cdecl*)(void))(funcs[ret])) ();


	return ret;

}
short ValEventHandler::throw_event_thread(int x, int y) {
	if (is_disabled)return -1;
	cout << "begin throw_event_thread x:y - " << x << ":" << y;
	if (functions_len == 1)return -1;
	if (y > height || x > width) {
		cout << "click out of bounds, returning nofunc-1\n";
		return -1;
	}
	//cout << "past fastclost\n";
	short* hold = collision_table;
	short ret = *hold;
	hold += (y * width) + x;
	ret = *hold;
	if (disabled[ret]) {
		cout << "   .. " << names[ret] << " is disabled\n";
		return -1;
	}
	if (*hold == 0) {
		cout <<" .. no object\n"; return -1;
	}
	
	cout << "  found event, index:name - " << ret << ":" << names[ret];
	
	//((void(__cdecl*)(void))(funcs[ret])) ();
	    //if(control_id[ret]!=0)   //insert some interact function in control that switch type does interact draw/function
	                               // can't be direct insert of either window or class, or call to global window or class
	//                                maybe can be a standalone function with void* map like eventthread written after control
	//                                that can properly call the control interact.

	if (funcs[ret] != VC_NOFUNC)_beginthread((_beginthread_proc_type)funcs[ret], 0, parents[ret]);
	else cout << " nofunc caught ";
	if (control_id[ret] != -1) {
		
		ret = control_id[ret];
		cout << " returning control id " << ret;
	}
	else ret = -1;

	cout << "\n";
	
	return ret;

}
void ValEventHandler::output_coltable() {
	short* hold = collision_table;
	for (int i = 0; i < height; i++) {
		for (int n = 0; n < width; n++) {
			cout << *hold << " ";
			hold++;

		}
		cout << endl;
	}
}

