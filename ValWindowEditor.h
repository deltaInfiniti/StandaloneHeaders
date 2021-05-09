#pragma once
//all edits left as comments currently ... cleanup imminent
void update_windowlist_but();
void update_controllist_but();
void process_controllist_but();
void target_controllist_but();
void do_clipboard(); void do_clipboard2(); void do_clipboard3();
void coutda() { cout << "da"; }
void controls_list_onclick();
void capture_proc(void* vwnd);
void new_control_but();
void copyxbut();
void copyybut();
void copyhbut();
void copywbut();
void filterbut();
void movesel_l();
void movesel_r();
void movesel_u();
void movesel_d();
void copytotargetbut();
void copytonewbut();
void togglecapturebut();
void savewindowbut();
void tabloopbut();
void clip_highlighted();
void createwindowbut();
void importwindowbut();
void exportwindowbut();

class ValWindowEditor {
public:
    stringlist windowlist, controllist;
    string cunder_status = "";
    string status = "";

    ValWindowEditor() {
        windowlist.clear();
        controllist.clear();
    }
    ~ValWindowEditor() {
        windowlist.clear();
        controllist.clear();
    }

    void valcontrol_to_varlist(ValControl* vc, varlist& vl) {
        // create a varlist that represents a valcontrol
    }
    void varlist_to_valcontrol_onwindow(ValWindow* vw, ValControl* vc, varlist& vl) {
        //add a valcontrol to a valwindow from a varlist
    }

    void target_window() {
        ValWindow* wind = WindowMan.fromName("Editor");
        ValControl* contarg = wind->controls[wind->find_control("windowslist")];
        ValWindow* targ = WindowMan.fromName(contarg->sval);
        if (!targ->IS_MOUSE_CAPTURED) {
            wind->GetControl("togglecapturebut")->setlabel("uncapture mouse");
        }else wind->GetControl("togglecapturebut")->setlabel("capture mouse");

        controllist.clear();
        for (int i = 0; i < targ->controlslen; i++) {
            controllist.queue(targ->controls[i]->title);
        }
        //controllist.queue("add control");
        contarg->drawtogfx();
        contarg->needs_redraw = true;

    }

    ValWindow* get_target_window() {
        status = "targeting";
        ValWindow* wind = WindowMan.fromName("Editor");
        ValControl* winltarg = wind->controls[wind->find_control("windowslist")];
        return WindowMan.fromName(winltarg->sval);
    }

    void target_control() {
        status = "targeting";
        ValWindow* wind = WindowMan.fromName("Editor");
        ValControl* winltarg = wind->controls[wind->find_control("windowslist")];
        ValWindow* wintarg = WindowMan.fromName(winltarg->sval);
        ValControl* conltarg = wind->controls[wind->find_control("controlslist")];
        ValControl* targ = wintarg->controls[wintarg->find_control(conltarg->sval)];
        if (targ == (ValControl*)0x1)return;
        wind->set_editctrl_text("x_coordbox", ctostr(targ->x));
        wind->set_editctrl_text("y_coordbox", ctostr(targ->y));
        wind->set_editctrl_text("w_coordbox", ctostr(targ->width));
        wind->set_editctrl_text("h_coordbox", ctostr(targ->height));
        wind->set_editctrl_text("titlebox", targ->title);
        wind->set_editctrl_text("databox", targ->dataname); 
        wind->set_editctrl_text("fontbox", targ->textformat->fontdat.lfFaceName);
        if (targ->type == VC_EDIT || targ->type == VC_PASSWORD) {
            wind->set_editctrl_text("textbox", wintarg->eval_edit(targ->title));
        }
        else wind->set_editctrl_text("textbox", targ->label);

        wind->set_editctrl_text("typebox", VC_TYPE_tostr(targ->type));
        wind->set_editctrl_text("codebox2", "wind->AddControl(\"" + targ->export_markup_string(true) + "\");");
    }

    string clip_target_window() {
        ValWindow* wind = WindowMan.fromName("Editor");
        ValControl* winltarg = wind->controls[wind->find_control("windowslist")];
        ValWindow* wintarg = WindowMan.fromName(winltarg->sval);
        string ret = "";
        for (int i = 0; i < wintarg->controlslen; i++) {
            
            ret += "wind->AddControl(\"" + wintarg->controls[i]->export_markup_string(true) + "\");\n";
            
        }
        return ret;
    }


    // readd new processcontrol here
    void add_control2() {
        status = "processing";
        ValWindow* wind = WindowMan.fromName("Editor");
        string wname = wind->evaluate_listbox("windowslist");
        int x = ctoint(wind->eval_edit("x_coordbox2"));
        int y = ctoint(wind->eval_edit("y_coordbox2"));
        int w = ctoint(wind->eval_edit("w_coordbox2"));
        int h = ctoint(wind->eval_edit("h_coordbox2"));
        string title = wind->eval_edit("titlebox2");
        string text = wind->eval_edit("textbox2");
        string data = wind->eval_edit("databox2");
        short type = VC_str_toTYPE(wind->eval_edit("typebox2"));
        ValWindow* wintarg = WindowMan.fromName(wname);
        string controlname = wind->evaluate_listbox("controlslist");
        string fontname = wind->eval_edit("fontbox2");
        short htemp = wintarg->add_control_ex_ts(type, title, text, VRECT{ x,y,w,h }, VC_NOFUNC, false);
        ValControl* targ = wintarg->controls[htemp];
        if (fontname != "")targ->textformat->SetFont(fontname);

        update_controllist_but();
        ValControl* listarg = wind->GetControl("controlslist");
        int i = 0;
        for (; i < controllist.length(); i++) {
            if (controllist[i] == title) {
                listarg->value[0] = 0;
                listarg->LISTDATA_OFFSET = i;
                break;
            }
        }
        
        listarg->drawtogfx();
        //controls_list_onclick();
        target_control();
        //listarg->needs_repaint = true;
        listarg->needs_redraw = true;
    }

