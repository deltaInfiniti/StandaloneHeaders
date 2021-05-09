#ifndef valwrapper_def
#define valwrapper_def

#define ctocp(ch) ((char*)ch.c_str())
#define GetPhysicalCursorPos(p) GetCursorPos(p) 
#define SetPhysicalCursorPos(x,y) SetCursorPos(x,y)
#define SHOW(a) cout << #a << ": " << (a) << "   "<<endl;
#define SHOWf(a,b) b << #a << ": "<< (a) << endl;
#define ctoint(s) atoi(s.c_str())
#define csl_pop(str) tokenizecsl(str)
#define ShowConsole() ShowWindow(GetConsoleWindow(),SW_SHOW);
#define HideConsole() ShowWindow(GetConsoleWindow(),SW_HIDE);
#define foreach(a,b) for(int a=0; a < b; a++)

#pragma comment(lib,"ws2_32")
#include <cstdlib>
#include <iostream>
//#include <wininet.h>
#include <windows.h>
//#include <winsock2.h>
#include <fstream>  
#include <varlist.h>

using namespace std;
static DWORD wsa_error;
#define BAD_SOCK(sock) wsa_error = GetLastError(); closesocket(sock); WSACleanup(); return ;

void vlog(string w,string fn="log.txt", bool nl=true){
    if(nl) w = "vlog: "+w;
    ofstream ofile(fn.c_str(),ios::app);
    if(!ofile.good()){ Sleep(50); vlog(w,fn,nl); return;}
    ofile << w; 
    if(nl) ofile << endl;
    ofile.close();
//    cout << w;
//    if(nl) cout << endl;
}

  
//void appendfile(string fn, string w){
//    ofstream ofile(fn.c_str(),ios::app);
//        if(ofile.good()){
//            ofile << w;
//            ofile.close();
//        }
//    return;
//}
//void writefile(string fn, string w){
//    ofstream ofile(fn.c_str());
//        if(ofile.good()){
//            ofile << w;
//            ofile.close();
//        }
//    return;
//}

#endif // valwrapper_def

#ifndef valwrapper_CORE
#define valwrapper_CORE

class valwrapper{

  private:
    string domain;
    
    int vwmilsec,vwmilmil,last_time;
    bool USE_PROXY;
    unsigned short VWPROXYPORT;
    string VWPROXY;
    struct hostent *target_ptr;
    WSADATA wsaData;
    SOCKET sock; 
    struct sockaddr_in sin;     

        void vw_parse();
        void ws_request(string prot,unsigned short port,string uri, string postdata,string extraheaders);
        void ws_request(string prot,unsigned short port,string uri, string postdata){ws_request(prot,port,uri,postdata,"");};
        void vw_download(string prot, string host, unsigned short port, string uri,string filename,string extraheaders, string postdat);
        
        void cut_headers();
        void parsecooks();
        string getcooks();
        

  public:
      string getdomain() { return domain; }
    varlist cookies;
    bool use_gz,do_parse;
    void reinit(string dom);
    bool init_proxy(string ip, unsigned short pt);
    string cursource;
    string headers;
    ~valwrapper();
    valwrapper();   
    valwrapper(string dom);
    void get(string filename);
    void get(string filename,string referer);
    void post(string filename,string data);
    void post(string filename,string data, string referer);
    void dl(string page, string fname);   
    //void dl_gz(string page, string fname); 
    //void gz_get( string page, string referer);
    //void gz_post( string page, string data, string referer);
    void time_s();
    int time_e();
    int GetLastTime(){return last_time;};
    int glt(){return last_time;};
};

    
bool valwrapper::init_proxy(string ip,unsigned short pt){
    VWPROXY=ip;
    VWPROXYPORT=pt;
    USE_PROXY=true;
    return true;
}
    
