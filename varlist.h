#ifndef VARLIST_h
#define VARLIST_h

#include<iostream>

#include<ctype.h>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<string>
using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
//#include"prototypes.h"
//#include"shortlist.h"
#include <iomanip>
#include <sys/timeb.h>
#include <process.h>
#include <valutils.h>
//#include "consoleutils.h"
#include<strlist.h>
//#include<CSLs.h>


#define dout() out("gab");
// returns the number of items found, items are queued into list
   


#define vlip VarListItem *
#define VLI VarListItem

struct VarListItem {
    string name;
    string value;
    VarListItem *next;
    VarListItem *last;
    VarListItem *jump;
};
vlip newvlip(string name, string value){
    vlip var = new VLI;
    var->name=name;
    var->value=value;
    var->next=NULL;
    var->last=NULL;
    var->jump=NULL;
    return var;
}
void newVLIP(string name, string value,vlip var){
    var = new VLI;
    var->name=name;
    var->value=value;
    var->next=NULL;
    var->last=NULL;
    var->jump=NULL;
}
vlip newvlip(){
    return newvlip("","");
}     

void VI(vlip v){
    v->name="";
    v->value="";
    v->next=NULL;
    v->jump=NULL;
    v->last=NULL;
}

class variablelist {

private:

    vlip start;
    vlip end;
    int size;
    int type;
    // 1=insert after 2=found
    int ptrto(string item, vlip& ret);


public:

    bool set(string what, string value);
    variablelist(string fname);
    variablelist();
    vlip ini() { return start; }
    void ini(vlip& a) { a = start; };
    void i_i(vlip& a) { a = start; };
    bool getnext(vlip& vv, string& name, string& value);
    string valueof(string n);

    string todsl(string delim);
    void fromdsl(string dsl, string delim);
    string tocsl() { return todsl(","); };
    int SaveFile(string filename);
    int LoadFile(string filename);
    int load(string f) { return LoadFile(f); };
    int save(string f) { return SaveFile(f); };
    void clear();
    void remove(string wh);

    void queue(string n, string v);
    void stack(string n, string v);
    string pop();
    string pop(string& n, string& v);
    string lift();
    string lift(string& n, string& v);
    string gettype();

    int getsize() { return size; };
    int length() { return size; };
    void point(variablelist& s);
    bool isempty() { return start->next == end; };
    bool eof() { return start->next == end; };
    void reset();
    bool isset(string wh);

    void output() { cout << todsl("\n") << endl; };
    void safe_save(string fname);
    void safe_load(string fname);
    string& saveformat(string f);
    string& loadformat(string f);
    string cookieval();

    string tocsl_safe() {

        vlip vv = ini();
        string name, val, ret = "";
        while (getnext(vv, name, val)) {
            ret += csl_vl_format(name) + "=" + csl_vl_format(val);
            ret = csl_vl_format(ret);
            if (vv->next != end)ret += ",";
        }
        return ret;
    }

    void fromcsl_safe(string& csl) {
        string tmp = csl, h, n, v;
        while (tmp != "") {
            h = tokenizecsl(tmp, false);
            csl_vl_unformat(h);
            breakarg(h, n, v);
            set(csl_vl_unformat(n), csl_vl_unformat(v));
        }

    }
    void fromcsl(string& csl) {
        string tmp = csl, h, n, v;
        while (tmp != "") {
            h = tokenizecsl(tmp, false);
            breakarg(h, n, v);
            set(n, v);
        }

    }
    string c_style_format(string str) {
        str=str_replace_all(str, "\\", "\\\\");
        str = str_replace_all(str, "=", "\\0");
        str = str_replace_all(str, ",", "\\1");
        str = str_replace_all(str, "\n", "\\n");
        str = str_replace_all(str, "\r", "\\r");
        return str;
    }
    string c_style_unformat(string str) {


        str = str_replace_all(str, "\\r", "\r");
        str = str_replace_all(str, "\\n", "\n");
        str = str_replace_all(str, "\\1", ",");
        str = str_replace_all(str, "\\0", "=");
        str = str_replace_all(str, "\\\\", "\\");
        return str;
    }