    void process_control() {
        status = "processing";
        ValWindow* wind = WindowMan.fromName("Editor");
        string wname = wind->evaluate_listbox("windowslist");
        int x = ctoint(wind->eval_edit("x_coordbox"));
        int y = ctoint(wind->eval_edit("y_coordbox"));
        int w = ctoint(wind->eval_edit("w_coordbox"));
        int h = ctoint(wind->eval_edit("h_coordbox"));
        string title = wind->eval_edit("titlebox");
        string text = wind->eval_edit("textbox");
        string data = wind->eval_edit("databox");
        short type = VC_str_toTYPE(wind->eval_edit("typebox"));

        ValWindow* wintarg = WindowMan.fromName(wname);
        string controlname = wind->evaluate_listbox("controlslist");
        string fontname = wind->eval_edit("fontbox");
        

        ValControl* targ;
        if (controlname == "Add new") { // add control and select that control in controlslist
            short htemp = wintarg->add_control_ex_ts(type, title, text, VRECT{ x,y,w,h }, VC_NOFUNC, false);
            targ = wintarg->controls[htemp];
            update_controllist_but();
            ValControl* listarg = wind->GetControl("controlslist");
            int i = 0;
            for (; i < controllist.length(); i++) {
                if (controllist[i] == title) {
                    listarg->value[0] = 0;
                    listarg->LISTDATA_OFFSET = i;
                    break;
                }
            }
            listarg->drawtogfx();
        }
        else {
            targ = wintarg->GetControl(controlname);

            targ->x = x;
            targ->y = y;

            //targ->width = ctoint(wind->eval_edit("w_coordbox"));
            //targ->height = ctoint(wind->eval_edit("h_coordbox"));
            targ->RESERVED_resize(w, h);

            targ->title = title;
            targ->label = text;
            targ->type = type;
            if (fontname != "")targ->textformat->SetFont(fontname);
        }
        // 
        /*string code = "wind->add_control_ex_ts(";
        string code2 = "wind->AddControl(\"title=" + title + ",text=" + text + ",type=" + VC_TYPE_tostr(type) + ",x=" + ctostr(x) + ",y=" + ctostr(y) + ",w=" + ctostr(w) + ",h=" + ctostr(h);
        switch (type) {
        case VC_EDIT:
            code = "wind->add_editctrl_ts(\"" + title + "\", VRECT{" + ctostr(x) + "," + ctostr(y) + "," + ctostr(w) + "," + ctostr(h) + "}, \"" + text + "\");";
            code2 += ",dataname=" + data;
            break;
        case VC_LISTBOX:
            code = "wind->create_listboxts(\"" + title + "\",\"nt\", VRECT{" + ctostr(x) + "," + ctostr(y) + "," + ctostr(w) + "," + ctostr(h) + "}, &NEEDASTRLISTPOINTER);";
            code2 += ",dataname=" + data;
            break;
        case VC_PASSWORD:
            code = "wind->add_passwordctrl_ts(\"" + title + "\", VRECT{" + ctostr(x) + "," + ctostr(y) + "," + ctostr(w) + "," + ctostr(h) + "}, \"" + text + "\");";
            code2 += ",dataname=" + data;

        default:
            code += VC_TYPE_tostr(type) + ",\"" + title + "\",\"" + text + "\", VRECT{" + ctostr(x) + "," + ctostr(y) + "," + ctostr(w) + "," + ctostr(h) + "},VC_NOFUNC,false);";
            break;
        }
        code2 += "\");";*/
        wind->set_editctrl_text("codebox2", "wind->AddControl(\"" + targ->export_markup_string(true) + "\");");
        //wind->set_editctrl_text("codebox", code);
        //wind->set_editctrl_text("codebox3", code2);


        targ->drawtogfx();

        //target_control();
        wintarg->full_render = true;
        //while(1)Sleep(500000);
    }

    


