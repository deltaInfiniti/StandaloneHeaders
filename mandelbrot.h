#pragma once
//1.66560284238240

/*special locations:
* 
  Not a precision error (can zoom out a bunch and still have reasonable fidelity
  x -0.00010284300783
  y -0.00028736029438
  w 0.00068637409881
  h 0.00060975689591
  i 1000-3060
  cx 0.54024351087_500-661 
  cy 0.66630033008119
  bail 1
  julia set threexp



*/

void Mandel_render_button(void* a) {
    // new render button for 2022.
    // accept values from listbox's
    //--> What render type to use (mand, wrong, julia)
    //--> accept values for x,y,w,h,cx,cy,itts
    //  --> maybe accept values for colorspace/catagories
    
    /* edit other functions for 2022:
    
       zoom to destination coords loop
       -- needs itts in 'animation'
       -- 
    */

}
void Mandel_copy_x_to_cx() {

}
void Mandel_copy_y_to_cy() {

}
void Mandel_end_renderloop() {

}

ValTextControl Mandel_vtc("Impact", 10, 10, 600, 30, "t");

int mandel_buffer[Mandelbrot_window_dims][Mandelbrot_window_dims];
stringlist G_Mandel_rendertypes;
double G_Mandel_lastx = 0, G_Mandel_lasty = 0, G_Mandel_lastw = 0, G_Mandel_lasth = 0;
double G_Mandel_lastcx = 0, G_Mandel_lastcy = 0, G_Mandel_lastitts = 0, G_Mandel_lastb = 0;
string G_Mandel_lastrend="";
string G_Mandel_gstatus = "", G_Mandel_loopstat = "";
bool G_Mandel_already_rendering = false;
bool G_Mandel_last_wasbuild = false;
bool G_Mandel_color_lastLinearCats = false;
int G_Mandel_color_last_type = 0;
void render_button(void* a) {
    auto militime = chrono_milli();
    G_Mandel_gstatus = "rendering";
    // get parent valwindow from *a
    // get values from edit controls on parent window
    // render manelbrot to copy
    // paste buffer
    // draw buffer to window
    G_VS_RANDSEED(getticks());
    if (G_Mandel_already_rendering) {
        cout << "already rendering, aborting current render\n";
        G_Mandel_threading_halt = true;
        Sleep(1000);
        G_Mandel_threading_halt = false;
        return;
    }
    G_Mandel_already_rendering = true;
    
    //cout << "render" << endl;
    string dataout = "";
    string dataout2 = "";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    string cxcoord = manwind->eval_edit("CxBox");
    string cycoord = manwind->eval_edit("CyBox");
    string itts = manwind->eval_edit("itterations");
    string bailout = manwind->eval_edit("bailoutBox");
    string threadcount = manwind->eval_edit("threadsBox");
    string samples = manwind->eval_edit("bbrot_samplesEdit");
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    manwind->set_editctrl_text("h_coord", hcoord);
    dataout += "x:" + xcoord + "  y:" + ycoord + "  w:" + wcoord + "  h:" + hcoord;
    dataout += "  itt:" + itts;

    //SHOW(xcoord);
    //SHOW(ycoord);
    //SHOW(wcoord);
    //SHOW(hcoord);
    //SHOW(itts);
    //cout <<xcoord <<endl;
    int type = VC_CHECKBOX;
    bool wrong_mand = manwind->evaluate_controlb("do_wrong_mand", type);
    double x = strtodbl(xcoord);
    double y = strtodbl(ycoord);
    double w = strtodbl(wcoord);
    double h = strtodbl(hcoord);
    double it = strtodbl(itts);
    G_Mandel_buddahbrot_samples = ctoint(samples);
    //SHOW(x);
    //SHOW(y);
    //SHOW(w);
    //SHOW(h);
    //SHOW(it);
    double cx = strtodbl(cxcoord);
    double cy = strtodbl(cycoord);
    double bail = strtodbl(bailout);
    int threadscount = ctoint(threadcount);
    int rebuild = 0;
    
    string rendtype = manwind->GetControl("RenderTypeListbox")->sval;
    manwind = WindowMan.fromName("mandelbrot");
//    if (wrong_mand) manwind->mygfx.draw_mandelbrot_tocopy_wrong(x, y, w, h, it);
//    else  manwind->mygfx.draw_mandelbrot_tocopy(x, y, w, h, it);
    string colortypestr = "linear";
    if(G_Mandel_colorizer_type == 1)colortypestr = "steep";
    else if (G_Mandel_colorizer_type == 3)colortypestr = "greyscale";
    dataout += " type: \"" + rendtype + "\" color: " + colortypestr;
    //cout << "rendering " << rendtype << "\n";
    G_Mandel_gstatus = "rendering" +rendtype;
    if (G_Mandel_lastx == x && G_Mandel_lasty == y && G_Mandel_lastw == w && G_Mandel_lasth == h
        && G_Mandel_lastcx == cx && G_Mandel_lastcy == cy && G_Mandel_last_wasbuild && G_Mandel_lastb == bail 
        && rendtype.find("rand")==string::npos) {
        if (G_Mandel_lastitts == it && G_Mandel_lastrend == rendtype && G_Mandel_color_last_type == G_Mandel_colorizer_type) {

            cout << "already rendered these settings, aborting\n";

            G_Mandel_already_rendering = false;
            return;
        }
        else if (G_Mandel_lastitts == it && G_Mandel_lastrend == rendtype) {  
            dataout += "   cx: " + cxcoord + " cy: " + cycoord;
            cout << "re-colorizing\n";
            manwind->mygfx.mandel_buffer_render(mandel_buffer, it);
            //cout << "mand drawn" << endl;
            manwind->mygfx.paste_buf();
            //manwind->mygfx.save_image("mandtest.bmp");
            Mandel_vtc.content = dataout;
            Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
            G_Mandel_color_lastLinearCats=G_Mandel_color_LinearCats ;
            G_Mandel_color_last_type = G_Mandel_colorizer_type;
            manwind->GFXdraw();
            //cout << manwind->evaluate_controlb("do_wrong_mand", type)<< "  type: " ;
            //cout << type << endl;

            G_Mandel_already_rendering = false;
            return;
        }
        if (wrong_mand)rebuild = G_Mandel_lastitts;
        G_Mandel_lastitts = it;
    }
    else {
        G_Mandel_lastx = x;
        G_Mandel_lasty = y;
        G_Mandel_lastw = w;
        G_Mandel_lasth = h;
        G_Mandel_lastcx = cx;
        G_Mandel_lastcy = cy;
        if (wrong_mand)rebuild = G_Mandel_lastitts; 
        G_Mandel_lastitts = it;
        G_Mandel_lastb = bail;
    }
    
    //SHOW(rebuild);
    G_Mandel_lastrend = rendtype;
    G_Mandel_last_wasbuild = false;
     G_Mandel_color_lastLinearCats= G_Mandel_color_LinearCats;
     G_Mandel_color_last_type = G_Mandel_colorizer_type;

     G_mandel_workerthread_info.global_threadlock=threadscount;

     if (rendtype == "ANDRO Newton") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO, mandel_buffer, rebuild, bail, 300); dataout += " bail: " + bailout;
        dataout += " func: " + ANDRO_Equation();
        dataout2 = " roots: " + ANDRO_Roots();
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    if (rendtype == "ANDRO Newton Nova") {
         manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_nova, mandel_buffer, rebuild, bail, 302); dataout += " bail: " + bailout;
         dataout += " func: " + ANDRO_Equation();
         dataout2 = " roots: " + ANDRO_Roots();
         //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
         G_Mandel_last_wasbuild = true;
     }
    if (rendtype == "ANDRO Newton Nova_D") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_nova, mandel_buffer, rebuild, bail, 300); dataout += " bail: " + bailout;
        dataout += " func: " + ANDRO_Equation();
        dataout2 = " roots: " + ANDRO_Roots();
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    if (rendtype == "ANDRO Newton Julia") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_novajulia, mandel_buffer, rebuild, bail, 301); dataout += " bail: " + bailout;
        dataout += " func: " + ANDRO_Equation();
        dataout2 = " roots: " + ANDRO_Roots();
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    if (rendtype == "ANDRO Newton Julia_D") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_novajulia, mandel_buffer, rebuild, bail, 303); dataout += " bail: " + bailout;
        dataout += " func: " + ANDRO_Equation();
        dataout2 = " roots: " + ANDRO_Roots();
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Buddahbrot random") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 400); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
    }
    else if (rendtype == "Buddahbrot random HC") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 401); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
    }
    else if (rendtype == "BBrot random cxcyLim") {
            manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 402); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
        dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
    }
    else if (rendtype == "Julia Set") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Sqrt1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Brot Sqrt1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Sqrt2") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt2, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Brot Sqrt2") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Sqrt3") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt3, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Brot Sqrt3") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Sqrt4") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt4, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Brot Sqrt4") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Sqrt5") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt5, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Brot Sqrt5") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt5, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton trueE3M1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_trueE3M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1_2") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1_2, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1_3") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1_3, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1_4") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton 2E4M1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_2E4M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E13M1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_E13M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1_4b") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4b, mandel_buffer, rebuild, bail, 201); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "threaded newton E3M1_4c") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4c, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newton E3M1_4c") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4c, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newtonWrong z^4-1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e4m1_db, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "newtonWrongCxCy z^4-1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e4m1_db_b, mandel_buffer, rebuild, bail, 201); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong2") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy_wrong2(x, y, w, h, cx, cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong3") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 2); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong4") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy_wrong4(x, y, w, h, cx, cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 2); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong5"|| rendtype == "Julia Set Wrong6") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        //manwind->mygfx.draw_jset_tocopy_wrong5(x, y, w, h, cx, cy, it);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 3); dataout += " bail: " + bailout;
    }
    else if (rendtype == "Julia Set Wrong7") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia3, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.draw_jset_tocopy_wrong7(x, y, w, h, cx, cy, it);
    }
    else if (rendtype == "Julia Set Wrong8") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild,bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong9") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia5, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia5, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong10") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia6, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia6, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Wrong11") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia7, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia7, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Tan") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_tan,mandel_buffer,rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Tanw") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_tanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set SinTanw") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin_tanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin_tanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set CoTanw") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cotanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cotanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Cos") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set Sin") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set SinTan") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin_tan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin_tan, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set CoTan") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cotan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cotan, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set expexp") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp_exp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set threexp") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set threexpLD") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexpLD, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexpLD, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set t_brot2") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail,1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexp);
    }
    else if (rendtype == "Julia Set t_brot1") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia);
    }
    else if (rendtype == "Julia Set t_brot3") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia4);
    }
    else if (rendtype == "Julia Set t_brot4") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tan, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_tan);
    }
    else if (rendtype == "Julia Set t_brot5") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_cos);
    }
    else if (rendtype == "Julia Set t_brot6") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_sin);
    }
    else if (rendtype == "Julia Set t_brot7") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp7);
    }
    else if (rendtype == "Julia Set exp7") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set t_brot8") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;

        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp);
    }
    else if (rendtype == "Julia Set exp8") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set exp9") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Julia Set t_brot9") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;

        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp127);
    }
    else if (rendtype == "VSet Beta") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.draw_Vset_tocopy(x, y, w, h, cx, cy, it);
    }
    else if (rendtype == "MandelJulia Euler") {
        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_julia_Euler, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler2") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler3") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler4") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler5") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler5, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler6") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler6, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler7") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler7, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler8") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler8, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler9") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler9, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler10") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler10, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler11") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler11, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler12") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler12, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot Euler13") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler13, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    G_Mandel_last_wasbuild = true; 
    }
    else if (rendtype == "Mandelbrot derbail") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot derbail2") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot derbail3") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "Mandelbrot derbail4") {
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if(rendtype == "Mandelbrot set") {
    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 1") {
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong);
    }
    else if (rendtype == "MandelWrong 2") {
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong2, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong2);
    }
    else if (rendtype == "MandelWrong 3") {
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong3, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong3);
    }
    else if (rendtype == "MandelWrong 4") {
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong4, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong4);
    }
    else if (rendtype == "MandelWrong 5") {
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong5);

        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong5, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 6") {
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong6);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong6, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 7") {
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong7);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong7, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 8") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong8);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong8, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 9") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong9);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong9, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 10") {
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong10);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong10, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 11") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong11);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong11, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 12") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong12);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong12, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 13") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong13);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong13, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 14") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong14);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong14, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 15") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong15);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong15, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 16") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong16);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong16, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 17") {
        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong17);
        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong17, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
        G_Mandel_last_wasbuild = true;
    }
    else if (rendtype == "MandelWrong 18") {
       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong18);
       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong18, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
       G_Mandel_last_wasbuild = true;
    }
    else {
        cout << "please select a render type\n";
    }

    //  add text to image-
    // include x,y,w,h,maxits,Renderer#,colorizer#
    // for jset include cx,cy
    militime = chrono_milli()-militime;
    cout << "militime: " << militime / 1000 << "." << militime % 1000 << " seconds\n";
    cout << "mand drawn" << endl;
    manwind->mygfx.paste_buf();
    //manwind->mygfx.save_image("mandtest.bmp");
    Mandel_vtc.content = dataout;
    Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
    if (dataout2 != "") {
        Mandel_vtc.content = dataout2;
        Mandel_vtc.y += 35;
        Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
        Mandel_vtc.y -= 35;
    }
    manwind->GFXdraw();
    //cout << manwind->evaluate_controlb("do_wrong_mand", type)<< "  type: " ;
    //cout << type << endl;G_Mandel_gstatus = "rendering";
    G_Mandel_gstatus = "done rendering";
    G_Mandel_already_rendering = false;
}

