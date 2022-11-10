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


  
  foreach(n,count){
    if(obj[n].name==rendertype){
        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, obj[n].func, mandel_buffer, rebuild, bail, obj[n].type); 
        break;
    }
   }
   if(rendtype.find("rand")!=string::npos){
     dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
     dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
  }
  if(rendtype.find("ANDRO")!=string::npos){
    dataout += " func: " + ANDRO_Equation();
    dataout2 = " roots: " + ANDRO_Roots();
  }
  if(rendtype.find("uli")!=string::npos || rendtype.find("cxcy")!=string::npos ){
     dataout += "   cx: " + cxcoord + " cy: " + cycoord;
  }
    

    Mandel_add_renderer("Mandelbrot set",calc_mandel,100);
    Mandel_add_renderer( "BBrot mouse orbit",calc_mandel,100);
    Mandel_add_renderer("Julia Set",calc_julia,0);

    Mandel_add_renderer("ANDRO Newton",calc_ANDRO,300);
    Mandel_add_renderer("ANDRO Newton Nova",calc_ANDRO_nova,302);
    Mandel_add_renderer("ANDRO Newton Nova_D",calc_ANDRO_nova,300);
    Mandel_add_renderer("ANDRO Newton Julia",calc_ANDRO_novajulia,301);
    Mandel_add_renderer("ANDRO Newton Julia_D",calc_ANDRO_novajulia,303);
    //        dataout += " func: " + ANDRO_Equation();
    //dataout2 = " roots: " + ANDRO_Roots();

    Mandel_add_renderer("Buddahm2 random",calc_mandle_magnetm2_buddah,400);
    Mandel_add_renderer("BBrotM2 randcxcyLim",calc_mandle_magnetm2_buddah,402);
    Mandel_add_renderer("Buddahbrot random",calc_mandle_buddah,400);
    Mandel_add_renderer("Buddahbrot random HC",calc_mandle_buddah,401);
    Mandel_add_renderer("BBrot random cxcyLim",calc_mandle_buddah,402);
   Mandel_add_renderer("BBrot rand cxcyLimHC",calc_mandle_buddah,403);
   //       dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
 //       dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
 
    Mandel_add_renderer("magnetm",calc_mandle_magnetm1,101);
    Mandel_add_renderer("magnetm1b",calc_mandle_magnetm1b,101);
    Mandel_add_renderer("magnetm2",calc_mandle_magnetm2,101);
    Mandel_add_renderer("magnetm2b",calc_mandle_magnetm2b,101);
   Mandel_add_renderer("magnetm2c",calc_mandle_magnetm2c,101);


    Mandel_add_renderer("Julia Sqrt1",calc_mandle_julia,4);
    Mandel_add_renderer("Brot Sqrt1",calc_mandle_sqrt,101);
    Mandel_add_renderer("Julia Sqrt2",calc_mandle_julia2,4);
    Mandel_add_renderer("Brot Sqrt2",calc_mandle_sqrt2,101);
    Mandel_add_renderer("Julia Sqrt3",calc_mandle_julia3,4);
    Mandel_add_renderer("Brot Sqrt3",calc_mandle_sqrt3,101);
    Mandel_add_renderer("Julia Sqrt4",calc_mandle_julia4,4);
    Mandel_add_renderer("Brot Sqrt4",calc_mandle_sqrt4,101);
    Mandel_add_renderer("Julia Sqrt5",calc_mandle_julia5,4);
    Mandel_add_renderer("Brot Sqrt5",calc_mandle_sqrt5,101);
    Mandel_add_renderer("Julia Sqrt6",calc_mandle_julia6,4);
    Mandel_add_renderer("Brot Sqrt6",calc_mandle_sqrt6,101);
    Mandel_add_renderer("Julia Sqrt7",calc_mandle_julia7,4);
    Mandel_add_renderer("Brot Sqrt7",calc_mandle_sqrt7,101);
    Mandel_add_renderer("Julia Sqrt8",calc_mandle_julia8,4);
    Mandel_add_renderer("Brot Sqrt8",calc_mandle_sqrt8,101);
    Mandel_add_renderer("Julia Sqrt9",calc_mandle_julia9,4);
    Mandel_add_renderer("Brot Sqrt9",calc_mandle_sqrt9,101);
    Mandel_add_renderer("Julia Sqrt10",calc_mandle_julia10,4);
    Mandel_add_renderer("Brot Sqrt10",calc_mandle_sqrt10,101);
    Mandel_add_renderer("Julia Sqrt11",calc_mandle_julia11,4);
    Mandel_add_renderer("Brot Sqrt11",calc_mandle_sqrt11,101);
    Mandel_add_renderer("Julia Sqrt12",calc_mandle_julia12,4);
    Mandel_add_renderer("Brot Sqrt12",calc_mandle_sqrt12,101);
    Mandel_add_renderer("Julia Sqrt13",calc_mandle_julia13,4);
    Mandel_add_renderer("Brot Sqrt13",calc_mandle_sqrt13,101);
    Mandel_add_renderer("Julia Sqrt14",calc_mandle_julia14,4);
    Mandel_add_renderer("Brot Sqrt14",calc_mandle_sqrt14,101);
    Mandel_add_renderer("Julia Sqrt error1",calc_mandle_julia_sqrt_error1,4);
    Mandel_add_renderer("Brot Sqrt error1",calc_mandle_sqrt_error1,101);
    Mandel_add_renderer("Julia Sqrt error2",calc_mandle_julia_sqrt_error2,4);
    Mandel_add_renderer("Brot Sqrt error2",calc_mandle_sqrt_error2,101);
    Mandel_add_renderer("Julia Sqrt errortest",calc_mandle_julia_sqrt_errortest,4);
    Mandel_add_renderer("Brot Sqrt errortest",calc_mandle_sqrt_errortest,101);
    Mandel_add_renderer("Julia Sqrt errortest2",calc_mandle_julia_sqrt_errortest2,4);
    Mandel_add_renderer("Brot Sqrt errortest2",calc_mandle_sqrt_errortest2,101);
    
    Mandel_add_renderer("newton E3M1",calc_Newton_e3m1,200);
   Mandel_add_renderer("newton trueE3M1",calc_Newton_trueE3M1,200);
    Mandel_add_renderer("newton E3M1_2",calc_Newton_e3m1_2,200);
    Mandel_add_renderer("newton E3M1_3",calc_Newton_e3m1_3,200);
    Mandel_add_renderer("newton E3M1_4",calc_Newton_e3m1_4,200);
   Mandel_add_renderer("newton 2E4M1",calc_Newton_2E4M1,200);
    Mandel_add_renderer("newton E13M1",calc_Newton_E13M1,200);
    Mandel_add_renderer("newton E3M1_4b",calc_Newton_e3m1_4b,201);
    Mandel_add_renderer("threaded newton E3M1_4c",calc_Newton_e3m1_4c,200);
   Mandel_add_renderer("newton E3M1_4c",calc_Newton_e3m1_4c,200);
    Mandel_add_renderer("newtonWrong z^4-1",calc_Newton_e4m1_db,200);
    Mandel_add_renderer("newtonWrongCxCy z^4-1",calc_Newton_e4m1_db_b,201);
    Mandel_add_renderer("Julia Set Wrong",calc_julia,1);
    Mandel_add_renderer("Julia Set Wrong2",calc_julia2,0);
    Mandel_add_renderer("Julia Set Wrong3",calc_julia,2);
    Mandel_add_renderer("Julia Set Wrong4",calc_julia2,2);
    Mandel_add_renderer("Julia Set Wrong5",calc_julia2,3);
    Mandel_add_renderer("Julia Set Wrong7",calc_julia3,0);
    Mandel_add_renderer("Julia Set Wrong8",calc_julia4,0);
    Mandel_add_renderer("Julia Set Wrong9",calc_julia5,0);
    Mandel_add_renderer("Julia Set Wrong10",calc_julia6,0);
    Mandel_add_renderer("Julia Set Wrong11",calc_julia7,0);
    Mandel_add_renderer("Julia Set Tan",calc_julia_tan,0);
    Mandel_add_renderer("Julia Set Tanw",calc_julia_tanwrong,0);
    Mandel_add_renderer( "Julia Set SinTanw",calc_julia_sin_tanwrong,0);
    Mandel_add_renderer("Julia Set CoTanw",calc_julia_cotanwrong,0);
    Mandel_add_renderer("Julia Set Cos",calc_julia_cos,0);
    Mandel_add_renderer("Julia Set Sin",calc_julia_sin,0);
    Mandel_add_renderer("Julia Set SinTan",calc_julia_sin_tan,0);
    Mandel_add_renderer("Julia Set CoTan",calc_julia_cotan,0);
    Mandel_add_renderer("Julia Set expexp",calc_julia_exp_exp,0);
    Mandel_add_renderer("Julia Set threexp",calc_julia_threexp,0);
    Mandel_add_renderer("Julia Set threexpLD",calc_julia_threexpLD,0);
    Mandel_add_renderer("Julia Set t_brot1",calc_julia,0);
    Mandel_add_renderer("Julia Set t_brot2",calc_julia_threexp,1);
    Mandel_add_renderer("Julia Set t_brot3",calc_julia4,1);
    Mandel_add_renderer("Julia Set t_brot4",calc_julia_tan,1);
    Mandel_add_renderer("Julia Set t_brot5",calc_julia_cos,1);
    Mandel_add_renderer("Julia Set t_brot6",calc_julia_sin,1);
    Mandel_add_renderer("Julia Set t_brot7",calc_julia_exp7,1);
    Mandel_add_renderer("Julia Set exp7",calc_julia_exp7,0);
    Mandel_add_renderer("Julia Set t_brot8",calc_julia_exp_exp_exp,1);
    Mandel_add_renderer("Julia Set exp8",calc_julia_exp_exp_exp,0);
    Mandel_add_renderer("Julia Set exp9",calc_julia_exp127,0);
    Mandel_add_renderer("Julia Set t_brot9",calc_julia_exp127,1);
    //Mandel_add_renderer("VSet Beta");
    Mandel_add_renderer("MandelJulia Euler",calc_mandle_julia_Euler,0);
    Mandel_add_renderer("Mandelbrot Euler1",calc_mandle_Euler,101);
    Mandel_add_renderer("Mandelbrot Euler2",calc_mandle_Euler2,101);
    Mandel_add_renderer("Mandelbrot Euler3",calc_mandle_Euler3,101);
    Mandel_add_renderer("Mandelbrot Euler4",calc_mandle_Euler4,101);
    Mandel_add_renderer("Mandelbrot Euler5",calc_mandle_Euler5,101);
    Mandel_add_renderer("Mandelbrot Euler6",calc_mandle_Euler6,101);
    Mandel_add_renderer("Mandelbrot Euler7",calc_mandle_Euler7,101);
    Mandel_add_renderer("Mandelbrot Euler8",calc_mandle_Euler8,101);
    Mandel_add_renderer("Mandelbrot Euler9",calc_mandle_Euler9,101);
    Mandel_add_renderer("Mandelbrot Euler10",calc_mandle_Euler10,101);
    Mandel_add_renderer("Mandelbrot Euler11",calc_mandle_Euler11,101);
    Mandel_add_renderer("Mandelbrot Euler12",calc_mandle_Euler12,101);
    Mandel_add_renderer("Mandelbrot Euler13",calc_mandle_Euler13,101);
    Mandel_add_renderer("Mandelbrot derbail",calc_mandle_derbail,101);
    Mandel_add_renderer("Mandelbrot derbail2",calc_mandle_derbail2,101);
    Mandel_add_renderer("Mandelbrot derbail3",calc_mandle_derbail3,101);
    Mandel_add_renderer("Mandelbrot derbail4",calc_mandle_derbail4,101);
    Mandel_add_renderer("Mandelbrot derbail5",calc_mandle_derbail5,101);
    Mandel_add_renderer("MandelWrong 18",calc_mandle_wrong18,100);
    Mandel_add_renderer("MandelWrong 17",calc_mandle_wrong17,100);
    Mandel_add_renderer("MandelWrong 16",calc_mandle_wrong16,100);
    Mandel_add_renderer("MandelWrong 15",calc_mandle_wrong15,100);
    Mandel_add_renderer("MandelWrong 14",calc_mandle_wrong14,100);
    Mandel_add_renderer("MandelWrong 13",calc_mandle_wrong13,100);
    Mandel_add_renderer("MandelWrong 12",calc_mandle_wrong12,100);
    Mandel_add_renderer("MandelWrong 11",calc_mandle_wrong11,100);
    Mandel_add_renderer("MandelWrong 10",calc_mandle_wrong10,100);
    Mandel_add_renderer("MandelWrong 9",calc_mandle_wrong9,100);
    Mandel_add_renderer("MandelWrong 8",calc_mandle_wrong8,100);
    Mandel_add_renderer("MandelWrong 7",calc_mandle_wrong7,100);
    Mandel_add_renderer("MandelWrong 6",calc_mandle_wrong6,100);
    Mandel_add_renderer("MandelWrong 5",calc_mandle_wrong5,100);
    Mandel_add_renderer("MandelWrong 4",calc_mandle_wrong4,100);
    Mandel_add_renderer("MandelWrong 3",calc_mandle_wrong3,100);
    Mandel_add_renderer("MandelWrong 2",calc_mandle_wrong2,100);
    Mandel_add_renderer("MandelWrong 1",calc_mandle_wrong,100);
    
*/
//
//class val_2darr_int_proxy {
//    int* arr;
//    int w = 0, h = 0, len=0;
//    val_2darr_int_proxy(int ww, int hh) { w = ww; h = hh; len = w * h; arr = new int[len]; }
//    int operator[](int x) { if(x>-1 && x<len) return arr[x]; };
//
//};
//class val_2darr_int {
//    val_2darr_int_proxy* data;
//    val_2darr_int(int w, int h) {
//        data = new val_2darr_int_proxy(w, h);
//    }
//    val_2darr_int_proxy* operator[](int x) { return arr + (y * w) + x; };
//
//
//};

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

strlist G_Mandel_dictionary;
void populate_mandeldictionary() {
    G_Mandel_dictionary.stack("mandelbrot");
    G_Mandel_dictionary.stack("juliaset");
    G_Mandel_dictionary.stack("newton");
    G_Mandel_dictionary.stack("buddahbrot");
    G_Mandel_dictionary.stack("exponential");
    G_Mandel_dictionary.stack("iterations");
    G_Mandel_dictionary.stack("bailout");
    G_Mandel_dictionary.stack("derbail");
    G_Mandel_dictionary.stack("renderer");
    G_Mandel_dictionary.stack("cardioid");
    G_Mandel_dictionary.stack("stardust");
    G_Mandel_dictionary.stack("attractiveroot");
    G_Mandel_dictionary.stack("repellantroot");
    G_Mandel_dictionary.stack("complexPlane");
    G_Mandel_dictionary.stack("trigfunction");
    G_Mandel_dictionary.stack("Euler");
    G_Mandel_dictionary.stack("mixedfunction");
    G_Mandel_dictionary.stack("nonlinear");
    G_Mandel_dictionary.stack("inherently");
    G_Mandel_dictionary.stack("gridofdots");
    G_Mandel_dictionary.stack("linear");
    G_Mandel_dictionary.stack("colorspace");
    G_Mandel_dictionary.stack("snake");
    G_Mandel_dictionary.stack("tentacle");
    G_Mandel_dictionary.stack("eye");
    G_Mandel_dictionary.stack("ocular");
    G_Mandel_dictionary.stack("galaxy");
    G_Mandel_dictionary.stack("starburst");
    G_Mandel_dictionary.stack("logarithmic");
    G_Mandel_dictionary.stack("algorithmic");
    G_Mandel_dictionary.stack("infinite");
    G_Mandel_dictionary.stack("infinity");
    G_Mandel_dictionary.stack("complexity");
    G_Mandel_dictionary.stack("dimension");
    G_Mandel_dictionary.stack("dimensionality");
    G_Mandel_dictionary.stack("rendertime");
    G_Mandel_dictionary.stack("searchspace");
    G_Mandel_dictionary.stack("orbit");
    G_Mandel_dictionary.stack("cloud");
    G_Mandel_dictionary.stack("former");
    G_Mandel_dictionary.stack("plane");
    G_Mandel_dictionary.stack("spiral");
    G_Mandel_dictionary.stack("something");
    G_Mandel_dictionary.stack("crazy");
    G_Mandel_dictionary.stack("insane");
    G_Mandel_dictionary.stack("horse");
    G_Mandel_dictionary.stack("burning");
    G_Mandel_dictionary.stack("ship");
    G_Mandel_dictionary.stack("container");
    G_Mandel_dictionary.stack("nova");
    G_Mandel_dictionary.stack("horseshoe");
    G_Mandel_dictionary.stack("phoenix");
    G_Mandel_dictionary.stack("convergent");
    G_Mandel_dictionary.stack("divergent");
    G_Mandel_dictionary.stack("somany");
    G_Mandel_dictionary.stack("math");
    G_Mandel_dictionary.stack("bom");
    G_Mandel_dictionary.stack("crushed");
    G_Mandel_dictionary.stack("imaginary");
    G_Mandel_dictionary.stack("phi");
    G_Mandel_dictionary.stack("argument");
    G_Mandel_dictionary.stack("sine");
    G_Mandel_dictionary.stack("tangent");
    G_Mandel_dictionary.stack("eipi");
    G_Mandel_dictionary.stack("distance");
    G_Mandel_dictionary.stack("wild");
    G_Mandel_dictionary.stack("squared");
    G_Mandel_dictionary.stack("modulus");
    G_Mandel_dictionary.stack("dust");
    G_Mandel_dictionary.stack("cellular");
    G_Mandel_dictionary.stack("magnet");
    G_Mandel_dictionary.stack("loop");
    G_Mandel_dictionary.stack("curve");
    G_Mandel_dictionary.stack("escape");
    G_Mandel_dictionary.stack("cubist");
    G_Mandel_dictionary.stack("shuffle");
    G_Mandel_dictionary.stack("electric");
    G_Mandel_dictionary.stack("spark");
    //G_Mandel_dictionary.stack("");
}

