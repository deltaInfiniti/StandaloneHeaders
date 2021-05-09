#ifndef ValCrypt_CORE
#define ValCrypt_CORE

/*     This file should be included by varlist under prototypes.h otherwise key functions will not work properly */

#include<windows.h>
#include<string>
#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;
#define vcdebug(a) 
#define __I(_nIt9_chse_) vc.decrypt_Sk(_nIt9_chse_)
//#define string std::string

long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

char* getbinfile(char* fn){
    
    char a;
    long size = GetFileSize((string)fn);
    
    char* ret = new char[size];
    FILE* fp = fopen(fn,"rb");
    if(fp == NULL){ 
        cout << "failed opening "<<fn<<endl;
        return NULL;
    }
    //cout << "file length: "<< filelength(fp)<<endl;
    int i = 0;
    while(!feof(fp)){
        a = (char)fgetc(fp);
        ret += a;
        i++;
    }
    cout << "read "<< i <<" times"<<endl;
    return ret;
}

class ValCrypt{

    //got a new idea-
    // generate junk data.. maybe reverse and hash the msg+random stuffs
    // use pass to generate hs key
    // copy key= cpy
    // use junk to suppliment that key with ms = key
    // enc msg with key = Enc
    // generate some data that equates by hash to the number of junk bytes = tail
    // -- last byte says how many bytes are in tail by EK possition
    // append enc to junk = msg2
    // append tail to msg2 = msg2
    // use cpy to crypt msg2 = Enc2
    
    // export Enc2

    // extract last byte form msg
    
    //make copy of newly generated key
    // dec msg with pass generated key
    // use late byte to query key for tail length
    // remove tail and calculate junk length
    // remove junk and suppliment key copy
    // left with internal msg
    // dec with supplimented key for decMSG



	private:

      unsigned char KEY[256];
      unsigned char SKEY[128];
      unsigned char KEY_c[256];
      unsigned char SKEY_c[128];
      int kswaps;
//	  unsigned char WorkEK[257];
	
    public:
	  ValCrypt(string pass, int pin);
	  ValCrypt();
	  bool do_cycle;
	  void start(string pass, int pin);  // returns corresponding Encryption Key
	  void encrypt(char * data, int Len, char *ret);
	  void decrypt(char * data, int Len, char *ret);
	  void EKout(bool);
	  int indexof(unsigned char);
	  int SKindexof(unsigned char);
      void swapkey(int,int);
      string val_pwhash(string pw);
      void RotateEK(unsigned short times);
      string strencrypt(const string &data);
      string strdecrypt(const string &data);
      string encrypt(string data);
      string decrypt(string data);
      void fillSKEY();
      string encrypt_Sk(string dat);
      string decrypt_Sk(string dat);
      string encrypt_Skr(string dat);
      string decrypt_Skr(string dat);
      void RotateSK();

      unsigned int uinthalf = ((unsigned int)-1) / 2;
      //beta:
      unsigned long long int swapkey_calls = 0;

