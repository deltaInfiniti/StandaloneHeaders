#ifndef StrList_CORE
#define StrList_CORE
//oringinally written in 2005 to handle arbitrary string lists and deduping for mingw gcc/devcpp
// adapted in 2020 for future use in msvc 


/*************************** comma separated list string modifier block*************************************/

string cslformat(string& str) {
    str= str_replace_all(str, "`", "`1");
    str= str_replace_all(str, ",", "`0");
    return str;
}
//when reading data from a csl call cslunformat to convert back
string cslunformat(string& str) {
    str=str_replace_all(str, "`0", ",");
    str=str_replace_all(str, "`1", "`");
    return str;
}
/*string& cslformat(string& str) {
    str_replace_all(str, "\\", "\\\\");
    str_replace_all(str, ",", "\\");
    return str;
}
//when reading data from a csl call cslunformat to convert back
string& cslunformat(string& str) {
    str_replace_all(str, "`0", ",");
    str_replace_all(str, "`1", "`");
    return str;
}
*/
#define csl_pop(str) tokenizecsl(str)
string tokenizecsl(string& str, bool format = true) {
    int i = findnext(str, ",", 0);
    string ret = "";
    if (i == -1) {
        ret = str;
        str = "";
        return ret;
    }
    ret = getbetween(str, 0, i);
    if (format)cslunformat(ret);
    str = getbetween(str, i + 1);
    return ret;
}
#define csl_add(csl,wh) addtocsl(csl,wh);
void addtocsl(string& str, string wh) {
    cslformat(wh);
    str += "," + wh;
}
bool csl_isin(string csl, string what) {
    string tmp;
    while (csl != "") {
        tmp = csl_pop(csl);
        if (tmp == what)return true;
    }
    return false;
}

/****************************************stringlist class block*******************************************************************/
#define slist_sorted 0
#define slist_unsorted 1
#define slip StrListItem *
#define SLIP slip
#define SLI StrListItem
#define debug(a) cout <<a<<endl;
#define JUMP_LENGTH 100
#define strlist stringlist

int abcomp(string,string);

