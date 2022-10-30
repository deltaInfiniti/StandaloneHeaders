//valutils
/* -mostly- written in 2005-2009.  Please forgive my naivity 
   commentary written 2020
   this file is included with varlist as part of my integral headers set 
   helper functions that don't fit well in other headers. Mostly standalone,
   general use functions that can be copied out into your own context as needed
   */
string getbetween(string, string, string, int);
string getbetween(string, int, string);
string getbetween(string, int, int);
string getbetween(string, int);


/*********************** breakarg *****************************************
//  n is set to the value of the string left of the first instance of delim
//  v is set to the value of the string right of the first instance of delim
//  such as: t= "a=b",  after abcomp, n==a and v==b                       */
//#define vlog(a)
void breakarg(string t, string &n, string &v, char delim='='){
    //for(int i = 0; i <100; i++)n+= " ";
    n="";v="";
    bool lv=false;
    for(int i = 0; i < t.length(); i++){
        if(t[i]==delim && !lv ){
            lv=!lv;
            i++;
        }
        if(lv) v= v+t[i];
        if(!lv) n.append(1,t[i]);
    }    
}
int abcomp(string o, string t){ // -1 o is less, 1 t is less, 0 they are the same
    int i = strcmp(o.c_str(),t.c_str()) ;
    if(i > 0)i=1;
    if(i < 0)i=-1;
    return i;
}
//2020 addition- ~8x faster than abcomp. output not the same, but self similar.
int string_compare(const string& a, const string& b) {
    int c = 0;
    if ((c = a.length() - b.length()) != 0) {
        return (c < 0 ? -1 : 1);
    }
    c = a.length();
    int d = 0;
    for (int i = 0; i < c; i++) {
        if ((d = (a[i] - b[i])) != 0) return (d < 0 ? -1 : 1);

    }
    return 0;
}
// findfirstof returns the index of the first instance of a character in chs
/* 
examples:
    findfirstof("abcdefg","dfb")
    would return 1, because 'b' is in str1[1]
    ffo_oper (or char &op arguement) are set to the char it found first
*/
char ffo_oper;
int findfirstof(string wh, string chs, char&op=ffo_oper){
    for(int i = 0; i < wh.length(); i++){
        for(int x = 0; x < chs.length();x++){
            if(wh[i]==chs[x]){
                op = chs[x];
                return i;
            }
        }
    }
    return -1;
}

// tokenize removes and returns the first token in str
// useful for list management
// op returns the operator after the token
char Token_op;
string tokenize(string &str,string delim,char &op=Token_op){
    string ret;
    int i = findfirstof(str ,delim,op);
    if(i == -1){
        op = 'n'; 
        ret = str;
        str = "";
        return ret;   
    }
    ret = getbetween(str,0,i);
    str = getbetween(str,i+1);
    return ret;
}
//csl functions:
//#define Replace(a,b,c) str_replace_all(a,b,c); 
//#define Replace(a,b,c,d) str_replace_all(a,b,c,d);
/*void str_replace_all(string &str, string wha,string whi, int ind=0){
    int whal = wha.length(),whil=whi.length();
    while((ind=findnext(str,wha,ind))!=-1){
           str=str.replace(ind,whal,whi);
           ind+= (higher(whal,whil));
    }
}
*/


/*********************string helper and search functions***********************/
string str_replace_all(string a, string b, string c, int ind = 0) {
    string ret = a;
    int plc = 0;
    while ((plc = ret.find(b, (size_t)plc)) != string::npos) {
        ret.replace(plc, b.length(), c);
        plc += (c.length() - b.length()) + 1;
    }
    return ret;
}
int stoint(string& s) {
    string::iterator ep = std::remove(s.begin(), s.end(), ',');
    s.erase(ep, s.end());
    return atoi(s.c_str());
}
// string easy convertion block 
string ctostr(int i) {
    char a[38];
    _itoa_s(i, a, 10);
    return a;

}
string ctostr(unsigned long int i) {
    char a[90];
    _ltoa_s(i, a, 10);
    return a;

}
string ctostr(LONG i) { return ctostr((int)i); }
string ctostr(unsigned int i) {
    char a[38];
    _itoa_s(i, a, 10);
    return a;
}
/*string ctostr(size_t i) {
    char a[38];
    _itoa_s((int)i, a, 10);
    return a;
}*/
    
string ctostr(double a) {
    char buff[25];
    sprintf(buff, "%14.14f", a);
    string ret = string(buff);
    while (ret[ret.length()-1] == '0' || ret[ret.length()-1] == '.')ret = ret.substr(0, ret.length() - 1);
    if (ret.length() == 0)return "0";
    return ret;
}

string ctostr(bool a) {
    if (a)return "true";
    return "false";
}

