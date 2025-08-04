//Junaid Muhammad 23L-1014 Section:F
#include<iostream>
#include<fstream>
using namespace std;

class Helper {//Class 1
public:
	//Find the string length
	static int stringlen(char* str) {
		int length = 0;
		for (char* i = str; *i != '\0'; i++)
			length++;
		return length;
	}
	//Copies one string into the other
	static void StringCopy(char*& dest, char*& src) {
		char* tempDest = dest;
		for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++)
			*tempDest = *tempSrc;
		*tempDest = '\0';
	}
	//Takes the string from the buffer
	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = stringlen(buffer);
		char* str = 0;
		if (strLen > 0)
		{
			str = new char[strLen + 1];
			StringCopy(str, buffer);
		}
		return str;
	}
	//Checks if one word is found in a specific string
	static int wordfound(char* string, char* word) {
		int wordlength = stringlen(word);
		int stringlength = stringlen(string);
		for (int i = 0; string[i] != '\0'; i++) {
			if (string[i] == word[0] && i <= stringlength - wordlength) {
				int count = 0;
				for (int j = 1; j < wordlength; j++)
					if (string[i + j] == word[j])
						count++;
				if (count == wordlength - 1)
					return 1;
			}
		}
		return 0;
	}
	//Simply concatenates the two strings
	static void stringconcatenate(char*& str1, char* str2) {
		int size1 = stringlen(str1);
		int size2 = stringlen(str2);

		char* temp = new char[size1 + size2 + 1];

		for (int i = 0; i < size1; i++)
			temp[i] = str1[i];

		for (int i = 0; i < size2; i++)
			temp[size1 + i] = str2[i];

		temp[size1 + size2] = '\0';
		delete[] str1;
		str1 = temp;

	}
	//Compares the two strings
	static int stringcompare(char* str1, char* str2) {
		int len1 = stringlen(str1), len2 = stringlen(str2);
		if (len1 != len2)
			return 0;
		else
		{
			int count = 0;
			for (int i = 0; i < len1; i++)
				if (str1[i] == str2[i])
					count++;
			if (count == len1)
				return 1;
		}
		return 0;
	}
};
//Forward Declaration
class Object;
class Date;
class Post;

class Date {//Class 2
private:
	int day;
	int month;
	int year;
public:
	static Date currentdate;
	Date(int D = 0, int M = 0, int Y = 0) {
		day = D;
		month = M;
		year = Y;
	}
	//no destructor required as no memory allocated on heap so nothing is there to be cleared
	Date* setvalues(int d = 0, int m = 0, int y = 0) {
		day = d;
		month = m;
		year = y;
		return this;
	}
	void setdate(int d = 0, int m = 0, int y = 0) {
		day = d;
		month = m;
		year = y;
	}
	//Prints out the date 
	void printdate() {
		//current day check
		Date::currentdate.setvalues(17, 4, 2024);
		if (Date::currentdate.getday() == day && Date::currentdate.getmonth() == month && Date::currentdate.getyear() == year)
			cout << "1h";
		else
			cout << day << "/" << month << "/" << year;
	}
	int getday() {
		return day;
	}
	int getmonth() {
		return month;
	}
	int getyear() {
		return year;
	}
};
Date Date::currentdate;

class Object {//Class 3
private:
	char* ID;
protected:
	Post** Timeline;
	int timelinecount;
public:
	Object() {
		ID = nullptr;
		Timeline = new Post * [10];
		for (int i = 0; i < 10; i++)
			Timeline[i] = nullptr;
		timelinecount = 0;
	}
	int gettimelinecount() {
		return timelinecount;
	}
	Post** getTimeline() {
		return Timeline;
	}
	char* getid() {
		return ID;
	}
	void setid(char* id) {
		ID = Helper::GetStringFromBuffer(id);
	}
	virtual char* getname() {
		return nullptr;
	};
	virtual ~Object() {

		delete[] ID;
		delete[] Timeline;
	}
	virtual void print() = 0;
	virtual void AddPostToTimeline(Post*) {};
	virtual void viewtimeline() {};
	virtual void PrintLatestPost() {};

};