struct StrListItem {
    string name;
    slip next=NULL;
    slip last=NULL;
    slip jump;
}; 
void VI(slip v){
    v->name="";
    v->next=NULL;
    v->jump=NULL;
    v->last=NULL;
}
void newSLIP(string name,slip &vv){
    vv = new SLI;
    vv->name=name;
    vv->next=NULL;
    vv->last=NULL;
    vv->jump=NULL;
}
slip newSLIP() {
    slip a;
    newSLIP("", a);
    return a;
}
void slip_insert(slip vv, string value){// inserts node with name=value after vv
    slip wh;
    slip nex=vv->next;
    newSLIP(value,wh);
    nex->last = wh;
    wh->next = nex;
    vv->next=wh;
    wh->last=vv;
}
void slip_delete(slip vv){
    slip left = vv->last;
    slip right = vv->next;
    if (left != NULL)left->next = right;
    if (right != NULL)right->last = left;
    delete vv;
}   
slip slip_remove(slip vv) {
    slip l = vv->last;
    slip n = vv->next;
    if (l != NULL) l->next = n;
    if (n != NULL) n->last = l;
    vv->next = NULL;
    vv->last = NULL;
    return vv;
}
//insert vv after targ
void slip_inject(slip vv, slip targ) {

    slip nex = targ->next;
    vv->last = targ;
    vv->next = nex;
    if (nex != NULL)nex->last = vv;
    targ->next = vv;
}
void slip_swap(slip a, slip b) {
    string aa = a->name;
    a->name = b->name;
    b->name = aa;
}
void slip_link(slip a, slip b) {
    a->next = b;
    b->last = a;
}
//golf bubblesort
int sliplist_sort_golf(slip first, slip last) {
    bool done = false;
    while (!done) {
        done = true;
        slip place = first;
        slip next = first->next;
        while (next != NULL) {
            if (string_compare(place->name, next->name) > 0) {
                slip_swap(place, next);
                done = false;
            }
            place = next;
            next = next->next;
        }


    }

}
//golf bubblesort but faster?
int sliplist_sort_golf2(slip first, slip last) {
    bool done = false;
    
    
    while (!done) {
        done = true;
        slip place = first;
        slip next = first->next;
        while (next != NULL) {
            if (string_compare(place->name, first->name) <1) { // before or equal to first
                slip_remove(place);
                first->last = place;
                place->next = first;
                first = place;
                done = false;
            }else if (string_compare(place->name, last->name) > -1) { // after or equal to last
                slip_remove(place);
                last->next = place;
                place->last = last;
                last = place;
                done = false;
            }else if (string_compare(place->name, next->name) ==1) { // set out of order
                slip_swap(place, next);
                done = false;
            }
            place = next;
            next = next->next;
        }

    }

}
int sliplist_check(slip s, slip e) {
    int i = 0;
    while (++i < 10000000 && s != e)s = s->next;
    if (i > 9999999)return 0;
    return i;
}
void sliplist_output(slip s, slip e) {
    slip t = s;
    int ti = 0;
    while (t != e->next) {
        cout << t->name << "\n";
        t = t->next;
        if (++ti > 100000)break;
    }
    if (ti > 100000) {
        cout << "sliplist output failed to find end of list" << endl;
    }
}
// fast and dirty simple insertion sort.  
//assumes first->next->next...==last eventually or first!=NULL at least.
//returns first=last with single node
int sliplist_ssort(slip& first, slip& last, bool dedupe =false) {
    if (last == NULL)first = last;
    if (first == last)return 1;
    slip lastnhold = last->next;
    slip firstlhold = first->last;
    slip rets = first;
    slip rete = new SLI;
    rete->last = last;
    last->next = rete;
    slip targ = first->next;
    slip tnext;
    slip lhold;
    int scompt;
    int size=2;
    while (targ != rete && targ!=NULL) {
        lhold = rets;
        tnext = targ->next;
        //slip_remove(targ);
        while (lhold != targ) {
            //cout << "testing " << targ->name << "  :  " << lhold->name << "\n";
            scompt = string_compare(targ->name, lhold->name);
            if (scompt == -1) {
                slip_remove(targ);
                if (lhold == rets) {
                    rets->last = targ;
                    targ->next = rets;
                    rets = targ;
                }
                else {
                    slip_inject(targ, lhold->last);
                }
                size++;
                break;
            }
            else if (dedupe && scompt == 0) {
                slip t = lhold->next;
                slip_delete(slip_remove(lhold));
                lhold = t;
            }
            else {
                lhold = lhold->next;
            }
        }
        targ = tnext;
        

    }
    first = rets;
    last = rete->last;
    last->next = lastnhold;
    first->last = firstlhold;
    return size;
}
int sliplist_ssort2(slip& first, slip& last, bool dedupe = false) {
    slip rets = first;
    first = first->next;
    slip rete = first;
    first = first->next;
    slip_remove(rets);
    slip_remove(rete);
    slip_link(rets,rete);
    if (string_compare(rets->name, rete->name) >0) {
        slip_swap(rets, rete);
    }
    slip lhold;
    slip nnext;
    int scompt = 0,size=2;
    while (1) {
        lhold = rets;
        nnext = first->next;
        while (lhold != NULL) {
            //cout << "testing " << first->name << "  :  " << lhold->name << "\n";
            scompt =string_compare(first->name, lhold->name);
            if (scompt == -1) {
                slip_remove(first);
                if (lhold == rets) {
                    rets->last = first;
                    first->next = rets;
                    rets = first;
                }
                else {
                    slip_inject(first, lhold->last);
                }
                if (lhold == rete)rete = lhold;
                size++;
                break;
            }
            else if (dedupe && scompt == 0) {
                slip t = lhold->next;
                slip_delete(slip_remove(lhold));
                lhold = t;
            }
            else {
                lhold = lhold->next;
            }
        }
        if (lhold == NULL) {
            slip_remove(first);
            slip_inject(first, rete);
            rete = first;
            size++;
        }
        

        if (first == last)break;
        first = nnext;
    }
    //cout << "sliplistcheck " << sliplist_check(rets, rete);
    //sliplist_output(rets, rete);
    first = rets;
    last = rete;
    return size;
}


