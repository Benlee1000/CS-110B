#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <ctype.h>
#include <iomanip>

using namespace std;

//useful constants
const long BILLION = 1000000000;
const long TEN_MILLION = 10000000;
const long MILLION = 1000000;
const long HUNDRED_THOUSAND = 100000;
const long TEN_THOUSAND = 10000;

//Useful for naming delimiters when you break strings into fields
const string BLANK = " ";
const string COLON = ":";
const string COMMA = ",";
const string DASH = "-";
const string SLASH = "/";
const string DOT = ".";
const string NULL_STRING = "";
const string NOT_APPLICABLE = "N/A";
const string EST_POPULATION = " ";//NULL_STRING;//"≈Pop.: ";



//#define DBG
//#define VERBOSE
#define TRACE

//trace("abc");
void trace (string s,bool b = false) {
#ifdef TRACE
  if (b) {
    cout << s << endl;
  }
#endif
}

void trace (string s,long l, bool b = false) {
#ifdef TRACE
  if (b) {
    cout << s << l << endl;
  }
#endif
}

void trace (string s,int j1, int j2, int j3, bool b = false) {
#ifdef TRACE
  if (b) {
    cout << s << j1 << "/" << j2 << "/" << j3 << endl;
  }
#endif
}




typedef vector<string> TextList;
typedef vector<TextList> TextLists;

// remember that an unordered_map class template specified
//   key/value pairs
//  TextTable pairs strings with vectors TextList objects
//  Suppose you were keep track of miles traveled on day of the week
/*
TextList week1 = { "123","921", "513"}
TextList week2 = { "183","891", "552"}
TextLists weeks = {week1, week2};
TextTable Mileage;
Mileage["Me"]= weeks;
Mileage["Me"].at(1).at(0).
TextTable 
*/

//Very useful in displaying the summary output
// the string keys are the entities of interest, e.g.,
// "Marin", or "US".  The values are a vector of stats
// for intervevals, and each interval is a vector of
// specific things people want to track in a pandemic.

typedef  unordered_map<string,TextLists > TextTable;
class Grp_spec; //think of it as an object representing an entity, like "California"

typedef unordered_map<string,Grp_spec *> Directory; 
//ca = filter["California"]

TextList BA_Counties,Aggregates;

/*
   pseudo-code
   TextList countries = {"Canada", "Italy", "US" };
   TextList counties = {"Alameda", "Napa", "Marin"};
   TextLists geoEntities = {countries, counties}

    CONST Int COUNTY_IDX = 1;
    geoEntities.at(COUNTY_IDX).at(2) == "Marin"

*/

//Values to return when the program exits unexpectedly
const int IO_FAILURE = 8;
const int CSV_FILE_ISSUE =  5000;
const int PROGRAM_FAILURE = 6000;
const int DB_ERROR = 0;

//Chooses which flavor of collection to use
const int BA_IDX = 0;
const int OTH_IDX = 1;
const int AGG_IDX = 2;


//***   config definitions
const string BA_COUNTY_CFG_FILE = "cfgBA.txt";
const string OTHER_COUNTIES_CFG_FILE = "cfgOther.txt";
const string AGGREGATES_CFG_FILE = "aggregatesCfg.txt";
const string INTERVALS_CFG_FILE = "intervalsCfg.txt";

//CSV field indices
const int FIPS = 0;  //provived by JHU, for what?  
const int COUNTY = 1;
const int PROVINCE = 2;
const int COUNTRY = 3;
const int LAST_UPDATE = 4;
const int LATITUDE = 5;
const int LONGTITUDE = 6;
const int CONFIRMED = 7;
const int DECEASED = 8;
const int RECOVERED = 9;
const int ACTIVE = 10;
const int FULL_NAME = 11;
const int LAST_FIELD = FULL_NAME;


const string Terra = "Terra";
const string US = "US";
const string CA = "California";
const string BA = "Bay Area";
const string CAN = "Canada";

//output summary field indices
const int OUT_NAME_OR_POP = 0;
const int OUT_DATE_RANGE = 1;
const int OUT_CCOUNT = 2;
const int OUT_IRATE = 3;
const int OUT_CINCR  = 4;
const int OUT_CDBL   = 5;
const int OUT_CFR    = 6;
const int OUT_DCOUNT = 7;
const int OUT_DINCR  = 8;
const int OUT_DDBL   = 9;

//to come
const string UpArrow = "";//"⇧";
const string DnArrow = "";//"⇩";

class Grouping; 

class Sample {
  friend class Grouping;
  //e.g., data collected for Missouri on 3/22/20 11:59 pm
  //time info posted in milliseconds since millenium
  // string humanReadableTime = asctime(localtime(&this->timeStamp));
  time_t timeStamp;
  string dateStr; //YYYY-MM-DD, the Johns Hopkins format
  int cases;    //confirmed cases
  int casesD;   //deceased
  int casesR;   //recovered
  int casesA;   //active cases
  
  static int numSamples; //track number of objects created
  