string global_FFMPEG_fps = "30", global_FFMPEG_fname = "out.mp4", global_FFMPEG_imgext="png";
void global_FFMPEG_runnerthread(void* a) {
    //string call = "ffmpeg -r " + global_FFMPEG_fps + " -f image2 -s 1920x1080 -i frame%d."+ global_FFMPEG_imgext + " -vcodec libx264 -crf 18 -pix_fmt yuv444 " + global_FFMPEG_fname ;
    string call = "ffmpeg -r " + global_FFMPEG_fps + " -f image2 -s 1920x1080 -i frame%d." + global_FFMPEG_imgext + " -vcodec libx264rgb -crf 18 -pix_fmt rgb24 " + global_FFMPEG_fname;
    system(call.c_str());
}

ValTextControl Mandel_vtc("Impact", 10, 10, 600, 30, "t");

int mandel_buffer[Mandelbrot_window_dims][Mandelbrot_window_dims];
stringlist G_Mandel_rendertypes, G_Mandel_rendertypes_master;
double G_Mandel_lastx = 0, G_Mandel_lasty = 0, G_Mandel_lastw = 0, G_Mandel_lasth = 0;
double G_Mandel_lastcx = 0, G_Mandel_lastcy = 0, G_Mandel_lastitts = 0, G_Mandel_lastb = 0;
string G_Mandel_lastrend="";
string G_Mandel_gstatus = "", G_Mandel_loopstat = "";
string G_Mandel_lastState = "";
bool G_Mandel_already_rendering = false;
bool G_Mandel_last_wasbuild = false;
bool G_Mandel_color_lastLinearCats = false;
int G_Mandel_color_last_type = 0;
bool G_Mandel_recolor_flag = false;

struct Mandel_rendertype {
    string name;
    void* func;
    int type;
};
Mandel_rendertype G_mandel_renderers[300];
int G_mandel_renderers_count = 0;
#include <direct.h>
bool folder_exists(string f) {
    struct stat buffer;
    return (stat(f.c_str(), &buffer) == 0);
}
string getUniqFname(string fname, int& plc, string ext) {
    string n = fname + ctostr(plc) + ext;
    while (file_exists(n))n = fname + ctostr(++plc) + ext;
    return n;
}
void ValFractal_frametofolder(string fold) {
    if (!folder_exists(fold))_mkdir(fold.c_str());
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    //string numb = manwind->eval_edit("imgfilenumBox");
    //string bullshitholder = manwind->eval_edit("savefilename") + numb + ".png";
    //numb = ctostr(ctoint(numb) + 1);
    string numb = manwind->eval_edit("framenumBox");
    int number = ctoint(numb);
    string fn = fold +"/frame";
    string bullshitholder = getUniqFname(fn, number, ".png");
    numb = ctostr(number + 1);
    manwind->set_editctrl_text("framenumBox", numb);
    gdiSaveHbitmap(WindowMan.fromName("mandelbrot")->mygfx.hbmp, bullshitholder, "png");
}

void Mandel_add_renderer(string n, void* f, int t,bool list=true) {
    G_mandel_renderers[G_mandel_renderers_count].name = n;
    G_mandel_renderers[G_mandel_renderers_count].func = f;
    G_mandel_renderers[G_mandel_renderers_count].type = t;
    if (list) {
        G_Mandel_rendertypes.stack(n);
        G_Mandel_rendertypes_master.stack(n);
    }
    G_mandel_renderers_count++;
}

string Mandel_savestate();
void Mandel_loadstate(string state, ValWindow* manwind);

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
    string dataout3 = "";
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
    G_Mandel_Buddahbrot_searchdims[0] = 1;
    G_Mandel_Buddahbrot_searchdims[1] = x;
    G_Mandel_Buddahbrot_searchdims[2] = y;
    G_Mandel_Buddahbrot_searchdims[3] = w;
    G_Mandel_Buddahbrot_searchdims[4] = h;
    if (manwind->evaluate_controlb("UseBoodahDimsChk", type)) {
        cout << "setting bbrot search dims\n";
        xcoord = manwind->eval_edit("x_coordboodah");
        ycoord = manwind->eval_edit("y_coordboodah");
        wcoord = manwind->eval_edit("w_coordboodah");
        hcoord = manwind->eval_edit("h_coordboodah");
        G_Mandel_Buddahbrot_searchdims[0] = 2;
        G_Mandel_Buddahbrot_searchdims[1] = strtodbl(xcoord);
        G_Mandel_Buddahbrot_searchdims[2] = strtodbl(ycoord);
        G_Mandel_Buddahbrot_searchdims[3] = strtodbl(wcoord);
        G_Mandel_Buddahbrot_searchdims[4] = strtodbl(hcoord);
        dataout3 += "search dims (x,y,w,h): " + xcoord + "," + ycoord + "," + wcoord + "," + hcoord;
    }

    string rendtype = manwind->GetControl("RenderTypeListbox")->sval;
    cout << "step 3\n";
    if (rendtype.find("DRO") != string::npos) {

        G_Mandel_ANDRO_relax = strtodbl(manwind->eval_edit("RelaxBox"));
        cout << "coppied relaxbox into global: " << G_Mandel_ANDRO_relax << ":\n";
    }
    else G_Mandel_ANDRO_relax = 1.0;
    cout << "step 4\n";
//    if (wrong_mand) manwind->mygfx.draw_mandelbrot_tocopy_wrong(x, y, w, h, it);
//    else  manwind->mygfx.draw_mandelbrot_tocopy(x, y, w, h, it);
    string colortypestr = "linear";
    if(G_Mandel_colorizer_type == 1)colortypestr = "steep";
    else if (G_Mandel_colorizer_type == 3)colortypestr = "greyscale";
    else if (G_Mandel_colorizer_type == 4) {
        colortypestr = "pallet";
        if (G_Mandel_colorizer_ex_num_catagories == 0)Linear_colorEx_fromstr(manwind->eval_edit("RandSeedBox"), ctoint(manwind->eval_edit("RandSeedcatsBox")));
    }
    dataout += " type: \"" + rendtype + "\" color: " + colortypestr;
    //cout << "rendering " << rendtype << "\n";
    G_Mandel_gstatus = "rendering" +rendtype;
    bool didrecolor = false;
    manwind = WindowMan.fromName("mandelbrot");
    if (rendtype.find("Lim") != string::npos) {
        cx = floor(cx);
        cy = floor(cy);
        if (cy == 0)cy = 1;
    }
    if (G_Mandel_recolor_flag|| (G_Mandel_lastx == x && G_Mandel_lasty == y && G_Mandel_lastw == w && G_Mandel_lasth == h
        && G_Mandel_lastcx == cx && G_Mandel_lastcy == cy && G_Mandel_lastb == bail && rendtype.find("ANDRO") == string::npos
        && G_Mandel_lastitts == it && G_Mandel_lastrend == rendtype && rendtype.find("rand")==string::npos)) {
        /*if (G_Mandel_lastitts == it && G_Mandel_lastrend == rendtype && G_Mandel_color_last_type == G_Mandel_colorizer_type) {

            cout << "already rendered these settings, aborting\n";

            G_Mandel_already_rendering = false;
            return;
        }*/
        
            //dataout += "   cx: " + cxcoord + " cy: " + cycoord;
            cout << "re-colorizing\n";
            manwind->mygfx.mandel_buffer_render(mandel_buffer, it);
            //cout << "mand drawn" << endl;
            //manwind->mygfx.paste_buf();
            didrecolor = true;
            //manwind->mygfx.save_image("mandtest.bmp");
            //Mandel_vtc.content = dataout;
            //Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
            //G_Mandel_color_lastLinearCats=G_Mandel_color_LinearCats ;
            //G_Mandel_color_last_type = G_Mandel_colorizer_type;
            //manwind->GFXdraw();
            ////cout << manwind->evaluate_controlb("do_wrong_mand", type)<< "  type: " ;
            ////cout << type << endl;

            //G_Mandel_already_rendering = false;
            //return;
        
        
    }
    
        G_Mandel_lastx = x;
        G_Mandel_lasty = y;
        G_Mandel_lastw = w;
        G_Mandel_lasth = h;
        G_Mandel_lastcx = cx;
        G_Mandel_lastcy = cy;
        G_Mandel_lastb = bail;
    
    if (wrong_mand)rebuild = G_Mandel_lastitts;
    G_Mandel_lastitts = it;
    //SHOW(rebuild);
    G_Mandel_lastrend = rendtype;
    G_Mandel_last_wasbuild = false;
     G_Mandel_color_lastLinearCats= G_Mandel_color_LinearCats;
     G_Mandel_color_last_type = G_Mandel_colorizer_type;

     G_mandel_workerthread_info.global_threadlock=threadscount;
     string state = Mandel_savestate();
     if (G_Mandel_lastState != state) {
         writefile("lastrender.di", state);
         cout << "wrote lastrender.di\n";
     }
     G_Mandel_lastState = state;
bool didrendflag = didrecolor;

if (!didrendflag) {
    foreach(n, G_mandel_renderers_count) {
        if (G_mandel_renderers[n].name == rendtype) {
            manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, G_mandel_renderers[n].func, mandel_buffer, rebuild, bail, G_mandel_renderers[n].type);
            didrendflag = true;
            break;
        }
    }
}
if (!didrendflag) {
    cout << "no render type found \n";
    return;
}
if (rendtype.find("rand") != string::npos) {

    dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
    dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
}
if (rendtype.find("ANDRO") != string::npos) {
    dataout += " func: " + ANDRO_Equation();
    dataout2 += " roots: " + ANDRO_Roots();
}
if (rendtype.find("uli") != string::npos || rendtype.find("cxcy") != string::npos || rendtype.find("jset") != string::npos) {
    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
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
        Mandel_vtc.y += 30;
        Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
        if (dataout3 != "") {
            Mandel_vtc.content = dataout3;
            Mandel_vtc.y += 30;
            Mandel_vtc.DIBdraw(manwind->mygfx.hdcDesktop, manwind->mygfx.hbmp);
            Mandel_vtc.y -= 30;
        }
        Mandel_vtc.y -= 30;
        
    }
    manwind->GFXdraw();
    //cout << manwind->evaluate_controlb("do_wrong_mand", type)<< "  type: " ;
    //cout << type << endl;G_Mandel_gstatus = "rendering";
    G_Mandel_gstatus = "done rendering";
    G_Mandel_already_rendering = false;
     manwind = WindowMan.fromName("mandelbrot controller");
    if (manwind->evaluate_controlb("animateChk", type)) {
        manwind->eval_edit("animationFolderBox");
        ValFractal_frametofolder(manwind->eval_edit("animationFolderBox"));
    }
}