    string operator[](string s) { return valueof(s); }
    

}variables;
string variablelist::valueof(string n){
    vlip v;
    int i =ptrto(n,v);
    if(i==2)return v->value;
    return "";
}
void variablelist::point(variablelist &s) {
    clear();
     start=s.start; 
     end=s.end; 
     size=s.size; 
     s.reset();  
}
// flag 1 = insert after ret, 2 = exact value found
int variablelist::ptrto(string item, vlip &ret){
    ret = start;
    if(start->next==end){
        return 1;
    }
    int flag;
    while( ( ret = ret->next) != end){
        flag = abcomp(item,ret->name);
        
        if(flag==-1 ){ 
            ret = ret->last;
            return 1;
        }
        if(flag==0){
            return 2;
        }
    }
    ret = ret->last;
    return 1;
}
void vlip_insert(vlip vv, string value,string v){// inserts node with name=value after vv
    vlip wh=newvlip(value,v);
    vlip nex=vv->next;
    nex->last = wh;
    wh->next = nex;
    vv->next=wh;
    wh->last=vv;
}
void vlip_delete(vlip vv){
    vlip left = vv->last;
    vlip right = vv->next;
    left->next = right;
    right->last = left;
    delete vv;
}   
bool variablelist::set(string what,string value){
    if(type==slist_unsorted){queue(what,value); return true;}
    vlip node;
    int flag = ptrto(what,node);
    
    if(flag==1){
        vlip_insert(node,what,value);
        size++;
        return false;
    }
    if(flag==2){
        node->value=value;
        return true;
    }
    return false;
}
    
void variablelist::reset(){
    start=newvlip("*start*","*start*");
    end=newvlip("*end*","*end*");
    start->next=end;
    end->last=start;
    size=0;
    type=slist_sorted;
}

variablelist::variablelist(){reset();}

variablelist::variablelist(string fname){
    reset();
    LoadFile(fname);
}
bool variablelist::getnext(vlip &vv, string &str,string &val){
    vv=vv->next;
    if(vv==end)return false;
    str = vv->name;
    val = vv->value;
    return true;
}   
    
int  variablelist::SaveFile(string filename){
    ofstream ofile(filename.c_str());
    ofile << todsl("\n");
    ofile.close();
    return 1;
}

int variablelist::LoadFile(string filename){
    ifstream ifile(filename.c_str());
    if(!ifile.good())return 0;
    string line,n,v;
    int lines = 0;
    cout << endl;
    while(!ifile.eof()){
        getline(ifile,line,'\n');
        breakarg(line,n,v,'=');
        set(n,v);
        lines++;
        if(lines%13==0)cout << lines << "\r";
    }
//    setjumps();
    return  size;
    
}
string variablelist::cookieval(){
    vlip vv = ini();
    
    string name, val, ret = "";
    while (getnext(vv, name, val)) {
        ret += name + "=" + val;
        if (vv->next != end)ret += "; ";
    }
    if (ret != "");
    ret = "\r\nCookie: " + ret;
    return ret;
}

string variablelist::todsl(string delim){
    vlip vv=ini();
    string name,val,ret="";
    while (getnext(vv,name,val)){
         ret += name+"="+val;
         if(vv->next!=end)ret+=delim;
    }
    return ret ;
} 
void variablelist::clear(){
    while(start->next!=end)vlip_delete(start->next);
    size=0;
}
void variablelist::remove(string wh){
    vlip ss;
    int fl = ptrto(wh,ss);
    if(fl == 2)vlip_delete(ss);
}    

void variablelist::queue(string n,string v){
    type = slist_unsorted;
    vlip_insert(start,n,v);
    size++;
}
void variablelist::stack(string n,string v){
    type = slist_unsorted;
    vlip_insert(end->last,n,v);
    size++;
}
string variablelist::pop(){
    if(isempty())return"";
    string ret = start->next->name+"="+start->next->value;
    vlip_delete(start->next);
    return ret;
}
string variablelist::lift(){
    if(isempty())return"";
    string ret = end->last->name+"="+end->last->value;
    vlip_delete(end->last);
    return ret;
}
string variablelist::pop(string &n,string &v){
    if(isempty())return"";
    string ret = start->next->name+"="+start->next->value;
    n = start->next->name;
    v = start->next->value;
    vlip_delete(start->next);
    return ret;
}
string variablelist::lift(string &n,string &v){
    if(isempty())return"";
    string ret = end->last->name+"="+end->last->value;
    n = end->last->name;
    v = end->last->value;
    vlip_delete(end->last);
    return ret;
}    
bool  variablelist::isset(string name){
    vlip ptr;
    int i = ptrto(name,ptr);
    return i==2;
}
void variablelist::safe_save(string fname) {
    vlip vv = ini();
    string name, val, ret = "";
    while (getnext(vv, name, val)) {
        ret += saveformat(name) + "=" + saveformat(val);
        if (vv->next != end)ret += "\n";
    }
    ofstream ofile(fname.c_str());
    ofile << ret;
    ofile.close();
}
void variablelist::safe_load(string fname) {
    ifstream ifile(fname.c_str());
    if (!ifile.good())return ;
    string line, n, v;
    int lines = 0;
    while (!ifile.eof()) {
        getline(ifile, line,'\n');
        if (line == "")continue;
        breakarg(line, n, v, '=');
        set(loadformat(n), loadformat(v));
        lines++;
        
    }
    

}

