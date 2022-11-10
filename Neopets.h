#pragma once
/*
functions, statistics, and features:
safe, secure login function
saved cookies between sessions
proprietary encryption suite for on-disk data
 -- can use master account to increase security
 -- can use per-account password to lock account files

 string urlEncode(string str){
	string new_str = "";
	char c;
	int ic;
	const char* chars = str.c_str();
	char bufHex[10];
	int len = strlen(chars);

	for(int i=0;i<len;i++){
		c = chars[i];
		ic = c;
		if (c==' ') new_str += '+';
		else if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') new_str += c;
		else {
			sprintf(bufHex, "%X", c);
			if (ic < 16)
				new_str += "%0";
			else
				new_str += "%";
			new_str += bufHex;
		}
	}
	return new_str;
 }

 string urlDecode(string str) {
	 string ret;
	 char ch;
	 int i, ii, len = str.length();

	 for (i = 0; i < len; i++) {
		 if (str[i] != '%') {
			 if (str[i] == '+')
				 ret += ' ';
			 else
				 ret += str[i];
		 }
		 else {
			 sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
			 ch = static_cast<char>(ii);
			 ret += ch;
			 i = i + 2;
		 }
	 }
	 return ret;
 }

 beta list
 -- shopwiz functions

 wants list
 -- username list generator
 --- shopwiz
 --- boards
 --- auctions
 --- 
 -- item price databaser
 -- score sending script
 -- neggsweeper obviously
 -- stocks buyer
 -- after shopwiz
 --- autoquesters 
 --- auto faerie quest checker
 --- quick heavily feature rich shop stocker






click avatars:
http://www.neopets.com/objects.phtml?obj_type=78&type=shop
http://www.neopets.com/petlookup.phtml?pet=wiley93




dailies
http://www.neopets.com/jelly/jelly.phtml  post type: get_jelly  You take some<strong>**</strong>
http://www.neopets.com/prehistoric/omelette.phtml " doesn't seem to be any left" failstate
/soupkitchen.phtml   www.neopets.com/get_soup.phtml?pet_name=kyahhhhhhhhhh
http://www.neopets.com/freebies/index.phtml  monthly?

/prehistoric/mediocrity.phtml 

wheel of excitement:
/faerieland/wheel.phtml
/np-templates/ajax/wheels/getResult.php?type=2
{"success":true,"degree":157.5,"image":"http:\/\/images.neopets.com\/common\/bag_of_np.gif","altimage":false,"prizeDescription":false,"name":"224 NP","slot":9,"prizeurl":false,"spinResultMessage":"Wow, what a spectacular prize!"}

/winter/kiosk.phtml
/winter/process_kiosk.phtml -> goto location header as /winter/kiosk.phtml?bought=8903
*/
#include"valwrapper.h"
//#include"strlist_sup_dedupe.h"
int random(int);
class NeopetsUser {
public:

	strlist_dedupe username_list;
	ValCrypt* VCrypt;
	varlist* data;

	valwrapper inet;

	string username, password;
	string status;
	ValScheduler schedule;
	bool loggedin = false;
	NeopetsUser(){ inet.reinit("www.neopets.com"); }
	NeopetsUser(string n, string p) { inet.reinit("www.neopets.com");  username = n; password = p;  }
	//void save
	bool init();
	bool login();
	//bool login(int usernumber);
	bool login(string n, string p) {
		if(inet.getdomain()!="www.neopets.com") inet.reinit("www.neopets.com");
		username = n; password = p;
		if (!init())return login();
		return false;
	}


};
//int m3333() {
//	NeopetsUser user("username", "password");
//	if (!user.init()) {
//		cout << "username/password failed. not logged in" << endl;
//		pause();
//		return;
//	}
//	else {
//		_beginthread(boards_usernames_gather, 0, (void*)(&user));
//		_beginthread(moneytree_usernames_gather, 0, (void*)(&user));
//		_beginthread(shops_usernames_gather, 0, (void*)(&user));
//		_beginthread(auctions_usernames_gather, 0, (void*)(&user));
//		_beginthread(dump_usernames, 0, (void*)(&user));
//	}
//	while (1)Sleep(1000);
//}