void Mandel_fill_rendertypes_default() { 

Mandel_add_renderer("Mandelbrot set", calc_mandle, 100); 
Mandel_add_renderer("Test3CrCi jset  J2", calc_mandle_weirdMag3Jset_buddah, 419);
Mandel_add_renderer("Test3CrCi jset  B", calc_mandle_weirdMag3Jset_buddahB, 419);
Mandel_add_renderer("Test3CrCi jset  C", calc_mandle_weirdMag3Jset_buddahC, 419); 
Mandel_add_renderer("Testvalsfunc CrCi jset  C", calc_mandle_Valsfunc_buddah, 419);
Mandel_add_renderer("TestvalsfuncB CrCi jset  C", calc_mandle_Valsfunc_buddahB, 419);
Mandel_add_renderer("TestvalsfuncC CrCi jset", calc_mandle_Valsfunc_buddahC, 419);
Mandel_add_renderer("TestvalsfuncD CrCi jset", calc_mandle_Valsfunc_buddahD, 419);
Mandel_add_renderer("TestvalsfuncE CrCi jset", calc_mandle_Valsfunc_buddahE, 419);
Mandel_add_renderer("TestvalsfuncF CrCi jset", calc_mandle_Valsfunc_buddahF, 419);
Mandel_add_renderer("TestvalsfuncG CrCi jset", calc_mandle_Valsfunc_buddahG, 419);
Mandel_add_renderer("TestvalsfuncH CrCi jset", calc_mandle_Valsfunc_buddahH, 419);
Mandel_add_renderer("TestvalsfuncI CrCi jset", calc_mandle_Valsfunc_buddahI, 419);
Mandel_add_renderer("TestvalsfuncJ CrCi jset", calc_mandle_Valsfunc_buddahJ, 419);
Mandel_add_renderer("TestvalsfuncK CrCi jset", calc_mandle_Valsfunc_buddahk, 419);
Mandel_add_renderer("TestvalsfuncL CrCi jset", calc_mandle_Valsfunc_buddahL, 419);
Mandel_add_renderer("TestvalsfuncM CrCi jset", calc_mandle_Valsfunc_buddahM, 419);
Mandel_add_renderer("TestvalsfuncN CrCi jset", calc_mandle_Valsfunc_buddahN, 419);

Mandel_add_renderer("calc_iansfunction", calc_iansfunction, 101); 
Mandel_add_renderer("iansfunctiontZrCi rand Lim", calc_iansfunction_buddah, 405);
Mandel_add_renderer("iansfunctionZrCr rand Lim", calc_iansfunction_buddah, 406);
Mandel_add_renderer("iansfunctionCrZi rand Lim", calc_iansfunction_buddah, 407);
Mandel_add_renderer("iansfunctionCiZi rand Lim", calc_iansfunction_buddah, 408);
Mandel_add_renderer("iansfunctionCrCi rand Lim", calc_iansfunction_buddah, 409);
Mandel_add_renderer("iansfunction mouse orbit_MPROC", calc_iansfunction_buddah, 402, false);
Mandel_add_renderer("iansfunction mouse orbit", calc_iansfunction, 101);
Mandel_add_renderer("iansfunction random cxcyLim", calc_iansfunction_buddah, 402); 

Mandel_add_renderer("calc_fractal_cos_zoverc t", calc_fractal_cos_zoverc, 101);
Mandel_add_renderer("calc_fractal_cos_zoverc_buddah", calc_fractal_cos_zoverc_buddah, 409);
Mandel_add_renderer("cos_zoverc ZrCi rand Lim", calc_fractal_cos_zoverc_buddah, 405);
Mandel_add_renderer("cos_zoverc ZrCr rand Lim", calc_fractal_cos_zoverc_buddah, 406);
Mandel_add_renderer("cos_zoverc CrZi rand Lim", calc_fractal_cos_zoverc_buddah, 407);
Mandel_add_renderer("cos_zoverc CiZi rand Lim", calc_fractal_cos_zoverc_buddah, 408);
//Mandel_add_renderer("iansfunctionCrCi rand Lim", calc_iansfunction_buddah, 409);
Mandel_add_renderer("cos_zoverc mouse orbit_MPROC", calc_fractal_cos_zoverc_buddah, 402, false);
Mandel_add_renderer("cos_zoverc mouse orbit", calc_fractal_cos_zoverc_buddah, 409);
Mandel_add_renderer("cos_zoverc random cxcyLim", calc_fractal_cos_zoverc_buddah, 402);

Mandel_add_renderer("Julia Set", calc_julia, 0);
Mandel_add_renderer("Buddahbrot random", calc_mandle_buddah, 400);
Mandel_add_renderer("Buddahbrot random HC", calc_mandle_buddah, 401);
Mandel_add_renderer("BBrot random cxcyLim", calc_mandle_buddah, 402);
Mandel_add_renderer("BBrot rand cxcyLimHC", calc_mandle_buddah, 403);
Mandel_add_renderer("BBrotZrCi rand Lim", calc_mandle_buddah, 405);
Mandel_add_renderer("BBrotZrCr rand Lim", calc_mandle_buddah, 406);
Mandel_add_renderer("BBrotCrZi rand Lim", calc_mandle_buddah, 407);
Mandel_add_renderer("BBrotCiZi rand Lim", calc_mandle_buddah, 408);
Mandel_add_renderer("BBrotCrCi rand Lim", calc_mandle_buddah, 409);

Mandel_add_renderer("TestCrCi rand Lim", calc_mandle_weirdMag_buddah, 409);
Mandel_add_renderer("TestCrCi rand LimB", calc_mandle_weirdMag_buddahB, 409);
Mandel_add_renderer("TestCrCi rand LimC", calc_mandle_weirdMag_buddahC, 409);
Mandel_add_renderer("TestCrCi rand LimD", calc_mandle_weirdMag_buddahD, 409);
Mandel_add_renderer("TestCrCi rand LimE", calc_mandle_weirdMag_buddahE, 409);
Mandel_add_renderer("TestCrCi rand LimF", calc_mandle_weirdMag_buddahF, 409);
Mandel_add_renderer("TestCrCi rand LimG", calc_mandle_weirdMag_buddahG, 409);
Mandel_add_renderer("Test2CrCi rand Lim", calc_mandle_weirdMag2_buddah, 409);
Mandel_add_renderer("Test2CrCi rand LimB", calc_mandle_weirdMag2_buddahB, 409);
Mandel_add_renderer("Test2CrCi rand LimC", calc_mandle_weirdMag2_buddahC, 409);
Mandel_add_renderer("Test2CrCi rand LimD", calc_mandle_weirdMag2_buddahD, 409);
Mandel_add_renderer("Test2CrCi rand LimE", calc_mandle_weirdMag2_buddahE, 409);
Mandel_add_renderer("Test2CrCi rand LimF", calc_mandle_weirdMag2_buddahF, 409);
Mandel_add_renderer("Test2CrCi rand LimG", calc_mandle_weirdMag2_buddahG, 409);
Mandel_add_renderer("Test2CrCi rand LimH", calc_mandle_weirdMag2_buddahH, 409);
Mandel_add_renderer("Test2CrCi rand LimI", calc_mandle_weirdMag2_buddahI, 409);
Mandel_add_renderer("Test2CrCi rand LimJ", calc_mandle_weirdMag2_buddahJ, 409);
Mandel_add_renderer("TestCrCi  jset  B", calc_mandle_weirdMagJset_buddahB, 419);
Mandel_add_renderer("TestCrCi  jset  D", calc_mandle_weirdMagJset_buddahD, 419);
Mandel_add_renderer("TestCrCi  jset  F", calc_mandle_weirdMagJset_buddahF, 419);
Mandel_add_renderer("Test2CrCi jset  J", calc_mandle_weirdMag2Jset_buddahJ, 419);
Mandel_add_renderer("Test2CrCi jset  J2", calc_mandle_weirdMag2Jset_buddahJ2, 419); 


Mandel_add_renderer("mandelbrot mouse orbit_MPROC", calc_mandle_buddah, 402,false);
Mandel_add_renderer("mandelbrot mouse orbit", calc_mandle, 100);
Mandel_add_renderer("magm2Wrong mouse orbit_MPROC", calc_mandle_magnetm2_buddah, 402,false);
Mandel_add_renderer("magm2Wrong mouse orbit", calc_mandle_magnetm2c, 101);
Mandel_add_renderer("magm1 mouse orbit_MPROC", calc_mandle_magnetm1_buddah, 402, false);
Mandel_add_renderer("magm1 mouse orbit", calc_mandle_magnetm1c, 101);
Mandel_add_renderer("magm2 mouse orbit_MPROC", calc_mandle_magnetm2_true_buddah, 402, false);
Mandel_add_renderer("magm2 mouse orbit", calc_mandle_magnetm2_true, 101);
Mandel_add_renderer("Euler mouse orbit_MPROC", calc_mandle_Euler_buddah, 402, false);
Mandel_add_renderer("Euler mouse orbit", calc_mandle_Euler, 101);
Mandel_add_renderer("ANDRO Newton mouse orbit", calc_ANDRO, 300);
Mandel_add_renderer("ANDRO Newton mouse orbit_MPROC", calc_ANDRO_buddah,  402, false);

Mandel_add_renderer("BBrotANDRO RNE rand", calc_ANDRO_novaE_buddah, 400);
Mandel_add_renderer("BBrotANDRO RNE rand Lim", calc_ANDRO_novaE_buddah, 402);
Mandel_add_renderer("BBrotANDRO RNE ZrCi rand Lim", calc_ANDRO_novaE_buddah, 405);
Mandel_add_renderer("BBrotANDRO RNE ZrCr rand Lim", calc_ANDRO_novaE_buddah, 406);
Mandel_add_renderer("BBrotANDRO RNE CrZi rand Lim", calc_ANDRO_novaE_buddah, 407);
Mandel_add_renderer("BBrotANDRO RNE CiZi rand Lim", calc_ANDRO_novaE_buddah, 408);

Mandel_add_renderer("ANDRO Newton RNovaE mouse orbit", calc_ANDRO_novaE, 304);
Mandel_add_renderer("ANDRO Newton RNovaE mouse orbit_MPROC", calc_ANDRO_novaE_buddah, 402, false);

Mandel_add_renderer("BBrotEul rand", calc_mandle_Euler_buddah, 400);
Mandel_add_renderer("BBrotEul rand Lim", calc_mandle_Euler_buddah, 402);
Mandel_add_renderer("BBrotEul ZrCi rand Lim", calc_mandle_Euler_buddah, 405);
Mandel_add_renderer("BBrotEul ZrCr rand Lim", calc_mandle_Euler_buddah, 406);
Mandel_add_renderer("BBrotEul CrZi rand Lim", calc_mandle_Euler_buddah, 407);
Mandel_add_renderer("BBrotEul CiZi rand Lim", calc_mandle_Euler_buddah, 408);

Mandel_add_renderer("ANDRO Newton", calc_ANDRO, 300); 
Mandel_add_renderer("ANDRO Newton Julia", calc_ANDRO_julia, 304);
Mandel_add_renderer("ANDRO Newton RNovaB", calc_ANDRO_novaB, 301); // cy relax, cx added to zr
Mandel_add_renderer("ANDRO Newton RNovaC", calc_ANDRO_novaC, 304); // cy relax, uses root 0
Mandel_add_renderer("ANDRO Newton RNovaE", calc_ANDRO_novaE, 304); // cy relax, uses 1,0
Mandel_add_renderer("ANDRO Newton RNovaF", calc_ANDRO_novaF, 304); // cy relax, root cx, z-=x+y
Mandel_add_renderer("ANDRO Newton RNovaG", calc_ANDRO_novaG, 304); // cy relax, root cx, z+=x+y
Mandel_add_renderer("ANDRO Newton Nova_D", calc_ANDRO_nova, 303);
Mandel_add_renderer("ANDRO Newton Nova Jset", calc_ANDRO_nova, 301);   // z += cx+cy
Mandel_add_renderer("ANDRO Newton nova Julia", calc_ANDRO_novajulia, 301);
Mandel_add_renderer("ANDRO Newton nova JuliaB", calc_ANDRO_novajuliaB, 301);
Mandel_add_renderer("ANDRO Newton nova Julia_D", calc_ANDRO_novajulia, 303);

//        dataout += " func: " + ANDRO_Equation();
//dataout2 = " roots: " + ANDRO_Roots();

Mandel_add_renderer("BBrotM1 rand", calc_mandle_magnetm1_buddah, 400); 
Mandel_add_renderer("BBrotM1 rand Lim", calc_mandle_magnetm1_buddah, 402);
Mandel_add_renderer("BBrotM1 ZrCi rand Lim", calc_mandle_magnetm1_buddah, 405);
Mandel_add_renderer("BBrotM1 ZrCr rand Lim", calc_mandle_magnetm1_buddah, 406);
Mandel_add_renderer("BBrotM1 CrZi rand Lim", calc_mandle_magnetm1_buddah, 407);
Mandel_add_renderer("BBrotM1 CiZi rand Lim", calc_mandle_magnetm1_buddah, 408);

Mandel_add_renderer("BBrotM2wrong rand", calc_mandle_magnetm2_buddah, 400);
Mandel_add_renderer("BBrotM2wrong rand Lim", calc_mandle_magnetm2_buddah, 402);
Mandel_add_renderer("BBrotM2W ZrCi rand Lim", calc_mandle_magnetm2_buddah, 405);
Mandel_add_renderer("BBrotM2W ZrCr rand Lim", calc_mandle_magnetm2_buddah, 406);
Mandel_add_renderer("BBrotM2W CrZi rand Lim", calc_mandle_magnetm2_buddah, 407);
Mandel_add_renderer("BBrotM2W CiZi rand Lim", calc_mandle_magnetm2_buddah, 408);

Mandel_add_renderer("BBrotM2 rand", calc_mandle_magnetm2_true_buddah, 400);
Mandel_add_renderer("BBrotM2 rand Lim", calc_mandle_magnetm2_true_buddah, 402);
Mandel_add_renderer("BBrotm2b rand", calc_mandle_magnetm2_true_buddahb, 400);
Mandel_add_renderer("BBrotm2b rand Lim", calc_mandle_magnetm2_true_buddahb, 402);
Mandel_add_renderer("BBrotM2 ZrCi randcxcyLim", calc_mandle_magnetm2_true_buddah, 405);
Mandel_add_renderer("BBrotM2 ZrCr randcxcyLim", calc_mandle_magnetm2_true_buddah, 406);
Mandel_add_renderer("BBrotM2 CrZi randcxcyLim", calc_mandle_magnetm2_true_buddah, 407);
Mandel_add_renderer("BBrotM2 CiZi randcxcyLim", calc_mandle_magnetm2_true_buddah, 408);


//       dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//       dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);

Mandel_add_renderer("magnetm1", calc_mandle_magnetm1, 101);
Mandel_add_renderer("magnetm1b", calc_mandle_magnetm1b, 101);
Mandel_add_renderer("magnetm1c", calc_mandle_magnetm1c, 101);
Mandel_add_renderer("magnetm1d jset", calc_mandle_magnetm1d, 4);
Mandel_add_renderer("true magnetm2", calc_mandle_magnetm2_true, 101);
Mandel_add_renderer("true magnetm2 2", calc_mandle_magnetm2_true2, 101);
Mandel_add_renderer("true magm2 jset1", calc_mandle_magnetm2_true3, 4);
Mandel_add_renderer("true magm2 jset2", calc_mandle_magnetm2_true3b, 4); 
Mandel_add_renderer("true magm2 jset3", calc_mandle_magnetm2_true3c, 4);
Mandel_add_renderer("true magm2 jset4", calc_mandle_magnetm2_true3d, 4);
Mandel_add_renderer("true magm2 jset5", calc_mandle_magnetm2_true3e, 4);
Mandel_add_renderer("true magm2 jset6", calc_mandle_magnetm2_true3f, 4);
Mandel_add_renderer("true magm2 jset7", calc_mandle_magnetm2_true3g, 4);
Mandel_add_renderer("true magm2 jset8", calc_mandle_magnetm2_true3h, 4);
Mandel_add_renderer("true magm2 jset9", calc_mandle_magnetm2_true3i, 4);
Mandel_add_renderer("true magm2 jset10", calc_mandle_magnetm2_true3j, 4);
Mandel_add_renderer("true magm2 jset11", calc_mandle_magnetm2_true3k, 4);
Mandel_add_renderer("true magm2 jset12", calc_mandle_magnetm2_true3l, 4);
Mandel_add_renderer("true magm2 jset13", calc_mandle_magnetm2_true3m, 4);
Mandel_add_renderer("true magm2 jset14", calc_mandle_magnetm2_true3n, 4);
Mandel_add_renderer("true magm2 jset15", calc_mandle_magnetm2_true3o, 4); 
 
Mandel_add_renderer("magnetm20", calc_mandle_magnetm2, 101);
Mandel_add_renderer("magnetm2b", calc_mandle_magnetm2b, 101);
Mandel_add_renderer("magnetm2c", calc_mandle_magnetm2c, 101);
Mandel_add_renderer("magnetm2d", calc_mandle_magnetm2d, 101);
Mandel_add_renderer("magnetm2db", calc_mandle_magnetm2db, 101);
Mandel_add_renderer("magnetm2dc", calc_mandle_magnetm2dc, 101);
Mandel_add_renderer("magnetm2bb", calc_mandle_magnetm2bb, 101);

Mandel_add_renderer("Julia Sqrt1", calc_mandle_julia_sqrt, 4);
Mandel_add_renderer("Brot Sqrt1", calc_mandle_sqrt, 101);
Mandel_add_renderer("Julia Sqrt2", calc_mandle_julia_sqrt2, 4);
Mandel_add_renderer("Brot Sqrt2", calc_mandle_sqrt2, 101);
Mandel_add_renderer("Julia Sqrt3", calc_mandle_julia_sqrt3, 4);
Mandel_add_renderer("Brot Sqrt3", calc_mandle_sqrt3, 101);
Mandel_add_renderer("Julia Sqrt4", calc_mandle_julia_sqrt4, 4);
Mandel_add_renderer("Brot Sqrt4", calc_mandle_sqrt4, 101);
Mandel_add_renderer("Julia Sqrt5", calc_mandle_julia_sqrt5, 4);
Mandel_add_renderer("Brot Sqrt5", calc_mandle_sqrt5, 101);
Mandel_add_renderer("Julia Sqrt6", calc_mandle_julia_sqrt6, 4);
Mandel_add_renderer("Brot Sqrt6", calc_mandle_sqrt6, 101);
Mandel_add_renderer("Julia Sqrt7", calc_mandle_julia_sqrt7, 4);
Mandel_add_renderer("Brot Sqrt7", calc_mandle_sqrt7, 101);
Mandel_add_renderer("Julia Sqrt8", calc_mandle_julia_sqrt8, 4);
Mandel_add_renderer("Brot Sqrt8", calc_mandle_sqrt8, 101);
Mandel_add_renderer("Julia Sqrt9", calc_mandle_julia_sqrt9, 4);
Mandel_add_renderer("Brot Sqrt9", calc_mandle_sqrt9, 101);
Mandel_add_renderer("Julia Sqrt10", calc_mandle_julia_sqrt10, 4);
Mandel_add_renderer("Brot Sqrt10", calc_mandle_sqrt10, 101);
Mandel_add_renderer("Julia Sqrt11", calc_mandle_julia_sqrt11, 4);
Mandel_add_renderer("Brot Sqrt11", calc_mandle_sqrt11, 101);
Mandel_add_renderer("Julia Sqrt12", calc_mandle_julia_sqrt12, 4);
Mandel_add_renderer("Brot Sqrt12", calc_mandle_sqrt12, 101);
Mandel_add_renderer("Julia Sqrt13", calc_mandle_julia_sqrt13, 4);
Mandel_add_renderer("Brot Sqrt13", calc_mandle_sqrt13, 101);
Mandel_add_renderer("Julia Sqrt14", calc_mandle_julia_sqrt14, 4);
Mandel_add_renderer("Brot Sqrt14", calc_mandle_sqrt14, 101);
Mandel_add_renderer("Julia Sqrt error1", calc_mandle_julia_sqrt_error1, 4);
Mandel_add_renderer("Brot Sqrt error1", calc_mandle_sqrt_error1, 101);
Mandel_add_renderer("Julia Sqrt error2", calc_mandle_julia_sqrt_error2, 4);
Mandel_add_renderer("Brot Sqrt error2", calc_mandle_sqrt_error2, 101);
Mandel_add_renderer("Julia Sqrt errortest", calc_mandle_julia_sqrt_errortest, 4);
Mandel_add_renderer("Brot Sqrt errortest", calc_mandle_sqrt_errortest, 101);
Mandel_add_renderer("Julia Sqrt errortest2", calc_mandle_julia_sqrt_errortest2, 4);
Mandel_add_renderer("Brot Sqrt errortest2", calc_mandle_sqrt_errortest2, 101);

Mandel_add_renderer("newton E3M1", calc_Newton_e3m1, 200);
Mandel_add_renderer("newton trueE3M1", calc_Newton_trueE3M1, 200);
Mandel_add_renderer("newton E3M1_2", calc_Newton_e3m1_2, 200);
Mandel_add_renderer("newton E3M1_3", calc_Newton_e3m1_3, 200);
Mandel_add_renderer("newton E3M1_4", calc_Newton_e3m1_4, 200);
Mandel_add_renderer("newton 2E4M1", calc_Newton_2E4M1, 200);
Mandel_add_renderer("newton E13M1", calc_Newton_E13M1, 200);
Mandel_add_renderer("newton E3M1_4b", calc_Newton_e3m1_4b, 201);
Mandel_add_renderer("threaded newton E3M1_4c", calc_Newton_e3m1_4c, 200);
Mandel_add_renderer("newton E3M1_4c", calc_Newton_e3m1_4c, 200);
Mandel_add_renderer("newtonWrong z^4-1", calc_Newton_e4m1_db, 200);
Mandel_add_renderer("newtonWrongCxCy z^4-1", calc_Newton_e4m1_db_b, 201);
Mandel_add_renderer("Julia Set Wrong", calc_julia, 1);
Mandel_add_renderer("Julia Set Wrong2", calc_julia2, 0);
Mandel_add_renderer("Julia Set Wrong3", calc_julia, 2);
Mandel_add_renderer("Julia Set Wrong4", calc_julia2, 2);
Mandel_add_renderer("Julia Set Wrong5", calc_julia2, 3);
Mandel_add_renderer("Julia Set Wrong7", calc_julia3, 0);
Mandel_add_renderer("Julia Set Wrong8", calc_julia4, 0);
Mandel_add_renderer("Julia Set Wrong9", calc_julia5, 0);
Mandel_add_renderer("Julia Set Wrong10", calc_julia6, 0);
Mandel_add_renderer("Julia Set Wrong11", calc_julia7, 0);
Mandel_add_renderer("Julia Set Tan", calc_julia_tan, 0);
Mandel_add_renderer("Julia Set Tanw", calc_julia_tanwrong, 0);
Mandel_add_renderer("Julia Set SinTanw", calc_julia_sin_tanwrong, 0);
Mandel_add_renderer("Julia Set CoTanw", calc_julia_cotanwrong, 0);
Mandel_add_renderer("Julia Set Cos", calc_julia_cos, 0);
Mandel_add_renderer("Julia Set Sin", calc_julia_sin, 0);
Mandel_add_renderer("Julia Set SinTan", calc_julia_sin_tan, 0);
Mandel_add_renderer("Julia Set CoTan", calc_julia_cotan, 0);
Mandel_add_renderer("Julia Set expexp", calc_julia_exp_exp, 0);
Mandel_add_renderer("Julia Set threexp", calc_julia_threexp, 0);
Mandel_add_renderer("Julia Set threexpLD", calc_julia_threexpLD, 0);
Mandel_add_renderer("Julia Set t_brot1", calc_julia, 0);
Mandel_add_renderer("Julia Set t_brot2", calc_julia_threexp, 1);
Mandel_add_renderer("Julia Set t_brot3", calc_julia4, 1);
Mandel_add_renderer("Julia Set t_brot4", calc_julia_tan, 1);
Mandel_add_renderer("Julia Set t_brot5", calc_julia_cos, 1);
Mandel_add_renderer("Julia Set t_brot6", calc_julia_sin, 1);
Mandel_add_renderer("Julia Set t_brot7", calc_julia_exp7, 1);
Mandel_add_renderer("Julia Set exp7", calc_julia_exp7, 0);
Mandel_add_renderer("Julia Set t_brot8", calc_julia_exp_exp_exp, 1);
Mandel_add_renderer("Julia Set exp8", calc_julia_exp_exp_exp, 0);
Mandel_add_renderer("Julia Set exp9", calc_julia_exp127, 0);
Mandel_add_renderer("Julia Set t_brot9", calc_julia_exp127, 1);
//Mandel_add_renderer("VSet Beta");
Mandel_add_renderer("MandelJulia Euler", calc_mandle_julia_Euler, 0);
Mandel_add_renderer("Mandelbrot Euler1", calc_mandle_Euler, 101);
Mandel_add_renderer("Mandelbrot Euler2", calc_mandle_Euler2, 101);
Mandel_add_renderer("Mandelbrot Euler3", calc_mandle_Euler3, 101);
Mandel_add_renderer("Mandelbrot Euler4", calc_mandle_Euler4, 101);
Mandel_add_renderer("Mandelbrot Euler5", calc_mandle_Euler5, 101);
Mandel_add_renderer("Mandelbrot Euler6", calc_mandle_Euler6, 101);
Mandel_add_renderer("Mandelbrot Euler7", calc_mandle_Euler7, 101);
Mandel_add_renderer("Mandelbrot Euler8", calc_mandle_Euler8, 101);
Mandel_add_renderer("Mandelbrot Euler9", calc_mandle_Euler9, 101);
Mandel_add_renderer("Mandelbrot Euler10", calc_mandle_Euler10, 101);
Mandel_add_renderer("Mandelbrot Euler11", calc_mandle_Euler11, 101);
Mandel_add_renderer("Mandelbrot Euler12", calc_mandle_Euler12, 101);
Mandel_add_renderer("Mandelbrot Euler13", calc_mandle_Euler13, 101);
Mandel_add_renderer("Mandelbrot derbail", calc_mandle_derbail, 101);
Mandel_add_renderer("Mandelbrot derbail2", calc_mandle_derbail2, 101);
Mandel_add_renderer("Mandelbrot derbail3", calc_mandle_derbail3, 101);
Mandel_add_renderer("Mandelbrot derbail4", calc_mandle_derbail4, 101);
Mandel_add_renderer("Mandelbrot derbail5", calc_mandle_derbail5, 101);
Mandel_add_renderer("MandelWrong 18", calc_mandle_wrong18, 100);
Mandel_add_renderer("MandelWrong 17", calc_mandle_wrong17, 100);
Mandel_add_renderer("MandelWrong 16", calc_mandle_wrong16, 100);
Mandel_add_renderer("MandelWrong 15", calc_mandle_wrong15, 100);
Mandel_add_renderer("MandelWrong 14", calc_mandle_wrong14, 100);
Mandel_add_renderer("MandelWrong 13", calc_mandle_wrong13, 100);
Mandel_add_renderer("MandelWrong 12", calc_mandle_wrong12, 100);
Mandel_add_renderer("MandelWrong 11", calc_mandle_wrong11, 100);
Mandel_add_renderer("MandelWrong 10", calc_mandle_wrong10, 100);
Mandel_add_renderer("MandelWrong 9", calc_mandle_wrong9, 100);
Mandel_add_renderer("MandelWrong 8", calc_mandle_wrong8, 100);
Mandel_add_renderer("MandelWrong 7", calc_mandle_wrong7, 100);
Mandel_add_renderer("MandelWrong 6", calc_mandle_wrong6, 100);
Mandel_add_renderer("MandelWrong 5", calc_mandle_wrong5, 100);
Mandel_add_renderer("MandelWrong 4", calc_mandle_wrong4, 100);
Mandel_add_renderer("MandelWrong 3", calc_mandle_wrong3, 100);
Mandel_add_renderer("MandelWrong 2", calc_mandle_wrong2, 100);
Mandel_add_renderer("MandelWrong 1", calc_mandle_wrong, 100);
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
void JSet_zoomconst(double xx, double yy) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("CxBox");
    string ycoord = manwind->eval_edit("CyBox");
    double x = strtodbl(xcoord);
    double y = strtodbl(ycoord);
    x +=xx;
    y += yy;
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
    string numb = manwind->eval_edit("imgfilenumBox");
    int number = ctoint(numb);

    string bullshitholder = getUniqFname(manwind->eval_edit("savefilename"), number , ".bmp");
    numb = ctostr(number + 1);
    manwind->set_editctrl_text("imgfilenumBox", numb);
    WindowMan.fromName("mandelbrot")->mygfx.save_image(bullshitholder);
}