class Comment {//Class 4
private:
	char* ID;
	Object* commentedby;
	char* text;
public:
	Comment() {
		commentedby = nullptr;
		ID = text = nullptr;
	}
	void SetValues(char* cid, Object* cby, char* content) {
		ID = Helper::GetStringFromBuffer(cid);
		commentedby = cby;
		text = Helper::GetStringFromBuffer(content);
	}
	void printcomment() {
		cout << commentedby->getname() << ": " << text << "\n";
	}
	~Comment() {

		if (ID)
			delete[] ID;
		if (text)
			delete[] text;
		commentedby = nullptr;
	}
};
class postcontent {
private:

public:
	virtual int gettype() {
		return 0;
	}
	virtual char* getvalue() {
		return nullptr;
	}
	virtual void settype(int) {}
	virtual void setvalue(char*) {}
};

class Activity :public postcontent {
private:
	int type = 0;
	char* value = nullptr;
public:
	void settype(int Type) {
		type = Type;
	}
	void setvalue(char* Value) {
		value = Helper::GetStringFromBuffer(Value);
	}
	int gettype() {
		return type;
	}
	char* getvalue() {
		return value;
	}
	~Activity() {

		if (value) {
			delete[] value;
		}
	}
};
class Post {//Class 4
private:
	char* ID;
	char* text;
	Object* sharedby;
	Date* sharedon;
	Object** likedby;
	Comment** comments;
	postcontent** contents;
	int currentlikes;
	int currentcomments;
	int contentcount;
public:
	Post() {
		ID = text = nullptr;
		sharedby = nullptr;
		sharedon = nullptr;
		likedby = new Object * [10];
		comments = new Comment * [10];
		contents = nullptr;
		for (int i = 0; i < 10; i++)
		{
			likedby[i] = nullptr;
			comments[i] = nullptr;
		}
		currentlikes = currentcomments = contentcount = 0;
	}
	char* gettext() {
		return text;
	}
	Post(char* Text, Object* curruser, Post* oldpostptr) {
		ID = Helper::GetStringFromBuffer(oldpostptr->getpostid());
		text = Helper::GetStringFromBuffer(Text);
		sharedby = curruser;
		sharedon = &(Date::currentdate);
		likedby = nullptr;
		comments = nullptr;
	}
	void addcontent(Activity* acti) {
		contentcount++;
		postcontent** newcontent = new postcontent * [contentcount];
		int i = 0;
		while (i < contentcount - 1) {
			newcontent[i] = contents[i];
			i++;
		}
		newcontent[i] = acti;
		delete[] contents;
		contents = newcontent;
	}
	void printactivity() {
		if (contents) {
			cout << sharedby->getname() << " is ";
			int type;
			type = contents[0]->gettype();
			if (type == 1)
				cout << " feeling ";
			else if (type == 2)
				cout << " thinking about ";
			else if (type == 3)
				cout << " making ";
			else if (type == 4)
				cout << " celebrating ";
			cout << contents[0]->getvalue();
		}
		else
			cout << sharedby->getname();
	}
	~Post() {

		if (ID)
			delete[] ID;

		if (text)
			delete[] text;

		if (sharedon)
			delete sharedon;

		if (likedby) {
			for (int i = 0; i < currentlikes; i++) {
				delete likedby[i];
			}
			delete[] likedby;
		}
		for (int i = 0; i < currentcomments; i++)
			delete[] comments[i];
		delete[] comments;
	}
	void addlike(Object* liker) {
		likedby[currentlikes] = liker;
		inccurrentlikes();
	}
	void AddComment(Comment* cptr) {
		comments[currentcomments] = cptr;
		inccurrentomments();
	}
	Date* getsharedon() {
		return sharedon;
	}
	char* getpostid() {
		return ID;
	}
	void inccurrentlikes() {
		currentlikes++;
	}
	void inccurrentomments() {
		currentcomments++;
	}
	virtual void printpostTime() {
		cout << "("; sharedon->printdate(); cout << ")\n";
		cout << "\t" << text << "\n";
		for (int i = 0; i < currentcomments; i++) {
			cout << "\t\t";
			comments[i]->printcomment();
		}
		cout << endl << endl;
	}
	void printpost() {
		cout << sharedby->getname();
		cout << "("; sharedon->printdate(); cout << ")\n";
		cout << "\t" << text << "\n";

		for (int i = 0; i < currentcomments; i++) {
			cout << "\t\t";
			comments[i]->printcomment();
		}
		cout << endl << endl;
	}
	void postlikedby() {
		cout << "Post Liked by: \n";
		int i = 0;
		while (likedby[i] != nullptr && i < 10) {
			cout << likedby[i]->getid() << " ";
			cout << "-" << likedby[i]->getname() << endl;
			i++;
		}
		if (i == 0)
			cout << "\nNo Likes Yet!\n";
		cout << endl;
	}