/* loads cookies/data from encrypted file into user space and tests cookies*/
bool NeopetsUser::init() { // super heavily logged for testing. 
	status = "initializing user space";
	VCrypt = new ValCrypt();
	VCrypt->start(password, 15);
	data = new varlist();
	string fn = username + ".udi";
	string tmp;
	if (file_exists(fn)) {
		status = "loading user data file";
		varlist_dec_load(*data, *VCrypt, fn);
		//data->output();
		tmp = data->valueof("cookies");
		cout << "tmp: " << tmp<<'\n';

		//csl_toshortlist(tmp, inet.cookies);
		inet.cookies.fromcsl_safe(tmp);
		cout << "tmp2: ";
		inet.cookies.output();
		inet.get("/");
		writefile("cooktest.txt", inet.cursource);
		if (findnext(inet.cursource, username, 0) != -1) {
			cout << "cookies loaded, accepted\n";
			status = "cookies loaded - accepted";
			loggedin = true;
			return true;
		}
		else {
			cout << "cookies loaded, failed\n";
			status = "cookies not accepted";
			
			inet.cookies.clear();
			login();
		}

	}
	else {
		status = "user file not found";
		cout << status << endl;
	//	login();
	}
	return false;
	

}

/* logs neopets account in and saves cookie data */
bool NeopetsUser::login() {

	status = "started login";
	inet.get("/");
	//Write_File("out.html", inet.cursource);
	inet.get("/login/");
	status = "logging in- sleep 2s";
	Sleep(1000);
	inet.post("/login.phtml", "username="+username+"&password="+password+"&destination=&return_format=1");
	writefile("login.txt", inet.cursource);
	Sleep(1000);
	inet.get("/");
	writefile("login2.txt", inet.cursource);
	if (findnext(inet.cursource, username, 0) != -1) {
		status = "login success";
		//shortlist_set_varlist(inet.cookies, *data);

		//data->set("cookies", shortlist_tocsl(inet.cookies));
		data->set("cookies", inet.cookies.tocsl_safe());
		//data->set("cookiesraw", inet.cookies.cookieval());
		data->set("username", username);
		data->set("password", password);
		//data->save(username + "_.di");
		varlist_enc_save(*data, *VCrypt, username + ".udi"); 
		// maybe decload into that space and reset values to make sure
		// they aren't being overwritten
		loggedin = true;
		return true;
	}
	status = "login failed check out.html";
	Write_File("out.html",inet.cursource);
	return false;
}
/*********************************************************************************************************************/
/******************************* end neopetsuser  block **************************************************************/
/*********************************************************************************************************************/
/******************************* begin string manipulation block******************************************************/
/*********************************************************************************************************************/
char ffoc_oper;
// finds the first instance of a char in chs that occurs in wh after offset.  
//sets op as char it hit and returns the index that char exists at.
int FindFirstOfChar(string wh, string chs, int offset=0, char& op = ffoc_oper) {
	for (int i = offset; i < wh.length(); i++) {
		for (int x = 0; x < chs.length(); x++) {
			if (wh[i] == chs[x]) {
				op = chs[x];
				return i;
			}
		}
	}
	return -1;
}
// parse out usernames from generic page. 
void parse_usernames(NeopetsUser* np) {
	int ind = 0;
	string pagesource = np->inet.cursource, name;
	while ((ind = findnext(pagesource, "kup.phtml?user=", ind)) != -1) {
		name = getbetween(pagesource, "kup.phtml?user=", "\">", ind - 1);
		np->username_list.dedupe_queue(name);
		ind += 3;
	}
	ind = 0;
	while ((ind = findnext(pagesource, "browseshop.phtml?owner=", ind)) != -1) {
		name = getbetween(pagesource, "browseshop.phtml?owner=", "&buy_cost", ind - 1);
		np->username_list.dedupe_queue(name);
	}
}
string strip_commas(string st){
	return str_replace(st, ",", "");
}
/*********************************************************************************************************************/
/******************************* end string manipulation block *******************************************************/
/*********************************************************************************************************************/
/******************************* begin NeopetsUser Friend functions **************************************************/
/*********************************************************************************************************************/
bool shopwiz_search_basic(NeopetsUser* np, string whatitem, bool exactmatch = false, int minp = 0, int maxp = 999999) {
	valwrapper* inet = &(np->inet);
	inet->get("/market.phtml?type=wizard");
	Sleep(3000); // more sleep here for safety. typing is slow. 
	inet->post("/market.phtml", "type=process_wizard&feedset=0&shopwizard=" + whatitem + "&table=shop&criteria="
		+ (exactmatch ? "exact" : "containing") + "&min_price=" + ctostr(minp) + "&max_price=" + ctostr(maxp));

	parse_usernames(np);
	if (findnext(inet->cursource, "&buy_cost_neopoints=") == -1) {
		np->status = "failed wizsearch for " + whatitem;
		return false;
	}
	np->data->set("last_wizsearch", whatitem);
	string price = getbetween(inet->cursource, "&buy_cost_neopoints=", "\"><", 0);
	if (price == "")return false;
	np->data->set("last_wizprice", price);
	string uname = getbetween(inet->cursource, "browseshop.phtml?owner=", "&buy_obj", 0);
	np->data->set("last_wizuname", uname);
	return true;

	/*
	http://www.neopets.com/market.phtml?type=wizard
	/market.phtml
	type: process_wizard
	feedset: 0
	shopwizard: cheese
	table: shop
	criteria: containing
	min_price: 0
	max_price: 999999

		string link = "/buyitem.phtml?" + getbetween(inet->cursource, "<a href=\"buy_item.phtml?" ,"\" ",0);
	np->data->set("last_wizlink", link);


	after search, usernames/shops for that item are as browseshop.phtml?owner=****&buy_cost
	buy item link as <a href="buy_item.phtml?***\"
	on usershop
	item names and prices after buy link ind as "sure you wish to buy *** at ****** NP. strip commas from np
	*/
}