string creftostr(COLORREF a) {
    string ret = ctostr((unsigned int)GetRValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetGValue(a));
    ret += ",";
    ret += ctostr((unsigned int)GetBValue(a));
    return ret;
}
bool can_convert_strdbl(string& a) {
    short hold;
    for (int i = 0; i < a.length(); i++) {
        hold = (BYTE)a[i];
        //cout << (short)hold << endl;
        if ((hold <= 44 || hold >= 58) || hold == 47)return false;
    }
    return true;
}
long double strtoldbl(string& a) {
    if (!can_convert_strdbl(a)) {
        cout << "cannot convert " << a << " to a decimal number";
        return -1;
    }
    return std::stold(a, 0);
}
double strtodbl(string a) {
    if (!can_convert_strdbl(a)) {
        cout << "cannot convert " << a << " to a decimal number";
        return -1;
    }
    return std::stod(a, 0);
}



string randstr(int l){
    string ret="";
    for(int i = 0; i < l; i++)ret += (char) ((rand()%95)+32);
    return ret;
}

bool isin(string w, string t){
    return (w.find(t,0)!=string::npos);
}
#define instr(w,t) isin(w,t)
int findnext(string n, string wh, int ind=0){
    size_t tmp = n.find(wh,ind);
    return (tmp == string::npos ? -1 : (int)tmp) ; 
}
int findnextl(string n, string wh, int ind){
    int tmp =findnext(n,wh,ind);
    return (tmp==-1 ? tmp : tmp +wh.length()); 
}
#define out(what) outt(what,true,__LINE__);
/* just like getbetween but sets ind to end of b string or -1 if not found*/
string getbetween_I(string wh, string a, string b, int& ind) {
    int xo = wh.find(a, ind) + a.length();
    int xt = wh.find(b, xo);
    if (xo == string::npos || xt == string::npos || xt - xo < 1) {
        ind = -1;
        return "";
    }
    string th = wh.substr(xo, xt - xo);
    ind = xt + b.length();
    return th;
}
/*getbetween returns value of string wh found between a and b after ind
wh = " hello ";  getbetween(wh, " h", " ", 0) returns "ello";
wh = " hello ";  getbetween(wh, " h", " ", 1) returns ""; because " h" does not appear after index 1;
wh = " hello ";  getbetween(wh, "he", " ", 0) returns "llo";
wh = " hello ";  getbetween(wh, "l", "l", 0) returns "";
*/
string getbetween(string wh, string a, string b, int ind){
    int xo = wh.find(a,ind) + a.length();
    int xt = wh.find(b,xo);
    if(xo==string::npos || xt==string::npos)return "";
    if(xt-xo < 1) return "";
    string th=wh.substr(xo,xt-xo); 
    return th;
}
string getbetween(string wh, int ind, string what){
    int xt = wh.find(what,ind);
    if(xt == string::npos) return "";   
    return wh.substr(ind,xt-ind);
}
string getbetween(string wh,int ind1, int ind2){
    return wh.substr(ind1,ind2);
}
string getbetween(string wh,int ind){
    return wh.substr(ind);
}

string getafter(string wh, string a,int ind=0){
    int b = findnextl(wh,a,ind);
    if(b==-1)return "";
    return wh.substr(b);
}
string getbefore(string wh, string a,int ind=0){
    int b = findnext(wh,a,ind);
    if(b==-1)return "";
    return wh.substr(0,b);
} 
#define getnextb(s,w,t) getnextbetween(s,w,t)

//destroys source string
string getnextbetween(string &src, string what, string towhat){
    
    string a = getbetween(src,what,towhat,0);
    if(a==""){
        src = "";
        return "";
    }
    int i = findnextl(src,what,0);
    
    src.erase(0,i);
    return a;
}

//written in 2005 for gcc. fails in 2020 on msvc
// depreciated for std::getline
int getline_fails(istream& in, string& var) {  
    char hold=' ';
    int ret = 0;
    while(1){
            in >> hold;
            var += hold;
            if (hold == '\n' || hold == '\0')return ret;
            if (in.eof())return ret;
            ret++;
    }
}

// console quick keyboard input functions. 
// password input found in consoleutils (depreciated)
string readstr(string q){
    cout << q << "==>";
    string var;
    getline(cin,var);
    return var;
}
bool readbool(string q){
    string r="";
    while(r!="y" && r != "n"){
        cout << q << "(y/n)==>";
        getline(cin,r);
    }
    return (r=="y");
}
int readint(string q){
    string s = readstr(q);
    return ctoint(s);
}
/***************time functions**********************************/
static bool G_END_PAUSE__ = false;
void pause_console() {
    cout << "press enter to continue";
    char wait;
    while (!G_END_PAUSE__) {
        Sleep(10);
        if (cin.peek()) {
            
            wait = cin.get();
            if (wait == '\n')break;
        }
    }
    cout << "\r                              \runpaused\n";
}
int milmil,milsec;

