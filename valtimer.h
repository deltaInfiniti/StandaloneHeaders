#ifndef fast_timer_def
#define fast_timer_def

unsigned long long timer_frames[100];
short timer_frames_plc=0;
long int VS_ms_ticks=1;  //set by calibration thread 
bool VS_timer_ = false;
#include<intrin.h>
#define vtimer_bitstep 16
static inline unsigned long long getticks(void)
{
    //unsigned int lo, hi;

    // RDTSC copies contents of 64-bit TSC into EDX:EAX
    //asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
    //return (unsigned long long)hi << 32 | lo;

	//uint64_t i;
	uint32_t ui;
	return (unsigned long long)__rdtscp(&ui);

}
short get_new_timer_frame(){
	timer_frames[timer_frames_plc]=getticks();
	return timer_frames_plc++;
}
short reset_timer_frame(short frame){
	timer_frames[frame]=getticks();
	return frame;
}
unsigned long long timer_convert_ticks_to_ms(unsigned long long ticks) {
	int a = (ticks >> vtimer_bitstep);
	a /= VS_ms_ticks;
	return a; 
}
unsigned long long get_timer_frame_ticks(short frame) {
	return getticks()-timer_frames[frame];
}
unsigned long long get_timer_frame_base(short frame) {
	return timer_frames[frame];
}
unsigned long int vs_timer_readms(short plc){
	return ((getticks()-timer_frames[plc])>> vtimer_bitstep) / VS_ms_ticks;
}
void ValTimer_randseed() {
	srand((unsigned int)getticks());
}
void calibrate_timer_thread(void*a){
	unsigned long long time =0;
	unsigned long long btime = getticks();
	int reps=10, wait=100;
	
	for(int i =0; i < reps; i++){
		btime = getticks();
		Sleep(wait);
		time+= getticks()-btime;
		
	}
	time/=wait;
	time /=reps;
	VS_ms_ticks=(time>> vtimer_bitstep) ;
	
}
void calibrate_timer_const_thread(void* a) {
	unsigned long long time = 0;
	unsigned long long dtime = 0;
	unsigned long long btime = getticks();
	int reps = 10, wait = 100, lc = 0;
	while (1) {
		lc++;

		btime = getticks();
		Sleep(wait);
		time += getticks() - btime;
		dtime = (time / wait) / lc;
		
		VS_ms_ticks = (dtime >> vtimer_bitstep);
	}
}

//add class stopwatch
class ValStopwatch {

	public:
		ValStopwatch();
		~ValStopwatch();

		//void Start();
		int Lap();
		unsigned long int Lapticks();
		int LapPause();
		void LapUnPause();
		void LapStart();
		void Restart();
		void output(string title);
		int read_ms_nolap();
		unsigned long long End(int &llaps, int &ms);
		unsigned long long hold;
		unsigned long long ticks;
		unsigned long long lastlap;
		unsigned long long lastticks;
		short timer;
		int laps;

};


ValStopwatch::ValStopwatch() {
	timer= get_new_timer_frame();
	hold = 0; ticks = 0; lastlap = 0; timer = 0; laps = 0; lastticks = 0;
}
ValStopwatch::~ValStopwatch() {
	// release timer when implimented
}
int ValStopwatch::read_ms_nolap() {

	return vs_timer_readms(timer) - timer_convert_ticks_to_ms(lastlap);

}
void ValStopwatch::Restart() {
	if (timer == 0)timer = get_new_timer_frame();
	timer = reset_timer_frame(timer);
	hold = 0; ticks = 0; lastlap = 0; timer = 0; laps = 0; lastticks = 0;
}
int ValStopwatch::Lap() {
	hold = get_timer_frame_ticks(timer);
	lastticks = hold - lastlap;
	ticks += hold-lastlap ;
	lastlap = hold;
	laps++;
	return timer_convert_ticks_to_ms(lastticks);
}
unsigned long int ValStopwatch::Lapticks() {
	hold = get_timer_frame_ticks(timer);
	lastticks = hold - lastlap;
	ticks += hold - lastlap;
	lastlap = hold;
	laps++;
	return lastticks;
}
int ValStopwatch::LapPause() {
	int ret = Lap();
	laps--;
	return ret;
}
void ValStopwatch::LapStart() {
	LapUnPause();
}
void ValStopwatch::LapUnPause() {
	hold = get_timer_frame_ticks(timer);
	lastlap = hold;
}
void ValStopwatch::output(string title) {
	unsigned long long ms = timer_convert_ticks_to_ms(ticks);
	cout << "**** " << title << "****\n" << "average ms: " << setprecision(4) << ((float)ms / (float)laps) << "  total laps: " << laps << "  total ms:" << ms << "\n\n";

}
unsigned long long ValStopwatch::End(int& llaps, int& ms) {
	Lap();
	llaps = laps;
	ms = timer_convert_ticks_to_ms(ticks);
	return ticks;
}