void jpgsavebutt(void* a) {
    G_Mandel_gstatus = "Saving Jpg";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string numb = manwind->eval_edit("imgfilenumBox");
    int number = ctoint(numb);

    string bullshitholder = getUniqFname(manwind->eval_edit("savefilename"), number, ".jpg");
    numb = ctostr(number + 1);
    manwind->set_editctrl_text("imgfilenumBox", numb);
    gdiSaveHbitmap(WindowMan.fromName("mandelbrot")->mygfx.hbmp, bullshitholder,"jpg");
    G_Mandel_gstatus = "Done saving Jpg";

    //const TCHAR* temp = bullshitholder.c_str();
    //newImage->Save(, CXIMAGE_FORMAT_JPG);
}
void pngsavebutt(void* a) {
    G_Mandel_gstatus = "Saving Png";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    //string numb = manwind->eval_edit("imgfilenumBox");
    //string bullshitholder = manwind->eval_edit("savefilename") + numb + ".png";
    //numb = ctostr(ctoint(numb) + 1);
    string numb = manwind->eval_edit("imgfilenumBox");
    int number = ctoint(numb);

    string bullshitholder = getUniqFname(manwind->eval_edit("savefilename"), number, ".png");
    numb = ctostr(number + 1);
    manwind->set_editctrl_text("imgfilenumBox", numb);
    gdiSaveHbitmap(WindowMan.fromName("mandelbrot")->mygfx.hbmp, bullshitholder, "png");
    G_Mandel_gstatus = "Done saving Png";
    //const TCHAR* temp = bullshitholder.c_str();
    //newImage->Save(, CXIMAGE_FORMAT_JPG);
}
void JsetconstZoomLoopBut(void* a) {
    unsigned long long militimeb = chrono_milli(), militime;
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string cxcoord = manwind->eval_edit("cx_constBox");
    string cycoord = manwind->eval_edit("cy_constBox");
    double cx = strtodbl(cxcoord);
    double cy = strtodbl(cycoord);

    ValControl* Vstop = manwind->GetControl("stopRenderLoopCHK");
    int type = VC_CHECKBOX;
    string loopc = manwind->eval_edit("loopscountedit");
    G_Mandel_gstatus = "initiating CxCyZoom loop x" + loopc;
    int top = ctoint(loopc);
    for (int i = 0; i < top; i++) {
        if (manwind->evaluate_controlb("stopRenderLoopCHK", type)) {
            Vstop->clicked(1, 1);
            return;
        }
        JSet_zoomconst(cx, cy);
        render_button(NULL);
        militime = chrono_milli() - militimeb;
        G_Mandel_loopstat = "Loops:" + ctostr(i) + "  time total:" + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
    }
    G_Mandel_gstatus = "Loop render complete";
}
void JsettargetZoomLoopBut(void* a) {
    unsigned long long militimeb = chrono_milli(), militime;
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string cxcoord = manwind->eval_edit("cx_constBox");
    string cycoord = manwind->eval_edit("cy_constBox");
    string xcoord = manwind->eval_edit("CxBox");
    string ycoord = manwind->eval_edit("CyBox");
    string loopc = manwind->eval_edit("loopscountedit");
    int top = ctoint(loopc);
    double cx = (strtodbl(cxcoord) - strtodbl(xcoord))/top;
    double cy = (strtodbl(cycoord) - strtodbl(ycoord))/top;

    ValControl* Vstop = manwind->GetControl("stopRenderLoopCHK");
    int type = VC_CHECKBOX;

    G_Mandel_gstatus = "initiating CxCyZoom loop x" + loopc + " steps: " +ctostr(cx)+","+ctostr(cy);
    
    for (int i = 1; i <= top; i++) {
        if (manwind->evaluate_controlb("stopRenderLoopCHK", type)) {
            Vstop->clicked(1, 1);
            return;
        }
        JSet_zoomconst(cx, cy);
        render_button(NULL);
        militime = chrono_milli() - militimeb;
        G_Mandel_loopstat = "Loops:" + ctostr(i) + "  time total|left:" + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + " | "+ctostr(((militime / i) * (top - i))/1000)+" seconds";
        cout << "time left: " << (militime / i) * (top - i) << "\n";
    }
    G_Mandel_gstatus = "Loop render complete";
}

void JsetrenderZoomLoopBut(void* a) {
    unsigned long long militimeb = chrono_milli(), militime;
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
        militime = chrono_milli() - militimeb;
        G_Mandel_loopstat = "Loops:" + ctostr(i) + "  time total:" + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
    }
    manwind->set_editctrl_text("x_coord", xcoord);
    manwind->set_editctrl_text("y_coord", ycoord);
    manwind->set_editctrl_text("h_coord", hcoord);
    manwind->set_editctrl_text("w_coord", wcoord);
    G_Mandel_gstatus = "Loop render complete";
}