void zoombutt(void* a) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    string zoomfa = manwind->eval_edit("zoom_factor");
    double x = strtodbl(xcoord);
    double y = strtodbl(ycoord);
    double w = strtodbl(wcoord);
    double h = strtodbl(hcoord);
    double zf = strtodbl(zoomfa);
    double cr = w * zf;
    w -= cr;
    x += cr / 2;
    cr = h * zf;
    h -= cr;
    y += cr / 2;

    //x /= 1.01;
    //y /= 1.01;
    //w /= 1.01;
    //h /= 1.01;

    manwind->set_editctrl_text("x_coord", ctostr(x));
    manwind->set_editctrl_text("y_coord", ctostr(y));
    manwind->set_editctrl_text("h_coord", ctostr(h));
    manwind->set_editctrl_text("w_coord", ctostr(w));
}
void unzoombutt(void* a) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    string zoomfa = manwind->eval_edit("zoom_factor");
    double x = strtodbl(xcoord);
    double y = strtodbl(ycoord);
    double w = strtodbl(wcoord);
    double h = strtodbl(hcoord);
    double zf = strtodbl(zoomfa);
    double cr = w * zf;
    w += cr;
    x -= cr / 2;
    cr = h * zf;
    h += cr;
    y -= cr / 2;

    //x /= 1.01;
    //y /= 1.01;
    //w /= 1.01;
    //h /= 1.01;

    manwind->set_editctrl_text("x_coord", ctostr(x));
    manwind->set_editctrl_text("y_coord", ctostr(y));
    manwind->set_editctrl_text("h_coord", ctostr(h));
    manwind->set_editctrl_text("w_coord", ctostr(w));
}
void JSet_zoombut(void* a) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("CxBox");
    string ycoord = manwind->eval_edit("CyBox");
    string zoomfa = manwind->eval_edit("zoom_factor");
    double x = strtodbl(xcoord);
    double y = strtodbl(ycoord);
    double zf = strtodbl(zoomfa);
    x -= x*zf;
    y -= y*zf;
    
    manwind->set_editctrl_text("CxBox", ctostr(x));
    manwind->set_editctrl_text("CyBox", ctostr(y));

}
void move_mand(int dir) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    double hold, shold;
    double fact = strtodbl(manwind->eval_edit("move_factor"));
    if (dir < 3) {
        hold = strtodbl(manwind->eval_edit("x_coord"));
        shold = strtodbl(manwind->eval_edit("w_coord"));

        if (dir == 1)hold -= shold * fact;
        if (dir == 2)hold += shold * fact;
        manwind->set_editctrl_text("x_coord", ctostr(hold));
    }
    if (dir > 2) {
        hold = strtodbl(manwind->eval_edit("y_coord"));
        shold = strtodbl(manwind->eval_edit("h_coord"));

        if (dir == 3)hold -= shold * fact;
        if (dir == 4)hold += shold * fact;
        manwind->set_editctrl_text("y_coord", ctostr(hold));
    }
}
void leftbutt(void* a) { move_mand(1); }
void rightbutt(void* a) { move_mand(2); }
void upbutt(void* a) { move_mand(3); }
void downbutt(void* a) { move_mand(4); }
void savebutt(void* a) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    WindowMan.fromName("mandelbrot")->mygfx.save_image(manwind->eval_edit("savefilename") + ".bmp");
}