    void build_editor_window2(ValWindow* wind) {



        //wind->AddControl("type=VC_LISTBOX,title=windowslist,text=nt,x=10,y=35,w=80,h=400,listboxfunc=update_controllist_but,dataname=windowlist,numblurs=0,textfont=Modern");
        //wind->AddControl("type=VC_LISTBOX,title=controlslist,text=nt,x=100,y=35,w=190,h=500,listboxfunc=controls_list_onclick,dataname=controllist,numblurs=0");
        //wind->AddControl("type=VC_GLOBAL_STAT_STRING,title=status,text=status:*S,x=10,y=-20,w=400,h=18,dataname=status");
        //wind->AddControl("type=VC_BUTTON,title=update_windowlist_but,text=update,x=10,y=435,w=80,h=16,dataname=update_windowlist_but");
        //wind->AddControl("type=VC_BUTTON,title=update_ctrl_but,text=update/unfilter,x=100,y=570,w=180,h=16,dataname=update_controllist_but");
        //wind->AddControl("type=VC_BUTTON,title=target_control_but,text=target,x=570,y=770,w=80,h=16,dataname=target_controllist_but");
        //wind->AddControl("type=VC_BUTTON,title=process_windowlist_but,text=process,x=425,y=247,w=100,h=22,dataname=process_controllist_but");
        //wind->AddControl("type=VC_LABEL,title=xLabel,text=  x,x=380,y=47,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=yLabel,text=  y,x=380,y=67,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=wLabel,text=width,x=380,y=87,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=hLabel,text=height,x=380,y=107,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=titlelabel,text=:title,x=490,y=137,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=textlabel,text=:text,x=490,y=157,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=typelabel,text=:type,x=490,y=177,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=datalabel,text=:data,x=490,y=197,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=fontlabel,text=:font,x=490,y=217,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_EDIT,title=x_coordbox,text= ,x=318,y=45,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coordbox");
        //wind->AddControl("type=VC_EDIT,title=y_coordbox,text=,x=318,y=65,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coordbox");
        //wind->AddControl("type=VC_EDIT,title=w_coordbox,text=,x=318,y=85,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coordbox");
        //wind->AddControl("type=VC_EDIT,title=h_coordbox,text=,x=318,y=105,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=titlebox");
        //wind->AddControl("type=VC_EDIT,title=titlebox,text=,x=318,y=135,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=textbox");
        //wind->AddControl("type=VC_EDIT,title=textbox,text=,x=318,y=155,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=typebox");
        //wind->AddControl("type=VC_EDIT,title=typebox,text=,x=318,y=175,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=databox");
        //wind->AddControl("type=VC_EDIT,title=databox,text=,x=318,y=195,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=fontbox");
        //wind->AddControl("type=VC_EDIT,title=fontbox,text=,x=318,y=215,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=x_coordbox");
        //wind->AddControl("type=VC_BUTTON,title=copyall_but,text=copy all,x=320,y=247,w=100,h=22");
        //wind->AddControl("type=VC_BUTTON,title=newctrl_but,text=create control,x=330,y=587,w=120,h=22,dataname=new_control_but");
        //wind->AddControl("type=VC_IMAGE,title=image1,text=cap.jpg,x=400,y=755,w=40,h=40,nointeract=true,background=cap.jpg");
        //wind->AddControl("type=VC_EDIT,title=codebox,text=codebox,x=648,y=743,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox3");
        //wind->AddControl("type=VC_EDIT,title=codebox2,text=,x=318,y=273,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox2");
        //wind->AddControl("type=VC_EDIT,title=codebox3,text=codebox3,x=648,y=703,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox");
        //wind->AddControl("type=VC_BUTTON,title=testclip,text=testclip,x=670,y=775,w=80,h=16,dataname=do_clipboard");
        //wind->AddControl("type=VC_BUTTON,title=clipwindowbut,text=clip window,x=650,y=85,w=150,h=25,dataname=do_clipboard3");
        //wind->AddControl("type=VC_BUTTON,title=testclip2,text=copy to clipboard,x=570,y=275,w=100,h=22,dataname=do_clipboard2,textfont=Modern");
        //wind->AddControl("type=VC_LABEL,title=xLabel2,text=  x,x=380,y=362,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=yLabel2,text=  y,x=380,y=382,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=wLabel2,text=width,x=380,y=402,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=hLabel2,text=height,x=380,y=422,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=titlelabel2,text=:title,x=490,y=452,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=textlabel2,text=:text,x=490,y=502,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=typelabel2,text=:type,x=490,y=522,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=datalabel2,text=:data,x=490,y=542,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=fontlabel2,text=:font,x=490,y=562,w=50,h=18,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_EDIT,title=x_coordbox2,text=,x=318,y=360,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coordbox2");
        //wind->AddControl("type=VC_EDIT,title=y_coordbox2,text=,x=318,y=380,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coordbox2");
        //wind->AddControl("type=VC_EDIT,title=w_coordbox2,text=,x=318,y=400,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coordbox2");
        //wind->AddControl("type=VC_EDIT,title=h_coordbox2,text=,x=318,y=420,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=titlebox2");
        //wind->AddControl("type=VC_EDIT,title=titlebox2,text=,x=318,y=450,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=textbox2");
        //wind->AddControl("type=VC_EDIT,title=textbox2,text=,x=318,y=500,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=typebox2");
        //wind->AddControl("type=VC_EDIT,title=typebox2,text=,x=318,y=520,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=databox2");
        //wind->AddControl("type=VC_EDIT,title=databox2,text=,x=318,y=540,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=fontbox2");
        //wind->AddControl("type=VC_EDIT,title=fontbox2,text=,x=318,y=560,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=x_coordbox2");
        //wind->AddControl("type=VC_GLOBAL_STAT_INT,title=statusx,text=mouse x:*I,x=10,y=-40,w=120,h=18,dataname=mscX");
        //wind->AddControl("type=VC_GLOBAL_STAT_INT,title=statusy,text=mouse y:*I,x=10,y=-60,w=120,h=18,dataname=mscY");
        //wind->AddControl("type=VC_GLOBAL_STAT_STRING,title=statusctrl,text=last clicked:*S,x=10,y=-80,w=250,h=18,dataname=cunder_status");
        //wind->AddControl("type=VC_EDIT,title=mousecapbox_x,text=,x=641,y=405,w=50,h=22,numblurs=0,transparent=true,nointeract=true,tabname=mousecapbox_y");
        //wind->AddControl("type=VC_EDIT,title=mousecapbox_y,text=,x=704,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=mousecapbox_w");
        //wind->AddControl("type=VC_EDIT,title=mousecapbox_w,text=,x=773,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=mousecapbox_h");
        //wind->AddControl("type=VC_EDIT,title=mousecapbox_h,text=,x=833,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=selmoveamtbox");
        //wind->AddControl("type=VC_BUTTON,title=copybutx,text=Copy,x=440,y=47,w=50,h=18,dataname=copyxbut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=copybuty,text=Copy,x=440,y=67,w=50,h=18,dataname=copyybut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=copybutw,text=Copy,x=440,y=87,w=50,h=18,dataname=copywbut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=copybuth,text=Copy,x=440,y=107,w=50,h=18,dataname=copyhbut,textfont=Modern");
        //wind->AddControl("type=VC_EDIT,title=filterbox,text=,x=100,y=540,w=140,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=filenamebox");
        //wind->AddControl("type=VC_BUTTON,title=filterbut,text=filter,x=249,y=540,w=40,h=22,dataname=filterbut,textfont=Modern");
        //wind->AddControl("type=VC_LABEL,title=mousecaplabal2,text=selection/click: ,x=640,y=363,w=90,h=19,numblurs=1,textfont=Modern,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=mousecaplabal,text=x:            y:                width:       height:,x=640,y=384,w=234,h=19,numblurs=1,textfont=Modern,transparent=true");
        //wind->AddControl("type=VC_BUTTON,title=movesell,text=left,x=685,y=485,w=50,h=18,dataname=movesel_l,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=moveselr,text=right,x=785,y=485,w=50,h=18,dataname=movesel_r,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=moveselu,text=up,x=735,y=465,w=50,h=18,dataname=movesel_u,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=moveseld,text=down,x=735,y=505,w=50,h=18,dataname=movesel_d,textfont=Modern");
        //wind->AddControl("type=VC_EDIT,title=selmoveamtbox,text=10,x=735,y=484,w=48,h=22,numblurs=0,transparent=true,nointeract=true,tabname=mousecapbox_x");
        //wind->AddControl("type=VC_BUTTON,title=copyrectnewbut,text=copy->new,x=640,y=432,w=100,h=22,dataname=copytonewbut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=copyrecttargbut,text=copy->target,x=758,y=432,w=100,h=22,dataname=copytotargetbut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=togglecapturebut,text=uncapture mouse,x=755,y=346,w=130,h=30,dataname=togglecapturebut");
        //wind->AddControl("type=VC_LABEL,title=targetlabel,text=Targetted control:,x=316,y=10,w=156,h=19,numblurs=1,transparent=true");
        //wind->AddControl("type=VC_LABEL,title=newctrllabel,text=New Control/Window,x=315,y=337,w=157,h=19,numblurs=1,textfont=Modern,transparent=true");
        //wind->AddControl("type=VC_EDIT,title=filenamebox,text=code.txt,x=656,y=50,w=127,h=20,numblurs=0,transparent=true,nointeract=true,tabname=filterbox");
        //wind->AddControl("type=VC_BUTTON,title=savebut,text=save,x=787,y=48,w=69,h=19,dataname=savewindowbut");
        //wind->AddControl("type=VC_BUTTON,title=new_windowbut,text=Create_Window,x=321,y=474,w=211,h=20,dataname=createwindowbut");
        //wind->AddControl("type=VC_BUTTON,title=edit_tabs_but,text=create edit tab loop,x=639,y=530,w=243,h=25,dataname=tabloopbut,textfont=Modern");
        //wind->AddControl("type=VC_BUTTON,title=clip_highlightedbut,text=highlighted->clipboard,x=639,y=560,w=243,h=25,dataname=clip_highlighted,textfont=Modern");
        //wind->AddControl("type=VC_LABEL,title=winconlabel,text=Windows:         Controls:,x=6,y=14,w=150,h=20,numblurs=1,textfont=Modern,transparent=true");
        //wind->AddControl("type=VC_SLIDER,title=Slidertest,text=slider,x=11,y=680,w=348,h=28,numblurs=0,textfont=Modern");
        wind->AddControl("type=VC_LISTBOX,title=windowslist,text=nt,x=10,y=35,w=140,h=400,listboxfunc=update_controllist_but,dataname=windowlist,numblurs=0,textfont=Modern");
        wind->AddControl("type=VC_LISTBOX,title=controlslist,text=nt,x=170,y=35,w=190,h=500,listboxfunc=controls_list_onclick,dataname=controllist,numblurs=0");
        wind->AddControl("type=VC_GLOBAL_STAT_STRING,title=status,text=status:*S,x=10,y=-20,w=400,h=18,dataname=status");
        wind->AddControl("type=VC_BUTTON,title=update_windowlist_but,text=update,x=10,y=445,w=140,h=18,dataname=update_windowlist_but");
        wind->AddControl("type=VC_BUTTON,title=update_ctrl_but,text=update/unfilter,x=170,y=570,w=180,h=16,dataname=update_controllist_but");
        wind->AddControl("type=VC_BUTTON,title=target_control_but,text=target,x=570,y=770,w=80,h=16,dataname=target_controllist_but");
        wind->AddControl("type=VC_BUTTON,title=process_windowlist_but,text=process,x=495,y=247,w=100,h=22,dataname=process_controllist_but");
        wind->AddControl("type=VC_LABEL,title=xLabel,text=  x,x=450,y=47,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=yLabel,text=  y,x=450,y=67,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=wLabel,text=width,x=450,y=87,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=hLabel,text=height,x=450,y=107,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=titlelabel,text=:title,x=560,y=137,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=textlabel,text=:text,x=560,y=157,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=typelabel,text=:type,x=560,y=177,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=datalabel,text=:data,x=560,y=197,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=fontlabel,text=:font,x=560,y=217,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_EDIT,title=x_coordbox,text= ,x=388,y=45,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coordbox");
        wind->AddControl("type=VC_EDIT,title=y_coordbox,text=,x=388,y=65,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coordbox");
        wind->AddControl("type=VC_EDIT,title=w_coordbox,text=,x=388,y=85,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coordbox");
        wind->AddControl("type=VC_EDIT,title=h_coordbox,text=,x=388,y=105,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=titlebox");
        wind->AddControl("type=VC_EDIT,title=titlebox,text=,x=388,y=135,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=textbox");
        wind->AddControl("type=VC_EDIT,title=textbox,text=,x=388,y=155,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=typebox");
        wind->AddControl("type=VC_EDIT,title=typebox,text=,x=388,y=175,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=databox");
        wind->AddControl("type=VC_EDIT,title=databox,text=,x=388,y=195,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=fontbox");
        wind->AddControl("type=VC_EDIT,title=fontbox,text=,x=388,y=215,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=x_coordbox");
        wind->AddControl("type=VC_BUTTON,title=copyall_but,text=copy all,x=390,y=247,w=100,h=22");
        wind->AddControl("type=VC_BUTTON,title=newctrl_but,text=create control,x=400,y=587,w=120,h=22,dataname=new_control_but");
        wind->AddControl("type=VC_IMAGE,title=image1,text=cap.jpg,x=400,y=755,w=40,h=40,nointeract=true,background=cap.jpg");
        wind->AddControl("type=VC_EDIT,title=codebox,text=codebox,x=648,y=743,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox3");
        wind->AddControl("type=VC_EDIT,title=codebox2,text=,x=388,y=273,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox2");
        wind->AddControl("type=VC_EDIT,title=codebox3,text=codebox3,x=648,y=703,w=244,h=22,numblurs=0,transparent=true,nointeract=true,tabname=codebox");
        wind->AddControl("type=VC_BUTTON,title=testclip,text=testclip,x=670,y=775,w=80,h=16,dataname=do_clipboard");
        wind->AddControl("type=VC_BUTTON,title=clipwindowbut,text=clip window,x=650,y=85,w=150,h=25,dataname=do_clipboard3");
        wind->AddControl("type=VC_BUTTON,title=testclip2,text=copy to clipboard,x=640,y=275,w=100,h=22,dataname=do_clipboard2,textfont=Modern");
        wind->AddControl("type=VC_LABEL,title=xLabel2,text=  x,x=450,y=362,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=yLabel2,text=  y,x=450,y=382,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=wLabel2,text=width,x=450,y=402,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=hLabel2,text=height,x=450,y=422,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=titlelabel2,text=:title,x=560,y=452,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=textlabel2,text=:text,x=560,y=502,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=typelabel2,text=:type,x=560,y=522,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=datalabel2,text=:data,x=560,y=542,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=fontlabel2,text=:font,x=560,y=562,w=50,h=18,numblurs=1,transparent=true");
        wind->AddControl("type=VC_EDIT,title=x_coordbox2,text=,x=388,y=360,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coordbox2");
        wind->AddControl("type=VC_EDIT,title=y_coordbox2,text=,x=388,y=380,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coordbox2");
        wind->AddControl("type=VC_EDIT,title=w_coordbox2,text=,x=388,y=400,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coordbox2");
        wind->AddControl("type=VC_EDIT,title=h_coordbox2,text=,x=388,y=420,w=44,h=22,numblurs=0,transparent=true,nointeract=true,tabname=titlebox2");
        wind->AddControl("type=VC_EDIT,title=titlebox2,text=,x=388,y=450,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=textbox2");
        wind->AddControl("type=VC_EDIT,title=textbox2,text=,x=388,y=500,w=154,h=22,numblurs=0,transparent=true,nointeract=true,tabname=typebox2");
        wind->AddControl("type=VC_EDIT,title=typebox2,text=,x=388,y=520,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=databox2");
        wind->AddControl("type=VC_EDIT,title=databox2,text=,x=388,y=540,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=fontbox2");
        wind->AddControl("type=VC_EDIT,title=fontbox2,text=,x=388,y=560,w=164,h=22,numblurs=0,transparent=true,nointeract=true,tabname=x_coordbox2");
        wind->AddControl("type=VC_GLOBAL_STAT_INT,title=statusx,text=mouse x:*I,x=10,y=-40,w=120,h=18,dataname=mscX");
        wind->AddControl("type=VC_GLOBAL_STAT_INT,title=statusy,text=mouse y:*I,x=10,y=-60,w=120,h=18,dataname=mscY");
        wind->AddControl("type=VC_GLOBAL_STAT_STRING,title=statusctrl,text=last clicked:*S,x=10,y=-80,w=250,h=18,dataname=cunder_status");
        wind->AddControl("type=VC_EDIT,title=mousecapbox_x,text=,x=641,y=405,w=50,h=22,numblurs=0,transparent=true,nointeract=true,tabname=mousecapbox_y");
        wind->AddControl("type=VC_EDIT,title=mousecapbox_y,text=,x=704,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=mousecapbox_w");
        wind->AddControl("type=VC_EDIT,title=mousecapbox_w,text=,x=773,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=mousecapbox_h");
        wind->AddControl("type=VC_EDIT,title=mousecapbox_h,text=,x=833,y=405,w=50,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=selmoveamtbox");
        wind->AddControl("type=VC_BUTTON,title=copybutx,text=Copy,x=510,y=47,w=50,h=18,dataname=copyxbut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=copybuty,text=Copy,x=510,y=67,w=50,h=18,dataname=copyybut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=copybutw,text=Copy,x=510,y=87,w=50,h=18,dataname=copywbut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=copybuth,text=Copy,x=510,y=107,w=50,h=18,dataname=copyhbut,textfont=Modern");
        wind->AddControl("type=VC_EDIT,title=filterbox,text=,x=170,y=540,w=140,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true,tabname=filenamebox");
        wind->AddControl("type=VC_BUTTON,title=filterbut,text=filter,x=319,y=540,w=40,h=22,dataname=filterbut,textfont=Modern");
        wind->AddControl("type=VC_LABEL,title=mousecaplabal2,text=selection/click: ,x=640,y=363,w=90,h=19,numblurs=1,textfont=Modern,transparent=true");
        wind->AddControl("type=VC_LABEL,title=mousecaplabal,text=x:            y:                width:       height:,x=640,y=384,w=234,h=19,numblurs=1,textfont=Modern,transparent=true");
        wind->AddControl("type=VC_BUTTON,title=movesell,text=left,x=685,y=485,w=50,h=18,dataname=movesel_l,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=moveselr,text=right,x=785,y=485,w=50,h=18,dataname=movesel_r,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=moveselu,text=up,x=735,y=465,w=50,h=18,dataname=movesel_u,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=moveseld,text=down,x=735,y=505,w=50,h=18,dataname=movesel_d,textfont=Modern");
        wind->AddControl("type=VC_EDIT,title=selmoveamtbox,text=10,x=735,y=484,w=48,h=22,numblurs=0,transparent=true,nointeract=true,tabname=mousecapbox_x");
        wind->AddControl("type=VC_BUTTON,title=copyrectnewbut,text=copy->new,x=640,y=432,w=100,h=22,dataname=copytonewbut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=copyrecttargbut,text=copy->target,x=758,y=432,w=100,h=22,dataname=copytotargetbut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=togglecapturebut,text=uncapture mouse,x=755,y=346,w=130,h=30,dataname=togglecapturebut");
        wind->AddControl("type=VC_LABEL,title=targetlabel,text=Targetted control:,x=386,y=10,w=156,h=19,numblurs=1,transparent=true");
        wind->AddControl("type=VC_LABEL,title=newctrllabel,text=New Control/Window,x=385,y=337,w=157,h=19,numblurs=1,textfont=Modern,transparent=true");
        wind->AddControl("type=VC_EDIT,title=filenamebox,text=code.txt,x=656,y=50,w=127,h=20,numblurs=0,transparent=true,nointeract=true,tabname=filterbox");
        wind->AddControl("type=VC_BUTTON,title=savebut,text=save,x=787,y=48,w=69,h=19,dataname=savewindowbut");
        wind->AddControl("type=VC_BUTTON,title=new_windowbut,text=Create_Window,x=391,y=474,w=211,h=20,dataname=createwindowbut");
        wind->AddControl("type=VC_BUTTON,title=edit_tabs_but,text=create edit tab loop,x=639,y=530,w=243,h=25,dataname=tabloopbut,textfont=Modern");
        wind->AddControl("type=VC_BUTTON,title=clip_highlightedbut,text=highlighted->clipboard,x=639,y=560,w=243,h=25,dataname=clip_highlighted,textfont=Modern");
        wind->AddControl("type=VC_LABEL,title=winconlabel,text=Windows:         Controls:,x=76,y=14,w=150,h=20,numblurs=1,textfont=Modern,transparent=true");
        wind->AddControl("type=VC_SLIDER,title=Slidertest,text=slider,x=11,y=680,w=348,h=28,numblurs=0,textfont=Modern");
        wind->AddControl("type=VC_EDIT,title=windowsavebox,text=window.txt,x=13,y=467,w=134,h=22,numblurs=0,textfont=Modern,transparent=true,nointeract=true");
        wind->AddControl("type=VC_BUTTON,title=windowsavesbut,text=export window,x=11,y=500,w=134,h=22,textfont=Modern,dataname=exportwindowbut");
        wind->AddControl("type=VC_BUTTON,title=windowimportbut,text=import window,x=11,y=527,w=134,h=22,textfont=Modern,dataname=importwindowbut");

        wind->calculate_edit_ctrl_tabs();
    }
    //ancient artifact. this is what I built with hard code and itself. this is what it looked like when I completed AddControl and windowclip 
    void build_editor_window(ValWindow* wind) {

        //wind->create_listboxts("windowslist", "nt", VRECT{ 10,10,80,400 }, &windowlist);
        //wind->controls[wind->controlslen - 1]->dataname = "windowlist";

        ValControl* vc = wind->AddControl("title=windowslist,text=nt,type=VC_LISTBOX,x=10,y=10,w=80,h=400,dataname=windowlist,textfont=MV Boli");
        vc->set_listbox_function(update_controllist_but, "update_controllist_but");
        vc= wind->controls[wind->create_listboxts("controlslist", "nt", VRECT{ 100,10,150,400 }, &controllist)];
        vc->dataname = "controllist";
        vc->set_listbox_function(controls_list_onclick, "controls_list_onclick");
        //target window button and function.if cant do on change
        //target control button if cant do on change
        wind->associate_data((void*)&windowlist, "windowlist");
        wind->associate_data((void*)&controllist, "controllist");
        short x = 280;

        wind->add_editctrl_ts("x_coordbox", VRECT{ x,10,40,18 }, "0");
        wind->add_editctrl_ts("y_coordbox", VRECT{ x,30,40,18 }, "0");
        wind->add_editctrl_ts("w_coordbox", VRECT{ x,50,40,18 }, "0");
        wind->add_editctrl_ts("h_coordbox", VRECT{ x,70,40,18 }, "0");
        //wind->add_editctrl_ts("titlebox", VRECT{ x,83,240,18 }, "");
        wind->add_editctrl_ts("titlebox", VRECT{ 280,100,150,18 }, "");
        //wind->add_editctrl_ts("textbox", VRECT{ x,100,240,18 }, "");
        wind->add_editctrl_ts("textbox", VRECT{ 280,120,150,18 }, "");
        //wind->add_editctrl_ts("typebox", VRECT{ x,120,240,18 }, "");
        wind->add_editctrl_ts("typebox", VRECT{ 280,140,160,18 }, "");
        wind->add_editctrl_ts("databox", VRECT{ 280,160,160,18 }, "");
        wind->add_editctrl_ts("fontbox", VRECT{ 280,180,160,18 }, "");

        wind->add_editctrl_ts("codebox", VRECT{ x,400,240,18 }, "");
        //wind->add_editctrl_ts("codebox2", VRECT{ 280,380,240,18 }, "");
        wind->AddControl("title=codebox2,text=,type=VC_EDIT,x=280,y=380,w=240,h=18,dataname=");
        wind->AddControl("title=codebox3,text=,type=VC_EDIT,x=280,y=360,w=240,h=18,dataname=");
        //title=windowslist,text=nt,x=10,y=10,w=80,h=400,dataname=,numblurs=0,textfont=Consolas
        //edits for x, y w h 
        //buttons and funcs for
        //bigger/smaller/arrow moves


        wind->add_control_ex_ts(VC_BUTTON, "update_windowlist_but", "update", VRECT{ 10,410,80,16 }, update_windowlist_but, false);
        wind->add_control_ex_ts(VC_BUTTON, "update_ctrl_but", "update ", VRECT{ 100,410,80,16 }, update_controllist_but, false);
        wind->add_control_ex_ts(VC_BUTTON, "target_control_but", "target", VRECT{ 100,440,80,16 }, target_controllist_but, false);
        wind->add_control_ex_ts(VC_BUTTON, "process_windowlist_but", "process", VRECT{ 100,470,80,16 }, process_controllist_but, false);
        //wind->add_control_ex_ts(VC_BUTTON, "clipwindow_but", "clip all", VRECT{ 100,490,80,16 }, process_controllist_but, false);

        //wind->add_control_ex_ts(VC_BUTTON, "testclip", "testclip", VRECT{ 300,430,80,16 }, do_clipboard, false);
        wind->AddControl("title=testclip,text=testclip,type=VC_BUTTON,x=300,y=430,w=80,h=16,dataname=do_clipboard");
        wind->AddControl("title=clipwindowbut,text=clip all,type=VC_BUTTON,x=300,y=480,w=80,h=25,dataname=do_clipboard3");
        
        short c = wind->add_control_ex_ts(VC_BUTTON, "testclip2", "testclip2", VRECT{ 390,430,90,16 }, do_clipboard2, false);
        wind->controls[c]->load_background("cap.jpg");
        wind->add_control_ex_ts(VC_LABEL, "xLabel", "  x", VRECT{ 340,10,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "yLabel", "  y", VRECT{ 340,30,50,18 }, VC_NOFUNC, false);

        wind->add_control_ex_ts(VC_LABEL, "wLabel", "width", VRECT{ 340,50,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "hLabel", "height", VRECT{ 340,70,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "titlelabel", ":title", VRECT{ 450,100,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "textlabel", ":text", VRECT{ 450,120,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "typelabel", ":type", VRECT{ 450,140,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "datalabel", ":data", VRECT{ 450,160,50,18 }, VC_NOFUNC, false);
        wind->add_control_ex_ts(VC_LABEL, "fontlabel", ":font", VRECT{ 450,180,50,18 }, VC_NOFUNC, false);
        
        wind->AddControl("type=VC_GLOBAL_STAT_STRING,title=status,text=status:*S,x=10,y=-20,w=400,h=18,dataname=status,transparent=true");
        wind->add_control_ex_ts(VC_IMAGE, "image1", "cap.jpg", VRECT{ 450,450,40,40 }, VC_NOFUNC, false);

        //wind->AddControl("type=VC_BUTTON,title=new_window_but,text=new wind,x=10,y=470,w=80,h=16");
        // need wid/hit box/label for ^^
        // filter box/label button function. 
        //  function call update and filter and * wildcard
        //move clip boxes/buttons down. 

        //wind->add_global_stat_int(VC_GLOBAL_STAT_STRING, "status", "status:*S", VRECT{ 10,  540,  400, 18 }, &status);

            //clicking a control in the list loads it's vars- x, y, w, h  can get crazy with this later
            // button on the right for 'execute changes' if can't automatically reset vars once a second or on lose focus or something
            //may have to make a function register class like eventshandler and register all the functions somehow.
            //static int values for mouse x,y coords, 
            //bigger/smaller/arrow move buttons
            //export window function/button.. filename editctrl.. safe varlist import/export
            //import window function/button.. filename editctrl
            //also maybe a sourcecode generator... once i simplify the calling types this will become far simpler
    }
    
    void start_window_editor_thread() {
        //if (WindowMan.is_splashing())WindowMan.wait_for_splash();
        //VWM_register_datan(, "");
        VWM_register_datan(&controllist,"controllist");
        VWM_register_datan(&windowlist,"windowlist");
        VWM_register_datan(&status, "status");
        VWM_register_datan(do_clipboard, "do_clipboard");
        VWM_register_datan(do_clipboard3, "do_clipboard3");
        VWM_register_datan(update_controllist_but, "update_controllist_but");  
        VWM_register_datan(controls_list_onclick, "controls_list_onclick");
        VWM_register_datan(update_windowlist_but, "update_windowlist_but");
        VWM_register_datan(target_controllist_but, "target_controllist_but");
        VWM_register_datan(process_controllist_but, "process_controllist_but");
        VWM_register_datan(do_clipboard2, "do_clipboard2");
        VWM_register_datan(&msc.x, "mscX");
        VWM_register_datan(&msc.y, "mscY");
        VWM_register_datan(new_control_but, "new_control_but");
        VWM_register_datan(copyxbut, "copyxbut");
        VWM_register_datan(copyybut, "copyybut");
        VWM_register_datan(copywbut, "copywbut");
        VWM_register_datan(copyhbut, "copyhbut");
        VWM_register_datan(filterbut, "filterbut");
        VWM_register_datan(&cunder_status, "cunder_status");
        VWM_register_datan(movesel_l, "movesel_l");
        VWM_register_datan(movesel_r, "movesel_r");
        VWM_register_datan(movesel_u, "movesel_u");
        VWM_register_datan(movesel_d, "movesel_d");
        VWM_register_datan(copytotargetbut, "copytotargetbut");
        VWM_register_datan(copytonewbut, "copytonewbut");
        VWM_register_datan(togglecapturebut, "togglecapturebut");
        VWM_register_datan(savewindowbut, "savewindowbut");
        VWM_register_data(tabloopbut, "tabloopbut");
        VWM_register_data(clip_highlighted, "clip_highlighted");
        VWM_register_data(createwindowbut, "createwindowbut");
        VWM_register_datan(importwindowbut, "importwindowbut");
        VWM_register_datan(exportwindowbut, "exportwindowbut");
        
        status = "window creation";
        ValWindow* wind2 = WindowMan.create_new_windowts("target", 900, 100, 900, 900, 1);
        wind2->events->disable_all_throws();
        
        wind2->hide();
        //write capture clicks function for eventhandler that can call a func(in,int)
        //write function that sets window and control selection on editor window
        build_editor_window2(wind2);

        
        ValWindow* wind = WindowMan.create_new_windowts("Editor", 100, 100, 900, 900, 1);
        wind->hide();

        build_editor_window2(wind);
        update_windowlist_but();
        //edit for window name on top. button to the right 'load window'
        //left side is listbox with all controls on window. last node is 'add control'.  work that out later
        
        WindowMan.remove_registered_data("controllist");

        status = "window creation finished";
        WindowMan.wait_for_splash();
        wind->show();
        wind2->show();
    }

    mouse_capture_struct msc = { 0,0,0 };
    mouse_capture_struct mscl = { 0,0,0 };
    mouse_capture_struct mscll = { 0,0,0 };
    

}valeditor;

void exportwindowbut() {
    ValWindow* wintarg= valeditor.get_target_window();
    ValWindow* wind = WindowMan.fromName("Editor");
    string markup = wintarg->export_markup();
    Write_File(wind->eval_edit("windowsavebox"),markup);

}
void importwindowbut() {
    string fname = WindowMan.fromName("Editor")->eval_edit("windowsavebox");
    WindowMan.import_markup_file(fname);

}
void createwindowbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    string title = wind->eval_edit("titlebox2");
    int x = ctoint(wind->eval_edit("x_coordbox2"));
    int y = ctoint(wind->eval_edit("y_coordbox2"));
    int w = ctoint(wind->eval_edit("w_coordbox2"));
    int h = ctoint(wind->eval_edit("h_coordbox2"));
    WindowMan.create_new_windowts(title, x, y, w, h, 1);
}
void tabloopbut() {
    ValWindow* wintarg = valeditor.get_target_window();
    wintarg->calculate_edit_ctrl_tabs_highlight();
}
void togglecapturebut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    ValWindow* wintarg = valeditor.get_target_window();
    ValControl* buttarg = wind->GetControl("togglecapturebut");
    if (wintarg->IS_MOUSE_CAPTURED) {
        wintarg->release_mouse();
        buttarg->setlabel("capture mouse");

    }
    else {
        wintarg->capture_mouse(&valeditor.msc, capture_proc);
        buttarg->setlabel("uncapture mouse");
    }

}

bool caught_first_mouselbut = false;
bool caught_secnd_mouselbut = false;
int caught_mousebutl_count = 0;

// ValWindow Mousecapture process. draws squares over drag area, highlights when mouse release or on non-drag click
void capture_proc(void* vwnd) {
    ValWindow* wind = (ValWindow*)vwnd;
    ValWindow* wind2 = WindowMan.fromName("Editor");
    //if(wind->mouse_cap->type==VW_MOUSECAP_CLICK)valeditor.msc = *(wind->mouse_cap);
    if (wind->mouse_cap->type == VW_MOUSECAP_CLICK) {
        

        
        valeditor.cunder_status = wind->control_nameat_c(wind->mouse_cap->x, wind->mouse_cap->y);
        
        if (caught_first_mouselbut && caught_secnd_mouselbut) {
            //wind->mygfxforg.makeblack();
            wind->mygfxforg.makecolor(VRGB_BLACK);
            wind->mygfxforg.draw_box2(valeditor.mscl.x, valeditor.mscl.y, valeditor.mscll.x, valeditor.mscll.y
                , 3, 0, VRGB_RED);
            if(!GetAsyncKeyState(VK_SHIFT)) wind->unhighlight_all();
            box_dims_highlow(valeditor.mscl.x, valeditor.mscl.y, valeditor.mscll.x, valeditor.mscll.y);
            wind2->set_editctrl_text("mousecapbox_w", ctostr(valeditor.mscll.x - valeditor.mscl.x)); 
            wind2->set_editctrl_text("mousecapbox_h", ctostr(valeditor.mscll.y - valeditor.mscl.y));
            wind2->set_editctrl_text("mousecapbox_x", ctostr(valeditor.mscl.x));
            wind2->set_editctrl_text("mousecapbox_y", ctostr(valeditor.mscl.y));
            wind->highlight_selection(valeditor.mscl.x, valeditor.mscl.y, valeditor.mscll.x - valeditor.mscl.x, valeditor.mscll.y - valeditor.mscl.y);
            
            
        }
        else if(valeditor.cunder_status!="") {
            
            ValControl* vc = wind->GetControl(valeditor.cunder_status);
            vc->toggle_highlight();
            vc->needs_repaint = true;
            vc->needs_redraw = true;
            
        }
        caught_first_mouselbut = false;
        caught_secnd_mouselbut = false;
        caught_mousebutl_count = 0;
        return;
    }
    if (wind->mouse_cap->type == VW_MOUSECAP_LDOWN) {
        if (caught_first_mouselbut ) {
            //wind->mygfxforg.makeblack();
            wind->mygfxforg.makecolor(VRGB_BLACK);
            if (caught_mousebutl_count > 8) {
                wind->mygfxforg.draw_box2(valeditor.mscl.x, valeditor.mscl.y, wind->mouse_cap->x, wind->mouse_cap->y
                    , 3, 0, VRGB_WHITE);
                wind->full_render = true;
                wind->read_mousecap(valeditor.mscll.x, valeditor.mscll.y, valeditor.mscll.type);
                caught_secnd_mouselbut = true;
            }
            caught_mousebutl_count++;
        }
        else {
            //cout << "caught first mousedown" << valeditor.mscl.type << endl;
            wind->read_mousecap(valeditor.mscl.x, valeditor.mscl.y, valeditor.mscl.type);
            caught_first_mouselbut = true;
        }
        return;

    }
    caught_secnd_mouselbut = false;
    caught_first_mouselbut = false;
    caught_mousebutl_count = 0;
    //wind2->set_editctrl_text("mousecapbox_x", ctostr(wind->mouse_cap->x));
    //wind2->set_editctrl_text("mousecapbox_y", ctostr(wind->mouse_cap->y));
    //valeditor.mscl.type = -1;
    //cout << "did capture_proc" << endl;
}

void filterbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    ValControl* contarg = wind->controls[wind->find_control("windowslist")];
    ValWindow* targ = WindowMan.fromName(contarg->sval);
    string filter = wind->eval_edit("filterbox");
    string t;

    valeditor.controllist.clear();
    for (int i = 0; i < targ->controlslen; i++) {
        t = targ->controls[i]->title;

        if(instr(t,filter)) valeditor.controllist.queue(t);
    }
    //controllist.queue("add control");
    ValControl* listtarg = wind->GetControl("controlslist");
    listtarg->drawtogfx();
    //listtarg->needs_repaint = true;
    listtarg->needs_redraw = true;
    //contarg->drawtogfx();
    //contarg->needs_redraw = true;
    controls_list_onclick();

}



void movesel(int x, int y) {
    cout << "movsel: " << x << ":" << y << endl;
    ValWindow* wind = valeditor.get_target_window();

    for (int i = 0; i < wind->controlslen; i++) {
        if (wind->controls[i]->do_highlight)wind->controls[i]->move(x, y,wind->clientwidth,wind->clientheight, 1);
    }
    wind->full_render = true;
}

void movesel_l(){
    int m = ctoint(WindowMan.fromName("Editor")->eval_edit("selmoveamtbox"));
    movesel(m*-1, 0);
}
void movesel_r(){
    int m = ctoint(WindowMan.fromName("Editor")->eval_edit("selmoveamtbox"));
    movesel(m, 0);
}
void movesel_u(){
    int m = ctoint(WindowMan.fromName("Editor")->eval_edit("selmoveamtbox"));
    movesel(0, m*-1);
}
void movesel_d(){
    int m = ctoint(WindowMan.fromName("Editor")->eval_edit("selmoveamtbox"));
    movesel(0, m);
}
void copyxbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("x_coordbox2", wind->eval_edit("x_coordbox"));
}
void copyybut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("y_coordbox2", wind->eval_edit("y_coordbox"));
}
void copyhbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("h_coordbox2", wind->eval_edit("h_coordbox"));
}
void copywbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("w_coordbox2", wind->eval_edit("w_coordbox"));
}

void copytonewbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("x_coordbox2", wind->eval_edit("mousecapbox_x"));
    wind->set_editctrl_text("y_coordbox2", wind->eval_edit("mousecapbox_y"));
    wind->set_editctrl_text("w_coordbox2", wind->eval_edit("mousecapbox_w"));
    wind->set_editctrl_text("h_coordbox2", wind->eval_edit("mousecapbox_h"));
}
void copytotargetbut() {
    ValWindow* wind = WindowMan.fromName("Editor");
    wind->set_editctrl_text("x_coordbox", wind->eval_edit("mousecapbox_x"));
    wind->set_editctrl_text("y_coordbox", wind->eval_edit("mousecapbox_y"));
    wind->set_editctrl_text("w_coordbox", wind->eval_edit("mousecapbox_w"));
    wind->set_editctrl_text("h_coordbox", wind->eval_edit("mousecapbox_h"));
}
void new_control_but() {

    valeditor.add_control2();
}

// simple copy string to clipboard. mostly copied from codeproject.
// move to utils when stable
void strtoclipboard(string code, HWND owner) {
    int lsize = (code.length() + 1);
    char* src = (char*)code.c_str();
    OpenClipboard(owner);
    EmptyClipboard();
    HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, lsize);
    if (hglb == NULL) {
        cout << "strtoclipboard couldn't allocate global\n"; return;
    }
    LPTSTR lptstr = (LPTSTR)GlobalLock(hglb);
    src[lsize - 1] = (char)0;
    memcpy(lptstr, src, lsize - 1);