      unsigned int super_swap(unsigned int seed, short depth, int &wrap) {

          //absolutely MUST swap seed with some other index
          seed %= 256;
          for (int i = 0; i < depth; i++) {
              

              seed += KEY[KEY[seed]];
              seed %= 256;
              swapkey(seed, KEY[(KEY[seed]+1)%256]);
              if (seed % 64 == 13 && depth<3)depth++;
              seed += KEY[KEY[KEY[seed]]];
              seed %= 256;
              swapkey(seed, KEY[KEY[KEY[KEY[seed]]]]);


              if (seed > 2)seed -= 3;
              swapkey(seed, KEY[(KEY[seed] + 15) % 256]);
              wrap += KEY[(KEY[seed] + 1) % 256];
              seed += (wrap / (seed + depth)) * KEY[seed];
              seed %= 256;
              swapkey(seed, wrap % 256);
              if (wrap > uinthalf)wrap /= depth+1;
              super_swap(seed, depth - 1,wrap);

          }
          return seed;
      }
      // expand string folding
      string xor_expand_stringf(string str) {
          string ret = "";
          string firsth = str.substr(0, str.length() / 2);
          string secndh = str.substr(str.length() / 2);
          char hold;
          int len = str.length() / 2;
          if (str.length() % 2)ret += firsth[0] ^ secndh[secndh.length() - 1];
          for (int i = 0; i < len; i++) {
              hold = firsth[i] ^ secndh[i];
              ret += firsth[i];
              ret += hold;
              ret += secndh[i];
          }
          
          return ret;
      }
      // expand string linear
      string xor_expand_stringl(string str) {
          string ret = "";

          char hold;
          int len = str.length()-1 ;
          ret += str[0];
          for (int i = 0; i < len; i++) {
              hold = str[i] ^ str[i + 1];
              ret += hold;
              ret += str[i + 1];
          }
          return ret;
      }
      string xor_collapse_stringf(string str) {
          string ret = "";
          string firsth = str.substr(0, str.length() / 2);
          string secndh = str.substr(str.length() / 2);
          char hold;
          int len = str.length() / 2;
          for (int i = 0; i < len; i++) {
              hold = firsth[i] ^ secndh[i];
              
              ret += hold;
              
          }
          return ret;
      }
      string xor_collapse_stringl(string str) {
          string ret = "";

          char hold;
          int len = str.length() / 2;
          for (int i = 0; i < len; i++) {
              hold = str[i] ^ str[i+1];
              ret += hold;

          }
          return ret;
      }
      string cycle_stringa(string &str, int reps=1000) {
          char hold;
          unsigned int index = str.length() / 2 - str.length() / 13;
          unsigned int slen = str.length();
          unsigned int nindex;
          //cout << slen << "string length " << endl;
          for (int i = 0; i < reps; i++) {
              hold = str[index];
              nindex = (hold * index) % slen;
              //cout << "index:nindex  " << index << ":" << nindex << endl;
              str[index] = str[nindex];
              
              str[nindex] = hold;
              
              index = (nindex * 105 - 1) % str.length();
          }
          return str;


          
      }
      // attempt at a proprietary cryptographic hash function
      string crypto_pwhash(string pw, int maxl, int reps=1 ) {
          string ret = xor_expand_stringf(pw);
          //string slide = xor_expand_stringf(ret);
          int maxll = maxl * 4;
          for (int i = 0; i < reps; i++) {
              ret = xor_expand_stringf(ret);
              ret += xor_expand_stringl(ret);
              cycle_stringa(ret, ret[ret.length()-3] * 3);

              while (ret.length() > maxll)ret = xor_collapse_stringf(ret);
          }
          //cout << "valcryptohash out of expand loop";
          BYTE* rett;
          while (ret.length() > maxl)ret = xor_collapse_stringl(ret);
          for (int ii = 0; ii < ret.length(); ii++) {
              rett = (BYTE*)&ret[ii];
              while (*rett > 127)*rett -= *rett / 3;
              while (*rett < 32)*rett+= (*rett*3)+1;
              while (*rett > 127)*rett -= *rett / 7;
          }
          //cout << "valcryptohash out of visibile loop";
          
          return ret;
      }

      void startHighSecurity(string pass, int pin) {
          kswaps = 0;
          string ps_hash = pass;
          for (int i = 0; i < 256; i++) {// reset EK to base values
              KEY[i] = i;
          }
          for (int i = 0; i < 5; i++) {
              ps_hash = crypto_pwhash(ps_hash,64,2);
          }
          int pos = 0, opos = 0;
          //use ps_hash to scramble key;
          int wrap = 0;
          for (int i = 0; i < 10; i++) {
              for (int m = 0; m < ps_hash.length(); m++) {
                  opos = pos;
                  pos += (BYTE)ps_hash[m];
                  pos %= 256;
                  //swapkey(pos, opos);
                  super_swap(pos * opos, 5, wrap);
              }
          }

          int tot = 0;
          while (pin != 0) {
              tot += pin % 10;
              pin = pin / 10;
          }
          RotateEK(tot);
          for (int i = 0; i < 256; i++) {
              if (KEY[i] == 0) swapkey(0, i);
              if (KEY[i] == 1) swapkey(1, i);
              if (KEY[i] == '\n') swapkey((unsigned short)'\n', i);
          }

          fillSKEY();
          return;
      }