/*
void neopets_MS_buycaptcha_downloader(NeopetsUser* np){
	// refresh a mainshop
	//mkdir imagefolder
	// find items to buy
	// pick random item in list
	// go to haggle page
	// find image link
	// parse out 'find the ___' string 
	//download image link to find_the__ string+ random#s filename in images folder
	// Sleep for like 3 mins


	is SOLD OUT!
	current_offer: 525
x: 94
y: 93
1:fresh foods
2:magic shop
3:toy shop
4:clothing shop
5:grooming parlor
6:none
7:bookshop
8:collectable card shop
9:battle magic
10:defence magic
11:none
12:garden centre
13:pharmacy
14:chocolate



new bank form:

			<form id='frmNewAccount' action='/np-templates/ajax/process_bank.php' method="post" onSubmit="return one_submit();">
			<input type='hidden' name='type' value='new_account'>
			<input type='hidden' name='_ref_ck' value='87d7ea9b0e890efd8936220fbe72c2e8'>

			<div id='frmNewAccountResult' style='color:green'></div>
			<div class='bank-createaccount-grid'>
				<h3>Your Name:</h3><input type='text' name='name' size=20 maxlength=30>
				<h3>Your Neopian Address</h3><input type='text' name='add1' size=30 maxlength=50>
				<input type='text' name='add2' size=30 maxlength=50>
				<input type='text' name='add3' size=30 maxlength=50>
				<p class='bank-address-info'>(Don't enter your real address.)</p>
				<h3>Current Employment:</h3>
				<select name='employment'>
					<option selected>Select One
					<option>Chia Custodian
					<option>Wocky Warden
					<option>Korbat Keeper
					<option>Grarrl Guardian
					<option>JubJub Janitor
					<option>Lenny Librarian
					<option>Kiko Caretaker
					<option>Scorchio Supervisor
					<option>Pteri Policeman
					<option>Blumaroo Babysitter
					<option>Chomby Curator
					<option>Nimmo Nurse
					<option>Skeith Secretary
					<option>Aisha Assistant
					<option>Techo Technician
					<option>Gelert Gardener
					<option>Meerca Master
					<option>Elephante Editor
					<option>Quiggle Quantum Physicist
					<option>Other
				</select>
				<h3>Annual Salary:</h3>
				<select name='salary'>
					<option selected>Select One
					<option>10,000 NP and below
					<option>10,000 to 25,000 NP
					<option>25,001 to 40,000 NP
					<option>40,001 to 60,000 NP
					<option>60,001 to 90,000 NP
					<option>90,001 to 120,000 NP
					<option>120,001 NP and above
				</select>
				<h3>Account Type:</h3>
				<select name='account_type'>
					<option value="-1" selected>Select One
					<option value='0'>Junior Saver (min 0 NP)
					<option value='1'>Neopian Student (min 1,000 NP)
					<option value='2'>Bronze Saver (min 2,500 NP)
					<option value='3'>Silver Saver (min 5,000 NP)
					<option value='4'>Super Gold Plus (min 10,000 NP)
					<option value='5'>Platinum Extra (min 25,000 NP)
					<option value='6'>Double Platinum (min 50,000 NP)
					<option value='7'>Triple Platinum (min 75,000 NP)
					<option value='8'>Diamond Deposit (min 100,000 NP)
					<option value='9'>Diamond Deposit Plus (min 250,000 NP)
					<option value='10'>Diamond Deposit Gold (min 500,000 NP)
					<option value='11'>Millionaire Platinum (min 1,000,000 NP)
					<option value='12'>Millionaire Double Platinum (min 2,000,000 NP)
					<option value='13'>Millionaire Mega-Platinum (min 5,000,000 NP)
					<option value='14'>Neopian Mega-Riches (min 7,500,000 NP)
					<option value='15'>Ultimate Riches! (min 10,000,000 NP)					</select>
				<h3>Initial Deposit:</h3>
				<div><input type='text' size=10 maxlength=10 name='initial_deposit'> <span class='bank-text-bold'>NP</span></div>
			</div>
			<input class='button-default__2020 button-yellow__2020 btn-single__2020' type='submit' value='Sign Me Up'>
			</form>
	
*/