 public:
  static int getNumSamples() { return numSamples; }
  int getC() { return this->cases;}
  int getD() { return this->casesD;}
  int getR() { return this->casesR;}
  int getA() { return this->casesA;}
  time_t getTimeStamp() { return this->timeStamp; }
  string getDateStr() { return this->dateStr; }
  void updC(int c) { this->cases += c; }
  void updD(int d) { this->casesD += d; }
  void updR(int r) { this->casesR += r; }
  void updA(int a) { this->casesA += a; }
  void update(int c, int d, int r, int a) {
    updC(c); updD(d); updR(r); updA(a); 
  }

  //Consructor defined in .cpp file  
  Sample(int c, int d, int r, int a, time_t ts,string ds);
  string showDateTime();
};//class Sample

//Initalize class variable
int Sample::numSamples = 0;  


//A grouping is a collective entity in the JHU DB that has no sub-entities
// There is only one entry for a grouping in each .csv file
class Grouping {
protected:
  string county;
  string province;
  string country;
  float longtitude;
  float latitude;
  long population;

  //Keep one sample for every day in the analysis interval.
  vector<Sample> samples; 

  //Tracks the number of Grouping objects created
  static int numGroupings;  
 public:
  
  static int getNumGroupings () { return numGroupings; }
  Grouping () {};
  Grouping (string county, string province, string country,
	    float longtitude, float latitude, int population);
  //2Dstring showDateTime() { return summary->showDateTime(); }
  void add(Sample sample) {this->samples.push_back(sample);}
  string toString();
  int getSampleSize() { return this->samples.size();}
  long getPopulation() { return this->population; }
  void setPopulation(long p) {this->population = p; return;}
  Sample getSample(int idx) { return this->samples[idx]; };          
  float CompoundDailyGrowthRate(int first,int last, char category = 'C');
  void  clear() { this->samples.clear(); }
};//class Grouping

int Grouping::numGroupings = 0;  //initialize class variable

//An aggregator combines the totals of many samples 
class Aggregator: public Grouping {
protected:
  string planet;
  string region;
  vector<Aggregator *> peers;
  vector<Aggregator *> children;
  Aggregator *parent;

public:
     
  Aggregator(Aggregator *parent,
	     string planet = "", string country = "",
	     string province = "",string region = "");

  //Create a new sample if the date has changed, or just
  // upate the latest on if it hasn't.
  void add(vector<string> f);
  

};//class Aggregator


class CSV {
  ifstream csv_file;
  string curLine;
  vector<string> fields;
  
public:
  CSV (string fn) {
    this->csv_file.open(fn);
  };//Constructor

  bool file_exists() { return !csv_file.fail(); }
  
  static time_t parseDateTime(string dateTime);

  //carve a string up into fields
  static void makeFields(string text, string fieldDelim,
			     vector<string> *fields);

  bool get(string *str = NULL); //read next line from .csv file 

  //load this->curFields from this->curLine, using comma as the field
  // delimiter
  bool getFields(vector<string> *fields_= NULL);
  
  void showFields(vector<string> *fields_= NULL);
  
  void repair();

  //void showDates(vector<time_t> *dates_= NULL);

  //Use fields from line in .csv file to decide which group or
  // aggregate to update, if any.  Createes Grouping or
  // Aggregate objects as needed.
  bool update(vector<Directory> filters_, TextList aNames_);

  //Useful static methods
  
  //Grab the date from a DB timestam
  static string makeDateStr(vector<string> f) {
    int blankPos = f[LAST_UPDATE].find(BLANK,0);
    return(f[LAST_UPDATE].substr(0,blankPos));
  }//makeDateStr()

  static string intToStr(int j) {
    char buf[20];
    sprintf(buf,"%d",j);
    string s = buf;
    return s;
  }

  static string floatToStr(float f) {
    char buf[20];
    sprintf(buf,"%.3f",f);
    string s = buf;
    return s;
  }

  //validate that a DB field is all numeric.
  static bool isNumeric(string s) {
    if (s.length() == 0) { return false; }
    int idx = 0;
    if (s[0] == '-' && s.length() == 1) {return false;}
    else  {++idx; }
    for(; idx< s.length(); ++ idx)
      if (!isdigit(s[idx])) {return false;}
    return true;
  } //isNumeric()
  
  //return a string representation of an int with commas every
  // three places  
  static string cfy (long n);  //display numbers with commas
}; //class CSV



struct Grp_spec{
  long population;
  Grouping *grp;
  Aggregator *agg;
  long getPopulation() { return this->population; }

  Aggregator *getAgg() { return this->agg;} 
  Grouping * asGrp () { Grouping *g = this-> agg != NULL ?
      (Grouping *) agg : this -> grp; return g;  }
  Grp_spec (long p, Aggregator *agg)
  { this->population = p; this->grp = NULL;this->agg = agg;}
  Grp_spec (long p)
  { this->population = p; this->grp = NULL;this->agg = NULL;}
  Grp_spec (const Grp_spec& old) {
    population = old.population;
    grp = old.grp;
    agg = old.agg;
  }
};//Grp_spec