      int swapskcalls = 0;
      void swap_sk(int i, int n) {
          if (i < 33 || n < 33 || i == n)return;
          //if (i == n)return;
          swapskcalls++;
          unsigned char h1 = SKEY[i];
          SKEY[i] = SKEY[n];
          SKEY[n] = h1;
      }

      unsigned int super_swap_sk(unsigned int seed, short depth, int& wrap) {
          if (seed < 34)return 0;
          seed %= 84;
          seed += 33;
          
          for (int i = 0; i < depth; i++) {


              seed += SKEY[SKEY[seed]];
              seed %= 84;
              seed += 33;
              swap_sk(seed, SKEY[((SKEY[seed] + 1) % 84)+33]);

              //if (seed % 64 == 13 && depth < 2)depth++;
              seed += SKEY[SKEY[SKEY[seed]]];
              seed %= 84;
              seed += 33; 
              swap_sk(seed, SKEY[SKEY[SKEY[SKEY[seed]]]]);


              if (seed > 35)seed -= 3;
              swap_sk(seed, SKEY[((SKEY[seed] + 15) % 84)+33]);
              wrap += SKEY[((SKEY[seed] + 1) % 84)+33];

              swap_sk(seed, (wrap % 84)+33);
              if (wrap > uinthalf)wrap /= depth;
              super_swap_sk(seed, depth - 1, wrap);

          }
          return seed;
      }

      string decrypt_Sksr(string data) {
          string ret = "";
          char sd;
          int wrap = 0;
          for (int i = 0; i < data.length(); i++) {
              sd = (char)SKindexof((BYTE)data[i]);
              ret += sd;
              //super_swap_sk((unsigned int)sd, ((unsigned int)sd % 3) + 1, wrap);
              super_swap_sk(sd, 6, wrap);
              RotateSK();
          }
          return ret;
      }
      string encrypt_Sksr(string data) {
          string ret = "";
          int wrap = 0;
          char a;
          for (int i = 0; i < data.length(); i++) {
              a = (char)SKEY[(BYTE)data[i]];
              ret += a;
              //super_swap_sk((unsigned int)data[i], ((unsigned int)data[i] % 3) + 1, wrap);
              a = data[i];
              super_swap_sk(a, 6, wrap);
              RotateSK();
          }
          return ret;
      }


      void copy_ek() {
          memcpy(KEY_c, KEY, 256);
          memcpy(SKEY_c, SKEY, 256);
      }
      void paste_ek() {
          memcpy( KEY, KEY_c, 256);
          memcpy(SKEY, SKEY_c, 256);
      }
      void refresh_sk() {
          fillSKEY();
      }
      int indexof_c(unsigned char a) {
          for (int i = 0; i < 256; i++) {
              if (KEY_c[i] == a) return i;
          }
          return -1;
      }
      //encrypts file named fnamein to file named fnameout
      //basic, no perturbations, copy ek, work on copy
      //does not delete source file
      void encrypt_binfile(string fnamein, string fnameout) {
          ifstream ifile((char*)fnamein.c_str(), ios::binary);
          ofstream ofile((char*)fnameout.c_str(), ios::binary);
          if (!ifile.good() || !ofile.good()) {
              cout << "cannot open files, in: " << fnamein << " out: " << fnameout << "\n";
              pause();
              return;
          }
          copy_ek();
          BYTE target;
          while (!ifile.eof()) {
              ifile >> target;
              ofile << KEY_c[target];
          }
          ifile.close();
          ofile.close();

      }
      //encrypts file named fnamein to file named fnameout
    //basic, no perturbations, copy ek, work on copy
      //does not delete source file
      void decrypt_binfile(string fnamein, string fnameout) {
          ifstream ifile((char*)fnamein.c_str(), ios::binary);
          ofstream ofile((char*)fnameout.c_str(), ios::binary);
          if (!ifile.good() || !ofile.good()) {
              cout << "cannot open files, in: " << fnamein << " out: " << fnameout << "\n";
              pause();
              return;
          }
          copy_ek();
          BYTE target;
          while (!ifile.eof()) {
              ifile >> target;
              ofile << indexof_c(target);
          }
          ifile.close();
          ofile.close();

      }

      
      /**********************end beta block ********************/
}Vc;

