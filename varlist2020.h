#pragma once
/*
varlist2020

VariableList2 is a perturbation of the original varlist.h VariableList class.
this version uses radix sorting tables, optional jumps(database mode), a faster string compare function
and a mutex to ensure data reliability
possibly a local bank for thread safety. need testing. 

*/
#include<iostream>
#include<string>
#define string std::string
#include<mutex>
#include<shared_mutex>
#include "strlist.h" // better for returning arbitrary lists

int string_compare(const string& a, const string& b); // in valutils.h 

#define ValVLI VarListItem2
#define VVLI VarListItem2
#define VVLIP VarListItem2*
struct VarListItem2 {
    string name;
    string value;
    VarListItem2* next;
    VarListItem2* last;
    VarListItem2* jump;

};
VVLIP new_VVLI() {
	VVLIP ret = new VVLI();
	ret->next = NULL;
	ret->last = NULL;
	ret->jump = NULL;
	return ret;
}
VVLIP new_VVLI(string& name, string& value) {
	VVLIP ret = new_VVLI();
	ret->name = name;
	ret->value = value;
	return ret;
}

VVLI* VVLI_insert(VVLI* before, VVLI* what) {
	if (before->next != NULL) {
		before->next->last = what;
		what->next = before->next;
	}
	before->next = what;
	what->last = before;
}

VVLI* VVLI_extract(VVLI* what) {
	VVLI* l = what->last;
	VVLI* n = what->next;
	l->next = n;
	if (n != NULL)n->last = l;
	what->next = NULL;
	what->last = NULL;
	return what;
}


#define varlist2 VariableList2
class VariableList2 {
    VVLI* start[96];
    VVLI* end[96];
    unsigned int len[96];
    unsigned int total_len = 0;
    std::shared_mutex getsetmutex;

	VariableList2() {
		for (int i = 0; i < 96; i++) {
			start[i] = new_VVLI();
			end[i] = new_VVLI(); 
			start[i]->next = end[i];
			end[i]->last = start[i];
			len[i] = 0;
		}
	}
	inline int get_findex(char v) {
		int ret = ((int)v) - 32;
		if (ret > 94 || ret < 0)ret = 95;
		return ret;

	}

	int lastptrtoval = NULL; // to catch lastptrto compare value
// returns the node with name, or the node before where this name would be.
	VVLI* ptrto(string name, int* cmpval = NULL) {
		if (cmpval == NULL)cmpval = &lastptrtoval;
		unsigned int findex = get_findex(name[0]);
		unsigned int l = len[findex];
		int temp;
		getsetmutex.lock_shared();
		VVLI* targ = start[findex]->next;

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

	int set(string name, string dat) {
		if (name == "") {
			std::cout << "Error: variablelist2 set cannot set var without a name\n";
			return -1;
		}
		int val = 0;
		VVLI* vdn = ptrto(name, &val);
		if (val != 0) {
			getsetmutex.lock();
			VVLI_insert(vdn, new_VVLI(name, dat));
			len[get_findex(name[0])]++;
			total_len++;
			getsetmutex.unlock();
		}
		else {
			vdn->value = dat;
		}

		return val;
	}
	int remove(string name) {
		if (name == "")return 0;
		int val = 0;
		VVLI* vdn = ptrto(name, &val);

		if (val == 0) {
			getsetmutex.lock();
			VVLI_extract(vdn);
			len[get_findex(name[0])]--;
			total_len--;
			getsetmutex.unlock();
			return 1;
		}
		return -1;
	}
	string get(string name) {
		if (name == "")return"";
		int val = 0;
		VVLI* vdn = ptrto(name, &val);
		if (val == 0) return vdn->value;
		return "";

	}


	void initialize_database() {
		//set node list jumps 
	}
	//double ended mode find node, processes jumps
	VVLI* ptrto_d(string name, int* cmpval = NULL) {
		if (cmpval == NULL)cmpval = &lastptrtoval;
		unsigned int findex = get_findex(name[0]);
		unsigned int l = len[findex];
		int temp;
		getsetmutex.lock_shared();
		VVLI* targ = start[findex]->next;
		VVLI* targe = end[findex]->last;
		for (int i = 0; i < l; i++) {
			temp = string_compare(targ->name, name);
			//cout << " strcomp(t->name,name): " << targ->name << " : " << name << " : " << temp << "\n";
			if ((temp) > -1) {
				*cmpval = temp;
				if (temp == 1)targ = targ->last;
				getsetmutex.unlock_shared();
				return targ;
			}
			temp = string_compare(targe->name, name);
			//cout << " strcomp(t->name,name): " << targ->name << " : " << name << " : " << temp << "\n";
			if ((temp) <1) {
				*cmpval = temp;
				getsetmutex.unlock_shared();
				return targe;
			}
			targe = targe->last;
			if (targe == targ)break;
			targ = targ->next;
			if (targe == targ)break;
		}
		*cmpval = -1;
		getsetmutex.unlock_shared();
		return end[findex]->last;
	}


};

#undef string