// sliplist_qsort is an attempt at a smart sort function. 
// assumes first->next->next->next.... eventually== last
// assumes list length is more than 3 (should be more than 10)
int sliplist_qsort(slip& first, slip& last, bool pivot_end = true) {
    // recursive qsort function, first/middle index pivot option.
    // middle pivot will take substantially longer for long lists but will be exponentially faster for 'nearly sorted' lists
    // after return, list represented by first->last is sorted and (maybe) deduped- needs testing
    //dedupes when matching pivot, dedupes when sent to ssort normally. that theoretically covers all situations

    //add mor pivot options later??  random, choose3rand-pick mid
    if (first == NULL) {
        last = first; return 0; // return first==last
    }
    if (last == NULL) {
        last = first;
        return 1;
    }
    slip tfirst = first->next;
    slip pivot = first;
    if (!pivot_end) { // set the pivot to the middle.
        slip t = first;
        bool tog = false;
        while (t != last) {
            if (tog)pivot = pivot->next;
            t = t->next;
            tog = !tog;
        }
    }
    slip tlast = last;
    slip left = NULL;
    slip lefte = NULL;
    slip right = NULL;
    slip righte = NULL;
    slip thold = NULL;
    int llen = 0;
    int rlen = 0;
    
    slip_remove(pivot); 
    int scompt = 0;
    while (tfirst != tlast) {
        thold = tfirst->next;
        scompt = string_compare(tfirst->name, pivot->name);
        if (scompt < 0) {
            if (left == NULL) {
                left = slip_remove(tfirst);
                llen++;
            }
            else if (lefte == NULL) {
                slip_inject( slip_remove(tfirst),left);
                lefte = left->next;
                llen++;
            }
            else {
                slip_inject(slip_remove(tfirst), lefte);
                llen++;
            }

        }
        else if (scompt > 0) {
            if (right == NULL) {
                right = slip_remove(tfirst);
                rlen++;
            }
            else if (righte == NULL) {
                slip_inject(slip_remove(tfirst),right);
                righte = right->next;
                rlen++;
            }
            else {
                slip_inject(slip_remove(tfirst), righte);
                rlen++;
            }
        }
        else {
            //cout << "slist_qsort deleted duplicate entry " << tfirst->name << endl;
            slip_delete(slip_remove(tfirst));
        }
        // after this left and right should be filled. 
        // check llen and rlen. 
        // if either are 0 special case. if 1-10 call ssort
        // if more than 10 call qsort again
        if (rlen > 0 && rlen < 10) {
            sliplist_ssort(right, righte);
        }
        else if (rlen > 9) {
            if (llen == 0) {// if whole list is on one side, do other pivot style
                rlen = sliplist_qsort(right, righte, !pivot_end);
                right->last = pivot;
                pivot->next = right;
                right = pivot;
                first = right;
                last = righte;
                return rlen+1 ;
            }
            rlen = sliplist_qsort(right, righte);
        }

        if (llen > 0 && llen < 10) {
            sliplist_ssort(left,lefte);
        }
        else if (llen > 9) {
            if (rlen == 0) {// if whole list is on one side, do other pivot style
                llen = sliplist_qsort(left, lefte, !pivot_end);
                lefte->next = pivot;
                pivot->last = lefte;
                lefte = pivot;
                first = left;
                last = lefte;
                return llen+1;
            }
            llen = sliplist_qsort(left, lefte);
        }
        // after that left and right should be sorted
        // knit lefte->pivot->right checking left and right for NULLness by llen/rlen
        if (llen != 0) {
            slip_inject(pivot, lefte);
        }
        else left = pivot;
        lefte = pivot;
        if (rlen != 0) {
            lefte->next = right;
            right->last = lefte;
        }
        else righte = pivot;


        // set first=left,last = righte and return;
        first = left;
        last = righte;
        return llen + rlen + 1;
        
    }
}

//merge two already sorted sliplists together. s1 e1 is returned, sorted list

void sliplist_twomerge(slip& s1, slip& e1, slip s2, slip e2) {
    int h = 0;
    slip rets = NULL;
    if (string_compare(s1->name, s2->name) == 1) {
        rets = s2;
        s2 = s2->next;
    }
    else {
        rets = s1;
        s1 = s1->next;
    }
    slip_remove(rets);
    slip rete = newSLIP();
    slip t;
    slip_link(rets, rete);
    while (s1 != NULL && s2 != NULL) {
        h = string_compare(s1->name, s2->name);
        if (h == 1) {
            t = s2;
            s2 = s2->next;
            slip_remove(t);
            cout << "merging *" << t->name << "*1 \n";
            slip_inject(t, rete->last);
        }
        else {
            t = s1;
            s1 = s1->next;
            slip_remove(t);
            cout << "merging *" << t->name << "* 2\n";
            slip_inject(t, rete->last);
        }
    }
    while (s1 != NULL) {
        t = s1;
        s1 = s1->next;
        cout << "merging *" << t->name << "*3 \n";
        slip_inject(t,rete->last);
    }
    while (s2 != NULL) {
        t = s2;
        s2 = s2->next;
        cout << "merging *" << t->name << "*4 \n";
        slip_inject(t, rete->last);
    }
    s1 = rets;
    s2 = rete->last;
    slip_delete(slip_remove(rete));

}

