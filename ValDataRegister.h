#pragma once
// replaces register data on windowmanager and associated data on window 

#include<string>
#include<iostream>
#define string std::string 

//attempt at fast compare strings for string sorting
//compare to abcomp from valutils.h for speed
// returns 0 if same, -1 if a is 'lower', 1 if b is 'lower'
int string_compare_best(const string& a, const string& b) {
	int c = 0;
	if ((c=a.length() - b.length())!=0) {
		return (c < 0 ? -1 : 1);
	}
	c = a.length();
	int d = 0;
	for (int i = 0; i < c; i++) {
		if ((d = (a[i] - b[i])) != 0) return (d < 0 ? -1 : 1);

	}
	return 0;
}
int string_compare2(const string& a, const string& b) {
	unsigned short al= a.length();
	if (al != b.length()) {
		return (al < b.length() ? -1 : 1);
	}
    short c = 0;
	for (int i = 0; i < al; i++) {
		if ((c = (a[i] - b[i])) != 0) return (c< 0 ? -1 : 1);

	}
	return 0;
}
//attempt at a bogo string compare for speed.
// cannot true sort list or fast may consider a 'lower' string 'higher' 
//not faster... first itteration is basically as optimized as I can make it
short string_compare_fast(const string& a, const string& b) {
	int c = 0;
	if ((c = a.length() - b.length()) != 0) return (c < 0 ? -1 : 1);
	
	
	int d = 0,l = a.length();
	c = l / 2;
	l--;
	BYTE* aa = (BYTE*)&a[0], * bb = (BYTE*)&b[0];// , * aaa = aa + l, * bbb = bb + l;
	for (int i = 0; i < c; i++) {
		if (*aa != *bb)return (*aa < *bb ? -1 : 1);
		//if (*aaa != *bbb)return (*aaa < *bbb ? -1 : 1);
		aa++; bb++;// aaa--; bbb--;
	}
	//for (int i = 0; i < c; i++) {// double ended equality check
	//	if ((d = (a[i] - b[i])) != 0) return (d < 0 ? -1 : 1);
	//	if ((d = (a[l-i] - b[l-i])) != 0) return (d < 0 ? -1 : 1);
	//}
	return !(a[0]==b[0]);//return 0 if there's only 1 letter in a&b and they're the same
}
#define VDNtype_NOTSET 0
#define VDNtype_function 1
#define VDNtype_thread 2
#define VDNtype_variable 3

#define ValDN valDataNode
struct valDataNode {
	ValDN* next = NULL;
	ValDN* last = NULL;
	void* data = NULL;
	string name = "";
	char type = 0;
};

void ValDN_insert(ValDN* before, ValDN* what) {
	if (before->next != NULL) {
		before->next->last = what;
		what->next = before->next;
	}
	before->next = what;
	what->last = before;
}

ValDN* ValDN_extract(ValDN* what) {
	ValDN* l = what->last;
	ValDN* n= what->next;
	l->next = n;
	if(n!=NULL)n->last = l;
	what->next = NULL;
	what->last = NULL;
	return what;
}
/**************global valnode bank***************/
// holds a bunch of pre-new'd valdatanode s for easy access to fast-dieing threads
//global to reduce on number of banks that need monitoring.  ram for performance trade.
// expect fewer than 1000 registered data points in a program
//valscript will likely use this class to register it's data, may need more than 1000 nodes.
//   even with heavy recycling
//call _fill in main thread on load and periodically to keep stores filled
static ValDN* GLOBAL_VALDATANODE_BANK = NULL;
static ValDN* GLOBAL_VALDATANODE_BANK_END = NULL;
static int GLOBAL_VALDATANODE_BANK_LENGTH = 0;
#include<mutex>
static std::mutex GLOBAL_VALDATANODE_BANK_MUTEX;
void RESERVED_GLOBAL_VALDATANODE_BANK_FILL(int size = 30000) {
	
	if (GLOBAL_VALDATANODE_BANK == NULL)GLOBAL_VALDATANODE_BANK = new ValDN;
	if (GLOBAL_VALDATANODE_BANK_END == NULL)GLOBAL_VALDATANODE_BANK_END = new ValDN;
	if (GLOBAL_VALDATANODE_BANK_LENGTH == 0) {
		GLOBAL_VALDATANODE_BANK->next = GLOBAL_VALDATANODE_BANK_END;
		GLOBAL_VALDATANODE_BANK_END->last = GLOBAL_VALDATANODE_BANK;
	}
	int sizel= size - GLOBAL_VALDATANODE_BANK_LENGTH;
	GLOBAL_VALDATANODE_BANK_MUTEX.lock();
	for (int i = 0; i < sizel; i++) {
		ValDN_insert(GLOBAL_VALDATANODE_BANK, new ValDN);
	}
	 GLOBAL_VALDATANODE_BANK_LENGTH=size  ;
	 GLOBAL_VALDATANODE_BANK_MUTEX.unlock();
	
}