void valwrapper::time_s(){
    vwmilsec = timestamp();
    vwmilmil = millitime();
}
int valwrapper::time_e(){
    int i=millitime();
    int a=(timestamp() - vwmilsec)*1000;
    int b = (1000-vwmilmil)+i;
    b-=1000;
//    int b=(i<vwmilmil?((-1000)+(vwmilmil-i)):(i-vwmilmil));
    last_time=a+b;
    return (a+b);
}
void valwrapper::dl(string page, string fname){
    time_s();
    vw_download("GET",domain,80,page,fname,"","");
    time_e();
}
/*
#include<gzstream.cpp>
void valwrapper::dl_gz(string page, string fname){
    time_s();
    vw_download("GET",domain,80,page,"tmp.gz","Accept-Encoding:gzip,deflate","");
    gz::igzstream in("tmp.gz");
    cursource="";
    string line;
    while(getline(in, line)){    
        cursource+= line+"\n";
    }
    time_e();
}
void valwrapper::gz_get( string page, string referer){
    if(page[0] != '/') page = "/"+page;
    if(referer != "")
        referer = "\r\nReferer: " + referer;
    
    time_s();
    cout << "before vw_download in gz_get" << endl;

    vw_download("GET",domain,80,page,"tmp.gz","Accept-Encoding:gzip,deflate"+referer,"");
    gz::igzstream in("tmp.gz");
    cursource="";
    string line;
    while(getline(in, line)){    
        cursource+= line+"\n";
    }
    time_e();
    _unlink("tmp.gz");
    
}
void valwrapper::gz_post( string page, string data, string referer){
    if(page[0] != '/') page = "/"+page;
    if(referer != "")
        referer = "\r\nReferer: " + referer;
    
 
    time_s();
    vw_download("POST",domain,80,page,"tmp.gz","Accept-Encoding:gzip,deflate"+referer,data);
    
    gz::igzstream in("tmp.gz");
    cursource="";
    string line;
    while(getline(in, line)){    
        cursource+= line+"\n";
    }
    time_e();
    _unlink("tmp.gz"); 
}   
*/
#define flog(a)  // writefile("fail.txt",ctostr(a));
void valwrapper::vw_download(string prot, string host, unsigned short port, string uri,string filename,string extraheaders, string postdata){

	int recvBytes = 0;
	string totalSize="";
	int fileSize=0;    
//    struct hostent *target_ptr;
    WSADATA wsaData;
    SOCKET sock; 
//    struct sockaddr_in sin;     
    char * recv_string;
    unsigned short nret;
    char data[1224];  
	unsigned long int totalbytes = 0;
    flog(1);
    string cooks = getcooks();
    
    string req = prot+ " "+uri+ " HTTP/1.0\r\n"; 
    req += "Host: "+domain+"\r\n";
    if(postdata.length()>0) req += "Content-Length: "+ctostr(postdata.length())+"\r\n"; 
    req += "Connection: close\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    
    //req += "Accept: text/plain\r\n";
    //req += "Keep-Alive:115"; 
    req += extraheaders+cooks+"\r\n\r\n"+postdata;
    writefile("req.txt",req);
    char  *httprequest= new char[req.length()+2];
    flog(2);
    sprintf(httprequest,"%s",req.c_str());    
    
    if (WSAStartup(MAKEWORD(2,2), &wsaData) < 0) { cout << "wsa startup failed" << endl; return ;}
//    if ((target_ptr = gethostbyname(domain.c_str())) == NULL){  BAD_SOCK(sock);  }
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){ BAD_SOCK(sock);  } 
    flog(3);
//    memcpy(&sin.sin_addr.s_addr, target_ptr->h_addr, target_ptr->h_length);
//	sin.sin_port = htons(port);
//	sin.sin_family = AF_INET;
	
	if ((connect(sock, (struct sockaddr *)&sin, sizeof(sin)))) {BAD_SOCK(sock);}
	if (send(sock, httprequest, strlen(httprequest), 0) == -1) {BAD_SOCK(sock);}

    flog(4);    
    recv_string = (char*)malloc(2);
	strcpy(recv_string, "");
	FILE *fwt;
	fwt = fopen((char*)filename.c_str(), "wb");
    flog(5);
	while ((nret = recv(sock, data, 1124, 0)) > 0) {
	//	string sData = data;
//		if (filesize ==0 && sData.find("Content-Length: ") != -1) {
//			totalSize = getbetween(sData, "Content-Length: ", "Server",0);
//			fileSize = (atoi(totalSize.c_str()) / 1124); 
//
//		} 
        flog(56);
		recv_string = (char*)realloc(recv_string, totalbytes + nret + 2);
		flog(57);
        memcpy(totalbytes + recv_string, data, nret);
		flog(58);
        totalbytes += nret; 
		//recvBytes += sizeof(nret);
		//if (fileSize != 0)
			//setStatus("Status: Downloaded ~ " + ctostr(recvBytes) + "/" + ctostr(fileSize) + " KB!");
	}
	flog(6);
	for(int i = 0; i < totalbytes - 5; i++) {
		if(recv_string[i] == '\r' && recv_string[i+1] == '\n' && recv_string[i+2] == '\r' && recv_string[i+3] == '\n' ) {
			fwrite(recv_string + i + 4, 1, totalbytes - (i + 4), fwt);
			break;
		}
	}
	flog(7);
    if(do_parse){
        cursource=recv_string;
	    vw_parse();
    }
    fclose(fwt);
	closesocket(sock);
	WSACleanup();
	flog(8);
	delete[] httprequest;
	free(recv_string);
	flog(9);
}


void valwrapper::get(string filename){
    cursource="";
    //if(use_gz){ gz_get(filename,""); return ;}
    time_s();
    if(filename[0] != '/') filename = "/"+filename;
    this->ws_request("GET",80,filename,"","");
    time_e();
}