//    cout << *lptstr << ": lptstr" << endl;
    //lptstr[lsize - 1] = (TCHAR)0;  // this was in tutorial but causes crashes. 
    GlobalUnlock(hglb);
    SetClipboardData(CF_TEXT, hglb);
//    cout << "set data" << endl;
    CloseClipboard();
//    cout << "closed clipboard" << endl;

}
void clip_highlighted() {
    ValWindow* wintarg = valeditor.get_target_window();
    string ret = "";
    for (int i = 0; i < wintarg->controlslen; i++) {
        if (wintarg->controls[i]->do_highlight) {
            ret+="wind->AddControl(\"" + wintarg->controls[i]->export_markup_string(true) + "\");\n" ;
        }

    }
    Write_File("controlcode.txt", ret);
    strtoclipboard( ret,wintarg->myhwnd);

}
void do_clipboard() {
    ValWindow* wind = WindowMan.fromName("Editor");
    string code = wind->eval_edit("codebox");
    cout << "do_clipboard code found: " << code << endl;
    strtoclipboard(code, wind->myhwnd);

}
void do_clipboard2() {
    
    ValWindow* wind = WindowMan.fromName("Editor");
    string code = wind->eval_edit("codebox2");
    cout << "do_clipboard code found: " << code << endl;
    strtoclipboard(code, wind->myhwnd);

}
void do_clipboard3() {
    ValWindow* wind = WindowMan.fromName("Editor");
    string t = valeditor.clip_target_window();
    Write_File("controlcode.txt", t);
    valeditor.status = "wrote controlcode.txt";
    //cout << t << endl;

    strtoclipboard(t,wind->myhwnd);
}