	void setsharedby(Object* sharer) {
		sharedby = sharer;
	}
	Object* getsharedby() {
		return sharedby;
	}
	Post* ReadDataFromFile(ifstream& fin) {
		char temp[100];
		fin >> temp;
		ID = Helper::GetStringFromBuffer(temp);

		int D, M, Y;

		fin >> D;

		fin >> M;

		fin >> Y;
		sharedon = new Date;
		sharedon->setvalues(D, M, Y);

		fin.getline(temp, 99);
		fin.getline(temp, 99);
		text = Helper::GetStringFromBuffer(temp);

		return this;
		//Rest of the reading done in the LoadPosts
	}
	void setsharedon(Date* date) {
		sharedon = date;
	}
};

class Memory :public Post {
private:
	Post* originalpostptr;
public:
	Memory(char* Text, Object* curruser, Post* oldpostptr) :Post(Text, curruser, oldpostptr) {
		originalpostptr = oldpostptr;
	}
	void printpostTime() {
		cout << " shared a memory ";
		cout << "("; Post::getsharedon()->printdate(); cout << ")";
		cout << endl << "\t" << Post::gettext() << endl;
		cout << "\t\t" << Date::currentdate.getyear() - originalpostptr->getsharedon()->getyear() << "years ago.\n";
	}
	//No destructor required here
};

class Page : public Object {//Class 6
private:
	char* Title;
public:
	Page() :Object() {
		Title = nullptr;
	}

	Page* ReadDataFromFile(ifstream& fin) {

		char temp[100];
		fin >> temp;
		setid(Helper::GetStringFromBuffer(temp));

		fin.getline(temp, 100);
		Title = Helper::GetStringFromBuffer(temp);

		return this;
	}
	void AddPostToTimeline(Post* postptr) {
		Timeline[timelinecount] = postptr;
		timelinecount++;
	}
	char* getname() {
		return Title;
	}
	void print() {
		cout << "ID: " << getid() << "\nTitle: " << Title << endl << endl << endl;
	}

	void viewtimeline() {
		for (int i = 0; i < timelinecount; i++) {
			Timeline[i]->printactivity();
			Timeline[i]->printpostTime();
		}
	}
	void PrintLatestPost() {
		Date today;
		today.setvalues(17, 4, 2024);
		for (int i = 0; i < timelinecount; i++) {
			Post* current = Timeline[i];
			Date* time = current->getsharedon();
			if (time->getday() == today.getday() && time->getmonth() == today.getmonth() && time->getyear() == today.getyear())
				current->printpost();
		}
	}
	~Page() {

		if (Title)
			delete[] Title;

	}
};

class User :public Object {//Class 7

private:
	char* Fname;
	char* Lname;
	User** FriendList;//null or 10 pointers max
	Page** LikedPages;//null or 10 pointers max
	int currentfriends;
	int currentpages;

public:
	User() :Object() {
		Fname = Lname = nullptr;
		FriendList = new User * [10];
		LikedPages = new Page * [10];

		for (int i = 0; i < 10; i++)
		{
			FriendList[i] = nullptr;
			LikedPages[i] = nullptr;
		}
		currentfriends = currentpages = 0;
	}
	~User() {

		if (Fname)
			delete[] Fname;
		if (Lname)
			delete[] Lname;
		delete[] FriendList;
		delete[] LikedPages;

	}
	void SeeYourMemories() {
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n";
		for (int i = 0; i < timelinecount; i++)
		{
			if (Timeline[i]->getsharedon()->getday() == Date::currentdate.getday() && Timeline[i]->getsharedon()->getmonth() == Date::currentdate.getmonth() && Timeline[i]->getsharedon()->getyear() != Date::currentdate.getyear()) {
				cout << Fname << " " << Lname << " shared a memory ";
				cout << "("; Timeline[i]->getsharedon()->printdate(); cout << ")";
				cout << endl << "\t" << Timeline[i]->gettext() << endl;
				cout << "\t\t" << Date::currentdate.getyear() - Timeline[i]->getsharedon()->getyear() << " years ago.\n";
			}
		}
	}
	char* getname() {
		char* name = Helper::GetStringFromBuffer(Fname);
		char space[] = " ";
		Helper::stringconcatenate(name, space);
		Helper::stringconcatenate(name, Lname);
		return name;
	}
	char* getfname() {
		return Fname;
	}
	char* getlname() {
		return Lname;
	}
	User(const User& obj) {//Unsure where to be used
		setid(Helper::GetStringFromBuffer(Object::getid()));
		Fname = Helper::GetStringFromBuffer(obj.Fname);
		Lname = Helper::GetStringFromBuffer(obj.Lname);

		FriendList = new User * [10];
		LikedPages = new Page * [10];

		for (int i = 0; i < 10; i++)
		{
			FriendList[i] = obj.FriendList[i];
			LikedPages[i] = obj.LikedPages[i];
		}

		currentfriends = obj.currentfriends;
		currentpages = obj.currentpages;
	}
	void incfriendscount() {
		currentfriends++;
	}