int neouser_source_parse_nponhand(string& source) {
	int ind = findnext(source, "<span id=\"npanchor\"", 0);
	string ret = getbetween(source, "\">", "</span", ind);
	
	return stoint(ret);
}

int get_database_index(string ext) {
	int r = 0;
	while (1) {
		if (!file_exists(ctostr(r) + ext))break;
		r++;
	}
	return r;
}

int neouser_mainshopsource_parse_items(string& source, varlist& items, string del= "_^_") {
	int ind = findnext(source, "<form name=\"items_for_sale\" method=\"post\">", 0);  // can change 0 to like 10k.. so much lead-in
	string name, img, price, link, stock;
	int n = 0;
	items.clear();
	while (ind != -1) { // fill up the items in stock list.. make it's own function.
		img = getbetween(source, "image:url(\"", "\")", ind);
		name = getbetween(source, ")' data-name='", "' ", ind);
		price = getbetween(source, "' data-price='", "' ", ind);
		link = getbetween(source, "' data-link='haggle.phtml?", "'>", ind);
		stock = getbetween_I(source, "lass='item-stock'>", " in stock", ind);
		if (ind == -1)break;
		ind = findnext(source, "<div class='shop-item'", ind);
		items.set("item" + ctostr(n), name);
		items.set("IMG"+del + name + del, img);
		items.set("PRICE" + del + name + del, img);
		items.set("LINK" + del + name + del, img);
		n++;
	}
	return n;

}
void mainshop_captcha_gather(NeopetsUser* np) {
	np->status =np->username+ "started mainshop captcha Gatherer";
	int sch_ID = np->schedule.GetId(60000,"mainshop captcha gather",1);
	np->schedule.Run(sch_ID);
	
	varlist items;
	
	string del = "_^_";
	int n = 0, sleep =0;
	int ind = 0;
	int database_index = get_database_index(".jpg");
	cout << "database index found: " << database_index << '\n';
	string shop_num = "3";
	while (1) {
		np->schedule.Run(sch_ID); // make sure it's my turn
		np->inet.get("/objects.phtml?type=shop&obj_type="+shop_num); // get the food shop, always stocked.

		ind = findnext(np->inet.cursource, "<form name=\"items_for_sale\" method=\"post\">", 0);  // can change 0 to like 10k.. so much lead-in
		string name, img, price, link, stock;
		n = 0;
		items.clear();
		while (ind != -1) { // fill up the items in stock list.. make it's own function.
			img = getbetween(np->inet.cursource, "image:url(\"", "\")", ind);
			name = getbetween(np->inet.cursource, ")' data-name='", "' ", ind);
			price = getbetween(np->inet.cursource, "' data-price='", "' ", ind);
			link = getbetween(np->inet.cursource, "' data-link='haggle.phtml?", "'>", ind);
			stock = getbetween_I(np->inet.cursource, "lass='item-stock'>", " in stock", ind);
			if (ind == -1)break;
			ind = findnext(np->inet.cursource, "<div class='shop-item'", ind);
			items.set("item" + ctostr(n), name);
			items.set("IMG_^_" + name + del, img);
			items.set("PRICE_" + name + del, img);
			items.set("LINK_" + name + del, img);
			n++;
		}
		if (n == 0) {
			cout << "no items found in shop\n";
			np->status = "no items found in shop #" + shop_num + " sleep 30sec";
			Sleep(30000);
			continue;
		}
		for (int i = 0; i < n / 5; i++) { // check some random items and download the captcha
			int which = random(n - 1);
			string nm = items.valueof("item" + ctostr(which));
			string lnk = items.valueof("LINK_" + nm);
			np->inet.get("/haggle.phtml?" + lnk);
			ind = findnext(np->inet.cursource, "<input type=\"image\" src=\"/captcha_show.phtml?", 0);
			if (ind == -1) {
				cout << "no captcha found on haggle page "<<lnk<<" .\n";
				continue;
			}
			img = getbetween(np->inet.cursource, "/captcha_show.phtml?", "\" s", ind);
			sleep = random(30000);
			np->status = "getting captcha #" + ctostr(database_index) + " , sleep:" +ctostr((30000 + sleep)/1000) + " sec";
			np->inet.dl("/captcha_show.phtml?" + img, ctostr(database_index) + ".jpg");
			database_index++;

			Sleep(30000 + sleep);
		}



	}

}
void boards_username_scrape_nolog(NeopetsUser* np) {// actually does log now

	np->status = "started Boards Uname Gatherer";

	np->inet.get("/neoboards/index.phtml");
	Sleep(8000);
	int ind = 0;
	string ldelim = " align='left' style='border-top: 1px solid black;'><a href='boardlist.phtml?board=";
	string boardnum;
	string boardsource = np->inet.cursource;
	string namehold;
	ofstream ofile("usernamelist.txt", fstream::app);
	int s = 0;
	string threadsource = "", topicnum;
	while ((ind = findnext(boardsource, ldelim, ind)) != -1) {
		boardnum = getbetween(boardsource, ldelim, "'><img", ind - 1);
		if (boardnum == "40") {
			ind += 50; continue;
		}
		for (int i = 1; i < 241; i += 40) {
			
			np->status = "getting board " + boardnum + " : " + ctostr(i);
			np->inet.get("/neoboards/boardlist.phtml?board=" + boardnum + "&next=" + ctostr(i));
			//Write_File("board.txt", np->inet.cursource);
			//pause();
			s = 3000 + random(3000);
			np->status += "sleep: " + ctostr(s);
			Sleep(s);
			int ind2 = 0;
			threadsource = np->inet.cursource;
			while ((ind2 = findnext(threadsource, "topic=", ind2)) != -1) {
				topicnum = getbetween(threadsource, "topic=", "\" ", ind2 - 1);
				string next = "";
				int nexti = 1;
				while (1) {
					np->status = " getting topic number: " + topicnum + next;
					np->inet.get("/neoboards/topic.phtml?topic=" + topicnum + next);
					s = 3000 + random(3000);
					np->status += "sleep: " + ctostr(s);
					Sleep(s);
					//can call parse_usernames here instead
					int ind3 = 0;
					string pagesource = np->inet.cursource, name;
					//Write_File("topic.txt", np->inet.cursource);
					while ((ind3 = findnext(pagesource, "kup.phtml?user=", ind3)) != -1) {
						name = getbetween(pagesource, "kup.phtml?user=", "\">", ind3 - 1);
						cout << name << endl;
						np->username_list.dedupe_queue(name);
						ind3 += 5;
					}
					nexti += 20;
					if (findnext(pagesource, "&next=" + ctostr(nexti), 0) != -1)next = "&next=" + ctostr(nexti);
					else break;

				}
			}
			// after this just parses out names from boards thread list, not from inside thread.
			// instead, here, parse out all thread numbers, hit each thread/thread page, parse out names as:
			// threads: topic=*****\" cla
			// names on threads:  find kup.phtml?user=*****\"><strong cla
			// if in thread source code exists "topic=***&next="+ value as 1 step 20, process next thread
			// -- else revert back to threads list and get next thread. 
			/*
			while ((ind2 = findnext(np->inet.cursource, "\" class=\"blistSmall\"><b>", ind2)) != -1) {
				namehold = getbetween(np->inet.cursource, "\" class=\"blistSmall\"><b>", "</b></a>", ind2 - 1);
				cout << namehold << endl;
				ofile << namehold << endl;
				ind2+=50;
			}
			*/
				
		}
		ind += 50;

	}
	np->status = "ended board username gather";
	

}