void jpgsavebutt(void* a) {
    G_Mandel_gstatus = "Saving Jpg";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
     
    string bullshitholder = manwind->eval_edit("savefilename") + ".jpg";
    
    gdiSaveHbitmap(WindowMan.fromName("mandelbrot")->mygfx.hbmp, bullshitholder);
    G_Mandel_gstatus = "Done saving Jpg";
    //const TCHAR* temp = bullshitholder.c_str();
    //newImage->Save(, CXIMAGE_FORMAT_JPG);
}

void JsetrenderZoomLoopBut(void* a) {
    
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    ValControl* Vstop = manwind->GetControl("stopRenderLoopCHK");
    int type = VC_CHECKBOX;
    string loopc = manwind->eval_edit("loopscountedit");
    G_Mandel_gstatus = "initiating CxCyZoom loop x"+loopc;
    int top = ctoint(loopc);
    for (int i = 0; i < top; i++) {
        if (manwind->evaluate_controlb("stopRenderLoopCHK", type)) {
            Vstop->clicked(1, 1);
            return;
        }
        JSet_zoombut(NULL);
        render_button(NULL);
        Sleep(30);
        G_Mandel_loopstat= "Loops:"+ctostr(i);
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("h_coord", hcoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    G_Mandel_gstatus = "Loop render complete";
}
void renderZoomLoopBut(void* a) {
    
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    ValControl* Vstop = manwind->GetControl("stopRenderLoopCHK");
    int type = VC_CHECKBOX;
    string loopc = manwind->eval_edit("loopscountedit");
    G_Mandel_gstatus = "initiating zoom loop x" + loopc;
    int top = ctoint(loopc);
    for (int i = 0; i < top; i++) {
        if (manwind->evaluate_controlb("stopRenderLoopCHK", type)) {
            Vstop->clicked(1, 1);
            return;
        }
        zoombutt(NULL);
        render_button(NULL);
        G_Mandel_loopstat = "Loops:" + ctostr(i);
        Sleep(30);
        cout << "render count :" << i << "\n";
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("h_coord", hcoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    G_Mandel_gstatus = "Loop render complete";
}
void renderbbrotLoopBut(void* a) {

    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    
    string rendtype = manwind->GetControl("RenderTypeListbox")->sval;
    if (rendtype.find("rand") == string::npos) {
        G_Mandel_gstatus = "can't bbrot loop unless BBrot type selected";
        return;
    }
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    ValControl* Vstop = manwind->GetControl("stopRenderLoopCHK");
    int type = VC_CHECKBOX;
    string loopc = manwind->eval_edit("loopscountedit");
    G_Mandel_gstatus = "initiating bbrot loop x" + loopc;
    int top = ctoint(loopc);
    for (int i = 0; i < top; i++) {
        if (manwind->evaluate_controlb("stopRenderLoopCHK", type)) {
            Vstop->clicked(1, 1);
            return;
        }
        render_button(NULL);
        G_Mandel_loopstat = "Loops:" + ctostr(i);
        cout << "render count :" << i << "\n";
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("h_coord", hcoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    G_Mandel_gstatus = "Loop render complete";
}
//static bool G_Mandel_color_LinearCats;
void mandel_switch_coloring_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    
    ValControl* ctrl;
    if (G_Mandel_colorizer_type==3) {
        cout << "switched to linear coloring \n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to steep coloring");
        G_Mandel_color_LinearCats = !G_Mandel_color_LinearCats;
        G_Mandel_colorizer_type = 0;
    }
    else if (G_Mandel_colorizer_type == 1) {
        cout << "switched to greyscale coloring \n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to linear coloring");
        G_Mandel_colorizer_type = 3;
    }
    else if(G_Mandel_colorizer_type == 0) {
        G_Mandel_colorizer_type = 1;
        G_Mandel_color_LinearCats = !G_Mandel_color_LinearCats;
        cout << "switched to steep coloring\n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to greyscale coloring");
    }

} 
void mandel_render_julia_set_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");


}
void mandel_render_colorstack() {
    G_Mandel_gstatus = "Rendering Color Stack";
    ValWindow* manwind = WindowMan.fromName("mandelbrot");
    COLORREF col;
    manwind->mygfx.makewhite();
    manwind->GFXdraw();
    for (int i = 0; i < manwind->clientheight; i++) {
        col = manwind->mygfx.get_mand_color(i, manwind->clientheight);
        //cout << col << "\n";
        manwind->mygfx.drawline2(0, i, manwind->clientwidth-1,true,1, col);
        
    }
    double step = 6.0 / 2000.0;
    int plc = 0,plccos,plcsin,plcn, plccos2, plcsin2 ;
    //manwind->mygfx.copy_buf();
    //manwind->mygfx.Get_blank_buffer();
    for (double n = -3.0+step+step; n < 3.0-(step*2); n += step) {
        plc = (n + 3.0) / step;
        plccos = (cos(n) + 3.0) / step;
        plcsin = (sin(n) + 3.0) / step;
        plccos2 = (cos(n+ 3.1415) + 3.0) / step;
        plcsin2 = (sin(n+ 3.1415) + 3.0) / step;

        plcn = ((n*-1) + 3.0) / step;
        //cout << plc << " " << plccos << " " << plcsin << " " << plcn << "\n";
        
        manwind->mygfx.editpixel(plc, plc, 0);
        manwind->mygfx.editpixel(plc+1, plc, 0);
        //
        manwind->mygfx.editpixel(1000, plc, 0);
        manwind->mygfx.editpixel(1001, plc, 0);
        manwind->mygfx.editpixel(999, plc, 0);
        //
        manwind->mygfx.editpixel(plc, 999, 0);
        manwind->mygfx.editpixel(plc, 1000,  0);
        manwind->mygfx.editpixel(plc, 1001, 0);
        //
        manwind->mygfx.editpixel(plc, plcn, 0);
        manwind->mygfx.editpixel(plc+1, plcn, 0);
        //
        if (plcsin > 0 && plcsin < 2000) {
            manwind->mygfx.editpixel(plc, plcsin, 0);
            manwind->mygfx.editpixel(plc+1, plcsin, 0);
        }
        //
        if (plccos > 0 && plccos < 1999) {
            manwind->mygfx.editpixel(plccos, plc, 0);
            manwind->mygfx.editpixel(plccos+1, plc, 0);
        }
        if (plcsin2 > 0 && plcsin2 < 1999) {
            manwind->mygfx.editpixel(plc, plcsin2, 0);
            manwind->mygfx.editpixel(plc+1, plcsin2, 0);
        }
        //
        if (plccos2 > 0 && plccos2 < 1999) {
            manwind->mygfx.editpixel(plccos2, plc, 0);
            manwind->mygfx.editpixel(plccos2+1, plc, 0);
        }
        if (plcsin > 0 && plcsin < 1999 && plccos > 0 && plccos < 1999) {
            manwind->mygfx.editpixel(plccos, plcsin, 0);
            manwind->mygfx.editpixel(plccos+1, plcsin, 0);
        }
        //if (plcsin > 0 && plcsin < 1000 && plccos > 0 && plccos < 1000) manwind->mygfx.editpixel(2*plccos, 2*plcsin, 0);

    }

    //manwind->mygfx.paste_buf();
    manwind->GFXdraw();

}
void mandel_rerender() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot");
    if (G_Mandel_already_rendering) {
        cout << "already rendering\n";
        return;
    }
    G_Mandel_already_rendering = true;

}
bool G_Mandel_Mousedown = false;
int G_Mandel_mousecap_ldown_x = -1, G_Mandel_mousecap_ldown_y = -1;
int G_Mandel_mousecap_ldown_xx = -1, G_Mandel_mousecap_ldown_yy = -1;
int G_Mandel_mousecap_downcount = 0;