//mergesort that breaks list down to lists of baselen and calls ssort
//merges equal sized parts preferably
// msort2 should be recursive equal parts
void sliplist_msort1(slip first, slip last, int baselen) {
    int len = 1; slip temp = first;
    while (temp != last) {
        temp = temp->next;
        len++;
    }
    len /= baselen;
    len++;
    slip lists = new SLI[len];
    slip liste = new SLI[len];

    for (int i = 0; i < len; i++)slip_link(lists+i, liste+i);

}

int sliplist_msort2(slip& first, slip& last, int baselen=10) {
    slip left = first;
    slip right = first->next;
    slip temp;
    first = right->next;
    slip_remove(left);
    slip_remove(right);
    slip lefte = newSLIP();
    slip_link(left, lefte);
    slip righte= newSLIP();
    slip_link(right, righte);
    bool tog = true;
    int len = 3;
    while (first != last) {
        temp = first;
        first = first->next;
        slip_remove(temp);
        if (tog)slip_inject(temp, lefte->last);
        else slip_inject(temp, righte->last);
        tog = !tog;
        len++;
    }

    slip_remove(first);
    if (tog) {
        slip_inject(first, lefte->last);
    }
    else {
        slip_inject(first, righte->last);
    }

    slip t = lefte;
    lefte = lefte->last;
    lefte->next = NULL;
    slip_delete(t);
    t = righte;
    righte = righte->last;
    righte->next = NULL;
    slip_delete(t);

    int rlen = len;
    len /= 2;
    if (len < baselen) { // recursive base case
        sliplist_ssort(left, lefte);
        sliplist_ssort(right, righte);
    }
    else {
        sliplist_msort2(left, lefte,baselen);
        sliplist_msort2(right, righte,baselen);
    }
    sliplist_twomerge(left, lefte, right, righte);
    first = left;
    last = lefte;
    return rlen;

}

class stringlist{

    private:
        
     slip start;
     slip end;
     int size;
     int type;
      // 1=insert after 2=found
     int ptrto(string item, slip &ret);


    public:

     bool set(string what);
     stringlist(string fname);
     stringlist();
     slip ini(){ return start;}
     void ini(slip a){ a = start;};
     void i_i(slip &a){a = start;};
     bool getnext(slip &vv, string &str);

     string todsl(string delim);
     string tocsl(){return todsl(",");};
     int SaveFile(string filename);
     int LoadFile(string filename);
     int load(string f){return LoadFile(f);};
     int save(string f){ return SaveFile(f);};
     void clear();
     void remove(string wh);
     
     void queue(string n);
     void stack(string n);
     string pop() ;
     string lift();
     string gettype();
     