	int getfriendscount() {
		return currentfriends;
	}

	void incpagecount() {
		currentpages++;
	}

	int getpagescount() {
		return currentpages;
	}

	void ViewFriendList() {
		int i = 0;
		while (FriendList[i] != nullptr && i < 10) {
			FriendList[i]->print();
			i++;
		}
		if (i == 0)
			cout << "\nNo Friends !\n";
	}

	void ViewLikedPages() {
		int i = 0;
		while (LikedPages[i] != nullptr && i < 10) {
			LikedPages[i]->print();
			i++;
		}
		if (i == 0)
			cout << "\nNo Liked Pages!\n";
	}

	void AddFriend(User*& newfriend) {
		if (currentfriends < 10) {
			FriendList[currentfriends] = newfriend;
			incfriendscount();
		}
	}

	void LikePage(Page*& newpage) {
		if (currentpages < 10) {
			LikedPages[currentpages] = newpage;
			incpagecount();
		}
	}

	User* ReadDataFromFile(ifstream& fin) {
		char temp[20];
		fin >> temp;
		setid(Helper::GetStringFromBuffer(temp));

		fin >> temp;
		Fname = Helper::GetStringFromBuffer(temp);

		fin >> temp;
		Lname = Helper::GetStringFromBuffer(temp);

		return this;
	}

	void AddPostToTimeline(Post* postptr) {
		Timeline[timelinecount] = postptr;
		timelinecount++;

	}
	void viewtimeline() {
		for (int i = 0; i < timelinecount; i++) {
			Timeline[i]->printactivity();
			Timeline[i]->printpostTime();
		}
	}
	void print() {
		cout << "ID: " << this->getid() << "- " << Fname << " " << Lname << endl;
	}
	void PrintLatestPost() {
		Date today;
		today.setvalues(17, 4, 2024);
		for (int i = 0; i < timelinecount; i++) {
			Post* current = Timeline[i];
			Date* time = current->getsharedon();
			if (time->getday() == today.getday() && time->getmonth() == today.getmonth() && time->getyear() == today.getyear())
				current->printpost();
		}
	}
	void ViewHome() {
		//Find posts from timeline no older than 2 days
		//For each friend, through their timeline display posts no older than 2 days
		//For each page, through their timeline display posts no older than 2 days
		//Above written lines are just for my own convenience 
		//Users own timeline
		for (int i = 0; i < timelinecount; i++)
		{
			Post* current = Timeline[i];
			Date* time = current->getsharedon();
			if (time->getmonth() == Date::currentdate.getmonth() && time->getyear() == Date::currentdate.getyear())
				if ((Date::currentdate.getday() - time->getday()) <= 2) {
					current->printactivity();
					current->printpostTime();
				}
		}
		//Posts posted by friends
		for (int i = 0; i < getfriendscount(); i++)
		{
			User* currentfriend = FriendList[i];
			for (int j = 0; j < currentfriend->timelinecount; j++)
			{
				Post* currentF = currentfriend->Timeline[j];
				Date* timeF = currentF->getsharedon();
				if (timeF->getmonth() == Date::currentdate.getmonth() && timeF->getyear() == Date::currentdate.getyear())
					if ((Date::currentdate.getday() - timeF->getday()) <= 2) {
						currentF->printactivity();
						currentF->printpostTime();
					}
			}
		}
		//Posts posted by liked pages
		for (int i = 0; i < getpagescount(); i++)
		{
			Page* currentpage = LikedPages[i];
			for (int j = 0; j < currentpage->gettimelinecount(); j++)
			{
				Post* currentP = currentpage->getTimeline()[j];
				Date* timeP = currentP->getsharedon();
				if (timeP->getmonth() == Date::currentdate.getmonth() && timeP->getyear() == Date::currentdate.getyear())
					if ((Date::currentdate.getday() - timeP->getday()) <= 2) {
						currentP->printactivity();
						currentP->printpostTime();
					}
			}
		}
	}
};