/* MS_AB notes
* 
haggle.phtml
current_offer: 250
x: 48
y: 68 
^^ocr coords

type="image" src="/captcha_show.phtml?
" s


/objects.phtml?obj_type=3&type=shop  // gets a shop

get lots of captchas to test running captchacatcher on.
notes on preliminary OCR reverse engineer
-- seems to be dark pixels currently that are what signify the image to click.
-- some deep analysis on multiple solve types should be done for overall accuracy- human checked. save resulting functions
-- first idea is to add values for 4pix squares into array 1/4x1/4 the size, find 10 highest squares, find 5 with least 
    -- overall space between them (5 with the smallest average distance to 5 closest patches), take average of coords

-- 2nd idea is to check alpha layer. jpgs may retain that info and the alpha would have to be set on the above pixels for the
   -- transparency to work as it does in many cases. 

-- 3rd- hardest and probably best-  get copies of all blank background cells and just find associated bk, find changed squares.
  -- this can fallback to alternate versions when nessesary.

-- 4th-  find the 20 darkest pixels, 10 with shortest distance between them, if longest distance between these 10 is less than x


packet scrapes:


***  create new shop
shop_name: Some Neopians junk
shop_world: 0
description: no description for now
remLen: 4000
shopkeeper_name: Tim
shopkeeper_greeting: "buy something"


quickstock page
http://www.neopets.com/quickstock.phtml
process_quickstock.phtml
buyitem: 0
id_arr[1]: 1652222143
id_arr[2]: 1652222530
checkall: on
   will need to parse out id_arr and names etc. download page. 



   moneytree
   /donations.phtml
   <a href="takedonation_new.phtml?donation_id=503&xcn=8e5ad4ba9496ba3bb83716d37e0a0574&location_id=0"><img src="http://images.neopets.com/items/vor_driftwood.gif" class="np" alt="Rotting Driftwood" /></a>
	<p class="name">Rotting Driftwood</p>
	<p class="by">donated by</p>
   <p class="donationuser">randgris9</p>
   can be 'The Wishing well name
* 
* 
* 
* 
* 
*/