void valwrapper::post(string filename,string data){
    cursource="";
    //if(use_gz){ gz_post(filename,data,""); return ;}
    time_s();
    if(filename[0] != '/') filename = "/"+filename;
    ws_request("POST",80,filename,data,"");
    time_e();
}

void valwrapper::get(string filename,string referer){
    cursource="";
    //if(use_gz){ gz_get(filename,referer); return ;}
    time_s();
    if(filename[0] != '/') filename = "/"+filename;
    if(referer != "")
        referer = "\r\nReferer: " + referer;

    ws_request("GET",80,filename,"",referer);
    time_e();
}

void valwrapper::post(string filename,string data,string referer){
    cursource="";
    //if(use_gz){ gz_post(filename,data,referer); return ;}
    time_s();
    if(filename[0] != '/') filename = "/"+filename;
    if(referer != "")
        referer = "\r\nReferer: " + referer;
    
    ws_request("POST",80,filename,data,referer);
    time_e();
}



void valwrapper::parsecooks(){
 int ind = 0,indt=0;;
 string temp,n,v; 
  while(1){
    ind = findnext(headers,"Set-Cookie: ",ind);
    if(ind == -1) break;
    temp = getbetween(headers,"Set-Cookie: ","; ",ind-3);
    if(!instr(temp,"=")){
        ind+= 1;
        if(ind > headers.length()) return;
        continue;
    }
    breakarg(temp,n,v);
    cookies.set(n,v);
    ind +=1;
 }
}    

void valwrapper::cut_headers() {
// no longer used.
}

string valwrapper::getcooks(){
    return cookies.cookieval();
}
void valwrapper::vw_parse(){
    
    headers.clear();
    if(cursource.length() < 5) return;
    while(cursource.length()>3){
        if(strspn(cursource.c_str(),"\r\n\r\n")==4){
             cursource.erase(0,4);
             break;
        }
        headers+=cursource[0];
        cursource.erase(0,1);
    }
    writefile("head.txt",headers);
    parsecooks();
}
        
void valwrapper::reinit(string dom){
    if(dom!=domain){
        cookies.clear();
        domain = dom;
    }
    
    if (WSAStartup(MAKEWORD(2,2), &wsaData) < 0) { cout << "wsa startup failed" << endl; return ;}
    sin.sin_port   = htons(80);
    if(USE_PROXY) sin.sin_port   = htons(VWPROXYPORT);
    
    sin.sin_family = AF_INET;
    if(USE_PROXY){
         sin.sin_addr.s_addr = inet_addr(VWPROXY.c_str());         
    }     
    else{
        if ((target_ptr = gethostbyname(domain.c_str())) == NULL){  BAD_SOCK(sock);  }
        memcpy(&sin.sin_addr.s_addr, target_ptr->h_addr, target_ptr->h_length);
    
    }
    
//    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){ BAD_SOCK(sock);  } 
    //if ((connect(sock, (struct sockaddr *)&sin, sizeof(sin)))){BAD_SOCK(sock);}

}

void valwrapper::ws_request(string prot, unsigned short port, string uri, string postdata,string extraheaders){
    
    
    
    //char * recv_string;
    unsigned short nret=0;
    char data[1012]; 
    unsigned long bytes_received=0;
    
    string cooks = getcooks();
    
    string req = prot+ " "+uri+ " HTTP/1.0\r\n"; 
    req += "Host: "+domain+"\r\n";
    req += "Content-Length: "+ctostr(postdata.length())+"\r\n"; 
    req += "Connection: close\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Accept: text/html\r\n";
    req += "Keep-Alive:115"; 
    req += extraheaders+cooks+"\r\n\r\n"+postdata;
    
    char * httprequest=new char[req.length()+1];
    sprintf(httprequest,"%s",req.c_str());
    
    if (WSAStartup(MAKEWORD(2,2), &wsaData) < 0) { cout << "wsa startup failed" << endl; return ;}
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){ BAD_SOCK(sock);  }     
    if ((connect(sock, (struct sockaddr *)&sin, sizeof(sin)))){BAD_SOCK(sock);}
    if (send(sock, httprequest, (int)strlen(httprequest), 0) == -1){BAD_SOCK(sock);}

    cursource="";
    while ((nret = recv(sock, (char*)&data, 1000, 0)) > 0) { 
        bytes_received += nret;
        cursource.append(data,nret);
    }
    
    headers = cursource;
    closesocket(sock);
    WSACleanup();  
    delete[] httprequest;
    //free(recv_string); 
    vw_parse();
}

valwrapper::valwrapper(string dom ){
    //use_gz = false;
    do_parse=true;
    USE_PROXY=false;
    reinit(dom);
}

valwrapper::valwrapper(){
    valwrapper("");
    USE_PROXY=false;
}

valwrapper::~valwrapper(){

}

#endif