void Mandel_copydims_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("capx_coordbox");
    string ycoord = manwind->eval_edit("capy_coordbox");
    string wcoord = manwind->eval_edit("capw_coordbox");
    string hcoord = manwind->eval_edit("caph_coordbox");
    if (xcoord == "" || ycoord == "" || wcoord == "" || hcoord == "") {
        G_Mandel_gstatus = "Can't Copy blanks";
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    manwind->set_editctrl_text("h_coord", hcoord);

}
void Mandel_copydimsother_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("copyx_coordbox");
    string ycoord = manwind->eval_edit("copyy_coordbox");
    string wcoord = manwind->eval_edit("copyw_coordbox");
    string hcoord = manwind->eval_edit("copyh_coordbox");
    if (xcoord == "" || ycoord == "" || wcoord == "" || hcoord == "") {
        G_Mandel_gstatus = "Can't Copy blanks";
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    manwind->set_editctrl_text("h_coord", hcoord);

}
void Mandel_mousecapture_process(void* vwind) {

    string type;
    ValWindow* wind = (ValWindow*)vwind;
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    int x = wind->mouse_cap->x;
    int y = wind->mouse_cap->y;

    if (wind->mouse_cap->type == VW_MOUSECAP_CLICK) {
        G_Mandel_Mousedown = false;

        string xcoord = manwind->eval_edit("x_coord");
        string ycoord = manwind->eval_edit("y_coord");
        string wcoord = manwind->eval_edit("w_coord");
        string hcoord = manwind->eval_edit("h_coord");
        double xxx = strtodbl(xcoord);
        double yyy = strtodbl(ycoord);
        double w = strtodbl(wcoord);
        double h = strtodbl(hcoord);
        double x_jump = w / (double)wind->clientwidth;
        double y_jump = h / (double)wind->clientheight;

        
        box_dims_highlow(G_Mandel_mousecap_ldown_x, G_Mandel_mousecap_ldown_y, x, y);
        manwind->set_editctrl_text("capx_coordbox", ctostr(xxx + (G_Mandel_mousecap_ldown_x * x_jump)));
        manwind->set_editctrl_text("capy_coordbox", ctostr(yyy + (G_Mandel_mousecap_ldown_y * y_jump)));
        
        manwind->set_editctrl_text("capw_coordbox", ctostr((vabs(x-G_Mandel_mousecap_ldown_x ) * x_jump)));
        manwind->set_editctrl_text("caph_coordbox", ctostr((vabs(y-G_Mandel_mousecap_ldown_y ) * y_jump)));

    }

    switch (wind->mouse_cap->type) {
    case VW_MOUSECAP_MOVE:
        //if (G_Mandel_Mousedown) {
            // draw square from ldown point.
        //}
        return;
        break;
    case VW_MOUSECAP_RCLICK:
        
        break;
    case VW_MOUSECAP_LDOWN:
        G_Mandel_Mousedown = true;
        G_Mandel_mousecap_downcount++;
        if (G_Mandel_mousecap_downcount == 1) {
            G_Mandel_mousecap_ldown_x = x;
            G_Mandel_mousecap_ldown_y = y;
            return;
        }
        if (G_Mandel_mousecap_downcount > 4) {
            if (x<0 || x>wind->clientwidth-5 || y<0 || y>=wind->clientheight-5)return;
            wind->mygfxforg.makecolor(VRGB_BLACK);
            wind->mygfxforg.draw_box2(G_Mandel_mousecap_ldown_x, G_Mandel_mousecap_ldown_y, x, y, 3, 0, VRGB_WHITE);
            wind->GFXdraw();
            wind->mygfxforg.transblt(GetDC(wind->myhwnd), 0, 0);
            
            //wind->full_render = true;
        }
        //process square into dims boxes
        return;
        break;
    };
    G_Mandel_mousecap_downcount = 0;

}

void Mandel_progress_callback(int i) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    auto slid = manwind->GetControl("progressSlider");
    slid->sval = ctostr(i);
    slid->drawtogfx();
    slid->needs_redraw = true;
}