void ValCrypt::fillSKEY(){
    // written 2009, read 2020- notes:
    // I am reviving this old project and on VC2020, normal encrypt crashes but sk encrypt works as intended
    // this seems to be filling only the chars for 9,10,13 and 33-126 in the SKEY.  meaning 0-33 except those stated are 0.
    for(int i = 0; i < 127; i++)SKEY[i]=(unsigned char)0;
    int i = 0;
    
    while(KEY[i]!=10 &&KEY[i]!=13&& KEY[i]!=9 && !(KEY[i]>32 && KEY[i]<127))i++;  //find first visible char
    SKEY[10]=KEY[i];
    i++;
    while(KEY[i]!=10 &&KEY[i]!=13&& KEY[i]!=9 && !(KEY[i]>32 && KEY[i]<127))i++;  //find first visible char
    SKEY[13]=KEY[i];
    i++;
    while(KEY[i]!=10 &&KEY[i]!=13&& KEY[i]!=9 && !(KEY[i]>32 && KEY[i]<127))i++;  //find first visible char
    SKEY[9]=KEY[i];
    i++;
    for(int x = 33; x < 127; x++){
        while(KEY[i]!=10 &&KEY[i]!=13&& KEY[i]!=9 && !(KEY[i]>32 && KEY[i]<127))i++;
        SKEY[x] = KEY[i];
        i++;
    }
}
string ValCrypt:: val_pwhash(string pw){
    if (pw.length() == 0)return "";
	string ret="",ret2="";
	for( int i = 0; i < pw.length()-1; i++){		
		ret += (char)(pw[i]+pw[i+1])/2;
		ret += (char)(pw[i]%64);
		ret += (char)((pw[i]+pw[i+1])%128);
    }
	for( int i = 0; i < (pw.length()/2)-1; i++)		
		ret2 += (char)((pw[i]+pw[pw.length()-(i+1)]) /2);

	return ret+ret2;
}

void ValCrypt::EKout(bool doout=true){
    bool done[256];
    for(int i=0; i < 256; i++){
      done[i]=false;
      if(doout)  cout << i << " : "<< KEY[i]<< " : " << (int)KEY[i]<<endl;  
    }
    system("PAUSE");
    bool redund=false;
    for(int i=0; i < 256; i++){
        if(done[KEY[i]]){
            redund = true;
            cout << "redundancy found in EK:   " << KEY[i] <<endl;
            for( int b = 0; b < 256; b++){
                if(KEY[b] == KEY[i]){
                    cout << "at: "<<b << ":"<<i<<endl;
                }
            }
            cout << "reddone"<<endl;
        }
        else
            done[KEY[i]] = true;
    }
    bool allchar = false;    
    for(int i=0; i < 256; i++){
        if(!done[i]){
            allchar = true;
            cout << "missing char in ek " << i << " : " << KEY[i] << endl;
       }
    }
    if(!redund) cout << "no redundancies found " << endl;
    if(!allchar) cout << "EK integrity check: success"<<endl;
    cout << "done checking " << endl;
}



ValCrypt::ValCrypt(string pass,int pin){
	for( int i = 0; i < 256; i++){
		KEY[i] = (unsigned char)i;
	}
//	EKout();
	do_cycle=false;
	start(pass,pin);
	vcdebug("finished constructing EK");
}
ValCrypt::ValCrypt(){
	ValCrypt("default",1357);
}


void ValCrypt::swapkey(int i, int n){
    if(i==n)return;
    swapkey_calls++;
    unsigned char h1= KEY[i],h2= KEY[n];
    kswaps++;
    KEY[i] = h2; 
    KEY[n] = h1;
}

void ValCrypt::RotateEK(unsigned short times){
    unsigned char a=KEY[0],b;
    for(int i = 1; i < 256; i++){
        b= KEY[i];
        KEY[i]=a;
        a=b;
    }
    KEY[0] = a;
}
    