ValDN* GLOBAL_VALDATANODE_BANK_GET() {
	GLOBAL_VALDATANODE_BANK_MUTEX.lock();
	if (GLOBAL_VALDATANODE_BANK_LENGTH == 0) {
		std::cout << "GLOBAL_VALDATANODE_BANK get failed, no nodes in bank\n";
		std::cout << "bank len: " << GLOBAL_VALDATANODE_BANK_LENGTH << endl;
		int i = 0;
		ValDN* t = GLOBAL_VALDATANODE_BANK;
			while (t->next != NULL) {
				cout << i++ << " ";
				t = t->next;
			}
		GLOBAL_VALDATANODE_BANK_MUTEX.unlock();
		return NULL;
	}

	ValDN*ret= ValDN_extract(GLOBAL_VALDATANODE_BANK->next);

	GLOBAL_VALDATANODE_BANK_LENGTH--;
	GLOBAL_VALDATANODE_BANK_MUTEX.unlock();
	return ret;
}
ValDN* GLOBAL_VALDATANODE_BANK_GET(string name, void* data) {
	ValDN* ret = GLOBAL_VALDATANODE_BANK_GET();
	ret->name = name;
	ret->data = data;
	return ret;
}
void GLOBAL_VALDATANODE_BANK_RECYCLE(ValDN* what){
	what->next = NULL;
	what->last = NULL;
	what->name = "";
	what->data = NULL;
	GLOBAL_VALDATANODE_BANK_MUTEX.lock();
	ValDN_insert(GLOBAL_VALDATANODE_BANK_END->last,what);
	GLOBAL_VALDATANODE_BANK_LENGTH++;
	GLOBAL_VALDATANODE_BANK_MUTEX.unlock();
}
//need recycle 

#include<shared_mutex>
class ValDataRegistry {
public:
	// split registry by first byte for faster searching
	// limited array length to 96-  95 for 32-126, 1 for all others.
	ValDN* start[96];
	ValDN* end[96];
	unsigned int len[96];
	unsigned int total_len = 0;
	 std::shared_mutex getsetmutex;

	ValDataRegistry() {
		for (int i = 0; i < 96; i++) {
			start[i] = GLOBAL_VALDATANODE_BANK_GET();
			end[i] = GLOBAL_VALDATANODE_BANK_GET();
			start[i]->next = end[i];
			end[i]->last = start[i];
			len[i] = 0;
		}
	}
	inline int get_findex(char v) {
		int ret = ((int)v)-32;
		if (ret > 94|| ret<0)ret = 95;
		return ret;

	}

	int lastptrtoval = NULL; // to catch lastptrto compare value
	// returns the node with name, or the node before where this name would be.
	ValDN* ptrto(string name, int* cmpval= NULL) {
		if (cmpval == NULL)cmpval = &lastptrtoval;
		unsigned int findex =get_findex(name[0]); 
		unsigned int l = len[findex];
		int temp;
		getsetmutex.lock_shared();
		ValDN* targ = start[findex]->next;
		for (int i = 0; i < l; i++) {
			temp = string_compare(targ->name, name);
			//cout << " strcomp(t->name,name): " << targ->name << " : " << name << " : " << temp << "\n";
			if ((temp) > -1) {
				*cmpval = temp;
				if (temp == 1)targ = targ->last;
				getsetmutex.unlock_shared();
				return targ;
			}
			targ = targ->next;
		}
		*cmpval = -1;
		getsetmutex.unlock_shared();
		return end[findex]->last;
	}

