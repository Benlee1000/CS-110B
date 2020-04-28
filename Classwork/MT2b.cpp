#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include  <time.h>

using namespace std;

/*
 *
 * The Memories class maps millisecond time stamps
 * to  descriptions of events.  The load() instance method
 * initializes the mapping with data from a file, and the
 * changeTime() method can change the date and time 
 * associated with any memory.  See the block comment
 * at the bottom with a transcript of the output from
 * main() when the memory mappings are loaded from 
 * Moments.dat
 *
 * ******* INSTRUCTIONS ****
 * (95 points) Make the modifications required so that main() could generate 
 * the output show in the closing block comment. This entails change 3 methods:
 *
 * changeTime() (70 points). Most of this is using field parsing skills you
 * honed on CSV files in order to extract date/time fields from a string
 * formatted as  MM/DD/YYYY hh:mm:ss.  You will also need to complete the 
 * specification of the fields for a tm structure, and add new elemetns to a 
 * vector and an unordered map.
 *  
 * showMemories() (10 points) Write the cout statement needed to generate
 * output that looks like this:
 *   Date/Time: Fri Dec 21 11:00:00 2012
 *   Milliseconds from millenium: 1356116400
 *   Description: Solstice was special that year
 *
 * load() (15 points) Complete the data read loop.
 */


//Return values for change time
static const int OK = 0;  
static const int KEY_NOT_FOUND = 1;
static const int INVALID_DATE_TIME = 2;
static const int DATA_STRUCTURE_CORRUPT = 10000;

static const string SPACE = " ";
static const string COLON = ":";
static const string SLASH = "/";

typedef vector<time_t> Times;
typedef Times::const_iterator Times_it;
typedef unordered_map<time_t,string> Memory;
typedef Memory::const_iterator Memory_it;

class Memories {
  Times timeStamps;
  Memory events;
  
public:
  //Convert a millisecond timestamp into a human-readable string.
  static string showTime(time_t t) { return asctime(localtime(&t)); }

  //Return an etnry from a timestamp vector.
  time_t getTimeStamp(int idx) { return this->timeStamps[idx]; }

  //Retur the number of memories.
  int getNumMemories() { return timeStamps.size(); }

  //Bare-bones constructor, most of the action happens in load()
  Memories() { timeStamps.clear(); events.clear(); }
  
  //change the date/time of an event
  //Expects t to be a key in events, and that dts will have the format
  //  MM/DD/YYYY hh:mm:ss (for example, "04/28/2020 14:10:00")
  int changeTime(time_t t, string dts) {
    int MM,DD,YYYY,hh,mm,ss;
    Memory_it  findIt = this->events.find(t);
                                    // t is not a key in this->events
    if (findIt == this->events.end()) { return KEY_NOT_FOUND; }
    int delimPos = dts.find(SPACE);
    if (delimPos == string::npos) { return INVALID_DATE_TIME; }
    string dateStr = dts.substr(0,delimPos);
    string timeStr = dts.substr(delimPos+1,dts.length() - delimPos);

    delimPos = dateStr.find(SLASH);
    if (delimPos == string::npos) { return INVALID_DATE_TIME; }
    try {MM = stoi(dateStr.substr(0,delimPos)); }
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; }