string G_Mandel_ANDRO_FactorStr = "None Set";
void Mandel_alterfactor_proc(int xf,int xe, bool neg) {
    /*static int G_Mandel_ANDRO_factorslist[300]; // initialize to zero
static int G_Mandel_ANDRO_factorslistlen = 0;
static double G_Mandel_ANDRO_rootslist[1000]; // holds roots associated with factorslist for newton fractal calculation
static int G_Mandel_ANDRO_rootslistlen = 0;*/
    
    ANDRO_factorlist_alter(xf, xe, neg, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
void Mandel_addfactor_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string qs = manwind->eval_edit("ANDRO_fact_qbox");
    string ps = manwind->eval_edit("ANDRO_fact_pbox");
    int q = ctoint(qs);
    int p = ctoint(ps);
    cout << "factor add but pressed, q,p: " << q << "," << p << "\n";
    ANDRO_factorlist_alter(q,p,false, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
    G_Mandel_ANDRO_FactorStr =ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
void Mandel_subfactor_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string qs = manwind->eval_edit("ANDRO_fact_qbox");
    string ps = manwind->eval_edit("ANDRO_fact_pbox");
    int q = ctoint(qs);
    int p = ctoint(ps);

    ANDRO_factorlist_alter( q,p, true, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
    G_Mandel_ANDRO_FactorStr = ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
void Mandel_remExp_but() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string ps = manwind->eval_edit("ANDRO_fact_pbox");
    int p = ctoint(ps);
    ANDRO_factors_removeExp(p, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
    G_Mandel_ANDRO_FactorStr = ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
void Mandel_fact_clrbut() {
    G_Mandel_ANDRO_factorslistlen = 0;
    G_Mandel_ANDRO_rootslistlen = 0;
}
mouse_capture_struct Mandel_mousecap;

void do_mandelbrot_thread(void* a) {
    foreach(i, 16) {
        _beginthread(Mandel_workerthread, 0, NULL);
    }
    foreach(i, 2000) {
        foreach(n, 2000) mandel_buffer[i][n] = 0;
    }
    G_VS_RANDSEED(getticks());
    G_Mandel_rendertypes.stack("Mandelbrot set"); 
    G_Mandel_rendertypes.stack("Julia Sqrt1");
    G_Mandel_rendertypes.stack("Brot Sqrt1");
    G_Mandel_rendertypes.stack("Julia Sqrt2");
    G_Mandel_rendertypes.stack("Brot Sqrt2");
    G_Mandel_rendertypes.stack("Julia Sqrt3");
    G_Mandel_rendertypes.stack("Brot Sqrt3");
    G_Mandel_rendertypes.stack("Julia Sqrt4");
    G_Mandel_rendertypes.stack("Brot Sqrt4");
    G_Mandel_rendertypes.stack("Julia Sqrt5");
    G_Mandel_rendertypes.stack("Brot Sqrt5");
    G_Mandel_rendertypes.stack("Buddahbrot random");
    G_Mandel_rendertypes.stack("Buddahbrot random HC");
    G_Mandel_rendertypes.stack("BBrot random cxcyLim");
    G_Mandel_rendertypes.stack("Mandelbrot derbail");
    G_Mandel_rendertypes.stack("Mandelbrot derbail2");
    G_Mandel_rendertypes.stack("Mandelbrot derbail3");
    G_Mandel_rendertypes.stack("Mandelbrot derbail4");
    G_Mandel_rendertypes.stack("Mandelbrot Euler"); 
    G_Mandel_rendertypes.stack("MandelJulia Euler");
    G_Mandel_rendertypes.stack("Mandelbrot Euler2");
    G_Mandel_rendertypes.stack("Mandelbrot Euler3");
    G_Mandel_rendertypes.stack("Mandelbrot Euler4");
    G_Mandel_rendertypes.stack("Mandelbrot Euler5");
    G_Mandel_rendertypes.stack("Mandelbrot Euler6");
    G_Mandel_rendertypes.stack("Mandelbrot Euler7");
    G_Mandel_rendertypes.stack("Mandelbrot Euler8");
    G_Mandel_rendertypes.stack("Mandelbrot Euler9");
    G_Mandel_rendertypes.stack("Mandelbrot Euler10");
    G_Mandel_rendertypes.stack("Mandelbrot Euler11");
    G_Mandel_rendertypes.stack("Mandelbrot Euler12");
    G_Mandel_rendertypes.stack("Mandelbrot Euler13");
    G_Mandel_rendertypes.stack("ANDRO Newton");
    G_Mandel_rendertypes.stack("ANDRO Newton Nova");
    G_Mandel_rendertypes.stack("ANDRO Newton Julia");
    G_Mandel_rendertypes.stack("ANDRO Newton Nova_D");
    G_Mandel_rendertypes.stack("ANDRO Newton Julia_D");
    G_Mandel_rendertypes.stack("newton E3M1");
    G_Mandel_rendertypes.stack("newton trueE3M1");
    G_Mandel_rendertypes.stack("newton E3M1_2");
    G_Mandel_rendertypes.stack("newton E3M1_3");
    G_Mandel_rendertypes.stack("newton E3M1_4");
    G_Mandel_rendertypes.stack("newton 2E4M1");
    G_Mandel_rendertypes.stack("newton E13M1"); 
    G_Mandel_rendertypes.stack("threaded newton E3M1_4c");
    G_Mandel_rendertypes.stack("newton E3M1_4c");
    G_Mandel_rendertypes.stack("newton E3M1_4b");
    G_Mandel_rendertypes.stack("Julia Set threexp");
    G_Mandel_rendertypes.stack("Julia Set threexpLD");
    G_Mandel_rendertypes.stack("newtonWrong z^4-1");
    G_Mandel_rendertypes.stack("newtonWrongCxCy z^4-1");
    //G_Mandel_rendertypes.stack("VSet Beta");
    G_Mandel_rendertypes.stack("Julia Set Wrong");
    G_Mandel_rendertypes.stack("MandelWrong 1");
    G_Mandel_rendertypes.stack("MandelWrong 2");
    G_Mandel_rendertypes.stack("MandelWrong 3");
    G_Mandel_rendertypes.stack("MandelWrong 4");
    G_Mandel_rendertypes.stack("MandelWrong 5");
    G_Mandel_rendertypes.stack("MandelWrong 6");
    G_Mandel_rendertypes.stack("MandelWrong 7");
    G_Mandel_rendertypes.stack("MandelWrong 8");
    G_Mandel_rendertypes.stack("MandelWrong 9");
    G_Mandel_rendertypes.stack("MandelWrong 10");
    G_Mandel_rendertypes.stack("MandelWrong 11");
    G_Mandel_rendertypes.stack("MandelWrong 12");
    G_Mandel_rendertypes.stack("MandelWrong 13");
    G_Mandel_rendertypes.stack("MandelWrong 14");
    G_Mandel_rendertypes.stack("MandelWrong 15");
    G_Mandel_rendertypes.stack("MandelWrong 16");
    G_Mandel_rendertypes.stack("MandelWrong 17");
    G_Mandel_rendertypes.stack("MandelWrong 18");
    G_Mandel_rendertypes.stack("Julia Set"); 

    G_Mandel_rendertypes.stack("Julia Set t_brot1");
    G_Mandel_rendertypes.stack("Julia Set t_brot2");
    G_Mandel_rendertypes.stack("Julia Set t_brot3");
    G_Mandel_rendertypes.stack("Julia Set t_brot4");
    G_Mandel_rendertypes.stack("Julia Set t_brot5");
    G_Mandel_rendertypes.stack("Julia Set t_brot6");
    G_Mandel_rendertypes.stack("Julia Set t_brot7");
    G_Mandel_rendertypes.stack("Julia Set t_brot8");
    G_Mandel_rendertypes.stack("Julia Set t_brot9");
    G_Mandel_rendertypes.stack("Julia Set exp7");
    G_Mandel_rendertypes.stack("Julia Set exp8");
    G_Mandel_rendertypes.stack("Julia Set exp9");

    G_Mandel_rendertypes.stack("Julia Set Tanw");
    G_Mandel_rendertypes.stack("Julia Set CoTanw");
    G_Mandel_rendertypes.stack("Julia Set SinTanw");

    G_Mandel_rendertypes.stack("Julia Set Tan");
    G_Mandel_rendertypes.stack("Julia Set CoTan");
    G_Mandel_rendertypes.stack("Julia Set Cos");
    G_Mandel_rendertypes.stack("Julia Set Sin");
    G_Mandel_rendertypes.stack("Julia Set expexp");
    G_Mandel_rendertypes.stack("Julia Set SinTan");
    
    G_Mandel_rendertypes.stack("Julia Set Wrong2");
    G_Mandel_rendertypes.stack("Julia Set Wrong3");
    G_Mandel_rendertypes.stack("Julia Set Wrong3b");

    G_Mandel_rendertypes.stack("Julia Set Wrong4");
    G_Mandel_rendertypes.stack("Julia Set Wrong5");
    G_Mandel_rendertypes.stack("Julia Set Wrong6");
    G_Mandel_rendertypes.stack("Julia Set Wrong7");
    G_Mandel_rendertypes.stack("Julia Set Wrong8");
    G_Mandel_rendertypes.stack("Julia Set Wrong9");
    G_Mandel_rendertypes.stack("Julia Set Wrong10");
    G_Mandel_rendertypes.stack("Julia Set Wrong11"); 
    
    /*wrong test coords for examples:
    fractal edge- stars -.6 -> -.609 : -.5559  : .02 : .035
    in the crack (switch x/y/wrong) .2501 -.000022 .0000875 .00004575



    */
    // creaet window
    // add controls to window- x,y,w,h,itts
    // add wrong render checkbox
    // add render button
    // add status functionality

    //ValWindow* vw = WindowMan.create_new_windowex("mandelbrot", 100, 100, 1000, 1000, 1);
    ValWindow* vw = WindowMan.create_new_windowts("mandelbrot", 0, 0, 2000, 2000, 1);
    int controllerw = 1000, controllerh = 1000;
    //ValWindow* vwc = WindowMan.create_new_windowex("mandelbrot controller", 100, 800, controllerw,controllerh,1);
    ValWindow* vwc = WindowMan.create_new_windowts("mandelbrot controller", 100, 800, controllerw, controllerh, 1);
    string xcord = "-3";// "-0.5892348415";
    string ycord = "-3";//"-0.570152343242";
    string wcord = "6";//"0.0200000065456001";
    string hcord = "6";//"0.0350000545600000001";
    string itts = "512";
    // this comment block is the original controller interface set from 2019 from before the window editor was live
    //   2022: my, have we come a long way.
    //vwc->add_control_ex_ts(VC_BUTTON, "render_button", "Render", VRECT{ 25,225,100,40 }, (void*)&render_button, true);
    //vwc->add_control_ex_ts(VC_BUTTON, "zoom_button", "zoom", VRECT{ 25,275,100,40 }, (void*)&zoombutt, true);
    //vwc->add_editctrl_ts("zoom_factor", VRECT{ 60,330,80,25 }, ".05");
    //vwc->add_control_ex_ts(VC_LABEL, "zoom_label", "zoom %: ", VRECT{ 5,330,50,25 }, VC_NOFUNC, false);
    //vwc->add_editctrl_ts("move_factor", VRECT{ 220,330,80,25 }, ".05");

    //vwc->add_control_ex_ts(VC_LABEL, "move_label", "move %: ", VRECT{ 150,330,60,25 }, VC_NOFUNC, false);

    //vwc->add_control_ex_ts(VC_BUTTON, "left_button", "left", VRECT{ 170,255,35,25 }, (void*)&leftbutt, true);
    //vwc->add_control_ex_ts(VC_BUTTON, "right_button", "right", VRECT{ 260,255,35,25 }, (void*)&rightbutt, true);
    //vwc->add_control_ex_ts(VC_BUTTON, "up_button", "up", VRECT{ 215,230,35,25 }, (void*)&upbutt, true);
    //vwc->add_control_ex_ts(VC_BUTTON, "down_button", "down", VRECT{ 215,280,35,25 }, (void*)&downbutt, true);

    //vwc->add_editctrl_ts("x_coord", VRECT{ 70,20,200,25 }, xcord);
    //vwc->add_control_ex_ts(VC_LABEL, "xcordlabel", "X: ", VRECT{ 5,20,50,25 }, VC_NOFUNC, false);
    //vwc->add_editctrl_ts("y_coord", VRECT{ 70,50,200,25 }, ycord);
    //vwc->add_control_ex_ts(VC_LABEL, "ycordlabel", "y: ", VRECT{ 20,50,50,25 }, VC_NOFUNC, false);
    //vwc->add_editctrl_ts("w_coord", VRECT{ 70,80,200,25 }, wcord);
    //vwc->add_control_ex_ts(VC_LABEL, "wcordlabel", "Width: ", VRECT{ 5,80,50,25 }, VC_NOFUNC, false);
    //vwc->add_editctrl_ts("h_coord", VRECT{ 70,110,200,25 }, hcord);
    //vwc->add_control_ex_ts(VC_LABEL, "hcordlabel", "Height: ", VRECT{ 5,110,50,25 }, VC_NOFUNC, false);
    //vwc->add_editctrl_ts("itterations", VRECT{ 70,140,200,25 }, itts);
    //vwc->add_control_ex_ts(VC_LABEL, "itts_label", "itterations: ", VRECT{ 5,140,50,25 }, VC_NOFUNC, false);

    //vwc->add_editctrl_ts("savefilename", VRECT{ 370,50,100,25 }, "mand");
    //vwc->add_control_ex_ts(VC_LABEL, "savelabel", ".bmp", VRECT{ 470,50,50,25 }, VC_NOFUNC, false);
    //vwc->add_control_ex_ts(VC_LABEL, "savelabel", "save file: ", VRECT{ 310,50,50,25 }, VC_NOFUNC, false);
    //vwc->add_control_ex_ts(VC_BUTTON, "save_button", "save", VRECT{ 320,80,60,25 }, (void*)&savebutt, true);
    //vwc->add_control_ex_ts(VC_CHECKBOX, "do_wrong_mand", "use wrong addition", VRECT{ 5,180,150,25 }, VC_NOFUNC, false);

    ValWindow* wind = vwc;
    VWM_register_datan(render_button, "render_button");
    VWM_register_datan(zoombutt, "zoombutt");
    VWM_register_datan(unzoombutt, "unzoombutt");
    VWM_register_datan(leftbutt, "leftbutt");
    VWM_register_datan(rightbutt, "rightbutt");

    VWM_register_datan(upbutt, "upbutt");
    VWM_register_datan(downbutt, "downbutt");

    VWM_register_datan(savebutt, "savebutt");
    VWM_register_datan(renderZoomLoopBut, "RenderZoomLoopBut");
    VWM_register_datan(mandel_switch_coloring_but, "switchcolorsbut");
    VWM_register_datan(&G_Mandel_rendertypes, "MandelRendersList");
    VWM_register_datan(mandel_render_colorstack, "colorstackbut");
    VWM_register_datan(JSet_zoombut, "JSet_zoombut");
    VWM_register_datan(JsetrenderZoomLoopBut, "JsetrenderZoomLoopBut");
    VWM_register_datan(jpgsavebutt, "jpgsavebutt");
    VWM_register_datan(&G_Mandel_gstatus,"G_Mandel_gstatus");
    VWM_register_datan(&G_Mandel_loopstat,"G_Mandel_loopstat"); 
    VWM_register_datan(&G_Mandel_threadstat, "G_Mandel_threadstat"); 
    VWM_register_datan(&G_Mandel_ANDRO_FactorStr, "G_Mandel_ANDRO_FactorStr");
    VWM_register_datan(Mandel_copydims_but, "Mandel_copydims_but");
    VWM_register_datan(Mandel_copydimsother_but, "Mandel_copydimsother_but");
    VWM_register_datan(Mandel_subfactor_but, "Mandel_subfactor_but");
    VWM_register_datan(Mandel_addfactor_but, "Mandel_addfactor_but");
    VWM_register_datan(Mandel_remExp_but, "Mandel_remExp_but"); 
    VWM_register_datan(Mandel_fact_clrbut, "Mandel_fact_clrbut"); 
    VWM_register_datan(renderbbrotLoopBut, "renderbbrotLoopBut");

    //VWM_register_datan();
    string G_Mandel_gstatus = "", G_Mandel_loopstat = "";

 /*   wind->AddControl("title=zoom_button,type=VC_BUTTON,text=+zoom,x=371,y=396,w=60,h=40,dataname=zoombutt,needsparent=true");
    wind->AddControl("title=zoom_factor,type=VC_EDIT,text=.05,x=426,y=450,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=zoom_label,type=VC_LABEL,text=zoom %: ,x=371,y=450,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=move_factor,type=VC_EDIT,text=.05,x=383,y=108,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=move_label,type=VC_LABEL,text=move %: ,x=313,y=108,w=60,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=left_button,type=VC_BUTTON,text=left,x=333,y=43,w=35,h=25,dataname=leftbutt,needsparent=true");
    wind->AddControl("title=right_button,type=VC_BUTTON,text=right,x=423,y=43,w=35,h=25,dataname=rightbutt,needsparent=true");
    wind->AddControl("title=up_button,type=VC_BUTTON,text=up,x=378,y=18,w=35,h=25,dataname=upbutt,needsparent=true");
    wind->AddControl("title=down_button,type=VC_BUTTON,text=down,x=378,y=68,w=35,h=25,dataname=downbutt,needsparent=true");
    wind->AddControl("title=x_coord,type=VC_EDIT,text=-3,x=90,y=30,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=xcordlabel,type=VC_LABEL,text=X: ,x=38,y=30,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=y_coord,type=VC_EDIT,text=-3,x=90,y=60,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ycordlabel,type=VC_LABEL,text=y: ,x=40,y=60,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=w_coord,type=VC_EDIT,text=6,x=90,y=90,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=wcordlabel,type=VC_LABEL,text=Width: ,x=25,y=90,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=h_coord,type=VC_EDIT,text=6,x=90,y=120,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=hcordlabel,type=VC_LABEL,text=Height: ,x=25,y=120,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=itterations,type=VC_EDIT,text=512,x=90,y=150,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=itts_label,type=VC_LABEL,text=itterations: ,x=25,y=150,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=savefilename,type=VC_EDIT,text=Mandelbrot,x=430,y=720,w=300,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=savelabel2,type=VC_LABEL,text=,x=740,y=705,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=savelabel,type=VC_LABEL,text=save file: ,x=340,y=720,w=80,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=save_button,type=VC_BUTTON,text=bmp save,x=432,y=750,w=70,h=25,dataname=savebutt,needsparent=true");
    wind->AddControl("title=stopRenderLoopCHK,type=VC_CHECKBOX,text=Stop Render Loop,x=354,y=321,w=175,h=30");
    wind->AddControl("title=RenderLoopbut,type=VC_BUTTON,text=testColorizer,x=676,y=754,w=107,h=32,dataname=colorstackbut");
    wind->AddControl("title=RenderZoomLoopbut,type=VC_BUTTON,text=Render/Zoom Loop,x=354,y=358,w=175,h=31,dataname=RenderZoomLoopBut");
    wind->AddControl("title=ColoringTypeBut,type=VC_BUTTON,text=switch to steep coloring,x=29,y=190,w=259,h=24,dataname=switchcolorsbut");
    wind->AddControl("title=CXLabel,type=VC_LABEL,text=JSet Cx,x=509,y=30,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=CyLabel,type=VC_LABEL,text=JSet Cy,x=510,y=60,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=CxBox,type=VC_EDIT,text=.3,x=576,y=31,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=CyBox,type=VC_EDIT,text=.37,x=576,y=61,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=UnZoomBut,type=VC_BUTTON,text=-zoom,x=449,y=396,w=60,h=40,dataname=unzoombutt");
    wind->AddControl("title=JSet_zoombut,type=VC_BUTTON,text=JSet 'zoom',x=359,y=485,w=169,h=29,dataname=JSet_zoombut,textfont=CONSOLAS");
    wind->AddControl("title=jset_zloopbut,type=VC_BUTTON,text=JSet 'zoomloop',x=359,y=518,w=169,h=29,dataname=JsetrenderZoomLoopBut");
    wind->AddControl("title=JpgSaveBut,type=VC_BUTTON,text=Jpg Save,x=515,y=751,w=70,h=23,dataname=jpgsavebutt");
    wind->AddControl("title=bailoutLabel,type=VC_LABEL,text=Bailout:,x=509,y=90,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=bailoutBox,type=VC_EDIT,text=4,x=576,y=91,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=status_stat,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=10,y=-20,w=400,h=18,dataname=G_Mandel_gstatus");
    wind->AddControl("title=Loop_stat,type=VC_GLOBAL_STAT_STRING,text=Loop status:*S,x=10,y=-40,w=400,h=18,dataname=G_Mandel_loopstat");
    wind->AddControl("title=capx_coordbox,type=VC_EDIT,text=,x=328,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=capy_coordbox,type=VC_EDIT,text=,x=328,y=190,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=capw_coordbox,type=VC_EDIT,text=,x=328,y=210,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=caph_coordbox,type=VC_EDIT,text=,x=328,y=230,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=CopyDimsBut,type=VC_BUTTON,text=Copy Dims ,x=322,y=261,w=170,h=28,dataname=Mandel_copydims_but");
    wind->AddControl("title=mousecap_label,type=VC_LABEL,text=Highlighted section:,x=325,y=144,w=237,h=19,numblurs=1,transparent=true");
    wind->AddControl("title=DimsCopyotherBut,type=VC_BUTTON,text=<--Copy Dims ,x=575,y=262,w=170,h=25,dataname=Mandel_copydimsother_but");
    wind->AddControl("title=copyx_coordbox,type=VC_EDIT,text=-3,x=575,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyy_coordbox,type=VC_EDIT,text=-3,x=575,y=190,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyw_coordbox,type=VC_EDIT,text=6,x=575,y=210,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyh_coordbox,type=VC_EDIT,text=6,x=575,y=230,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=render_button,type=VC_BUTTON,text=Render,x=205,y=265,w=100,h=415,dataname=render_button,needsparent=true");
    wind->AddControl("title=threadsLabel,type=VC_LABEL,text=Threads:,x=200,y=683,w=70,h=19,numblurs=1,transparent=true");
    wind->AddControl("title=threadsBox,type=VC_EDIT,text=10,x=275,y=683,w=36,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=Thread_stat,type=VC_GLOBAL_STAT_STRING,text=Thread status:*S,x=10,y=-60,w=400,h=18,dataname=G_Mandel_threadstat");
    wind->AddControl("title=RenderTypeListbox,type=VC_LISTBOX,text=nt,x=21,y=244,w=171,h=450,listboxfunc=NOFUNC,dataname=MandelRendersList,numblurs=0");
    wind->AddControl("title=rendertypeslabel,type=VC_LABEL,text=Render Types:,x=20,y=213,w=168,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=do_wrong_mand,type=VC_CHECKBOX,text=over black only If Pos,x=21,y=704,w=250,h=25");
    wind->AddControl("title=ANDRO_SStat,type=VC_LABEL,text=Arbitrary Newton Function:,x=333,y=576,w=444,h=26,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_fact_qbox,type=VC_EDIT,text=1,x=420,y=624,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ANDRO_fact_pbox,type=VC_EDIT,text=4,x=420,y=654,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ANDRO_fact_plusbut,type=VC_BUTTON,text=add,x=329,y=685,w=80,h=18,dataname=Mandel_addfactor_but");
    wind->AddControl("title=ANDRO_fact_minbut,type=VC_BUTTON,text=sub,x=420,y=685,w=80,h=18,dataname=Mandel_subfactor_but");
    wind->AddControl("title=ANDRO_fact_rembut,type=VC_BUTTON,text=rem,x=510,y=685,w=80,h=18,dataname=Mandel_remExp_but");
    wind->AddControl("title=ANDRO_Q_label,type=VC_LABEL,text=qz^p    q:,x=316,y=624,w=89,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_P_label,type=VC_LABEL,text=         P:,x=316,y=650,w=89,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_fact_clrbut,type=VC_BUTTON,text=clear,x=600,y=685,w=80,h=18,dataname=Mandel_fact_clrbut");
    wind->AddControl("title=ANDRO_stat,type=VC_GLOBAL_STAT_STRING,text=function:*S,x=317,y=601,w=469,h=18,dataname=G_Mandel_ANDRO_FactorStr");
    wind->AddControl("title=loopscountlabel,type=VC_LABEL,text=loops:,x=360,y=551,w=62,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=loopscountedit,type=VC_EDIT,text=100,x=431,y=551,w=91,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=bbrot_samplesLabel,type=VC_LABEL,text=Buddahbrot Samples per thread,x=544,y=120,w=240,h=20,numblurs=1,transparent=true");
    wind->AddControl("title=bbrot_samplesEdit,type=VC_EDIT,text=500,x=544,y=144,w=240,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=progressSlider,type=VC_SLIDER,text=Progress:0,x=11,y=882,w=979,h=39,numblurs=0,textfont=Modern,nointeract=true");*/
    wind->AddControl("title=zoom_button,type=VC_BUTTON,text=+zoom,x=371,y=396,w=60,h=40,dataname=zoombutt,needsparent=true");
    wind->AddControl("title=zoom_factor,type=VC_EDIT,text=.05,x=426,y=450,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=zoom_label,type=VC_LABEL,text=zoom %: ,x=371,y=450,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=move_factor,type=VC_EDIT,text=.05,x=383,y=108,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=move_label,type=VC_LABEL,text=move %: ,x=313,y=108,w=60,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=left_button,type=VC_BUTTON,text=left,x=333,y=43,w=35,h=25,dataname=leftbutt,needsparent=true");
    wind->AddControl("title=right_button,type=VC_BUTTON,text=right,x=423,y=43,w=35,h=25,dataname=rightbutt,needsparent=true");
    wind->AddControl("title=up_button,type=VC_BUTTON,text=up,x=378,y=18,w=35,h=25,dataname=upbutt,needsparent=true");
    wind->AddControl("title=down_button,type=VC_BUTTON,text=down,x=378,y=68,w=35,h=25,dataname=downbutt,needsparent=true");
    wind->AddControl("title=x_coord,type=VC_EDIT,text=-3,x=90,y=30,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=xcordlabel,type=VC_LABEL,text=X: ,x=38,y=30,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=y_coord,type=VC_EDIT,text=-3,x=90,y=60,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ycordlabel,type=VC_LABEL,text=y: ,x=40,y=60,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=w_coord,type=VC_EDIT,text=6,x=90,y=90,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=wcordlabel,type=VC_LABEL,text=Width: ,x=25,y=90,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=h_coord,type=VC_EDIT,text=6,x=90,y=120,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=hcordlabel,type=VC_LABEL,text=Height: ,x=25,y=120,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=itterations,type=VC_EDIT,text=512,x=90,y=150,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=itts_label,type=VC_LABEL,text=itterations: ,x=25,y=150,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=savefilename,type=VC_EDIT,text=Mandelbrot,x=610,y=930,w=300,h=25,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=savelabel2,type=VC_LABEL,text=,x=740,y=705,w=50,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=savelabel,type=VC_LABEL,text=save file: ,x=520,y=930,w=80,h=25,numblurs=1,transparent=true");
    wind->AddControl("title=save_button,type=VC_BUTTON,text=bmp save,x=612,y=960,w=70,h=25,dataname=savebutt,needsparent=true");
    wind->AddControl("title=stopRenderLoopCHK,type=VC_CHECKBOX,text=Stop Render Loop,x=354,y=321,w=175,h=30");
    wind->AddControl("title=RenderLoopbut,type=VC_BUTTON,text=testColorizer,x=856,y=964,w=107,h=32,dataname=colorstackbut");
    wind->AddControl("title=RenderZoomLoopbut,type=VC_BUTTON,text=Render/Zoom Loop,x=354,y=358,w=175,h=31,dataname=RenderZoomLoopBut");
    wind->AddControl("title=ColoringTypeBut,type=VC_BUTTON,text=switch to linear coloring,x=29,y=190,w=259,h=24,dataname=switchcolorsbut");
    wind->AddControl("title=CXLabel,type=VC_LABEL,text=JSet Cx,x=509,y=30,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=CyLabel,type=VC_LABEL,text=JSet Cy,x=510,y=60,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=CxBox,type=VC_EDIT,text=.3,x=576,y=31,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=CyBox,type=VC_EDIT,text=.37,x=576,y=61,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=UnZoomBut,type=VC_BUTTON,text=-zoom,x=449,y=396,w=60,h=40,dataname=unzoombutt");
    wind->AddControl("title=JSet_zoombut,type=VC_BUTTON,text=JSet 'zoom',x=359,y=485,w=169,h=29,dataname=JSet_zoombut,textfont=CONSOLAS");
    wind->AddControl("title=jset_zloopbut,type=VC_BUTTON,text=JSet 'zoomloop',x=359,y=518,w=169,h=29,dataname=JsetrenderZoomLoopBut");
    wind->AddControl("title=JpgSaveBut,type=VC_BUTTON,text=Jpg Save,x=695,y=961,w=70,h=23,dataname=jpgsavebutt");
    wind->AddControl("title=bailoutLabel,type=VC_LABEL,text=Bailout:,x=509,y=90,w=60,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=bailoutBox,type=VC_EDIT,text=4,x=576,y=91,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=status_stat,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=10,y=-20,w=400,h=18,dataname=G_Mandel_gstatus");
    wind->AddControl("title=Loop_stat,type=VC_GLOBAL_STAT_STRING,text=Loop status:*S,x=10,y=-40,w=400,h=18,dataname=G_Mandel_loopstat");
    wind->AddControl("title=capx_coordbox,type=VC_EDIT,text=,x=328,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=capy_coordbox,type=VC_EDIT,text=,x=328,y=190,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=capw_coordbox,type=VC_EDIT,text=,x=328,y=210,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=caph_coordbox,type=VC_EDIT,text=,x=328,y=230,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=CopyDimsBut,type=VC_BUTTON,text=Copy Dims ,x=322,y=261,w=170,h=28,dataname=Mandel_copydims_but");
    wind->AddControl("title=mousecap_label,type=VC_LABEL,text=Highlighted section:,x=325,y=144,w=237,h=19,numblurs=1,transparent=true");
    wind->AddControl("title=DimsCopyotherBut,type=VC_BUTTON,text=<--Copy Dims ,x=575,y=262,w=170,h=25,dataname=Mandel_copydimsother_but");
    wind->AddControl("title=copyx_coordbox,type=VC_EDIT,text=-3,x=575,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyy_coordbox,type=VC_EDIT,text=-3,x=575,y=190,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyw_coordbox,type=VC_EDIT,text=6,x=575,y=210,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=copyh_coordbox,type=VC_EDIT,text=6,x=575,y=230,w=170,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=render_button,type=VC_BUTTON,text=Render,x=205,y=265,w=100,h=415,dataname=render_button,needsparent=true");
    wind->AddControl("title=threadsLabel,type=VC_LABEL,text=Threads:,x=200,y=683,w=70,h=19,numblurs=1,transparent=true");
    wind->AddControl("title=threadsBox,type=VC_EDIT,text=10,x=275,y=683,w=36,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=Thread_stat,type=VC_GLOBAL_STAT_STRING,text=Thread status:*S,x=10,y=-60,w=400,h=18,dataname=G_Mandel_threadstat");
    wind->AddControl("title=RenderTypeListbox,type=VC_LISTBOX,text=nt,x=21,y=244,w=171,h=450,listboxfunc=NOFUNC,dataname=MandelRendersList,numblurs=0");
    wind->AddControl("title=rendertypeslabel,type=VC_LABEL,text=Render Types:,x=20,y=213,w=168,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=do_wrong_mand,type=VC_CHECKBOX,text=over black only If Pos,x=21,y=704,w=250,h=25");
    wind->AddControl("title=ANDRO_SStat,type=VC_LABEL,text=Arbitrary Newton Function:,x=33,y=746,w=444,h=26,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_fact_qbox,type=VC_EDIT,text=1,x=120,y=794,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ANDRO_fact_pbox,type=VC_EDIT,text=4,x=120,y=824,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=ANDRO_fact_plusbut,type=VC_BUTTON,text=add,x=29,y=855,w=80,h=18,dataname=Mandel_addfactor_but");
    wind->AddControl("title=ANDRO_fact_minbut,type=VC_BUTTON,text=sub,x=120,y=855,w=80,h=18,dataname=Mandel_subfactor_but");
    wind->AddControl("title=ANDRO_fact_rembut,type=VC_BUTTON,text=rem,x=210,y=855,w=80,h=18,dataname=Mandel_remExp_but");
    wind->AddControl("title=ANDRO_Q_label,type=VC_LABEL,text=qz^p    q:,x=16,y=794,w=89,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_P_label,type=VC_LABEL,text=         P:,x=16,y=820,w=89,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=ANDRO_fact_clrbut,type=VC_BUTTON,text=clear,x=300,y=855,w=80,h=18,dataname=Mandel_fact_clrbut");
    wind->AddControl("title=ANDRO_stat,type=VC_GLOBAL_STAT_STRING,text=function:*S,x=17,y=771,w=469,h=18,dataname=G_Mandel_ANDRO_FactorStr");
    wind->AddControl("title=loopscountlabel,type=VC_LABEL,text=loops:,x=360,y=591,w=62,h=22,numblurs=1,transparent=true");
    wind->AddControl("title=loopscountedit,type=VC_EDIT,text=100,x=431,y=591,w=91,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=bbrot_samplesLabel,type=VC_LABEL,text=Buddahbrot Samples per thread,x=544,y=120,w=240,h=20,numblurs=1,transparent=true");
    wind->AddControl("title=bbrot_samplesEdit,type=VC_EDIT,text=500,x=544,y=144,w=240,h=21,numblurs=0,transparent=true,nointeract=true");
    wind->AddControl("title=progressSlider,type=VC_SLIDER,text=Progress:100,x=11,y=882,w=979,h=39,numblurs=0,textfont=Modern,nointeract=true");
    wind->AddControl("title=BBrotloopBut,type=VC_BUTTON,text=BBrot Loop,x=358,y=553,w=169,h=29,dataname=renderbbrotLoopBut");

    VWM_register_datar(render_button, "render_button");  
    VWM_register_datar(zoombutt, "zoombutt");
    VWM_register_datar(leftbutt, "leftbutt");
    VWM_register_datar(rightbutt, "rightbutt");
    VWM_register_datar(upbutt, "upbutt");
    VWM_register_datar(downbutt, "downbutt");
    VWM_register_datar(savebutt, "savebutt");
    VWM_register_datar(renderZoomLoopBut, "RenderZoomLoopBut");
    VWM_register_datar(mandel_switch_coloring_but, "switchcolorsbut");
    VWM_register_datar(unzoombutt, "unzoombutt");
    VWM_register_datar(mandel_render_colorstack, "colorstackbut");
    Mandel_vtc.SetFont("Impact");
    Mandel_vtc.SetColor(VRGB_WHITE);
    Mandel_vtc.fontdat.lfHeight = 26;
    Mandel_vtc.fontdat.lfWeight = 300;
    Mandel_vtc.BK_Color = VRGB_RED;

    vw->capture_mouse(&MS_mousecap, Mandel_mousecapture_process);

    cout << "worker threads reporting: " << G_mandel_workerthread_info.threadsinpool;
    cout << "\nworker threads reporting idle: " << G_mandel_workerthread_info.threadsidle;
}