void ValCrypt::start(string pass, int pin){
    kswaps=0;
	string ps_hash=pass;	
	for( int i = 0; i < 256; i++){// reset EK to base values
		KEY[i] = i;
	}
	for(int i = 0; i < 5; i++){
		ps_hash = val_pwhash(ps_hash);
	}	
	int pos = 0,opos=0;
	//use ps_hash to scramble key;
	for(int i = 0; i < 10; i++){
		for(int m = 0; m < ps_hash.length(); m++){
			opos=pos;
			pos += 	(unsigned char)ps_hash[m];
            pos = (pos > 255 ? pos-256 : pos); 
            swapkey(pos,opos);	 
		}
	}

    int tot = 0;
    while(pin!=0){
        tot += pin%10;
        pin = pin/10;
    }
	RotateEK(tot);
    for(int i = 0; i<256; i++){
        if(KEY[i] == 0) swapkey(0,i);
        if(KEY[i] == 1) swapkey(1,i);
        if(KEY[i] == '\n') swapkey((unsigned short)'\n',i);
    }  

    fillSKEY();
    return;
}
	

void ValCrypt::encrypt(char * data, int Len, char *ret){
	for(int i = 0; i < Len; i++){
		ret[i] = KEY[(unsigned char)data[i]];
	}
}

int ValCrypt::indexof(unsigned char a){
    for( int i = 0; i < 256; i++){
        if(KEY[i] == a) return i;
    }
    return -1;
}

void ValCrypt::decrypt(char * data, int Len,char *ret){
	for(int i = 0; i < Len; i++){
		ret[i] = (char)indexof((unsigned char)data[i]);
    }
}

string ValCrypt::strencrypt(const string &data){
	string ret="";
    for(int i = 0; i < data.length(); i++){
		ret[i] = KEY[(unsigned char)data[i]];
	}
	return ret;
}
string ValCrypt::strdecrypt(const string &data){
    string ret="";
    for(int i = 0; i < data.length(); i++){
		ret += (char)indexof((unsigned char)data[i]);
    }
    return ret;
}
string ValCrypt::encrypt(string data){
    char *ret= new char[data.length()];

    encrypt((char*)data.c_str(),data.length(),(char*)ret);
    string retu = ret;
    delete[] ret;
    return retu;
}
string ValCrypt::decrypt(string data){
    char *ret=new char[data.length()+1];
    decrypt((char*)data.c_str(),data.length()+1,(char*)ret);
    string retu = ret;
    delete[] ret;
    return retu;
}
string ValCrypt::encrypt_Sk(string data){
	string ret="";
    for(int i = 0; i < data.length(); i++){
		ret += (char)SKEY[(unsigned char)data[i]];
    }
	return ret;
}

int ValCrypt::SKindexof(unsigned char a){
    for( int i = 0; i < 127; i++){
        if(SKEY[i] == a) return i;
    }
    return -1;
}
string ValCrypt::decrypt_Sk(string data){
    string ret="";
    for(int i = 0; i < data.length(); i++){
		ret += (char)SKindexof((unsigned char)data[i]);
    }
    return ret;
}
void ValCrypt::RotateSK() {
    char f = SKEY[33], a,b;
    for (int i = 34; i < 127; i++) {
        SKEY[i - 1] = SKEY[i];
    }
    SKEY[126] = f;
}
/*
swapsk  copy of swapek for sk, inline
superswap_sk copy of superswap for SK.  create number, mod 86 instead of 256, add 33. 
*/
string ValCrypt::decrypt_Skr(string data) {
    string ret = "";
    for (int i = 0; i < data.length(); i++) {
        ret += (char)SKindexof((unsigned char)data[i]);
        RotateSK();
    }
    return ret;
}
string ValCrypt::encrypt_Skr(string data) {
    string ret = "";
    for (int i = 0; i < data.length(); i++) {
        ret += (char)SKEY[(unsigned char)data[i]];
        RotateSK();
    }
    return ret;
}
#undef string

#endif