    //3.a (10 points) Write code to set DD
    try {DD = stoi(dateStr.substr(delimPos + 1, 2)); } 
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; };

    //3.b (10 points) Write code to set YYYY
    try {YYYY = stoi(dateStr.substr(delimPos + 4, 4)); }
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; };

    delimPos = timeStr.find(COLON);
    if (delimPos == string::npos) { return INVALID_DATE_TIME; }
    try {hh = stoi(timeStr.substr(0,delimPos)); }
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; }
    
    //3.c (10 points) Write code to set mm
    try {mm = stoi(timeStr.substr(delimPos + 1, 2)); }
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; }
    
    //3.d (10 points) Write code to set ss
    try {ss = stoi(timeStr.substr(delimPos + 4, 2)); }
    catch (exception &e) { cout << e.what(); return INVALID_DATE_TIME; }

    //3.e (10 points) complete setting the fields in the ts structure
    tm ts;
    ts.tm_mon = MM -1;
    ts.tm_mday = DD;
    ts.tm_year = YYYY - 1900;
    ts.tm_hour = hh - 1;
    ts.tm_min = mm;
    ts.tm_sec = ss;

    string description = findIt->second;
    this->events.erase(findIt);  //delete the old mapping

    //Create a new time stamp from the tm structure set per
    // the user's instructions
    time_t  new_t = mktime(&ts);  

    //3.f (10 points Insert the new_t/description key/value pair in
    // this->events 
    this->events[new_t] = description; 

    Times_it it;
    for (it = this->timeStamps.begin(); it != this->timeStamps.end(); ++it){
      if (*it == t) { break; }
    } //for

    if (it != this->timeStamps.end()) { this->timeStamps.erase(it); }
    else {
      cout << " Fatal program error in Memories/changeTime()" << endl;
      cout << "timeStamps corrupt, " << t << " not found." << endl;
      exit(DATA_STRUCTURE_CORRUPT);
    }

    //3.g (10 points) Add new_t to timeStamps.
    this->timeStamps.push_back(new_t);
    return OK;
  } //changeTime() 
    

  //show the millisecond time stamps of all memories
  void showTimeStamps() {
    for (int idx=0; idx < this->timeStamps.size(); ++ idx) {
      cout << idx + 1 << ". " << this->timeStamps[idx] << endl;

    } //for all timeStamps()
  } //showTimeStamps()

  //Show all memories
  void showMemories() {
    Memory_it it = this->events.begin();
    for (; it != this->events.end(); ++it) {
      time_t t = it->first;
      string description = it->second;
      // 4. (10 points).  Write a cout statement, using the showTime()
      //  static method, that would produce an entry that looks like this:
      // Date/Time: Fri Dec 21 11:00:00 2012
      // Milliseconds from millenium: 1356116400
      // Description: Solstice was special that year

      //I'm confused here, my program runs well without this line, but
      //when I pass time_t t to showtime() the program shows a logic error
      cout << "Date/Time: " << showTime(t) << endl; 
      
      cout << "Milliseconds from millenium: " << t <<endl;
      cout << "Description: " << description << endl;
    } //for

  } //showMemories()

  // load memories from data file
  void load (string fn) {
    ifstream reader;
    reader.open(fn);    
    time_t t;
    string timeStr;
    string description;
    
    //5. (15 points). Complete the while loop below to
    //   initialize the timStamps and events instance data fields

    while(!reader.fail() ) {
      getline(reader, timeStr);
      if (reader.eof()) { break; } 
      t = stol(timeStr);
      this->timeStamps.push_back(t);
      getline(reader, description);

      //Add the approprite key/value pair to events
      events[t] = description;
    } //while

    reader.close();
    return;
  } //load()
};//class Memories

int main( ) {
  Memories *m  = new Memories();
  m->load("Moments.dat");
  cout << "*** *** *** Memories *** *** *** " << endl;
  m->showMemories();
  string answer;          //User response
  int tsIdx;              //time stamp index
  time_t t;               // milliseconds from millenium
  int changeTimeResult;   //return code from changeTime()
      while (true) {
	cout << "*** *** *** Timestamp listing *** *** *** " << endl;
	m->showTimeStamps();
	cout << "Enter # of timestamp to change, or Q to quit: ";
	getline(cin,answer);
	if (answer == "Q" or answer == "q") { break; }
	try { tsIdx = stoi(answer); }
	catch (exception &e) {
	  //answer was non-numeric and could not be convert to an int
	  cout << e.what() << "Invalid selection" << endl; 
	  continue; 
	}
	
	if (tsIdx < 1 || tsIdx > m->getNumMemories() ) {
	  cout << tsIdx << " is not a valid timeStamp number." << endl;
	  continue;
	} //if out of range

	//Get the time stamp corresponding to the user selection.
	// The parameter passes is the index in the timeStamps vector,
	// one less than the value entered by the user.
	//
        t = m->getTimeStamp(tsIdx-1);
        cout << "Enter new date/time in format MM/DD/YYYY hh:mm:ss: ";
        getline(cin,answer);

	//change the date and/or time for a memory
        changeTimeResult = m->changeTime(t,answer);
        if (changeTimeResult != OK) {
	  cout << "could not change time " << changeTimeResult << endl;
	}
        else {
          cout << "*** *** *** Memories *** *** *** " << endl;
          m->showMemories();
        } //else
      } //while the user wants to make changes
    cout << "Thanks for the memories" << endl;
  } //main()
  
/* Transcript of program run using Moments.dat
*** *** *** Memories *** *** *** 
Date/Time: Tue Nov 11 12:00:00 1997
Milliseconds from millenium: 879278400
Description: Forget it not

Date/Time: Fri Dec 21 17:00:00 2012
Milliseconds from millenium: 1356138000
Description: Solstice was special that year

Date/Time: Sat Feb  2 05:06:07 1952
Milliseconds from millenium: -565268033
Description: Was it Groundhog Day again?

*** *** *** Timestamp listing *** *** *** 
1. -565268033
2. 1356138000
3. 879278400
Enter # of timestamp to change, or Q to quit: 1
Enter new date/time in format MM/DD/YYYY hh:mm:ss: 02/02/1952 8:0:0
*** *** *** Memories *** *** *** 
Date/Time: Sat Feb  2 08:00:00 1952
Milliseconds from millenium: -565257600
Description: Was it Groundhog Day again?

Date/Time: Tue Nov 11 12:00:00 1997
Milliseconds from millenium: 879278400
Description: Forget it not

Date/Time: Fri Dec 21 17:00:00 2012
Milliseconds from millenium: 1356138000
Description: Solstice was special that year

*** *** *** Timestamp listing *** *** *** 
1. 1356138000
2. 879278400
3. -565257600
Enter # of timestamp to change, or Q to quit: Q
Thanks for the memories
 */