class Controller {//Class 8

private:
	int totalusers;
	int totalpages;
	int totalposts;
	int totalcomments;
public:
	static User** AllUsers;
	static Page** AllPages;
	static Post** AllPosts;

	Controller() {
		totalusers = totalpages = 0;
		totalposts = totalcomments = 0;
	}
	~Controller() {

		for (int i = 0; i < totalusers; i++)
			delete[] AllUsers[i];
		for (int i = 0; i < totalpages; i++)
			delete[] AllPages[i];
		delete[] AllUsers;
		delete[] AllPages;
		delete[] AllPosts;
	}
	int gettotalusers() {
		return totalusers;
	}

	int gettotalpages() {
		return totalpages;
	}
	int gettotalposts() {
		return totalposts;
	}
	static User* SearchUserByID(char* userid) {
		for (int i = 0; i < 20; i++) {
			char* id = AllUsers[i]->getid();
			if (Helper::stringcompare(userid, id))
				return AllUsers[i];
		}
		return nullptr;
	}
	static Page* SearchPageByID(char* pageid) {
		for (int i = 0; i < 12; i++) {
			if (Helper::stringcompare(pageid, AllPages[i]->getid()))
				return AllPages[i];
		}
		return nullptr;
	}

	static Post* SearchPostByID(char* postid) {
		for (int i = 0; i < 12; i++) {
			if (Helper::stringcompare(postid, AllPosts[i]->getpostid()))
				return AllPosts[i];
		}
		return nullptr;
	}
	static Object* SearchObjByID(char* id) {
		for (int i = 0; i < 20; i++) {
			if (Helper::stringcompare(id, AllUsers[i]->getid()))
				return AllUsers[i];
		}
		for (int i = 0; i < 12; i++) {
			if (Helper::stringcompare(id, AllPages[i]->getid()))
				return AllPages[i];
		}
	}
	void LoadAllUsers(char* filename) {
		ifstream fin;
		fin.open(filename);
		if (fin) {
			fin >> totalusers;
			AllUsers = new User * [totalusers];
			for (int i = 0; i < totalusers; i++)
			{
				AllUsers[i] = new User();
				AllUsers[i]->ReadDataFromFile(fin);
			}
		}
		else
			exit(0);
	}

	void LoadAllPages(char* filename) {
		ifstream fin;
		fin.open(filename);
		if (fin) {
			fin >> totalpages;
			AllPages = new Page * [totalpages];
			for (int i = 0; i < totalpages; i++)
			{
				AllPages[i] = new Page();
				AllPages[i]->ReadDataFromFile(fin);
			}
		}
		else
			exit(0);
	}

	void LinkUsersAndPages() {
		ifstream fin;
		fin.open("Liked.txt");
		if (fin) {
			for (int i = 0; i < 20; i++) {
				char id[10];
				fin >> id;
				User* current = Controller::SearchUserByID(id);//This is the person we are saving the friends for
				char check[] = "-1";
				char* neg = check;
				if (Helper::stringcompare(id, neg)) {
					break;
				}
				fin >> id;//Now reading the friend IDs
				while (!(Helper::stringcompare(id, neg))) {
					User* temp = Controller::SearchUserByID(id);
					if (temp != nullptr)
						current->AddFriend(temp);
					fin >> id;
				}

				fin >> id;//For page
				while (!(Helper::stringcompare(id, neg))) {
					Page* temp = Controller::SearchPageByID(id);
					if (temp != nullptr)
						current->LikePage(temp);
					fin >> id;
				}
			}
		}
		else
			exit(0);
	}