	void* get_data(string name) {
		if (name == "") {
			std::cout << "Error: ValDataRegistry add_genericdata cannot locate data without a name\n";
			return NULL;
		}
		int val = 0;
		ValDN* vdn = ptrto(name, &val);
		if (val != 0) {
			std::cout << "Error: ValDataRegistry get_data(" << name << ") did not find any data\n";
			return NULL;
		}
		else {
			return vdn->data;
		}

	}
	int add_genericdata(string name, void* dat, char type) {
		if (name == "") {
			std::cout << "Error: ValDataRegistry add_genericdata cannot register data without a name\n";
			return -1;
		}
		int val = 0;
		ValDN* vdn = ptrto(name, &val);
		//cout << "add_data ptrto val: " << val << endl;
		unsigned int findex = get_findex(name[0]);
		if (val != 0) {
			getsetmutex.lock();
			ValDN_insert(vdn,GLOBAL_VALDATANODE_BANK_GET(name, dat));
			len[findex]++;
			//cout <<"len[findex]++;" << len[findex]<<endl;
			//cout << "vdn,vdn->next names" << vdn->name << " : " << vdn->next->name << " \n";
			total_len++;
			getsetmutex.unlock();
		}
		else {
			std::cout << "Warning- valDataRegistry add_genericdata- data with name " << name << " already exists; overwriting\n";
			vdn->data = dat;
		}

		return val;
	}
	void remove_data(string name) {
		int val = 0;
		ValDN* vdn = ptrto(name, &val);

		if (val == 0) {
			getsetmutex.lock();
			len[get_findex(name[0])]--;
			total_len--;
			GLOBAL_VALDATANODE_BANK_RECYCLE(ValDN_extract(vdn));
			getsetmutex.unlock();
		}
		else {
			std::cout << "warning valDataRegistry remove_data: no node named " << name << " \n";
		}
	}
	void hard_remove(void* data,string name="") {
		//find target void* data and remove that node
	}

};


void coutra() { cout << "ra"; }
void test_valdataregister() {
	cout << "in test valdatarester" << endl;
	//RESERVED_GLOBAL_VALDATANODE_BANK_FILL();
	//WindowMan.startup();


	ValDataRegistry* vdr = new ValDataRegistry();
	cout << "adding data" << endl;
	vdr->add_genericdata("getticks", coutra, VDNtype_function);
	vdr->add_genericdata("getticks2", coutra, VDNtype_function);
	vdr->add_genericdata("getticks3", coutra, VDNtype_function);
	vdr->add_genericdata("getticks1", coutra, VDNtype_function);
	vdr->add_genericdata("getticks3", coutra, VDNtype_function);
	cout << "getting data" << endl;
	void* a = vdr->get_data("getticks2");
	cout << "calling function\n";
	(((void(__cdecl*)(void))(a)) ());

}

void test_stringcomp() {
	cout << string_compare("test1", "test2") <<":-1"<< endl;;
	cout << string_compare("test", "test2") << ":-1" << endl;;
	cout << string_compare("test2", "test2") << ":0" << endl;;
	cout << string_compare("4test1", "test") << ":1" << endl;;
	cout << string_compare("4tst1", "test") << ":1" << endl;;
	cout << string_compare("4test1", "3test") << ":1" << endl;;
	cout << string_compare("4test1", "werwertest") << ":-1" << endl;;
}
#define G_speedtest_size 40000

void speedtest_stringcomp() {
	string* tests= new string[G_speedtest_size];
	for (int x = 0; x < G_speedtest_size; x++)tests[x] = randstr(8 + (rand() % 8));
	int ret = 0;
	unsigned long long int mret = 0;
	
	ValStopwatch vst;
	vst.LapStart();
	for (int i = 0; i < G_speedtest_size; i++) {
		for (int n = i + 1; n < G_speedtest_size; n++) {
			ret+=string_compare2(tests[i], tests[n]);
			mret++;
		}
	}
	cout << vst.Lap()<<":time,ret:" << ret << endl;
	ret = 0;
	vst.Restart();
	vst.LapStart();
	for (int i = 0; i < G_speedtest_size; i++) {
		for (int n = i + 1; n < G_speedtest_size; n++) {
			ret += string_compare(tests[i], tests[n]);
			mret++;
		}
	}
	cout << vst.Lap() << ":time,ret:" << ret << endl;
	ret = 0;
	vst.Restart();
	vst.LapStart();
	for (int i = 0; i < G_speedtest_size; i++) {
		for (int n = i + 1; n < G_speedtest_size; n++) {
			ret++;
			mret++;
		}
	}
	cout << vst.Lap() << ":time,ret:" << ret << endl;
	cout << "mret: " << mret << endl;



}

#undef string