string& variablelist::saveformat(string str) {
    str_replace_all(str, "`", "`1");
    str_replace_all(str, "=", "`0");
    str_replace_all(str, ",", "`2");
    str_replace_all(str, "\n", "`3");
    str_replace_all(str, "\r", "`4");
    return str;
}
string& variablelist::loadformat(string str) {
    
    
    str_replace_all(str, "`4", "\r");
    str_replace_all(str, "`3", "\n");
    str_replace_all(str, "`2", ",");
    str_replace_all(str, "`0", "=");
    str_replace_all(str, "`1", "`");
    return str;
}


/**************************************************end varlist class ********************************************/
#include<ValCrypt.h>
/**************************************************ValCrypt encryption suite ************************************
  valcrypt is a simple encryption class.
  declare as
  ValCrypt VCDat(string password, int pin);
  or
  ValCrypt VCDat;
  VCDat.start(string password,int pin);
  class ValCrypt{

    public:
	  ValCrypt(string pass, int pin);
	  void start(string pass, int pin);   //  readies the new encryption key
	  
	  void encrypt(char * data, int Len, char *ret);  // these are raw data encryption 
	  void decrypt(char * data, int Len, char *ret);  //      and decryption functions
	 
      void EKout(bool); // tests the EK for redundancies and completeness, if bool outputs whole EK to CMD
      
      string encrypt(string data);  // encrypts and decrypts regular 
      string decrypt(string data);  //               regular strings

       
       Attatched helper functions include:
        void varlist_enc_save(varlist &vlst, ValCrypt &vc,string filename)
        void varlist_dec_load(varlist &vlst, ValCrypt &vc,string filename)
         
             these functions will save and restore varlist vlst to a file
             encrypted by ValCrypt vc, written to and read from file with 
             string filename formatted to not lose data and work properly
             with varlist by vc_enc_format and vc_enc_unformat.
        
        
             
        
/******************************************************Begin Varlist and strlist encryption to and from file ***************/


string& enc_vl_format(string &str){
    str_replace_all(str,"`","`1");
    str_replace_all(str,"=","`0");
    str_replace_all(str, ",", "`2");
    str_replace_all(str, "\n", "`3");
    str_replace_all(str, "\r", "`4");
    return str;
}
string& enc_vl_unformat(string &str){
    str_replace_all(str,"`0","=");
    str_replace_all(str,"`1","`"); 
    str_replace_all(str, "`2", ",");
    str_replace_all(str, "`3", "\n");
    str_replace_all(str, "`4", "\r");
    return str;
}
#define varlist variablelist   
void varlist_enc_save(varlist &vlst, ValCrypt &vc,string filename){
    ofstream ofile(filename.c_str());
    string n,v,en,ev,tmp;
    vlip vv=vlst.ini();
    while(vlst.getnext(vv,n,v)){

        tmp = enc_vl_format(n)+"="+enc_vl_format(v);
        en= vc.encrypt_Sk(tmp);
        ofile << enc_vl_format(en)<<"\n";
    }
}


void varlist_dec_load(varlist &vlst, ValCrypt &vc,string filename){
    ifstream ifile(filename.c_str());
    string ins = "",n,v;
    while(!ifile.eof()){
        getline(ifile,ins,'\n');
        if(ins=="")continue;
        ins = vc.decrypt_Sk(ins);
        ins = enc_vl_unformat(ins);
        breakarg(ins,n,v,'=');

        n = enc_vl_unformat(n);
        v=enc_vl_unformat(v);  
        vlst.set(n,v);
    }
    ifile.close();
}            
    

 #endif