#include<mutex>
	
class ValScheduler {
	// valscheduler - thread scheduling made easy.
	// allows set schedules, random schedules, weighted random spreads 
	// simply blocks threads untill their turn with minimal CPU usage
	// call GetId at the beginning of your acitivty, call Run at a 'break point'
	// multiple threads may have the same ID, under these conditions they run concurrently.
	//random requires substantially more thread check-ins when entangled
	BYTE currentactivity = 0;
	
	BYTE activitylist[255];
	BYTE activityweight[255];
	string activitynames[255];
	int activity_length[255];
	short length = 0;
	bool captured = false;
	short totalweight = 0;

	
public:
	//random = random activity on activity change
	//weighted = weighted random
	//strict = next event's time starts -  false: after next thread capture   true: when last thread commits
	bool random = 0, weighted = 0, strict=0;
	bool paused = 0;
	// flag threads for destruction. threads commit to cleanup and exit
	bool destroy_all=0;
	ValStopwatch timer;
	std::mutex IDlock;
	string currentactivityname = "";
	string status = "";
	// call to get a new scheduler ID for your activity
	// l is the length in MilSec your activity is allocated
	// weight is how many slots in the random spread this entry gets when random&&weighted
	// name for easy status outputs
	int GetId(int l, string name, int weight = 1) { 
		IDlock.lock();
		if (length == 0)currentactivityname = name;
		activity_length[length] = l; 
		activitynames[length] = name;
		activityweight[length]=weight;
		int ret = length;
		length++;
		totalweight += weight; 
		IDlock.unlock();
		//Sleep(1000);
		return ret;
	}
	//call this in your activity while(1) loop when a user would move onto something else
	//if this activity's turn is up, waits for next turn, otherwise, returns to calling thread
	//if return true, calling thread commits to cleanup/end activity
	bool Run(int id) {  // needs to be renamed.   
		if (!commit(id,false))entangle(id);
		while (paused)Sleep(100);
		return destroy_all;
	}

	// kill all waiting threads.
	void destroy_schedule() {
		destroy_all = true;
	}
	void pause() { paused = true; }
	void unpause() { paused = false; }
	ValScheduler() { timer.Restart(); ZeroMemory(activity_length, sizeof(int) * 255); }
	
	bool check(int id){ // check if my turn is up but don't commit to it.
		if (id != currentactivity) return false;
		return timer.read_ms_nolap() < activity_length[id];
	}
	
	int my_wait(int id) { // see how long I have to wait until my turn
		int cat = currentactivity, total = 0;
		if (random) return my_time_left(cat);
		if (cat > id) {
			for (int i = cat; i < length; i++)total += activity_length[i];
			cat = 0;
		}
		for(int i = cat; i < id;i++ )total += activity_length[i];
		return total;
	}

	int my_time_left(int id) { // how long my activity has left
		return   activity_length[id] - timer.read_ms_nolap();
	}

private:
	bool entangle(int id ) { // wait for my turn
		int sleep = (my_wait(id)/20)+1;
		while (1) {
			if (destroy_all||propose(id)) return true;
			
			Sleep(sleep);
			//sleep -= (sleep<2?sleep/2: (my_wait(id) / 2)+10);
			sleep = (my_wait(id)/20 )+1;
			if (sleep < 0)sleep = 1;
		}
	}
	bool propose(int id) { // ask for exclusive thread priority
		
		if (captured==true || id != currentactivity) return false;
		if(!strict)timer.Lap();
		captured = true;
		return true;
	}
	void next_activity() { // calculate and set currentactivity
		if (random) {
			//short top = length;
			//if (weighted) top = totalweight;
			short top = (weighted ? totalweight : length);
			int temp = abs((short)(rand() + rand()) % top);
			int tot = 0;
			if (weighted) {
				for (int i = 0; i < length; i++) {
					tot += activityweight[i];
					if (tot > temp)tot = i;
				}
				if (tot > length - 1)tot = length - 1;
				temp = tot;
			}
			else {
				//cout << "\nin random temp,len: " << temp<<","<<(short)length << endl;
				int topout = 0;
				while (temp == currentactivity) {
					//cout << "ll";
					temp = abs((int)rand() % top);
					if (++topout > 10)break;
				}
			}
			currentactivity = temp;
		}
		else  if (currentactivity == length - 1)currentactivity = 0;
		else currentactivity++;
		currentactivityname = activitynames[currentactivity];
		captured = false;
	}
	void force_commit(int id, bool entang=true) { // commit early if task is done and time restricted
		if (id != currentactivity) return;
		next_activity();
		timer.Lap();
		
		if(entang)entangle(id);
	}