void savewindowbut() {
    string t = valeditor.clip_target_window();
    string fname = WindowMan.fromName("Editor")->eval_edit("filenamebox");
    Write_File(fname, t);
    valeditor.status = "saved file to " + fname;
}
ValControl* lasthighlight = NULL;
void controls_list_onclick() {
    
    
    ValWindow* wind = WindowMan.fromName("Editor");
    string wname = wind->evaluate_listbox("windowslist");
    if (wname == "")return;
    ValWindow* wintarg = WindowMan.fromName(wname);
    string ctrltarg = wind->evaluate_listbox("controlslist");
    ValControl* vc = wintarg->GetControl(ctrltarg);
    if (lasthighlight != NULL && lasthighlight != vc) {
        cout << "removed old highlight" << endl;
        lasthighlight->set_highlight(false);
        lasthighlight->needs_repaint = true;
        lasthighlight->needs_redraw = true;
    }
    lasthighlight = vc;
    if (vc == NULL)return;
    vc->toggle_highlight();
    vc->needs_repaint = true;
    vc->needs_redraw = true;
    target_controllist_but();


}
void update_windowlist_but() {
    int len = WindowMan.windowslen;
    valeditor.windowlist.clear();
    string h;
    for (int i = 0; i < len; i++) {
        h = WindowMan.windows[i]->windowtitle;
        if (h == "Editor")continue;
        valeditor.windowlist.queue(h);
    }
    ValControl* targ = WindowMan.fromName("Editor")->GetControl("windowslist");
    targ->drawtogfx();
    targ->needs_redraw = true;
    update_controllist_but();
}

void update_controllist_but() {
    ValWindow* wind = WindowMan.fromName("Editor");
    string wname = wind->evaluate_listbox("windowslist");

    if (wname == "")return;
    ValWindow* wintarg = WindowMan.fromName(wname);
    ValControl* targ = wind->GetControl("controlslist");
    valeditor.controllist.reset();
    if (wintarg->IS_MOUSE_CAPTURED) {
        wind->GetControl("togglecapturebut")->setlabel("uncapture mouse");
    }
    else wind->GetControl("togglecapturebut")->setlabel("capture mouse");


    int len = wintarg->controlslen;
    for (int i = 0; i < len; i++) {
        //valeditor.controllist.set(wintarg->controls[i]->title);
        valeditor.controllist.stack(wintarg->controls[i]->title);
    }
    //valeditor.controllist.set("Add new");
    //valeditor.controllist.stack("Add new"); // defunct now. use the button.
    targ->drawtogfx();
    targ->needs_redraw = true;
    


}
void process_controllist_but() {
    valeditor.process_control();
    //Sleep(5000);
}
void target_controllist_but() {
    valeditor.target_control();
}