void renderZoomLoopBut(void* a) {
    unsigned long long militimeb = chrono_milli(), militime;
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
        militime = chrono_milli() - militimeb;
        G_Mandel_loopstat = "Loops:" + ctostr(i) + "  time total:" + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
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
    unsigned long long militimeb = chrono_milli(),militime;

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
        
        militime = chrono_milli() - militimeb;
        G_Mandel_loopstat = "Loops:" + ctostr(i)+"  time total:"+ ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
        //cout << "render count :" << i << "\n";
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
    if (G_Mandel_colorizer_type == 4) {
        cout << "switched to linear coloring \n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to steep coloring");
        G_Mandel_color_LinearCats = !G_Mandel_color_LinearCats;
        G_Mandel_colorizer_type = 0;
    }
    else if (G_Mandel_colorizer_type==3) {
        cout << "switched to random pallet coloring \n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to linear coloring");
        G_Mandel_color_LinearCats = !G_Mandel_color_LinearCats;
        G_Mandel_colorizer_type = 4;
    }
    else if (G_Mandel_colorizer_type == 1) {
        cout << "switched to greyscale coloring \n";
        manwind->GetControl("ColoringTypeBut")->setlabel("switch to random pallet coloring");
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
unsigned long long int G_Mandel_lastmousecaprender = 0;
void Mandel_mousecapture_process(void* vwind) {
    ValWindow* wind = (ValWindow*)vwind;
    if (G_Mandel_lastmousecaprender - chrono_milli() < 30  && wind->mouse_cap->type != VW_MOUSECAP_CLICK) {
        return;
    }
    G_Mandel_lastmousecaprender = chrono_milli();

    string type;
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    int x = wind->mouse_cap->x;
    int y = wind->mouse_cap->y;

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
    if (wind->mouse_cap->type == VW_MOUSECAP_CLICK) {
        G_Mandel_Mousedown = false;box_dims_highlow(G_Mandel_mousecap_ldown_x, G_Mandel_mousecap_ldown_y, x, y);
        manwind->set_editctrl_text("capx_coordbox", ctostr(xxx + (G_Mandel_mousecap_ldown_x * x_jump)));
        manwind->set_editctrl_text("capy_coordbox", ctostr(yyy + (G_Mandel_mousecap_ldown_y * y_jump)));
        
        manwind->set_editctrl_text("capw_coordbox", ctostr((vabs(x-G_Mandel_mousecap_ldown_x ) * x_jump)));
        manwind->set_editctrl_text("caph_coordbox", ctostr((vabs(y-G_Mandel_mousecap_ldown_y ) * y_jump)));

    }
    string rendtype;
    double* trackbuf,*tb,xh,yh;
    int its;
    int mypos = 0;
    double bail = strtodbl(manwind->eval_edit("bailoutBox"));
    
    switch (wind->mouse_cap->type) {
    case VW_MOUSECAP_MOVE:

        rendtype = manwind->GetControl("RenderTypeListbox")->sval;
        if (rendtype.find("orbit") != string::npos){//rendtype == "BBrot mouse orbit") {
            rendtype += "_MPROC";
            foreach(n, G_mandel_renderers_count) {
                if (G_mandel_renderers[n].name == rendtype) {
                    mypos = n;
                    break;
                }
            }
            if (mypos != 0) {
                wind->mygfx.CopyToGFX(wind->mygfxforg, 0, 0);
                trackbuf = new double[512];
                xh = (x * x_jump) + xxx;
                yh = (y * y_jump) + yyy;
                its = ((int(__cdecl*)(double, double, int, double, double*))(G_mandel_renderers[mypos].func)) (xh, yh, 256, 4.0, trackbuf);//
                //its = calc_mandle_buddah(xh, yh, 256, 4.0, trackbuf);
                tb = trackbuf;
                foreach(n, its) {
                    xh = *tb;
                    yh = *(tb + 1); tb += 2;
                    xh = ((xh - xxx) / x_jump);
                    yh = ((yh - yyy) / y_jump);
                    if (xh < 5 || xh>1995 || yh < 5 || yh>1995)continue;
                    wind->mygfxforg.draw_box2(xh - 2, yh - 2, xh + 2, yh + 2, 1, 1, VRGB_WHITE);
                }
                wind->mygfxforg.blt(GetDC(wind->myhwnd), 0, 0);

                delete[] trackbuf;
            }
            else {
                cout << "orbit analyzer failed\n";
            }
                //wind->GFXdraw();
            
        }
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
    if (i < 0 || i > 100) return;
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

void Mandel_getactives(double& x, double& y, double& w, double& h, double& cx, double& cy, double& bail, int& its, ValWindow*& manwind) {
    manwind = WindowMan.fromName("mandelbrot controller");
    string xcoord = manwind->eval_edit("x_coord");
    string ycoord = manwind->eval_edit("y_coord");
    string wcoord = manwind->eval_edit("w_coord");
    string hcoord = manwind->eval_edit("h_coord");
    string cxcoord = manwind->eval_edit("CxBox");
    string cycoord = manwind->eval_edit("CyBox");
    string itts = manwind->eval_edit("itterations");
    string bailout = manwind->eval_edit("bailoutBox");
    x = strtodbl(xcoord);
    y = strtodbl(ycoord);
    w = strtodbl(wcoord);
    h = strtodbl(hcoord);
    its = ctoint(itts);    
    cx = strtodbl(cxcoord);
    cy = strtodbl(cycoord);
    bail = strtodbl(bailout);
}
void Mandel_drawshape() {
    double x, y, w, h, cx, cy, bail;
    int its;
    ValWindow* manwind;
    Mandel_getactives(x, y, w, h, cx, cy, bail, its, manwind);
    ValWindow* diswind = WindowMan.fromName("mandelbrot");
}
void mandel_recolorbut() {
    G_Mandel_recolor_flag = true;
    render_button(NULL);
    G_Mandel_recolor_flag = false;
}

string ANDRO_Getrecallstr() {
    int plc = 0;
    string ret = "";
    foreach(n, G_Mandel_ANDRO_factorslistlen) {
        plc = n * 3;
        ret += ctostr(G_Mandel_ANDRO_factorslist[plc]);
        ret += "|";
        ret += ctostr(G_Mandel_ANDRO_factorslist[plc+1]);
        ret += "|";
        ret += ctostr(G_Mandel_ANDRO_factorslist[plc+2]);
        if(n!= G_Mandel_ANDRO_factorslistlen - 1)ret += "|";
    }
    return ret;
}
string ANDRO_Fromrecallstr(string recall) {
    string token;
    char op;
    int a, b, c;    
    G_Mandel_ANDRO_factorslistlen = 0;
    G_Mandel_ANDRO_rootslistlen = 0;
    while (recall != "") {
        token = tokenize(recall, "|", op);
        if (token == "")break;
        a = ctoint(token);
        token = tokenize(recall, "|", op);
        if (token == "")break;
        b = ctoint(token);
        token = tokenize(recall, "|", op);
        if (token == "")break;
        c = ctoint(token);
        ANDRO_factorlist_alter(a, b, c != 0, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
    }
    G_Mandel_ANDRO_FactorStr = ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}

void append_qualifier_box_to_string(string& str, ValWindow* manwind, string boxn) {
    str += boxn+ "$"+ manwind->eval_edit(boxn)+"!";
}
strlist G_Mandel_savestatenames;
string Mandel_savestate() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string name = manwind->eval_edit("statenamebox");
    
    manwind->GetControl("SaveStateNamesListbox")->needs_redraw = true;
    manwind->GetControl("SaveStateNamesListbox")->needs_repaint = true;
    string ret = name+"=";
    ret += "renderer$" + manwind->GetControl("RenderTypeListbox")->sval + "!";
    append_qualifier_box_to_string(ret, manwind,"x_coord" );
    append_qualifier_box_to_string(ret, manwind,"y_coord" );
    append_qualifier_box_to_string(ret, manwind, "w_coord");
    append_qualifier_box_to_string(ret, manwind,"h_coord" );
    append_qualifier_box_to_string(ret, manwind,"CxBox" );
    append_qualifier_box_to_string(ret, manwind,"CyBox" );
    append_qualifier_box_to_string(ret, manwind,"itterations" );
    append_qualifier_box_to_string(ret, manwind,"bailoutBox" );
    append_qualifier_box_to_string(ret, manwind, "bbrot_samplesEdit");
    append_qualifier_box_to_string(ret, manwind, "x_coordboodah");
    append_qualifier_box_to_string(ret, manwind, "y_coordboodah");
    append_qualifier_box_to_string(ret, manwind, "w_coordboodah");
    append_qualifier_box_to_string(ret, manwind, "h_coordboodah");
    append_qualifier_box_to_string(ret, manwind, "RandSeedBox");
    append_qualifier_box_to_string(ret, manwind, "RelaxBox");
    
    string Andro = ANDRO_Getrecallstr();
    ret += "ANDRO$" + Andro + "!";
    return ret;
}

void Mandel_loadstate(string state,ValWindow* manwind) {
    string token;
    char op;
    string name, val;
    while (state != "") {
        token=tokenize(state, "!", op);
        name = tokenize(token, "$", op);
        val = token;
        cout << "setting name=val : " << name << "=" << val << "\n";
        if (name == "renderer")listbox_selectstring(manwind->GetControl("RenderTypeListbox"), val);
        else if (name == "")continue;
        else if (name != "ANDRO")manwind->set_editctrl_text(name, val);
        else ANDRO_Fromrecallstr(token);
    }
}
string G_Mandel_states_loadedFile = "";
void Mandel_loadstatesbut() {
    cout << "load states but hit\n";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    ValControl* vc = manwind->GetControl("SaveStateNamesListbox");
    G_Mandel_savestatenames.clear();
    cout << "statefile started\n";
    string fname = manwind->eval_edit("savestatenameBox");
    G_Mandel_states_loadedFile = fname;
    string file = file_contents(fname);
    //cout << "file contents: " << file << "\n";
    string token;
    string name;
    char op;
    while (file != "") {
        token = tokenize(file, "\n", op);
        name = tokenize(token, "=", op);
        //cout << "found name: " << name << endl;
        if (name == "")continue;
        G_Mandel_savestatenames.stack(name);
    }

    vc->drawtogfx();
    vc->needs_redraw = true;

}
void Mandel_loadstatebut() {
    cout << "load state but hit\n";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string fname = manwind->eval_edit("savestatenameBox");
    if (fname != G_Mandel_states_loadedFile)Mandel_loadstatesbut();
    string file = file_contents(fname);
    string sname = manwind->eval_edit("statenamebox");
    string token;
    string name;
    char op;
    while (file != "") {
        token = tokenize(file, "\n", op);
        name = tokenize(token, "=", op);
        if (name == sname)Mandel_loadstate(token, manwind);
    }
}

void Mandel_savestatebut() {
    cout << "save state but hit\n";
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string fname = manwind->eval_edit("savestatenameBox");
    if (fname != G_Mandel_states_loadedFile)Mandel_loadstatesbut();
    string sname = manwind->eval_edit("statenamebox");
    string srch = sname;
    int plc = 0;
    while (G_Mandel_savestatenames.isset(srch))srch = sname + ctostr(++plc);
    manwind->set_editctrl_text("statenamebox", srch);
    appendfile(fname, Mandel_savestate() + "\n");
    G_Mandel_savestatenames.stack(sname);
    

}



void Mandel_GeneratePallet() {
    double x, y, w, h, cx, cy, bail;
    int its;
    ValWindow* manwind;
    Mandel_getactives(x, y, w, h, cx, cy, bail, its, manwind);
    
    
    Linear_colorEx_fromstr(manwind->eval_edit("RandSeedBox"), ctoint(manwind->eval_edit("RandSeedcatsBox")));
    if(G_Mandel_colorizer_type==4)mandel_recolorbut();
    //int col;
    //manwind = WindowMan.fromName("mandelbrot");
    //manwind->mygfx.makewhite();
    //for (int i = 0; i < manwind->clientheight; i++) {
    //    col =linear_colorEx(i, manwind->clientheight);
    //   // cout << col << "\n";
    //    manwind->mygfx.drawline2(0, i, manwind->clientwidth - 1, true, 1, col);

    //}
    //manwind->GFXdraw();
}
int G_Mandel_builtpalletswitch = 0;
void Mandel_test() {
    G_Mandel_builtpalletswitch++;
    if(G_Mandel_builtpalletswitch > 2) G_Mandel_builtpalletswitch = 0;
    G_Mandel_colorizer_ex_num_catagories = 0;
    switch (G_Mandel_builtpalletswitch) {
    case 0:
        Linear_colorEx_addCatagory(192, 0, 0, 192, 0, 0);
        Linear_colorEx_addCatagory(0, 128, 192, 0, 0, 128);
        Linear_colorEx_addCatagory(64, 256, 0, 256, 128, 256);

        cout << "catagory 0\n";
    break;
    case 1:
        Linear_colorEx_addCatagory(64, 256, 0, 256, 128, 256);
        Linear_colorEx_addCatagory(0, 64, 192, 0, 0, 128);
        Linear_colorEx_addCatagory(192, 0, 0, 192, 0, 0);
        cout << "catagory 1\n";
        break;

    case 2:
        Linear_colorEx_addCatagoryb(0, 0, 0, 255, 0, 0);
        Linear_colorEx_addCatagoryb( 255, 0, 0,192,128,0);
        Linear_colorEx_addCatagoryb(192, 128, 0,255,255,0);
        Linear_colorEx_addCatagoryb(255, 255, 0,128,192,0);
        Linear_colorEx_addCatagoryb(128, 192, 0,0,255,0);
        Linear_colorEx_addCatagoryb(0, 255, 0,0,192,128);
        Linear_colorEx_addCatagoryb( 0, 192, 128,0,192,192);
        Linear_colorEx_addCatagoryb(0, 192, 192,0,128,192);
        Linear_colorEx_addCatagoryb(0, 128, 192,0,64,192);
        Linear_colorEx_addCatagoryb( 0, 64, 192,0,0,255);
        Linear_colorEx_addCatagoryb( 0, 0, 255,64,0,192);
        Linear_colorEx_addCatagoryb(64, 0, 192,128,0,192);
        Linear_colorEx_addCatagoryb(128, 0, 192,192,0,192);
        Linear_colorEx_addCatagoryb( 192, 0, 192,255,0,255);
        Linear_colorEx_addCatagoryb(255, 0, 255,255, 255, 255);
        cout << "catagory 2\n";
        break;

    }


}
void beta_testfunc() {
    Mandel_test();

}
void Mandel_filter_renderers() {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    G_Mandel_rendertypes.clear();

    string filter = manwind->eval_edit("FilterBox");
    foreach(n, G_Mandel_rendertypes_master.length()) {
        if (G_Mandel_rendertypes_master.index(n).find(filter) != string::npos) {
            G_Mandel_rendertypes.stack(G_Mandel_rendertypes_master.index(n));
        }
    }
    ValControl* vc = manwind->GetControl("RenderTypeListbox");
    vc->LISTDATA_OFFSET = 0;
    vc->value[0] = 0;
    vc->drawtogfx();
    vc->needs_repaint = true;
    vc->needs_redraw = true;
}


void Mandel_savestatelist_proc(void* a) {
    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    ValControl* vc = manwind->GetControl("SaveStateNamesListbox");
    if (vc->sval == "")return;
    manwind->set_editctrl_text("statenamebox", vc->sval);
    Mandel_loadstatebut();

}

void Mandel_copydimstoBBrotSearch() {

    ValWindow* manwind = WindowMan.fromName("mandelbrot controller");
    string h = manwind->eval_edit("caph_coordbox");
    manwind->set_editctrl_text("h_coordboodah", h);
    cout << "setting height for boodahsearch " << h << "\n";
    manwind->set_editctrl_text("w_coordboodah", manwind->eval_edit("capw_coordbox"));
    manwind->set_editctrl_text("y_coordboodah", manwind->eval_edit("capy_coordbox"));
    manwind->set_editctrl_text("x_coordboodah", manwind->eval_edit("capx_coordbox"));
}

void do_mandelbrot_thread(void* a) {
    foreach(i, 16) {
        _beginthread(Mandel_workerthread, 0, NULL);
    }
    foreach(i, 2000) {
        foreach(n, 2000) mandel_buffer[i][n] = 0;
    }
    
    populate_mandeldictionary();
    
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
    vw->hide();
    int controllerw = 1400, controllerh = 1200;
    //ValWindow* vwc = WindowMan.create_new_windowex("mandelbrot controller", 100, 800, controllerw,controllerh,1);
    ValWindow* vwc = WindowMan.create_new_windowts("mandelbrot controller", 100, 800, controllerw, controllerh, 1);
    vwc->hide();
    string xcord = "-3";// "-0.5892348415";
    string ycord = "-3";//"-0.570152343242";
    string wcord = "6";//"0.0200000065456001";
    string hcord = "6";//"0.0350000545600000001";
    string itts = "512";
    G_VS_RANDSEED(getticks());
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
    Mandel_fill_rendertypes_default();
    ValWindow* wind = vwc;
    VWM_register_datan(render_button, "render_button");
    VWM_register_datan(zoombutt, "zoombutt");
    VWM_register_datan(unzoombutt, "unzoombutt");
    VWM_register_datan(leftbutt, "leftbutt");
    VWM_register_datan(rightbutt, "rightbutt");

    VWM_register_datan(upbutt, "upbutt");
    VWM_register_datan(downbutt, "downbutt");

    VWM_register_datan(savebutt, "savebutt");
    VWM_register_datan(jpgsavebutt, "jpgsavebutt");
    VWM_register_datan(pngsavebutt, "pngsavebutt");
    VWM_register_datan(renderZoomLoopBut, "RenderZoomLoopBut");
    VWM_register_datan(mandel_switch_coloring_but, "switchcolorsbut");
    VWM_register_datan(&G_Mandel_rendertypes, "MandelRendersList"); 
    VWM_register_datan(&G_Mandel_savestatenames, "G_Mandel_savestatenames");
    VWM_register_datan(mandel_render_colorstack, "colorstackbut");
    VWM_register_datan(JSet_zoombut, "JSet_zoombut");
    VWM_register_datan(JsetrenderZoomLoopBut, "JsetrenderZoomLoopBut");

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
    VWM_register_datan(beta_testfunc, "beta_testfunc"); 
    VWM_register_datan(Mandel_GeneratePallet, "Mandel_GeneratePallet");
    VWM_register_datan(mandel_recolorbut, "mandel_recolorbut"); 
    VWM_register_datan(Mandel_loadstatebut, "Mandel_loadstatebut");
    VWM_register_datan(Mandel_savestatebut, "Mandel_savestatebut"); 
    VWM_register_datan(Mandel_savestatelist_proc, "Mandel_savestatelist_proc"); 
    VWM_register_datan(Mandel_loadstatesbut, "Mandel_loadstatesbut"); 
    VWM_register_datan(Mandel_filter_renderers, "Mandel_filter_renderers"); 
    VWM_register_datan(Mandel_copydimstoBBrotSearch, "Mandel_copydimstoBBrotSearch"); 
    VWM_register_datan(JsetconstZoomLoopBut, "JsetconstZoomLoopBut"); 
    VWM_register_datan(JsettargetZoomLoopBut, "JsettargetZoomLoopBut");

    //VWM_register_datan();
    string G_Mandel_gstatus = "", G_Mandel_loopstat = "";


//
//wind->AddControl("title=zoom_button,type=VC_BUTTON,text=+zoom,x=319,y=421,w=82,h=25,dataname=zoombutt,needsparent=true");
//wind->AddControl("title=zoom_factor,type=VC_EDIT,text=-.5,x=388,y=450,w=100,h=25,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=zoom_label,type=VC_LABEL,text=zoom: ,x=319,y=450,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=move_factor,type=VC_EDIT,text=.05,x=378,y=108,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=move_label,type=VC_LABEL,text=move %: ,x=316,y=108,w=60,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=left_button,type=VC_BUTTON,text=left,x=322,y=59,w=35,h=25,dataname=leftbutt,needsparent=true");
//wind->AddControl("title=right_button,type=VC_BUTTON,text=right,x=412,y=58,w=35,h=25,dataname=rightbutt,needsparent=true");
//wind->AddControl("title=up_button,type=VC_BUTTON,text=up,x=367,y=34,w=35,h=25,dataname=upbutt,needsparent=true");
//wind->AddControl("title=down_button,type=VC_BUTTON,text=down,x=367,y=76,w=35,h=25,dataname=downbutt,needsparent=true");
//wind->AddControl("title=x_coord,type=VC_EDIT,text=-3,x=98,y=25,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=y_coord");
//wind->AddControl("title=xcordlabel,type=VC_LABEL,text=X: ,x=46,y=25,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=y_coord,type=VC_EDIT,text=-3,x=98,y=55,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=w_coord");
//wind->AddControl("title=ycordlabel,type=VC_LABEL,text=y: ,x=48,y=55,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=w_coord,type=VC_EDIT,text=6,x=98,y=85,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=h_coord");
//wind->AddControl("title=wcordlabel,type=VC_LABEL,text=Width: ,x=33,y=85,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=h_coord,type=VC_EDIT,text=6,x=98,y=115,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=itterations");
//wind->AddControl("title=hcordlabel,type=VC_LABEL,text=Height: ,x=33,y=115,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=itterations,type=VC_EDIT,text=512,x=98,y=145,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=x_coord");
//wind->AddControl("title=itts_label,type=VC_LABEL,text=itterations: ,x=33,y=145,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=savefilename,type=VC_EDIT,text=Mandelbrot,x=610,y=1000,w=300,h=25,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=savelabel2,type=VC_LABEL,text=,x=370,y=715,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=savelabel,type=VC_LABEL,text=save file: ,x=520,y=1000,w=80,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=save_button,type=VC_BUTTON,text=bmp save,x=612,y=1030,w=70,h=25,dataname=savebutt,needsparent=true");
//wind->AddControl("title=stopRenderLoopCHK,type=VC_CHECKBOX,text=Stop Render Loop,x=314,y=621,w=175,h=30");
//wind->AddControl("title=RenderLoopbut,type=VC_BUTTON,text=testColorizer,x=157,y=291,w=140,h=22,dataname=colorstackbut");
//wind->AddControl("title=RenderZoomLoopbut,type=VC_BUTTON,text=Render/Zoom Loop,x=319,y=480,w=170,h=25,dataname=RenderZoomLoopBut");
//wind->AddControl("title=ColoringTypeBut,type=VC_BUTTON,text=switch to steep coloring,x=39,y=182,w=259,h=24,dataname=switchcolorsbut");
//wind->AddControl("title=CXLabel,type=VC_LABEL,text=JSet Cx,x=489,y=30,w=60,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=CyLabel,type=VC_LABEL,text=JSet Cy,x=490,y=60,w=60,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=CxBox,type=VC_EDIT,text=.3,x=556,y=31,w=213,h=21,numblurs=0,transparent=true,nointeract=true,tabname=CyBox");
//wind->AddControl("title=CyBox,type=VC_EDIT,text=.37,x=556,y=61,w=213,h=21,numblurs=0,transparent=true,nointeract=true,tabname=CxBox");
//wind->AddControl("title=UnZoomBut,type=VC_BUTTON,text=-zoom,x=406,y=420,w=82,h=25,dataname=unzoombutt");
//wind->AddControl("title=JSet_zoombut,type=VC_BUTTON,text=JSet 'zoom',x=319,y=508,w=170,h=25,dataname=JSet_zoombut,textfont=CONSOLAS");
//wind->AddControl("title=jset_zloopbut,type=VC_BUTTON,text=JSet 'zoomloop',x=319,y=535,w=170,h=25,dataname=JsetrenderZoomLoopBut");
//wind->AddControl("title=JpgSaveBut,type=VC_BUTTON,text=Jpg Save,x=695,y=1031,w=70,h=23,dataname=jpgsavebutt");
//wind->AddControl("title=bailoutLabel,type=VC_LABEL,text=Bailout:,x=489,y=90,w=60,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=bailoutBox,type=VC_EDIT,text=4,x=556,y=91,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=status_stat,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=10,y=-20,w=400,h=18,dataname=G_Mandel_gstatus");
//wind->AddControl("title=Loop_stat,type=VC_GLOBAL_STAT_STRING,text=Loop status:*S,x=10,y=-40,w=400,h=18,dataname=G_Mandel_loopstat");
//wind->AddControl("title=capx_coordbox,type=VC_EDIT,text=,x=315,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capy_coordbox");
//wind->AddControl("title=capy_coordbox,type=VC_EDIT,text=,x=315,y=193,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capw_coordbox");
//wind->AddControl("title=capw_coordbox,type=VC_EDIT,text=,x=315,y=216,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=caph_coordbox");
//wind->AddControl("title=caph_coordbox,type=VC_EDIT,text=,x=315,y=239,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capx_coordbox");
//wind->AddControl("title=CopyDimsBut,type=VC_BUTTON,text=<--Copy to Dims ,x=315,y=266,w=170,h=25,dataname=Mandel_copydims_but");
//wind->AddControl("title=mousecap_label,type=VC_LABEL,text=Highlighted section:,x=315,y=144,w=237,h=19,numblurs=1,transparent=true");
//wind->AddControl("title=DimsCopyotherBut,type=VC_BUTTON,text=<--Copy to Dims ,x=599,y=266,w=170,h=25,dataname=Mandel_copydimsother_but");
//wind->AddControl("title=copyx_coordbox,type=VC_EDIT,text=-3,x=599,y=170,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyy_coordbox");
//wind->AddControl("title=copyy_coordbox,type=VC_EDIT,text=-3,x=599,y=193,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyw_coordbox");
//wind->AddControl("title=copyw_coordbox,type=VC_EDIT,text=6,x=599,y=216,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyh_coordbox");
//wind->AddControl("title=copyh_coordbox,type=VC_EDIT,text=6,x=599,y=239,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyx_coordbox");
//wind->AddControl("title=render_button,type=VC_BUTTON,text=Render,x=218,y=361,w=80,h=400,dataname=render_button,needsparent=true");
//wind->AddControl("title=threadsLabel,type=VC_LABEL,text=Threads:,x=16,y=266,w=61,h=19,numblurs=1,transparent=true");
//wind->AddControl("title=threadsBox,type=VC_EDIT,text=10,x=98,y=266,w=30,h=20,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=Thread_stat,type=VC_GLOBAL_STAT_STRING,text=Thread status:*S,x=10,y=-60,w=400,h=18,dataname=G_Mandel_threadstat");
//wind->AddControl("title=RenderTypeListbox,type=VC_LISTBOX,text=nt,x=7,y=317,w=200,h=450,listboxfunc=NOFUNC,dataname=MandelRendersList,numblurs=0");
//wind->AddControl("title=rendertypeslabel,type=VC_LABEL,text=Render Types:,x=7,y=295,w=105,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=do_wrong_mand,type=VC_CHECKBOX,text=OverRender Mode,x=144,y=266,w=153,h=20");
//wind->AddControl("title=ANDRO_SStat,type=VC_LABEL,text=Arbitrary Newton Function:,x=8,y=839,w=444,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=ANDRO_fact_qbox,type=VC_EDIT,text=1,x=111,y=882,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=ANDRO_fact_pbox,type=VC_EDIT,text=4,x=111,y=908,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=ANDRO_fact_plusbut,type=VC_BUTTON,text=add,x=12,y=933,w=80,h=18,dataname=Mandel_addfactor_but");
//wind->AddControl("title=ANDRO_fact_minbut,type=VC_BUTTON,text=sub,x=98,y=934,w=80,h=18,dataname=Mandel_subfactor_but");
//wind->AddControl("title=ANDRO_fact_rembut,type=VC_BUTTON,text=rem,x=183,y=934,w=80,h=18,dataname=Mandel_remExp_but");
//wind->AddControl("title=ANDRO_Q_label,type=VC_LABEL,text=qz^p    q:,x=7,y=882,w=89,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=ANDRO_P_label,type=VC_LABEL,text=         P:,x=7,y=908,w=89,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=ANDRO_fact_clrbut,type=VC_BUTTON,text=clear,x=268,y=934,w=80,h=18,dataname=Mandel_fact_clrbut");
//wind->AddControl("title=ANDRO_stat,type=VC_GLOBAL_STAT_STRING,text=function:*S,x=8,y=862,w=469,h=18,dataname=G_Mandel_ANDRO_FactorStr");
//wind->AddControl("title=loopscountlabel,type=VC_LABEL,text=loops:,x=318,y=592,w=62,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=loopscountedit,type=VC_EDIT,text=100,x=398,y=592,w=91,h=21,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=bbrot_samplesLabel,type=VC_LABEL,text=Buddah Samples:thread,x=490,y=146,w=180,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=bbrot_samplesEdit,type=VC_EDIT,text=500,x=689,y=145,w=80,h=21,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=progressSlider,type=VC_SLIDER,text=Progress:100,x=11,y=956,w=979,h=39,numblurs=0,textfont=Modern,nointeract=true");
//wind->AddControl("title=BBrotloopBut,type=VC_BUTTON,text=BBrot Loop,x=319,y=563,w=170,h=25,dataname=renderbbrotLoopBut");
//wind->AddControl("title=imgfilenumBox,type=VC_EDIT,text=1,x=913,y=1000,w=74,h=23,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=pngsaveBut,type=VC_BUTTON,text=Png Save,x=772,y=1031,w=73,h=22,dataname=pngsavebutt");
//wind->AddControl("title=x_coordboodah,type=VC_EDIT,text=-3,x=559,y=345,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=y_coordboodah");
//wind->AddControl("title=xcordlabelboodah,type=VC_LABEL,text=X: ,x=529,y=345,w=25,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=y_coordboodah,type=VC_EDIT,text=-3,x=559,y=375,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=w_coordboodah");
//wind->AddControl("title=ycordlabelboodah,type=VC_LABEL,text=y: ,x=529,y=375,w=25,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=w_coordboodah,type=VC_EDIT,text=6,x=559,y=405,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=h_coordboodah");
//wind->AddControl("title=wcordlabelboodah,type=VC_LABEL,text=Width: ,x=506,y=405,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=h_coordboodah,type=VC_EDIT,text=6,x=559,y=435,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=x_coordboodah");
//wind->AddControl("title=hcordlabelboodah,type=VC_LABEL,text=Height: ,x=506,y=435,w=50,h=25,numblurs=1,transparent=true");
//wind->AddControl("title=bbrot_samplesLabelboodah,type=VC_LABEL,text=Buddahbrot search dims,x=515,y=321,w=180,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=UseBoodahDimsChk,type=VC_CHECKBOX,text=use,x=700,y=321,w=60,h=20");
//wind->AddControl("title=betatestbut,type=VC_BUTTON,text=betafunction,x=847,y=892,w=131,h=48,dataname=beta_testfunc");
//wind->AddControl("title=RandSeedBox,type=VC_EDIT,text=RandomSeed,x=99,y=214,w=200,h=20,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=RandSeedcatsBox,type=VC_EDIT,text=20,x=99,y=238,w=50,h=21,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=RandSeedLBL,type=VC_LABEL,text=RandSeed,x=27,y=214,w=67,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=RandSeedcatsLBL,type=VC_LABEL,text=colors(<50),x=14,y=240,w=83,h=22,numblurs=1,transparent=true,nointeract=true");
//wind->AddControl("title=ReColorBtn,type=VC_BUTTON,text=Recolor,x=218,y=320,w=80,h=32,dataname=mandel_recolorbut");
//wind->AddControl("title=savestatenameBox,type=VC_EDIT,text=StateSaves.txt,x=783,y=699,w=200,h=22,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=statenamebox,type=VC_EDIT,text=bbbrot3,x=783,y=749,w=200,h=25,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=LoadstatefileBut,type=VC_BUTTON,text=Load State file,x=783,y=724,w=200,h=22,dataname=Mandel_loadstatesbut");
//wind->AddControl("title=savestateBut,type=VC_BUTTON,text=save state,x=783,y=777,w=95,h=22,dataname=Mandel_savestatebut");
//wind->AddControl("title=loadstateBut,type=VC_BUTTON,text=load state,x=887,y=777,w=95,h=22,dataname=Mandel_loadstatebut");
//wind->AddControl("title=SaveStateNamesListbox,type=VC_LISTBOX,text=savestates,x=783,y=30,w=200,h=665,listboxfunc=Mandel_savestatelist_proc,dataname=G_Mandel_savestatenames,numblurs=0");
//wind->AddControl("title=RandomPalletBut,type=VC_BUTTON,text=generate pallet,x=158,y=239,w=140,h=20,dataname=Mandel_GeneratePallet");
//wind->AddControl("title=FilterBox,type=VC_EDIT,text=,x=12,y=775,w=179,h=20,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=FilterBtn,type=VC_BUTTON,text=filter,x=208,y=775,w=88,h=20,dataname=Mandel_filter_renderers");
//wind->AddControl("title=RelaxBox,type=VC_EDIT,text=1,x=557,y=121,w=213,h=21,numblurs=0,transparent=true,nointeract=true");
//wind->AddControl("title=RelaxLbl,type=VC_LABEL,text=relax:,x=492,y=123,w=60,h=22,numblurs=1,transparent=true");
//wind->AddControl("title=xcordlabelshared,type=VC_LABEL,text=:<-X->:,x=513,y=170,w=65,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=ycordlabelshared,type=VC_LABEL,text=:<-Y->:,x=513,y=194,w=65,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=wcordlabelshared,type=VC_LABEL,text=:<-Width->:,x=497,y=217,w=90,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=hcordlabelshared,type=VC_LABEL,text=:<-Height->:,x=493,y=241,w=100,h=20,numblurs=1,transparent=true");
//wind->AddControl("title=copytoBBSearchBut,type=VC_BUTTON,text=to BBrot Dims-->,x=316,y=294,w=170,h=25,dataname=Mandel_copydimstoBBrotSearch");
//
wind->AddControl("title=zoom_button,type=VC_BUTTON,text=+zoom,x=304,y=265,w=82,h=25,dataname=zoombutt,needsparent=true");
wind->AddControl("title=zoom_factor,type=VC_EDIT,text=-.5,x=378,y=293,w=100,h=25,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=zoom_label,type=VC_LABEL,text=zoom: ,x=309,y=293,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=move_factor,type=VC_EDIT,text=.05,x=397,y=238,w=80,h=25,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=move_label,type=VC_LABEL,text=move %: ,x=316,y=238,w=60,h=25,numblurs=1,transparent=true");
wind->AddControl("title=left_button,type=VC_BUTTON,text=left,x=329,y=193,w=35,h=25,dataname=leftbutt,needsparent=true");
wind->AddControl("title=right_button,type=VC_BUTTON,text=right,x=405,y=193,w=35,h=25,dataname=rightbutt,needsparent=true");
wind->AddControl("title=up_button,type=VC_BUTTON,text=up,x=367,y=179,w=35,h=25,dataname=upbutt,needsparent=true");
wind->AddControl("title=down_button,type=VC_BUTTON,text=down,x=367,y=209,w=35,h=25,dataname=downbutt,needsparent=true");
wind->AddControl("title=x_coord,type=VC_EDIT,text=-3,x=98,y=27,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coord");
wind->AddControl("title=xcordlabel,type=VC_LABEL,text=X: ,x=46,y=27,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=y_coord,type=VC_EDIT,text=-3,x=98,y=50,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coord");
wind->AddControl("title=ycordlabel,type=VC_LABEL,text=y: ,x=48,y=50,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=w_coord,type=VC_EDIT,text=6,x=98,y=73,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coord");
wind->AddControl("title=wcordlabel,type=VC_LABEL,text=Width: ,x=33,y=73,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=h_coord,type=VC_EDIT,text=6,x=98,y=96,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=itterations");
wind->AddControl("title=hcordlabel,type=VC_LABEL,text=Height: ,x=33,y=96,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=itterations,type=VC_EDIT,text=512,x=98,y=119,w=200,h=25,numblurs=0,transparent=true,nointeract=true,tabname=x_coord");
wind->AddControl("title=itts_label,type=VC_LABEL,text=itterations: ,x=33,y=119,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=savefilename,type=VC_EDIT,text=Mandelbrot,x=650,y=1000,w=300,h=25,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=savelabel2,type=VC_LABEL,text=,x=489,y=715,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=savelabel,type=VC_LABEL,text=save file: ,x=560,y=1000,w=80,h=25,numblurs=1,transparent=true");
wind->AddControl("title=save_button,type=VC_BUTTON,text=bmp save,x=652,y=1030,w=70,h=25,dataname=savebutt,needsparent=true");
wind->AddControl("title=stopRenderLoopCHK,type=VC_CHECKBOX,text=Stop Render Loop,x=484,y=320,w=175,h=30");
wind->AddControl("title=RenderLoopbut,type=VC_BUTTON,text=testColorizer,x=157,y=327,w=140,h=22,dataname=colorstackbut");
wind->AddControl("title=RenderZoomLoopbut,type=VC_BUTTON,text=Render/Zoom Loop,x=489,y=206,w=170,h=25,dataname=RenderZoomLoopBut");
wind->AddControl("title=ColoringTypeBut,type=VC_BUTTON,text=switch to steep coloring,x=39,y=219,w=259,h=24,dataname=switchcolorsbut");
wind->AddControl("title=CXLabel,type=VC_LABEL,text=JSet Cx,x=31,y=144,w=60,h=22,numblurs=1,transparent=true");
wind->AddControl("title=CyLabel,type=VC_LABEL,text=JSet Cy,x=32,y=166,w=60,h=22,numblurs=1,transparent=true");
wind->AddControl("title=CxBox,type=VC_EDIT,text=.3,x=98,y=145,w=200,h=21,numblurs=0,transparent=true,nointeract=true,tabname=CyBox");
wind->AddControl("title=CyBox,type=VC_EDIT,text=.37,x=98,y=167,w=200,h=21,numblurs=0,transparent=true,nointeract=true,tabname=CxBox");
wind->AddControl("title=UnZoomBut,type=VC_BUTTON,text=-zoom,x=396,y=265,w=82,h=25,dataname=unzoombutt");
wind->AddControl("title=JSet_zoombut,type=VC_BUTTON,text=JSet 'zoom',x=308,y=322,w=170,h=25,dataname=JSet_zoombut,textfont=CONSOLAS");
wind->AddControl("title=jset_zloopbut,type=VC_BUTTON,text=JSet 'zoomloop',x=489,y=234,w=170,h=25,dataname=JsetrenderZoomLoopBut");
wind->AddControl("title=JpgSaveBut,type=VC_BUTTON,text=Jpg Save,x=735,y=1031,w=70,h=23,dataname=jpgsavebutt");
wind->AddControl("title=bailoutLabel,type=VC_LABEL,text=Bailout:,x=31,y=187,w=60,h=22,numblurs=1,transparent=true");
wind->AddControl("title=bailoutBox,type=VC_EDIT,text=4,x=98,y=188,w=80,h=21,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=status_stat,type=VC_GLOBAL_STAT_STRING,text=status:*S,x=10,y=-20,w=800,h=18,dataname=G_Mandel_gstatus");
wind->AddControl("title=Loop_stat,type=VC_GLOBAL_STAT_STRING,text=Loop status:*S,x=10,y=-40,w=800,h=18,dataname=G_Mandel_loopstat");
wind->AddControl("title=capx_coordbox,type=VC_EDIT,text=,x=311,y=27,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capy_coordbox");
wind->AddControl("title=capy_coordbox,type=VC_EDIT,text=,x=311,y=50,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capw_coordbox");
wind->AddControl("title=capw_coordbox,type=VC_EDIT,text=,x=311,y=73,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=caph_coordbox");
wind->AddControl("title=caph_coordbox,type=VC_EDIT,text=,x=311,y=96,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=capx_coordbox");
wind->AddControl("title=CopyDimsBut,type=VC_BUTTON,text=<--Copy to Dims ,x=311,y=123,w=170,h=25,dataname=Mandel_copydims_but");
wind->AddControl("title=mousecap_label,type=VC_LABEL,text=Highlighted section:,x=311,y=7,w=237,h=19,numblurs=1,transparent=true");
wind->AddControl("title=DimsCopyotherBut,type=VC_BUTTON,text=<--Copy to Dims ,x=599,y=123,w=170,h=25,dataname=Mandel_copydimsother_but");
wind->AddControl("title=copyx_coordbox,type=VC_EDIT,text=-3,x=599,y=27,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyy_coordbox");
wind->AddControl("title=copyy_coordbox,type=VC_EDIT,text=-3,x=599,y=50,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyw_coordbox");
wind->AddControl("title=copyw_coordbox,type=VC_EDIT,text=6,x=599,y=73,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyh_coordbox");
wind->AddControl("title=copyh_coordbox,type=VC_EDIT,text=6,x=599,y=96,w=170,h=22,numblurs=0,transparent=true,nointeract=true,tabname=copyx_coordbox");
wind->AddControl("title=render_button,type=VC_BUTTON,text=Render,x=301,y=397,w=180,h=405,dataname=render_button,needsparent=true");
wind->AddControl("title=threadsLabel,type=VC_LABEL,text=Threads:,x=16,y=302,w=61,h=19,numblurs=1,transparent=true");
wind->AddControl("title=threadsBox,type=VC_EDIT,text=10,x=98,y=302,w=30,h=20,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=Thread_stat,type=VC_GLOBAL_STAT_STRING,text=Thread status:*S,x=10,y=-60,w=800,h=18,dataname=G_Mandel_threadstat");
wind->AddControl("title=RenderTypeListbox,type=VC_LISTBOX,text=nt,x=16,y=353,w=280,h=450,listboxfunc=NOFUNC,dataname=MandelRendersList,numblurs=0");
wind->AddControl("title=rendertypeslabel,type=VC_LABEL,text=Render Types:,x=7,y=331,w=105,h=22,numblurs=1,transparent=true");
wind->AddControl("title=do_wrong_mand,type=VC_CHECKBOX,text=OverRender Mode,x=144,y=302,w=153,h=20");
wind->AddControl("title=ANDRO_SStat,type=VC_LABEL,text=Arbitrary Newton Function:,x=8,y=839,w=444,h=20,numblurs=1,transparent=true");
wind->AddControl("title=ANDRO_fact_qbox,type=VC_EDIT,text=1,x=111,y=882,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=ANDRO_fact_pbox,type=VC_EDIT,text=4,x=111,y=908,w=118,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=ANDRO_fact_plusbut,type=VC_BUTTON,text=add,x=12,y=933,w=80,h=18,dataname=Mandel_addfactor_but");
wind->AddControl("title=ANDRO_fact_minbut,type=VC_BUTTON,text=sub,x=98,y=934,w=80,h=18,dataname=Mandel_subfactor_but");
wind->AddControl("title=ANDRO_fact_rembut,type=VC_BUTTON,text=rem,x=183,y=934,w=80,h=18,dataname=Mandel_remExp_but");
wind->AddControl("title=ANDRO_Q_label,type=VC_LABEL,text=qz^p    q:,x=7,y=882,w=89,h=22,numblurs=1,transparent=true");
wind->AddControl("title=ANDRO_P_label,type=VC_LABEL,text=         P:,x=7,y=908,w=89,h=22,numblurs=1,transparent=true");
wind->AddControl("title=ANDRO_fact_clrbut,type=VC_BUTTON,text=clear,x=268,y=934,w=80,h=18,dataname=Mandel_fact_clrbut");
wind->AddControl("title=ANDRO_stat,type=VC_GLOBAL_STAT_STRING,text=function:*S,x=8,y=862,w=469,h=18,dataname=G_Mandel_ANDRO_FactorStr");
wind->AddControl("title=loopscountlabel,type=VC_LABEL,text=loops:,x=488,y=291,w=62,h=22,numblurs=1,transparent=true");
wind->AddControl("title=loopscountedit,type=VC_EDIT,text=100,x=568,y=291,w=91,h=21,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=bbrot_samplesLabel,type=VC_LABEL,text=Buddah Samples:thread,x=772,y=123,w=180,h=20,numblurs=1,transparent=true");
wind->AddControl("title=bbrot_samplesEdit,type=VC_EDIT,text=500,x=945,y=122,w=80,h=21,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=progressSlider,type=VC_SLIDER,text=Progress:100,x=31,y=956,w=979,h=39,numblurs=0,textfont=Modern,nointeract=true");
wind->AddControl("title=BBrotloopBut,type=VC_BUTTON,text=BBrot Loop,x=489,y=262,w=170,h=25,dataname=renderbbrotLoopBut");
wind->AddControl("title=imgfilenumBox,type=VC_EDIT,text=1,x=953,y=1000,w=74,h=23,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=pngsaveBut,type=VC_BUTTON,text=Png Save,x=812,y=1031,w=73,h=22,dataname=pngsavebutt");
wind->AddControl("title=x_coordboodah,type=VC_EDIT,text=-3,x=825,y=28,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=y_coordboodah");
wind->AddControl("title=xcordlabelboodah,type=VC_LABEL,text=X: ,x=795,y=28,w=25,h=25,numblurs=1,transparent=true");
wind->AddControl("title=y_coordboodah,type=VC_EDIT,text=-3,x=825,y=51,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=w_coordboodah");
wind->AddControl("title=ycordlabelboodah,type=VC_LABEL,text=y: ,x=795,y=51,w=25,h=25,numblurs=1,transparent=true");
wind->AddControl("title=w_coordboodah,type=VC_EDIT,text=6,x=825,y=74,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=h_coordboodah");
wind->AddControl("title=wcordlabelboodah,type=VC_LABEL,text=Width: ,x=772,y=74,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=h_coordboodah,type=VC_EDIT,text=6,x=825,y=97,w=200,h=22,numblurs=0,transparent=true,nointeract=true,tabname=x_coordboodah");
wind->AddControl("title=hcordlabelboodah,type=VC_LABEL,text=Height: ,x=772,y=97,w=50,h=25,numblurs=1,transparent=true");
wind->AddControl("title=bbrot_samplesLabelboodah,type=VC_LABEL,text=Buddahbrot search dims,x=781,y=6,w=180,h=20,numblurs=1,transparent=true");
wind->AddControl("title=UseBoodahDimsChk,type=VC_CHECKBOX,text=use,x=966,y=6,w=60,h=20");
wind->AddControl("title=betatestbut,type=VC_BUTTON,text=betafunction,x=897,y=892,w=131,h=48,dataname=beta_testfunc");
wind->AddControl("title=RandSeedBox,type=VC_EDIT,text=RandomSeed,x=99,y=251,w=200,h=20,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=RandSeedcatsBox,type=VC_EDIT,text=20,x=99,y=275,w=50,h=21,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=RandSeedLBL,type=VC_LABEL,text=RandSeed,x=27,y=251,w=67,h=20,numblurs=1,transparent=true");
wind->AddControl("title=RandSeedcatsLBL,type=VC_LABEL,text=colors(<50),x=14,y=277,w=83,h=22,numblurs=1,transparent=true,nointeract=true");
wind->AddControl("title=ReColorBtn,type=VC_BUTTON,text=Recolor,x=301,y=352,w=180,h=42,dataname=mandel_recolorbut");
wind->AddControl("title=savestatenameBox,type=VC_EDIT,text=StateSaves.txt,x=778,y=699,w=250,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=statenamebox,type=VC_EDIT,text=bbbrot3,x=778,y=749,w=250,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=LoadstatefileBut,type=VC_BUTTON,text=Load State file,x=778,y=724,w=250,h=22,dataname=Mandel_loadstatesbut");
wind->AddControl("title=savestateBut,type=VC_BUTTON,text=save state,x=778,y=777,w=120,h=22,dataname=Mandel_savestatebut");
wind->AddControl("title=loadstateBut,type=VC_BUTTON,text=load state,x=908,y=777,w=120,h=22,dataname=Mandel_loadstatebut");
wind->AddControl("title=SaveStateNamesListbox,type=VC_LISTBOX,text=savestates,x=778,y=230,w=250,h=465,listboxfunc=Mandel_savestatelist_proc,dataname=G_Mandel_savestatenames,numblurs=0");
wind->AddControl("title=RandomPalletBut,type=VC_BUTTON,text=generate pallet,x=158,y=276,w=140,h=20,dataname=Mandel_GeneratePallet");
wind->AddControl("title=FilterBox,type=VC_EDIT,text=,x=12,y=811,w=179,h=20,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=FilterBtn,type=VC_BUTTON,text=filter,x=208,y=811,w=88,h=20,dataname=Mandel_filter_renderers");
wind->AddControl("title=RelaxBox,type=VC_EDIT,text=1,x=248,y=188,w=50,h=21,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=RelaxLbl,type=VC_LABEL,text=relax:,x=184,y=187,w=60,h=22,numblurs=1,transparent=true");
wind->AddControl("title=xcordlabelshared,type=VC_LABEL,text=:<-X->:,x=513,y=27,w=65,h=20,numblurs=1,transparent=true");
wind->AddControl("title=ycordlabelshared,type=VC_LABEL,text=:<-Y->:,x=513,y=51,w=65,h=20,numblurs=1,transparent=true");
wind->AddControl("title=wcordlabelshared,type=VC_LABEL,text=:<-Width->:,x=497,y=74,w=90,h=20,numblurs=1,transparent=true");
wind->AddControl("title=hcordlabelshared,type=VC_LABEL,text=:<-Height->:,x=493,y=98,w=100,h=20,numblurs=1,transparent=true");
wind->AddControl("title=copytoBBSearchBut,type=VC_BUTTON,text=to BBrot Dims-->,x=311,y=151,w=170,h=25,dataname=Mandel_copydimstoBBrotSearch,textfontsize=12");

wind->AddControl("title=animationFolderBox,type=VC_EDIT,text=Mandelbrot,x=150,y=1000,w=300,h=25,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=animfoldlabel,type=VC_LABEL,text=save file: ,x=60,y=1000,w=80,h=25,numblurs=1,transparent=true");
wind->AddControl("title=animateChk,type=VC_CHECKBOX,text=save frames,x=152,y=1030,w=170,h=25");
wind->AddControl("title=framenumBox,type=VC_EDIT,text=1,x=453,y=1000,w=74,h=23,numblurs=0,transparent=true,nointeract=true");

wind->AddControl("title=cx_constBox,type=VC_EDIT,text=-3,x=575,y=368,w=200,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=constcxLab,type=VC_LABEL,text=X: ,x=485,y=368,w=25,h=25,numblurs=1,transparent=true");
wind->AddControl("title=cy_constBox,type=VC_EDIT,text=-3,x=575,y=391,w=200,h=22,numblurs=0,transparent=true,nointeract=true");
wind->AddControl("title=constcxLab,type=VC_LABEL,text=y: ,x=485,y=391,w=25,h=25,numblurs=1,transparent=true");
wind->AddControl("title=constjsetzoomBut,type=VC_BUTTON,text=const cxcy zoom,x=489,y=418,w=118,h=30,textfont=Consolas,textfontsize=12,dataname=JsetconstZoomLoopBut");
wind->AddControl("title=targetjsetzoomBut,type=VC_BUTTON,text=target cxcy zoom,x=628,y=418,w=137,h=28,textfont=Consolas,textfontsize=12,dataname=JsettargetZoomLoopBut");



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
    if (file_exists("lastrender.di")) {
        char op = '=';
        string token = file_contents("lastrender.di");
        cout << tokenize(token, "=", op) << " state loaded \n";
        Mandel_loadstate(token, wind);
        cout << "loaded last state\n";
    }
    string ranfname = G_Mandel_dictionary.index(G_VS_Rand3(G_Mandel_dictionary.length()));
    ranfname += G_Mandel_dictionary.index(G_VS_Rand3(G_Mandel_dictionary.length()));
    wind->set_editctrl_text("savefilename", ranfname);
    ranfname = G_Mandel_dictionary.index(G_VS_Rand3(G_Mandel_dictionary.length()));
    ranfname += G_Mandel_dictionary.index(G_VS_Rand3(G_Mandel_dictionary.length()));
    wind->set_editctrl_text("animationFolderBox", ranfname);
    vwc->load_background("mandleBack.png");
    vw->capture_mouse(&MS_mousecap, Mandel_mousecapture_process);
    vw->show();
    vwc->show();
    
    cout << "worker threads reporting: " << G_mandel_workerthread_info.threadsinpool;
    cout << "\nworker threads reporting idle: " << G_mandel_workerthread_info.threadsidle;
}

//     if (rendtype == "ANDRO Newton") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO, mandel_buffer, rebuild, bail, 300); dataout += " bail: " + bailout;
//        dataout += " func: " + ANDRO_Equation();
//        dataout2 = " roots: " + ANDRO_Roots();
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    if (rendtype == "ANDRO Newton Nova") {
//         manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_nova, mandel_buffer, rebuild, bail, 302); dataout += " bail: " + bailout;
//         dataout += " func: " + ANDRO_Equation();
//         dataout2 = " roots: " + ANDRO_Roots();
//         //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//         G_Mandel_last_wasbuild = true;
//     }
//    if (rendtype == "ANDRO Newton Nova_D") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_nova, mandel_buffer, rebuild, bail, 300); dataout += " bail: " + bailout;
//        dataout += " func: " + ANDRO_Equation();
//        dataout2 = " roots: " + ANDRO_Roots();
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    if (rendtype == "ANDRO Newton Julia") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_novajulia, mandel_buffer, rebuild, bail, 301); dataout += " bail: " + bailout;
//        dataout += " func: " + ANDRO_Equation();
//        dataout2 = " roots: " + ANDRO_Roots();
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    if (rendtype == "ANDRO Newton Julia_D") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_ANDRO_novajulia, mandel_buffer, rebuild, bail, 303); dataout += " bail: " + bailout;
//        dataout += " func: " + ANDRO_Equation();
//        dataout2 = " roots: " + ANDRO_Roots();
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Buddahm2 random") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_magnetm2_buddah, mandel_buffer, rebuild, bail, 400); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//    }
//    else if (rendtype == "Buddahm2 randcxcylim") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_magnetm2_buddah, mandel_buffer, rebuild, bail, 402); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//    }
//    else if (rendtype == "Buddahbrot random") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 400); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//    }
//    else if (rendtype == "Buddahbrot random HC") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 401); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//    }
//    else if (rendtype == "BBrot random cxcyLim") {
//            manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 402); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//        dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
//    }
//    else if (rendtype == "BBrot rand cxcyLimHC") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_buddah, mandel_buffer, rebuild, bail, 403); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        dataout2 = " samples rendered: " + ctostr(G_Mandel_Buddahbrot_samplecount) + "  Total hits: " + ctostr(G_Mandel_Buddahbrot_HitcountTotal);
//        dataout2 += " iteration range accepted: " + ctostr((int)((it * cx) / cy)) + " - " + ctostr((int)it - 1);
//    }
//    else if (rendtype == "Julia Set") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt2, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt3") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt3, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt3") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt4") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt4, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt4") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt5") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt5, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt5") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt5, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt6") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt6, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt6") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt6, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt7") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt7, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt7") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt7, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt8") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt8, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt8") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt8, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt9") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt9, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt9") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt9, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt10") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt10, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt10") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt10, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt11") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt11, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt11") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt11, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt12") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt12, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt12") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt12, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt13") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt13, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt13") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt13, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt14") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt14, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt14") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt14, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt error1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt_error1, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt error1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt_error1, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt error2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt_error2, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt error2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt_error2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt errortest") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt_errortest, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt errortest") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt_errortest, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Sqrt errortest2") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_julia_sqrt_errortest2, mandel_buffer, rebuild, bail, 4); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Brot Sqrt errortest2") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_sqrt_errortest2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "magnetm1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_magnetm1, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "magnetm1b") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_magnetm1b, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "magnetm2") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_magnetm2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "magnetm2b") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_magnetm2b, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "magnetm2c") {
//    dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//    //manwind->mygfx.draw_jset_tocopy(x, y, w, h,cx,cy, it);
//    manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_magnetm2c, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton trueE3M1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_trueE3M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1_2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1_2, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1_3") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_Newton_e3m1_3, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1_4") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton 2E4M1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_2E4M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E13M1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_E13M1, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1_4b") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4b, mandel_buffer, rebuild, bail, 201); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "threaded newton E3M1_4c") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4c, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newton E3M1_4c") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e3m1_4c, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newtonWrong z^4-1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e4m1_db, mandel_buffer, rebuild, bail, 200); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "newtonWrongCxCy z^4-1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_Newton_e4m1_db_b, mandel_buffer, rebuild, bail, 201); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy_wrong2(x, y, w, h, cx, cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong3") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 2); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong4") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy_wrong4(x, y, w, h, cx, cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 2); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong5"|| rendtype == "Julia Set Wrong6") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        //manwind->mygfx.draw_jset_tocopy_wrong5(x, y, w, h, cx, cy, it);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia2, mandel_buffer, rebuild, bail, 3); dataout += " bail: " + bailout;
//    }
//    else if (rendtype == "Julia Set Wrong7") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia3, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.draw_jset_tocopy_wrong7(x, y, w, h, cx, cy, it);
//    }
//    else if (rendtype == "Julia Set Wrong8") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild,bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong9") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia5, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia5, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong10") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia6, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia6, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Wrong11") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia7, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia7, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Tan") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_tan,mandel_buffer,rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Tanw") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_tanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set SinTanw") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin_tanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin_tanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set CoTanw") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cotanwrong, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cotanwrong, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Cos") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set Sin") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set SinTan") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin_tan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_sin_tan, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set CoTan") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cotan, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_cotan, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set expexp") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp_exp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set threexp") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set threexpLD") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexpLD, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexpLD, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set t_brot2") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_threexp, mandel_buffer, rebuild, bail,1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_threexp);
//    }
//    else if (rendtype == "Julia Set t_brot1") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia);
//    }
//    else if (rendtype == "Julia Set t_brot3") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia4, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia4);
//    }
//    else if (rendtype == "Julia Set t_brot4") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_tan, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_tan);
//    }
//    else if (rendtype == "Julia Set t_brot5") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_cos, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_cos);
//    }
//    else if (rendtype == "Julia Set t_brot6") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_sin, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_sin);
//    }
//    else if (rendtype == "Julia Set t_brot7") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp7);
//    }
//    else if (rendtype == "Julia Set exp7") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp7, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set t_brot8") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp);
//    }
//    else if (rendtype == "Julia Set exp8") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp_exp_exp, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set exp9") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
////        manwind->mygfx.multiJset(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Julia Set t_brot9") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_julia_exp127, mandel_buffer, rebuild, bail, 1); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multiJset_brot(x, y, w, h, cx, cy, it, calc_julia_exp127);
//    }
//    else if (rendtype == "VSet Beta") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.draw_Vset_tocopy(x, y, w, h, cx, cy, it);
//    }
//    else if (rendtype == "MandelJulia Euler") {
//        dataout += "   cx: " + cxcoord + " cy: " + cycoord;
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_julia_Euler, mandel_buffer, rebuild, bail, 0); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler2") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler3") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler4") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler5") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler5, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler6") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler6, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler7") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler7, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler8") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler8, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler9") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler9, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler10") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler10, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler11") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler11, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler12") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler12, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot Euler13") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_Euler13, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    G_Mandel_last_wasbuild = true; 
//    }
//    if (rendtype == "Mandelbrot derbail") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot derbail2") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail2, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot derbail3") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail3, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot derbail4") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail4, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "Mandelbrot derbail5") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle_derbail5, mandel_buffer, rebuild, bail, 101); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if(rendtype == "Mandelbrot set") {
//    manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//    //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "BBrot mouse orbit") {
//        manwind->mygfx.OmniMandel_thread(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        //manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 1") {
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong);
//    }
//    else if (rendtype == "MandelWrong 2") {
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong2, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong2);
//    }
//    else if (rendtype == "MandelWrong 3") {
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong3, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong3);
//    }
//    else if (rendtype == "MandelWrong 4") {
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong4, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong4);
//    }
//    else if (rendtype == "MandelWrong 5") {
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong5);
//
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong5, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 6") {
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong6);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong6, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 7") {
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong7);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong7, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 8") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong8);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong8, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 9") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong9);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong9, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 10") {
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong10);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong10, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 11") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong11);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong11, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 12") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong12);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong12, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 13") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong13);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong13, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 14") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong14);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong14, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 15") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong15);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong15, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 16") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong16);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong16, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 17") {
//        //manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong17);
//        manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong17, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//        G_Mandel_last_wasbuild = true;
//    }
//    else if (rendtype == "MandelWrong 18") {
//       // manwind->mygfx.multimandelbrot(x, y, w, h, it, calc_mandle_wrong18);
//       manwind->mygfx.OmniMandel(x, y, w, h, cx, cy, it, calc_mandle_wrong18, mandel_buffer, rebuild, bail, 100); dataout += " bail: " + bailout;
//       G_Mandel_last_wasbuild = true;
//    }
//    else {
//        cout << "please select a render type\n";
//    }

    //G_Mandel_rendertypes.stack("Mandelbrot set");
    //G_Mandel_rendertypes.stack("BBrot mouse orbit");
    //G_Mandel_rendertypes.stack("magnetm1");
    //G_Mandel_rendertypes.stack("magnetm1b");
    //G_Mandel_rendertypes.stack("magnetm2");
    //G_Mandel_rendertypes.stack("magnetm2b");
    //G_Mandel_rendertypes.stack("magnetm2c");
    //G_Mandel_rendertypes.stack("Mandelbrot derbail5");
    //G_Mandel_rendertypes.stack("Buddahm2 random");
    //G_Mandel_rendertypes.stack("Buddahm2 randcxcylim");
    //G_Mandel_rendertypes.stack("Julia Sqrt1");
    //G_Mandel_rendertypes.stack("Brot Sqrt1");
    //G_Mandel_rendertypes.stack("Julia Sqrt2");
    //G_Mandel_rendertypes.stack("Brot Sqrt2");
    //G_Mandel_rendertypes.stack("Julia Sqrt3");
    //G_Mandel_rendertypes.stack("Brot Sqrt3");
    //G_Mandel_rendertypes.stack("Julia Sqrt4");
    //G_Mandel_rendertypes.stack("Brot Sqrt4");
    //G_Mandel_rendertypes.stack("Julia Sqrt5");
    //G_Mandel_rendertypes.stack("Brot Sqrt5");
    //G_Mandel_rendertypes.stack("Julia Sqrt6");
    //G_Mandel_rendertypes.stack("Brot Sqrt6");
    //G_Mandel_rendertypes.stack("Julia Sqrt7");
    //G_Mandel_rendertypes.stack("Brot Sqrt7");
    //G_Mandel_rendertypes.stack("Julia Sqrt8");
    //G_Mandel_rendertypes.stack("Brot Sqrt8");
    //G_Mandel_rendertypes.stack("Julia Sqrt9");
    //G_Mandel_rendertypes.stack("Brot Sqrt9");
    //G_Mandel_rendertypes.stack("Julia Sqrt10");
    //G_Mandel_rendertypes.stack("Brot Sqrt10");
    //G_Mandel_rendertypes.stack("Julia Sqrt11");
    //G_Mandel_rendertypes.stack("Brot Sqrt11");
    //G_Mandel_rendertypes.stack("Julia Sqrt12");
    //G_Mandel_rendertypes.stack("Brot Sqrt12");
    //G_Mandel_rendertypes.stack("Julia Sqrt13");
    //G_Mandel_rendertypes.stack("Brot Sqrt13");
    //G_Mandel_rendertypes.stack("Julia Sqrt14");
    //G_Mandel_rendertypes.stack("Brot Sqrt14");
    //G_Mandel_rendertypes.stack("Brot Sqrt error1");
    //G_Mandel_rendertypes.stack("Julia Sqrt error1");
    //G_Mandel_rendertypes.stack("Brot Sqrt error2");
    //G_Mandel_rendertypes.stack("Julia Sqrt error2");
    //G_Mandel_rendertypes.stack("Brot Sqrt errortest");
    //G_Mandel_rendertypes.stack("Julia Sqrt errortest");
    //G_Mandel_rendertypes.stack("Brot Sqrt errortest2");
    //G_Mandel_rendertypes.stack("Julia Sqrt errortest2");
    //G_Mandel_rendertypes.stack("Buddahbrot random");
    //G_Mandel_rendertypes.stack("Buddahbrot random HC");
    //G_Mandel_rendertypes.stack("BBrot random cxcyLim");
    //G_Mandel_rendertypes.stack("BBrot rand cxcyLimHC");
    //G_Mandel_rendertypes.stack("Mandelbrot derbail");
    //G_Mandel_rendertypes.stack("Mandelbrot derbail2");
    //G_Mandel_rendertypes.stack("Mandelbrot derbail3");
    //G_Mandel_rendertypes.stack("Mandelbrot derbail4");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler");
    //G_Mandel_rendertypes.stack("MandelJulia Euler");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler2");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler3");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler4");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler5");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler6");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler7");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler8");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler9");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler10");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler11");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler12");
    //G_Mandel_rendertypes.stack("Mandelbrot Euler13");
    //G_Mandel_rendertypes.stack("ANDRO Newton");
    //G_Mandel_rendertypes.stack("ANDRO Newton Nova");
    //G_Mandel_rendertypes.stack("ANDRO Newton Julia");
    //G_Mandel_rendertypes.stack("ANDRO Newton Nova_D");
    //G_Mandel_rendertypes.stack("ANDRO Newton Julia_D");
    //G_Mandel_rendertypes.stack("newton E3M1");
    //G_Mandel_rendertypes.stack("newton trueE3M1");
    //G_Mandel_rendertypes.stack("newton E3M1_2");
    //G_Mandel_rendertypes.stack("newton E3M1_3");
    //G_Mandel_rendertypes.stack("newton E3M1_4");
    //G_Mandel_rendertypes.stack("newton 2E4M1");
    //G_Mandel_rendertypes.stack("newton E13M1");
    //G_Mandel_rendertypes.stack("threaded newton E3M1_4c");
    //G_Mandel_rendertypes.stack("newton E3M1_4c");
    //G_Mandel_rendertypes.stack("newton E3M1_4b");
    //G_Mandel_rendertypes.stack("Julia Set threexp");
    //G_Mandel_rendertypes.stack("Julia Set threexpLD");
    //G_Mandel_rendertypes.stack("newtonWrong z^4-1");
    //G_Mandel_rendertypes.stack("newtonWrongCxCy z^4-1");
    ////G_Mandel_rendertypes.stack("VSet Beta");
    //G_Mandel_rendertypes.stack("Julia Set Wrong");
    //G_Mandel_rendertypes.stack("MandelWrong 1");
    //G_Mandel_rendertypes.stack("MandelWrong 2");
    //G_Mandel_rendertypes.stack("MandelWrong 3");
    //G_Mandel_rendertypes.stack("MandelWrong 4");
    //G_Mandel_rendertypes.stack("MandelWrong 5");
    //G_Mandel_rendertypes.stack("MandelWrong 6");
    //G_Mandel_rendertypes.stack("MandelWrong 7");
    //G_Mandel_rendertypes.stack("MandelWrong 8");
    //G_Mandel_rendertypes.stack("MandelWrong 9");
    //G_Mandel_rendertypes.stack("MandelWrong 10");
    //G_Mandel_rendertypes.stack("MandelWrong 11");
    //G_Mandel_rendertypes.stack("MandelWrong 12");
    //G_Mandel_rendertypes.stack("MandelWrong 13");
    //G_Mandel_rendertypes.stack("MandelWrong 14");
    //G_Mandel_rendertypes.stack("MandelWrong 15");
    //G_Mandel_rendertypes.stack("MandelWrong 16");
    //G_Mandel_rendertypes.stack("MandelWrong 17");
    //G_Mandel_rendertypes.stack("MandelWrong 18");
    //G_Mandel_rendertypes.stack("Julia Set");

    //G_Mandel_rendertypes.stack("Julia Set t_brot1");
    //G_Mandel_rendertypes.stack("Julia Set t_brot2");
    //G_Mandel_rendertypes.stack("Julia Set t_brot3");
    //G_Mandel_rendertypes.stack("Julia Set t_brot4");
    //G_Mandel_rendertypes.stack("Julia Set t_brot5");
    //G_Mandel_rendertypes.stack("Julia Set t_brot6");
    //G_Mandel_rendertypes.stack("Julia Set t_brot7");
    //G_Mandel_rendertypes.stack("Julia Set t_brot8");
    //G_Mandel_rendertypes.stack("Julia Set t_brot9");
    //G_Mandel_rendertypes.stack("Julia Set exp7");
    //G_Mandel_rendertypes.stack("Julia Set exp8");
    //G_Mandel_rendertypes.stack("Julia Set exp9");

    //G_Mandel_rendertypes.stack("Julia Set Tanw");
    //G_Mandel_rendertypes.stack("Julia Set CoTanw");
    //G_Mandel_rendertypes.stack("Julia Set SinTanw");

    //G_Mandel_rendertypes.stack("Julia Set Tan");
    //G_Mandel_rendertypes.stack("Julia Set CoTan");
    //G_Mandel_rendertypes.stack("Julia Set Cos");
    //G_Mandel_rendertypes.stack("Julia Set Sin");
    //G_Mandel_rendertypes.stack("Julia Set expexp");
    //G_Mandel_rendertypes.stack("Julia Set SinTan");

    //G_Mandel_rendertypes.stack("Julia Set Wrong2");
    //G_Mandel_rendertypes.stack("Julia Set Wrong3");
    //G_Mandel_rendertypes.stack("Julia Set Wrong3b");

    //G_Mandel_rendertypes.stack("Julia Set Wrong4");
    //G_Mandel_rendertypes.stack("Julia Set Wrong5");
    //G_Mandel_rendertypes.stack("Julia Set Wrong6");
    //G_Mandel_rendertypes.stack("Julia Set Wrong7");
    //G_Mandel_rendertypes.stack("Julia Set Wrong8");
    //G_Mandel_rendertypes.stack("Julia Set Wrong9");
    //G_Mandel_rendertypes.stack("Julia Set Wrong10");
    //G_Mandel_rendertypes.stack("Julia Set Wrong11");