int timestamp(){
    time_t seconds;
    time(&seconds);
    return seconds;
}
int millitime()
{
   struct _timeb timebuffer;
   _ftime64_s( &timebuffer );
   return timebuffer.millitm;
}
void startmil(int&s,int&m){
    s = timestamp();
    m = millitime();
}
int endmil(int s,int m){
    int i=millitime();
    int a=(timestamp() - s)*1000;
    if(a==0) return i-m;
    int b = (1000-m)+i;
    b-=1000;
//    int b=(i<m? ((-1000) +(m-i)):(i-m));
    return (a+b);
}


void startmil(){
    milsec = timestamp();
    milmil = millitime();
}
int endmil(){
    int i=millitime();
    int a=(timestamp() - milsec)*1000;
    int b=(i<milmil?((-1000)+(milmil-i)):(i-milmil));
    return (a+b);
}

string timeformat(int i){
    string ret = "";
    int h = i /3600;
    i=i%3600;
    int m = i /60;
    i=i%60;
    if(h > 9)ret += ctostr(h);
    else if(h>0) ret += "0"+ctostr(h);
    if(h!=0)ret += ":";

    if(m > 9)ret += ctostr(m);
    else if(m>0) ret += "0"+ctostr(m);
//    else ret += "00";
    if(m!=0)ret += ":";    
    
    if(i > 9)ret += ctostr(i);
    else if(i>0) ret += "0"+ctostr(i);
    else ret += "00";
    return ret;
}


/**************string helper functions **************/
string extension(string a){
    size_t t = a.rfind('.');
    if(t!=string::npos) return a.substr(t);
    return "";
}
string getfile(string a){
    size_t t = a.rfind('/');
    if(t == string::npos) return a;
    return a.substr(t);
}

string getdir(string a){
    size_t t = a.rfind('/');
    size_t tt= a.rfind('\\');
    t =( t<tt?t:tt); 
    if(t == string::npos) return "";
    return a.substr(0,t);
}

string limchars(string a,int num){
    while(a.length()>num) a.erase(a.length()-1);
    return a;
}
string makelen(string a,int num){
    while(a.length()>num) a.erase(a.length()-1);
    while(a.length()<num) a+=" "; 
    return a;
}
string makelen_center(string a, int num){
    bool fb=true;
    while(a.length()>num) a.erase(a.length()-1);
    while(a.length()<num){ (fb ? a+=" ":a=" "+a); fb=!fb;} 
    return a;
}
string allowerc(string low){
    string work="";
    int n = 0;
    while(n < low.length()){
        work += tolower(low[n]);
        n++;
    }
    return work;
} 
/*******************************file helper functions*************************************/
string file_contents(string name){
    string ret="",tmp;
    ifstream ifile(name.c_str());
    if(!ifile)return ret;
    while(!ifile.eof()){
        getline(ifile,tmp);
        ret += tmp+"\n";
    }
    return ret;
}
int file_size(string fname) { 
  struct stat filestatus;
  stat(fname.c_str(), &filestatus );
  return  filestatus.st_size ;
}
bool file_exists(string fname){
  struct stat filestatus;
  return  stat(fname.c_str(), &filestatus)==0;
}

void appendfile(string fn, string w) {
    ofstream ofile(fn.c_str(), ios::app);
    if (ofile.good()) {
        ofile << w;
        ofile.close();
    }
    return;
}
void writefile(string fn, string w) {
    ofstream ofile(fn.c_str());
    if (ofile.good()) {
        ofile << w;
        ofile.close();
    }
    return;
}
void Write_File(string name, string& text) {
    ofstream ofile(name.c_str());
    ofile << text;
    ofile.close();

}

#include <iterator>
 
int copyfile(string fr,string t){
  fstream f(fr.c_str(), fstream::in|fstream::binary);
  f << noskipws;
  istream_iterator<unsigned char> begin(f);
  istream_iterator<unsigned char> end;
 
  fstream f2(t.c_str(),
    fstream::out|fstream::trunc|fstream::binary); 
  ostream_iterator<char> begin2(f2);
 
  copy(begin, end, begin2);
  return 0;
}
/***************Math functions************/

int powmod(int tis, int exp, int mod) { // adapted from bufferwrapper. recursive powmod
    if (exp == 0)return 1;
    if (exp % 2 == 0) {
        int b = powmod(tis, exp / 2, mod);
        return  (b * b) % mod;
    }
    else return (tis * powmod(tis, exp - 1, mod)) % mod;
    
    return -1; // never
}

bool val_mil_rab(int r, int d, int n) {
    int x = powmod(2 + (rand() % (n - 4)), d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < r; i++) {
        x = powmod(x, 2, n);
        if (x == n - 1)return true;
    }
    return false;
}



bool probprime(int x, int reps) {
    int hold = x - 1;
    int n = 0;
    while (hold != 0) {
        if (hold % 2 != 0)break;
        hold /= 2;
        n++;
    }
    for (int i = 0; i < reps; i++) {
        if (!val_mil_rab(n, hold, x))return false;
    }
    return true;

}