	void LoadAllPosts(char* filename) {
		ifstream fin;
		fin.open(filename);
		if (fin) {
			fin >> totalposts;
			AllPosts = new Post * [totalposts];
			for (int i = 0; i < totalposts; i++) {
				AllPosts[i] = new Post();
				Date date;
				AllPosts[i]->ReadDataFromFile(fin);//ID, Date, Text
				char temp[10];
				fin >> temp;
				if (temp[0] == 'u') {//Sharedby
					User* sharer = SearchUserByID(temp);
					AllPosts[i]->setsharedby(sharer);
					sharer->AddPostToTimeline(AllPosts[i]);
				}
				else if (temp[0] == 'p') {
					Page* sharer = SearchPageByID(temp);
					AllPosts[i]->setsharedby(sharer);
					sharer->AddPostToTimeline(AllPosts[i]);
				}
				fin >> temp;
				while (temp[0] != '-')//checking if the id is equal to -1, so we take the negative sign for the check
				{
					if (temp[0] == 'u') {
						AllPosts[i]->addlike(SearchUserByID(temp));
					}
					else if (temp[0] == 'p') {
						AllPosts[i]->addlike(SearchPageByID(temp));
					}
					fin >> temp;
				}
			}
		}
		else
			exit(0);
	}
	void LoadAllComments(char* filename) {
		ifstream fin;
		fin.open(filename);
		if (fin) {
			fin >> totalcomments;
			for (int i = 0; i < totalcomments; i++) {
				Comment* cptr = new Comment();
				char cid[4];
				char pid[6];
				fin >> cid;
				fin >> pid;

				Post* postptr = SearchPostByID(pid);
				postptr->AddComment(cptr);

				fin >> cid;
				Object* optr = SearchObjByID(cid);

				char temp[100];
				fin.getline(temp, 99);
				cptr->SetValues(cid, optr, temp);
			}
		}
		else
			exit(0);
	}
	void LoadAllActivites(char* filename) {
		ifstream fin;
		fin.open(filename);
		if (fin) {
			int totalactivites = 0;
			fin >> totalactivites;
			for (int i = 0; i < totalactivites; i++) {
				char pid[7];
				fin >> pid;
				Post* postptr = SearchPostByID(pid);
				Activity* act = new Activity();
				int type;
				fin >> type;
				act->settype(type);
				char value[100];
				fin.getline(value, 99);
				act->setvalue(value);
				postptr->addcontent(act);

			}
		}
		else
			exit(0);
	}
	void friendlistbyid(char* id) {
		User* current;
		current = SearchUserByID(id);
		current->ViewFriendList();
	}

