#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <ctype.h>
#include <iomanip>

using namespace std; 
const int SEVEN = 7;

class B {
  const int *iPtr;
  char c;

public:
     //Note the dereferencing *
  int getIpVal(){ return *this->iPtr; }
  
  char getC() { return this->c; }

  void setC(char c) { this-> c = c;}
  B(const int *ip) {
    this->iPtr = ip;
    this->c = 'w';
  } //B constructor
}; //class B

class D: public B {
  char c;
public:
  D(char c)  : B(&SEVEN)
               { this->c = c; }
  D()        : B(&SEVEN)
               { this->setC('q'); }
};

class D2 : public D {
  char c;
public:
  D2() { this->c = 'm'; }

};  

int main( )
{    
  string numStr = "42";
  int ans = stoi(numStr);
  B *bptr = new B(&ans);
  //cout << bptr->getIpVal() << endl;

  D *dptr = new D('Z');
  //cout << dptr->getC() << endl;

  D2 *d2ptr = new D2();
  cout << d2ptr->getC() << endl;  
    

  /*
  vector<string> names;

  //Put Alice at the end of the vector
  names.push_back("Alice");

  //Put Aaron at the head of the vector
  names.insert(names.begin(),"Aaron");

  //Put Alan ?? in 2nd pos. vector
  names.insert(names.begin()+1,"Alan");
  
  cout << "Name 1: " << names[0] << endl;
  cout << "Name 3: " << names[2] << endl;
  */
  
  typedef unordered_map<string,string> Dictionary;
  typedef unordered_map<string,Dictionary> Dictionaries;
  Dictionary plurals;
  Dictionary person;
  Dictionaries d;

  plurals["fish"] = "fish";
  plurals["datum"] = "data";
  plurals["program"] = "programs";
  
  person["me"] = "you";
  person["mine"] = "yours";
   
  string key1 =  "Pluralization";
  string key2 = "1pTo2p";
  d[key1] = plurals;
  d[key2] = person;

  //d[key1] ["datum"]  == d["Pluralization"] ["datum"]
  // == plurals["datum"] == "data"
  //cout << d[key1] ["datum"] << endl;

    
  typedef vector<Dictionary>  BookShelf;
  BookShelf b;
  b.push_back(person);
  b.push_back(plurals);
  //b[0]["me"] == person["me"] == "you"
  //cout << b[0]["me"] << endl;
  
  //time
  tm timeStamp;  
  timeStamp.tm_mon  = 3; //tm_mon = month -1
  timeStamp.tm_mday = 23;
  timeStamp.tm_year = 120; //tm_year = year - 1900
  timeStamp.tm_hour = 13;  //tm_hour = hour -1
  timeStamp.tm_min =  10;
  timeStamp.tm_sec = 28;

  //milliseconds since 1/1/1970 GMT 
  time_t t = mktime(&timeStamp);

  //localtime(&t) converts millis since the millenium into the
  // the equivalent time in the processor's local time zone.
  // asctime takes the values reprsentig a date/time and
  // output an expression represeting that date/time in
  // human friendly form.
  string dateTimeStr = asctime(localtime(&t));

  
  //cout << dateTimeStr << "millis since millenium = " << t << endl;
  

  //  Thu Apr 23 14:10:28 2020
  //               ^^
  int delimPos = dateTimeStr.find("/");
  if (delimPos == string::npos) {delimPos = dateTimeStr.find(":");}
  string subs =
    dateTimeStr.substr(delimPos+1,dateTimeStr.length() - delimPos);
  //Consider this.  The number of values between any two integers (inclusive)
  // is the the difference between those integers + 1.
  // For example, the number of values between 7 and 9  is 3: 7, 8, and 9.
  // In terms of strings, the number of characters between a given position
  // and the end of the string is str.length() - position.  For example, if
  // the string is "ab", and the position is 1, the number of characters
  // in "ab" from postion 1 to the of the string is 2-1 = 1.
  // delimPos gives us a certain position in the string, and we want to
  // extract everything  starting after the delimiter.  So...
  //cout << subs << endl;
  exit(0);

  
} //main()