	bool commit(int id, bool entang=true) {// commit to giving up thread priority if my turn is up.
		if (id != currentactivity) return false;
		if (timer.read_ms_nolap() > activity_length[id]) {
			next_activity();
			timer.Lap();

			if (entang)entangle(id);
			//return true;
			return false;
		}
		return true;
	}



};


struct vschedulertesterstruct {
	string value="";
	ValScheduler* sch = NULL;
};

void valschedulertester_thread(void* a) {
	vschedulertesterstruct* b = (vschedulertesterstruct*)a;
	string c = b->value;
	ValScheduler* s = b->sch;
	ValTimer_randseed();
	int myID = s->GetId(2500,c);
	while (1) {
		if (s->Run(myID))break;
		cout << c;
		Sleep(499);
		
	}

	s->IDlock.lock();
	cout << "loop " << c << " ended" << endl;
	s->IDlock.unlock();
}

void TEST_VALSCHEDULER() {
	ValScheduler v;
	vschedulertesterstruct vs1, vs2, vs3, vs4, vs5, vs6;
	vs1.value = "a"; vs1.sch = &v;
	vs2.value = "b"; vs2.sch = &v;
	vs3.value = "c"; vs3.sch = &v;
	vs4.value = "d"; vs4.sch = &v;
	vs5.value = "e"; vs5.sch = &v;
	vs6.value = "f"; vs6.sch = &v;
	v.random = true;
	_beginthread(valschedulertester_thread, 0, (void*)&vs1);
	_beginthread(valschedulertester_thread, 0, (void*)&vs2);
	_beginthread(valschedulertester_thread, 0, (void*)&vs3);
	_beginthread(valschedulertester_thread, 0, (void*)&vs4);
	_beginthread(valschedulertester_thread, 0, (void*)&vs5);
	_beginthread(valschedulertester_thread, 0, (void*)&vs6);
	Sleep(40000);
	cout << endl;
	v.destroy_schedule();
	Sleep(30000);
}



/****************************************************end valscheduler block******************************************/
/**************************************************begin VS_random section*******************************************/
//this is a testing block.  wanted a proprietary substantially nonpseudo RNGenerator that would also be useful cross thread
 unsigned long long int G_VS_randoverflowcatch;
 unsigned long long int G_VS_randseed = 13545654654635;
 unsigned long long int G_VS_randoverflowcatch2;
 unsigned long long int G_VS_randMAX = 18446744073709551;
 unsigned long long int G_VS_randoverflowcatch3;

 unsigned long long int G_VS_randsway = 1855161;
 unsigned long long int G_VS_randoverflowcatch4;
 unsigned long long int G_VS_randswayMAX = 134855521617;
 unsigned long long int G_VS_randoverflowcatch5;

 //fallback rand
unsigned long long int G_VS_Rand5(unsigned long long int max) {
     unsigned long long int t = (rand() <<16)+ rand();
     t %= max;
     return t;
 }
//my random function
 unsigned long long int G_VS_Rand3(unsigned long long int max) {

     unsigned long long int ret = G_VS_randseed | G_VS_randsway;
     ret *= ret; ret %= G_VS_randsway;
     if (ret == 0)ret = G_VS_randsway * G_VS_randseed;
     G_VS_randsway = (ret * (G_VS_randseed % G_VS_randsway)) % G_VS_randswayMAX;
     if (G_VS_randsway == 0) {
         G_VS_randsway = (getticks() * getticks() ) % G_VS_randswayMAX;
     }
     ret = (G_VS_randsway * G_VS_randsway)% G_VS_randMAX;
     G_VS_randseed = ret;
     while (G_VS_randseed == 0) {
         G_VS_randseed = (getticks() * getticks()) % G_VS_randMAX;
     }
     return ret % max;

 }
 void G_VS_RANDSEED(unsigned long long int val) {
	 G_VS_randseed = val;
 }
#endif