	void LoadData()
	{
		char userfile[] = "Users.txt";

		char pagefile[] = "Pages.txt";

		char postfile[] = "Posts.txt";

		char commentfile[] = "Comments.txt";

		char activityfile[] = "Activites.txt";

		LoadAllUsers(userfile); //Keep it easily configurable
		LoadAllPages(pagefile); //Keep it easily configurable
		LinkUsersAndPages();
		LoadAllPosts(postfile);
		LoadAllComments(commentfile);
		LoadAllActivites(activityfile);
	}
	void currentuser() {
		static Date currentdate;
		currentdate.setvalues(17, 4, 2024);
		cout << "------------------------------------------------------------\n";
		cout << "Command:Set current System Date 17 4 2024\n";
		cout << "------------------------------------------------------------\n";

		//This part runs all the commands for user with id u7
		cout << "\n------------------------------------------------------------\n";
		cout << "Set current user: u7 \n";
		cout << "------------------------------------------------------------\n";
		User* current;
		char id[] = "u7";
		char* user = id;
		current = SearchUserByID(user);
		cout << current->getfname() << " " << current->getlname() << " successfully set as Current User.\n";

		cout << "------------------------------------------------------------\n";
		cout << "Command:\t View Friend List\n";
		cout << "------------------------------------------------------------\n";
		cout << current->getfname() << " " << current->getlname() << "-Friend List\n";
		current->ViewFriendList();

		cout << "------------------------------------------------------------\n";
		cout << "Command: \t View Liked Pages\n";
		cout << "------------------------------------------------------------\n";
		cout << current->getfname() << " " << current->getlname() << "-Liked Pages\n";
		current->ViewLikedPages();

		cout << "------------------------------------------------------------\n";
		cout << "Command: \t View TimeLine\n";
		cout << "------------------------------------------------------------\n";
		cout << current->getfname() << " " << current->getlname() << "-Timeline\n";
		current->viewtimeline();

		cout << "------------------------------------------------------------\n";
		cout << "Command: \t View LikedList(post5)\n";
		cout << "------------------------------------------------------------\n";
		Post* currentpost;
		char postid[] = "post5";
		char* poid = postid;
		currentpost = SearchPostByID(poid);
		currentpost->postlikedby();

		cout << "------------------------------------------------------------\n";
		cout << "Command:\t LikePost(post5)\n";
		cout << "------------------------------------------------------------\n";
		currentpost->addlike(current);

		cout << "------------------------------------------------------------\n";
		cout << "Command:\t ViewLikedList(post5)\n";
		cout << "------------------------------------------------------------\n";
		currentpost->postlikedby();

		cout << "------------------------------------------------------------\n";
		cout << "Command:\t ViewPage(p1)\n";
		cout << "------------------------------------------------------------\n";
		//This part runs all the commands for page with id p1
		char pageid[] = "p1";
		char* paid = pageid;
		Page* page;
		page = SearchPageByID(paid);
		cout << page->getname() << "-Timeline\n";
		page->viewtimeline();

		cout << "----------------------------Latest-------------------------\n";
		current->PrintLatestPost();

		cout << "\n-------------------------ViewHome-------------------------\n";
		current->ViewHome();
		cout << "------------------------------------------------------------\n";
		cout << "Command: SeeYourMemories()\n";
		cout << "------------------------------------------------------------\n";
		current->SeeYourMemories();

		cout << "------------------------------------------------------------\n";
		cout << "Command: ShareMemory(post10,Never thought I will be specialist in this field)\n";
		char text[] = "Never thought I will be specialist in this field";
		char oldpost[] = "post10";
		Post* oldpostptr = SearchPostByID(oldpost);
		Memory* memptr = new Memory(text, current, oldpostptr);
		current->AddPostToTimeline(memptr);

		cout << "------------------------------------------------------------\n";
		cout << "Command : View TimeLine\n";
		cout << "------------------------------------------------------------\n";
		current->viewtimeline();

		cout << "------------------------------------------------------------\n";
		cout << "Command: PostComment(post4, Good Luck for your Result)\n";
		char Pid[] = "post4";
		Post* Postptr = SearchPostByID(Pid);
		char Text[] = "Good Luck for you Result";
		Comment* Newcomment = new Comment();
		char Cid[] = "c14";
		Newcomment->SetValues(Cid, current, Text);
		Postptr->AddComment(Newcomment);

		cout << "------------------------------------------------------------\n";
		cout << " Command : ViewPost(post4)\n";
		cout << "------------------------------------------------------------\n";
		Postptr->printpost(); cout << endl;

		cout << "------------------------------------------------------------\n";
		cout << "Command: PostComment(post8, Thanks for the wishes)\n";
		char pid[] = "post8";
		Post* postptr = SearchPostByID(pid);
		//current is the object*
		char tex[] = "Thanks for the wishes";
		Comment* newcomment = new Comment();
		char cid[] = "c15";//just a use of random comment id
		newcomment->SetValues(cid, current, tex);
		postptr->AddComment(newcomment);

		cout << "------------------------------------------------------------\n";
		cout << "Command : ViewPost(post8)\n";
		cout << "------------------------------------------------------------\n";
		postptr->printpost(); cout << endl;

		cout << "-------------------------THE END----------------------------\n";
	}
	//Below are some functions written just for the sake of testing the code
	void printusers() {
		for (int i = 0; i < totalusers; i++)
			AllUsers[i]->print();
	}
	void printpages() {
		for (int i = 0; i < totalpages; i++)
			AllPages[i]->print();
	}
	void printposts() {
		for (int i = 0; i < 12; i++)
			AllPosts[i]->printpost();
	}
	void printfriendlist() {
		for (int i = 0; i < totalusers; i++) {
			cout << "\n\nUser: " << i << endl << endl;
			AllUsers[i]->ViewFriendList();
		}
	}
	void printlikedpages() {
		for (int i = 0; i < totalusers; i++) {
			cout << "\n\nUser: " << i << endl << endl;
			AllUsers[i]->ViewLikedPages();
		}
	}
};
Page** Controller::AllPages = nullptr;
User** Controller::AllUsers = nullptr;
Post** Controller::AllPosts = nullptr;
int main() {
	Controller mainApp;
	mainApp.LoadData();
	mainApp.currentuser();
	return 0;
}