/*****************************************neopets adjacent functions.  remove for release versions to alternative file.. *******************************************************/
void scrape_jellyneo_itemdatabase() {
	valwrapper inet("www.deltainfiniti.com");

	varlist varli;
	varli.load("itemdatabase.di");
	int lastpage = 0;
	string itemname, itemprice;
	if (varli.isset("lastpage")) lastpage = ctoint(varli.valueof("lastpage"));
	int ind = 0, checkind;
	while (lastpage < 58650) {
		inet.get("/pprox.php?page=https%3A%2F%2Fitems.jellyneo.net%2Fsearch%2F%3Fstart%3D" + ctostr(lastpage));
		ind = findnextl(inet.cursource, "no-padding small-block-grid-3 large-block-grid-5 text-center word-wrap-break-word", 0);
		while ((ind = findnext(inet.cursource, "if\" alt=\"", ind)) != -1) {
			itemname = getbetween(inet.cursource, "if\" alt=\"", "\" ti", ind);
			checkind = ind;
			ind = findnextl(inet.cursource, "ce-history-lin", ind);
			if (ind == -1 || ind > findnext(inet.cursource, "</li>", checkind) || inet.cursource[ind] == 'I') {
				itemprice = "-1";
				ind = checkind;
			}
			else itemprice = getbetween(inet.cursource, "\">", " NP<", ind);
			if (itemprice.length() > 12) {
				itemprice = "-1";
				ind = checkind;
			}
			cout << endl << itemname;
			varli.set(itemname, itemprice);
			if (ind == -1)break;
			ind += 10;
		}
		lastpage += 50;
		varli.set("lastpage", ctostr(lastpage - 50));
		varli.save("itemdatabase.di");
		cout << "varlist size: " << varli.getsize() << "  lastpage: " << lastpage << "                 \r";
		Sleep(60000);
	}
	cout << "finished scraping jellyneo" << endl;
	//("https://items.jellyneo.net/search/?start=0");
	// find no-padding small-block-grid-3 large-block-grid-5 text-center word-wrap-break-word
	// item name as "if\" alt=\"***\" cla" 
	// find ce-history-lin after item name index
	// price = getbetween "\">*** NP<"

	Write_File("neoout.txt", inet.cursource);

}