     int getsize(){ return size;};
     int length(){ return size;};
     void point(stringlist &s); 
     bool isempty(){return start->next==end;};
     bool eof(){return start->next==end;};
     void reset();
     bool isset(string wh);
     
     
     string index(int i ){ SLIP s = start->next; for (int x = 0; x < i; x++)s = s->next; return s->name; }
     string operator[](int i) { SLIP s = start->next; for (int x = 0; x < i; x++)s = s->next; return s->name; }
     SLIP ITTplace = NULL;
     int ITTindex = 0;
     string ITT(int i) {
         return index(i % length());
         if (i == 0) {
            // cout << "passed check 1" << endl;
             ITTplace = start->next;// ->next;
             ITTindex = 0;
             return (ITTplace)->name;
         }
         
         if (i == ITTindex) return ITTplace->name;
         if (i < ITTindex) return index(i);
         //cout << "to check 3" << endl;
         i -= ITTindex;
         for (int x = 0; x < i; x++) {
             if (ITTplace->next == end) {
                 ITTplace = start->next;
                 ITTindex = 0;
             }
             else {
                 ITTplace = ITTplace->next;
                 ITTindex++;
             }
         }
         return ITTplace->name;
     }
};
void stringlist::point(stringlist &s) {
    clear();
     start=s.start; 
     end=s.end; 
     size=s.size; 
     s.reset();  
}
// flag 1 = insert after ret, 2 = exact value found
int stringlist::ptrto(string item, slip &ret){
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

bool stringlist::set(string what){
    if(type==slist_unsorted){queue(what); return true;}
    slip node;
    int flag = ptrto(what,node);
    
    if(flag==1){
        slip_insert(node,what);
        size++;
        return true;
    }
    return false;
}
    
void stringlist::reset(){
    newSLIP("*start*",start);
    newSLIP("*end*",end);
    start->next=end;
    end->last=start;
    size=0;
    type=slist_sorted;
}
stringlist::stringlist(){reset();}

stringlist::stringlist(string fname){
    reset();
    LoadFile(fname);
}
bool stringlist::getnext(slip &vv, string &str){
    vv=vv->next;
    if(vv==end)return false;
    str = vv->name;
    return true;
}   
    
int  stringlist::SaveFile(string filename){
    ofstream ofile(filename.c_str());
    ofile << todsl("\n");
    ofile.close();
    return 1;
}

int  stringlist::LoadFile(string filename){
    ifstream ifile(filename.c_str());
    if(!ifile.good())return 0;
    string line,n;
    int lines = 0;
    
    while(!ifile.eof()){
        getline(ifile,line);
        set(line);
        lines++;
        if(lines%137==0)cout<<lines<<"\r";
    }
    cout<<"                          \r";
    return  size;
}
string stringlist::todsl(string delim){
    slip vv=ini();
    string ctc,ret="";
    while (getnext(vv,ctc)){
         ret += vv->name;
         if(vv->next!=end)ret+=delim;
    }
    return ret ;
} 
void stringlist::clear(){
    while(start->next!=end)slip_delete(start->next);
    size=0;
}
void stringlist::remove(string wh){
    slip ss;
    int fl = ptrto(wh,ss);
    if(fl == 2)slip_delete(ss);
}    

void stringlist::queue(string n){
    type = slist_unsorted;
    slip_insert(start,n);
    size++;
}
void stringlist::stack(string n){
    type = slist_unsorted;
    slip_insert(end->last,n);
    size++;
}
string stringlist::pop(){
    if(isempty())return"";
    string ret = start->next->name;
    slip_delete(start->next);
    return ret;
}
string stringlist::lift(){
    if(isempty())return"";
    string ret = end->last->name;
    slip_delete(end->last);
    return ret;
}
    
bool  stringlist::isset(string name){
    slip ptr;
    int i = ptrto(name,ptr);
    return i==2;
}

void strlist_and(strlist &a,strlist &b,strlist &c){
    slip ss;
    a.i_i(ss);
    string tmp;
    while( a.getnext(ss,tmp)){
        if(b.isset(tmp))c.set(tmp);
    }
    return;
}

int slist_queue_copyall(strlist &lines,strlist &allines){
    slip t;
    allines.i_i(t);
    string tmp;
    int ret = 0;
    while(  allines.getnext(t,tmp)){
        lines.queue(tmp);
        ret++;
    }
    return ret;
}

/*****************************2nd csl block for strlist convertion *****************************************/

string& csl_vl_format(string& str) {
    
    str_replace_all(str, "`", "`1");
    str_replace_all(str, "=", "`0");
    str_replace_all(str, ",", "`2");
    str_replace_all(str, "\n", "`3");
    return str;
}
string& csl_vl_unformat(string& str) {
    str_replace_all(str, "`0", "=");
    str_replace_all(str, "`1", "`");
    str_replace_all(str, "`2", ",");
    str_replace_all(str, "`3", "\n");
    return str;
}
/*
string shortlist_tocsl(shortlist& sl) {
    string ret = "", h;
    cnptr pt = sl.start;
    do {
        h = csl_vl_format(pt->name) + "=" + csl_vl_format(pt->value);
        ret += csl_vl_format(h) + ",";
    } while ((pt = pt->next) != NULL);
    return ret;
}
void csl_toshortlist(string csl, shortlist& sl) {
    string tmp = csl, h, n, v;
    while (tmp != "") {
        h = tokenizecsl(tmp, false);
        csl_vl_unformat(h);
        breakarg(h, n, v);
        sl.set(csl_vl_unformat(n), csl_vl_unformat(v));
    }

}
*/
/*****************************************more strlist helper functions *************************************************************/


#define getallbetween(a,b,c,d) getbetweenall(a,b,c,d);
int getbetweenall(string src,string wh,string to,strlist &list){
    string hold = "";
    while((hold = getnextbetween(src,wh,to)) != ""){
        list.set(hold);
    }
    return 1;
}      

// link parser I wrote circa 2005 for a spidering refresher. parses all href links out and dedupe adds them to new if they're not in old
void parse_links(string src,strlist &visited,strlist& newlinks){
    string hold, holdtwo,hs=src;
    
    while((hold=getnextbetween(src,"a href=\"",">")) != ""){
        if(hold[0] == '"' || hold[0] == '\'') hold.erase(0,1);
        holdtwo= getbetween(hold,0,"\"");
        if(holdtwo != "") hold = holdtwo;
        if(hold[hold.length()-1]=='"' ||hold[hold.length()-1]=='\'') hold.erase(hold.length()-1,1);
        //if(instr(hold,"www")) continue;
        if(hold == "") continue;
        if(visited.isset(hold)) continue; 
        //if(isfilter(filter,hold)) continue;
        newlinks.set(hold);
        //lnks++;
    }
    src=hs;
    while((hold=getnextbetween(src,"a href='",">")) != ""){
        if(hold[0] == '"' || hold[0] == '\'') hold.erase(0,1);
        holdtwo= getbetween(hold,0,"\"");
        if(holdtwo != "") hold = holdtwo;
        if(hold[hold.length()-1]=='"' ||hold[hold.length()-1]=='\'') hold.erase(hold.length()-1,1);
        //if(instr(hold,"www")) continue;
        if(hold == "") continue;
        if(visited.isset(hold)) continue; 
        //if(isfilter(filter,hold)) continue;
        newlinks.set(hold);
        //lnks++;
    }
    //cout << hold << endl;
    //cout << hold << endl;
}


/*********************strlist dedupe block***********************************************



stringlist supliment for half-radix deduping
attempts to dedupe stringlist by dumping radix buckets of 256 (per char, LSD), with possible depth of 2 currently

first pass, take A=str.length-1(or 0); basenodeslist[A].append(str)

for each basenodeslist, parse into worknodeslist in the same fasion as first pass, but with str[length-2]
once each basenodeslist[index] has been parsed into worknodeslist
for each worknodeslist[index]
take first non "" node after finished portion, remove node = target node
parse through rest of list and remove any that == target node and set them to "" ( or remove/delete the node)
inject target node at end of finished portion, or after start if first.
loop, loop

purge worknodeslist to deduped list, parse next basenodeslist[]

uses the SLIP struct and related functions
StringListItemPointer- slip
*/


class strlist_dedupe {
    slip basenodes[256];
    slip worknodes[256];
    slip basenodesend[256];
    slip worknodesend[256];
public:
    slip deduped;
    slip deduped_end;
    int dedupedlen;

    strlist_dedupe() {
        //ZeroMemory(basenodes, sizeof(slip) * 256);
        //ZeroMemory(worknodes, sizeof(slip) * 256);
        for (int i = 0; i < 256; i++) {
            newSLIP("*base*", basenodes[i]);
            newSLIP("*end*", basenodes[i]->next);
            basenodesend[i] = basenodes[i]->next;
            basenodesend[i]->last = basenodes[i];
            newSLIP("*base*", worknodes[i]);
            newSLIP("*end*", worknodes[i]->next);
            worknodesend[i] = worknodes[i]->next;
            worknodesend[i]->last = worknodes[i];

        }
        newSLIP("*base*", deduped);
        newSLIP("*end*", deduped_end);

        deduped->next = deduped_end;
        deduped_end->last = deduped;

        dedupedlen = 0;
    }
    void deduped_tofile(string fname) {
        ofstream ofile(fname.c_str());
        if (!ofile.good())return;
        slip start = deduped->next;
        while (start->next!= deduped_end) {
            ofile << start->name << endl;
            start = start->next;
        }
        ofile.close();

    }
    void dedupe_queue(string what) {
        slip_insert(basenodes[(BYTE)what[what.length() - 1]], what);
    }

    void check_worknodes() {
        int count = 0;
        slip targ;
        for (int i = 0; i < 256; i++) {
            targ = worknodes[i]->next;
            while (targ->name != "*end*") {
                count++;
                targ = targ->next;
                //cout << "tcount " << i << " : " << count << "           \r";
                if (count > 100000) {
                    cout << "worknode " << i << " failed to find end               " << endl;
                    pause();
                    break;
                }
            }
            //cout << "tcount " << i << " : " << count << "           \n\n";
            count = 0;
        }

    }
    void dedupeout() {
        slip targ = deduped->next;
        int t = 0;
        while (targ->name != "*end*") {
            if (targ->name != "") {
                cout << targ->name << endl;
                t++;
            }
            targ = targ->next;
        }
        cout << "total in dedupe array: " << t << endl;
    }

    // processes the worknodes in 1 pass. called by twopass_dedupe after filling worknodes
    void onepass_worknodes() {
        slip outlist, * slide, * dtarg;
        //dedupdedlen = 0;

        for (int i = 0; i < 256; i++) {
            outlist = worknodes[i]->next;
            while (outlist->name != "*end*") {
                //if (outlist->name == "*end*")continue;
                slide = outlist->next;
                slip_remove(outlist);
                while (slide->name != "*end*") {
                    if (slide->name == outlist->name) {
                        dtarg = slide;
                        slide = slide->next;
                        slip_remove(dtarg);
                        slip_delete(dtarg);
                        //dtarg->name = "";
                    }
                    else slide = slide->next;
                }
                if (outlist->name != "") {
                    slip_inject(outlist, deduped);
                    dedupedlen++;
                }
                outlist = worknodes[i]->next;
            }
        }
    }
    // processes the dedupe directly in basenodes instead of splitting to worknodes.
    void onepass_dedupe() {
        slip outlist, * slide, * dtarg;
        //dedupdedlen = 0;

        for (int i = 0; i < 256; i++) {
            outlist = basenodes[i]->next;
            while (outlist->name != "*end*") {
                //if (outlist->name == "*end*")continue;
                slide = outlist->next;
                slip_remove(outlist);
                while (slide->name != "*end*") {
                    if (slide->name == outlist->name) {
                        dtarg = slide;
                        slide = slide->next;
                        slip_remove(dtarg);
                        slip_delete(dtarg);
                        //dtarg->name = "";
                    }
                    else slide = slide->next;
                }
                if (outlist->name != "") {
                    slip_inject(outlist, deduped);
                    dedupedlen++;
                }
                outlist = basenodes[i]->next;
            }
        }
    }
    // backup copy of onepass so I can fiddle with it and get it a little faster
    void onepass_dedupe_knowngood() {
        // simple, elegant, 1pass 256 bucket radix dedupe method.
        slip outlist, * slide, * dtarg;
        //dedupdedlen = 0;

        for (int i = 0; i < 256; i++) {
            outlist = basenodes[i]->next; // get first entry in basenode
            while (outlist->name != "*end*") { // loop through all entries
                //if (outlist->name == "*end*")continue;
                slide = outlist->next; // set slide to next item
                slip_remove(outlist); // remove this target from the basenodes list
                while (slide->name != "*end*") { // loop through the rest of the list
                    if (slide->name == outlist->name) {// if a dupe is found
                        dtarg = slide;
                        slide = slide->next;
                        slip_remove(dtarg);  // remove the dupe and incriment slide
                        slip_delete(dtarg);
                        //dtarg->name = "";
                    }
                    else slide = slide->next; // if not a dupe, incriment slide
                }
                if (outlist->name != "") { // if the node isn't blank
                    slip_inject(outlist, deduped); // add it to deduped list
                    dedupedlen++;
                }
                outlist = basenodes[i]->next; // get the 'next' node. since outlist was removed previously, next is first in list
            }
        }
    }

    //twopass dedupe, fills basenodes, then for each basenode, fills worknodes and calls onepass worknodes
    void twopass_dedupe() {
        slip place, * next, * slide;
        int count, x, comphold, outcount = 0;
        int mcount = 0;
        for (int i = 0; i < 256; i++) {
            //cout << "outer loop start i:" << i << endl;
            mcount = 0;
            while (basenodes[i]->next != basenodesend[i]) {
                slip t = basenodes[i]->next;
                slip_remove(t);
                slip_inject(t, worknodes[(BYTE)t->name[t->name.length() - 2]]);
                outcount++;
                mcount++;
            }
            if (mcount == 0)continue;
            //cout << "after worknodes transfer outcount:" << outcount << endl;
            onepass_worknodes();
        }
    }
};
#endif
