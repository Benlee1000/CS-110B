/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  
** 2.
** 3. 
**************************************************************************/  

#include "pandemicTracker.hpp"

// #define DBG

time_t CSV::parseDateTime(string dateTime) {
    //DB timestamp look like thisP: 3/22/20 23:45
    int blankPos = dateTime.find(BLANK);
    string dateText = dateTime.substr(0,blankPos);
    ++blankPos;
    string timeText = dateTime.substr(blankPos,dateTime.length() - blankPos);
    vector<string> dateFields, timeFields;
    CSV::makeFields(dateText,DASH,&dateFields);

    if (dateFields.size() != 3) {
        dateFields.clear();
        CSV::makeFields(dateText,SLASH,&dateFields);
        if (dateFields.size() != 3) { return DB_ERROR; }
    } //if need to try another format

    CSV::makeFields(timeText,COLON,&timeFields);
    if (timeFields.size() == 2) {timeFields.push_back("0");}
    if (timeFields.size() != 3) { return DB_ERROR; }  
    tm timeStamp;

    try {    
        timeStamp.tm_mon  = stoi(dateFields[1]) -1;
        timeStamp.tm_mday = stoi(dateFields[2]);
        timeStamp.tm_year = stoi(dateFields[0]) -1900;
        timeStamp.tm_hour = stoi(timeFields[0]);
        timeStamp.tm_min = stoi(timeFields[1]);
        timeStamp.tm_sec = stoi(timeFields[2]);
    } catch(exception &e) {
        cout << "CSV::parseDateTime()/" << e.what() << endl;
        cout << "Date fields: (" << dateFields.size() << " fields)"; 
        for (int idx = 0; idx < dateFields.size(); ++ idx) {
            cout << dateFields.at(idx);
            if (idx < dateFields.size()-1) { cout << "/"; }		       
    } //for
    cout << endl;
    cout << "Time fields: ";
    for (int idx = 0; idx < timeFields.size(); ++ idx) {
        cout << timeFields.at(idx);
        if (idx < timeFields.size()-1) { cout << ":"; }		       
    } //for;
    cout << endl;
    return DB_ERROR;
    //cout << "timeFields[2]: \"" << timeFields[2] << "\"" << endl;

    } //catch

    time_t t = mktime(&timeStamp);
    return t;
} //CSV::parseDateTime()

void audit(vector<string> f) {
    if (!CSV::isNumeric(f[CONFIRMED]) || !CSV::isNumeric(f[DECEASED]) || !CSV::isNumeric(f[RECOVERED])|| !CSV::isNumeric(f[ACTIVE]) ) {
        cout << "*** PROGRAM ERROR ***\n" << "  Non-numeric char find in number field\n" << f[COUNTRY] << ", " << f[PROVINCE] << f[COUNTY] << "\n" << "    C: " << f[CONFIRMED] << "; D: " << f[DECEASED] << "; R: " << f[RECOVERED] << "; A: " << f[ACTIVE] << endl;
        exit(PROGRAM_FAILURE);
    } //if error
    
} //audit()




void profile(vector<string> f) {
    cout << "CTRY: " << f[COUNTRY] << ", PROV: " << f[PROVINCE] << ", CTY: " << f[COUNTY] << "\n" << f[LAST_UPDATE] << ", " << f[LATITUDE] << ", " << f[LONGTITUDE] << "\n" << "    C: " << f[CONFIRMED] << "; D: " << f[DECEASED] << "; R: " << f[RECOVERED] << "; A: " << f[ACTIVE]  << "; FULL NAME: " << f[FULL_NAME] << endl;                                      
} //profile


//Handle situations where the country name is in quotes with an
// embedded comma, such as "Korea, South"
void CSV::repair() {
    if (!CSV::isNumeric(this->fields[CONFIRMED])) {

        // Assume there was an embeddedc comma in the country field
        // and move everything left
        this->fields[COUNTRY] += ", " + this->fields[LAST_UPDATE];
        for (int idx = LAST_UPDATE; idx <= LAST_FIELD; ++ idx) {
            this->fields[idx] = this->fields[idx+1];
        } //for all remaining defined fields
        for (int idx = LAST_FIELD + 1; idx < this->fields.size(); ++idx) {
            this->fields[LAST_FIELD] += " " + this->fields[idx];
        }

    } //If confirmed does not have numeric data
} //CSV::repair()


void CSV::showFields(vector<string> *fields_) {
    if (fields_ == NULL) {
        fields_ = &this->fields;
    }
    int idx = 1;
    for (vector<string>::iterator iter = fields_->begin(); iter != fields_->end(); ++iter, ++idx) {
        cout << "Field " << idx << ": \"" << *iter << "\"" << endl;
    } //for
  
} //CSV::showFields()

///  ************** Complex Constructors ******************   

Sample::Sample(int c, int d, int r, int a, time_t ts,string ds) {
    this->cases = c;
    this->casesD = d;
    this->casesR = r;
    this->casesA = a;
    this->timeStamp = ts;
    this->dateStr = ds;
    Sample::numSamples++; //update the satic/class variable within the object constructor
};//constructor to set data points


Aggregator::Aggregator(Aggregator *parent, string planet, string country, string province,string region) {
    this->parent = parent;
    this->planet = planet;
    this->country = country;
    this->province = province;
    this->region = region;
} //Constructor

Grouping::Grouping (string county, string province, string country,float longtitude, float latitude, int population){
    this->county = county; this->province=province; this->country = country;
    this->longtitude = longtitude; this->latitude = latitude;
    this->population = population;
    ++Grouping::numGroupings;
} //Grouping::Grouping()


float Grouping::CompoundDailyGrowthRate(int first,int last, char category) {
    int len = last + 1 - first;
    int initial, final;
  
    switch (category) {
    case 'C':
        initial = getSample(first).getC();
        final   = getSample(last).getC();
        break;
    case 'D':
        initial = getSample(first).getD();
        final   = getSample(last).getD();
        break;
    default:
        cout << "'" << category << "'" << " is unsupported category for Grouping::growthPerecent()" << endl;
        exit(PROGRAM_FAILURE);
  } //swtich

    float rate = pow( ( (float)final/initial),((float)1/(len-1)));
    float percent = (rate-1) *100;
    return percent;
} //CompoundDailyGrowthRate()

string Sample::showDateTime() {
    char * cstr =  asctime(localtime(&this->timeStamp));
    cstr[strlen(cstr)-1] = '\0';
    string str = cstr;
    return str;
};//getDateTime()

//NULL is default arg
bool CSV::get(string *str) {
    if (this->csv_file.eof() ) { return false; }

    getline(this->csv_file,this->curLine);
    if (this->csv_file.eof()) { return false; }
    if (str != NULL) {
        *str = this->curLine;
    } //if
  
    return true;
} //CSV::get()

//Divide line from CSV file into fields, using the comma as the delimiter
bool CSV::getFields(vector<string> *fields_) {
    if (!this->get() ) { //try to read new line
        return false;
    }
    int commaPos;
    string text = this->curLine;
    string field;

    this->fields.clear();

    TextList quoteFields; quoteFields.clear();
    TextList commaFields; quoteFields.clear();
    CSV::makeFields(text,QUOTE,&quoteFields);
    for (int idx = 0; idx < quoteFields.size(); ++idx) {
        if (idx%2 == 0) {
            CSV::makeFields(quoteFields.at(idx),COMMA,&commaFields);
            for (int cIdx = 0; cIdx < commaFields.size(); ++cIdx) {
                this->fields.push_back(commaFields.at(cIdx));
            } //inner for
            commaFields.clear();
        } //if
        else {
            this->fields.push_back(QUOTE+quoteFields.at(idx) + QUOTE);
        }
    } //outer for loop
    this->repair(); //touch-up if needed
    if (fields_ != NULL) {
        *fields_ = this->fields;
    }
    return true;
} //CSV::getFields()

//Divide text into fields using delimiter
void CSV::makeFields(string text, string fieldDelim, vector<string> *fields) {
    int delimPos;
    string field;
    while (true) {
        delimPos = text.find(fieldDelim,0);
        if (delimPos == string::npos) {
            field = text.substr(0,text.length());
            fields->push_back(field);
            break;
        } //if no more fields found found
        else {
            field = text.substr(0,delimPos);
            fields->push_back(field);
            
            if (delimPos == text.length() -1) {
                //fields->push_back(NULL_STRING);
                break;
            }
            delimPos++;
            text = text.substr(delimPos, text.length() - delimPos);
        }//else 
    }//while there's another field to parse
} //CSV:makeFields()



//mp HW 3: part 3: supply a body for toString that returns the specified
// information in a string

// The only that Aggregator::toString() needs to do on top what gets back 
// from Grouping::toString() is possibly to change or supply a name. 

string Aggregator::toString() {
    int delimPos1, delimPos2;
    char text[4000];
    //mp How would we get the Aggregator name?

    //Aggregator::toString() will need to call Grouping::toString()
    //And possibly make some adjustments to the name
    //I'll send out email tonight explaining how to call a base class
    //method with the same name as a method in the derived class.

    //if (this->region != NULL_STRING) {change description to use this->region as the name}
    //if (description is nameless) {use this->planet as the name}

    string name = NULL_STRING; // Default, all country and province aggs
    if (this->region != NULL_STRING) {name = this->region;} // region agg, bay area
    else if (this->province != NULL_STRING) {name = this->province;} // province
    else if (this->country != NULL_STRING) {name = this->country;} // contry
    else if (this->planet != NULL_STRING) {name = this->planet;} // planet agg, Terra

    //Name: text;  
    //Get everything about the counts and the dates
    // a cast is when you say I'm going to cast a variable in another role
    //  than how it's defined. Casting a float from an int: int score = (int) 77.3;
    // We're casting a Aggregator pointer to a Grouping pointer
    // ((Grouping *)this)->toString();
    string description = this->Grouping::toString(); // Get string from Grouping

#ifdef DBG
cout << "Agg to string was called" << endl;
#endif
    
    delimPos1 = description.find(COLON); // find space
    if (delimPos1==string::npos){
        cout << "Couldn't find the delim" << endl; 
    } // if
    delimPos2 = description.find("|"); // find pipe
    if (delimPos2==string::npos){
        cout << "Couldn't find the delim" << endl; 
    } // if
    sprintf(text, "%s %- 14s %s", description.substr(0,delimPos1 + 1).c_str(), name.c_str(), description.substr(delimPos2, description.length() - delimPos2).c_str()); 
    // insert name into string, did sprintf instead of string cat for better formatting

    description = text; // store c_string into string

    //This is the point where we supply the Name if needed.  That is, if this is either of
    // our two special Aggregator objets, the one that represents Terra, and the one
    // that represents the Bay Area.
    
    //Possibly the start of the string the Grouping toString() method returns could look
    // like what is shown below, where "text" could be NULL_STRING.  In that call, we
    // could pull out the name in the same we pull out the MM DD YYYY parts of a
    // date string: with the .find and .substr string methods.

    return description; 
    
} //Aggregator::toString() 


//mp HW 3: part 3: supply a body for toString that returns the specified
// information in a string 
string Grouping::toString() {
    string description;
    char text[4000];  //create C-string buffer for sprintf()
    char text2[4000];  //Create another C-string buffer

#ifdef DBG
cout << "Grp to string was called" << endl;
#endif

    string name = NULL_STRING, secondLineStart = NULL_STRING;
    if (this->county != NULL_STRING) {name = this->county;}
    // else if (this->province != NULL_STRING) {name = this->province;}
    // else if (this->country != NULL_STRING) {name = this->country;}
    // Moved to Aggregator for formatting reasons

    if (this->getSampleSize() == 0) {
        return "Name: " + name + " No data collected.";
    }
    else  {
        //create a description of the first sample
        Sample firstSample = this->samples[0];
        float firstInfectionRate = ((float)firstSample.getC()/this->population) * 100; // cast as float to do float div, multiple 100 for percent value

#ifdef DBG
    cout << "Infected: "<< firstSample.getC() << "Population" << this->population << endl;
#endif

        string firstDateStr = firstSample.getDateStr();

        sprintf(text,"Name: %- 14s | Start Date: %s | Infection Rate: % 2.3f%% | Cases: % 9d | Deceased: % 9d\n", name.c_str(), firstDateStr.c_str(), firstInfectionRate, firstSample.getC(), firstSample.getD());
        // %- 14s the - is to left justify, the space is the filler character, 14 is the number of reserved spaces, s for string
        // % 2.3f the space after % is setting the filler character, 2 is the space reserved before decimal, .3 is the number of decimal places, f for float
        // %% is to display % character       

        description = text;

    }
    if (this->samples.size() == 1) {return description;}

    else {
        //create a description of the last sample and append it.
        strcpy(text2,text); //strcpy works right-to-left

        Sample lastSample = this->samples[this->samples.size()-1];
        float lastInfectionRate = ((float)lastSample.getC()/this->population) * 100; // same as firstInfectionRate 
        string lastDateStr = lastSample.getDateStr();
    
        for (int idx = 0; idx < 20; ++idx){
            secondLineStart = secondLineStart + BLANK;
        }

        sprintf(text,"%s\n%s | End Date:   %s | Infection rate: % 2.3f%% | Cases: % 9d | Deceased: % 9d\n", text2,secondLineStart.c_str(),lastDateStr.c_str(), lastInfectionRate, lastSample.getC(),lastSample.getD());


        float caseGrowthRate = this->CompoundDailyGrowthRate(0,this->samples.size()-1,'C'); // replaced this. with this->
        float decGrowthRate = this->CompoundDailyGrowthRate(0,this->samples.size()-1,'D'); // same as above
        float cDbLtime = log10(2)/(log10(1 + (caseGrowthRate/100)) );
        float dDbLtime = log10(2)/(log10(1 + (decGrowthRate/100)) );
        //format these four floats as the possible 3rd line returned
        //from Grouping::toString()
        strcpy(text2,text);
        sprintf(text, "%s\nCases Avg Increase: \t\t% 2.3f%% \nCases Days to Double: \t\t% 2.3f \nDeceased Avg Increase: \t\t% 2.3f%% \nDeceased Days to Double: \t% 2.3f\n", text2,caseGrowthRate,cDbLtime,decGrowthRate,dDbLtime);

        description = text;
    }
    return description;
} //Grouping::toString() 


//Create a new sample if the date has changed
// or just update latest sample if it hasn't.
void Aggregator::add(vector<string> f) {
    string newDateStr = CSV::makeDateStr(f);
    string curDateStr = NULL_STRING;
    Sample *curSample;

    if (this->getSampleSize() > 0) {
        //mp HW #3: set curSample to a pointer to the last (most recent) Sample
        // object in this->samples -done-
        curSample = &this->samples[samples.size() - 1]; //-done- -Needed to be address, added & L-

        //mp HW #3: get the date string from curSample -done-
        curDateStr = curSample->getDateStr(); //-done- -needed same to getDateStr, added curSample-> L-
    } //if aggregator has at least one sample  

    Sample *sample;
    // mp HW #3: Construct a boolean that is true if the Aggregator object
    // doesn't have any samples yet, OR the date in the DB rec is more recent 
    // than the date of the last (and therefore most recent) sample.  -done l-

    // How could we tell if the date in the DB rec is more recent?
    //   You could compare dates by comparing strings. That is, if
    //   date string 1 comes before date string 2 when you compare them using
    //   alphabetic (Unicode) order, then the date represented by date string 1 is
    //   less recent than the one represented by date string 2.
    //   The date strings we're comparing are  newDateStr, which we got from
    //   the DB rec, and  curDateStr, which we got from the most recent sample
    //   the Aggregator object has collected, assuming it's collected any.
    //   Finally, the C++ string method .compare() compares deciding in terms
    //   of alphabetic order.
    if ((samples.size() == 0) || (curDateStr < newDateStr)) { //-done L-
        time_t timeStamp = CSV::parseDateTime(f[LAST_UPDATE]);
        if (timeStamp == DB_ERROR) {
            cout << "Aggregator::add()/new sample: invalid timestamp" << endl;
            profile(f);
        }  //if the DB rec timeStamp could not be converted milliseconds

        try {
            sample = new Sample(stoi(f[CONFIRMED]),stoi(f[DECEASED]), stoi(f[RECOVERED]), stoi(f[ACTIVE]), timeStamp,newDateStr);
        } catch(exception &e) {
            //Ee
            cout << "Aggregator::add()/new sample:" << e.what() << endl;
            profile(f);
        }

        //mp HW #3: add a new sample to Aggregtor object, which is also
        //  a Grouping object.  How does one call a base class method with
        //  the same name as a derived method? -I'm pretty sure this is done-
        this->Grouping::add(*sample); //-I'm pretty sure this is done- -arguement needed to be sample, derefernced sample pointer L-

    }   //if this is the first sample, or the date has changed, then
        // you need to create a new Sample object and append to the
        // samples vector.

    else if (newDateStr.compare(curDateStr) == 0) {

        try {
            //mp HW 3: Increase the last (most recent) Aggregator object 
            // sample with by the amounts in the DB rec. -??-
            //obj. var.     method name.
            curSample->update(stoi(f[CONFIRMED]),stoi(f[DECEASED]), stoi(f[RECOVERED]), stoi(f[ACTIVE])); //-??- -curSample->update done L-
        } catch(exception &e) {
            //Exception most likely caused stoi() trying to convert a non-numeric
            //  string into an integer
            cout << "Aggregator::add()/update sample:" << e.what() << endl;
            profile(f);
        }
      
    } //else if the the date hasn't changed, and there is at least one sample,
    // just update the totals on the most recent (last) sample
    else {
    cout << "DB record has decreasing date\n" << "Latest date: " << curDateStr << "\n";
    profile(f);
    } //else COMPLETELY contrary to expectation, a previous DB record has a
  //   a more recent date than the current one -- just report the problem
} //Aggregator::add()


bool CSV::update(vector<Directory> filters_, TextList aNames_) {

    Directory bFilter_ = filters_.at(BA_IDX);  //get unordered map for Bay Area counties
    Directory aFilter_ = filters_.at(AGG_IDX); //get unordered map for Aggregators   
    //aFilter is an unordered_map == dictionary == associative array
    // it's a collection of key/values pairs.  In aFilter_, the keys are the namees
    // of aggregates, and the values are Grp_spec pointers


    vector<string> f = this->fields; //save some keystrokes

    //mp Add everything to planetary totals -- all DB records add to total for
    // the planet.  

    // Which class defines the add() method in the line below?
    // That is, add() is an instance method in which class?
    // Sometimes OO programming is conceptualized as sending messages to objects.
    // In those, terms the line send a message to an Aggregator telling to update
    // with whatever  is f, which represents a DB record
    // The value to fill is the string key that will get you to the Aggregate
    //   representing the whole planet.  So … what is that string key
    aFilter_[Terra]->agg->add(f);

    string country = f[COUNTRY];    //convenience variable
    string province = f[PROVINCE];

    // Traverse aNames_, the string vector of Aggregator names.
    // If an Aggregator name matches the country or province name in a DB
    // record, reprsented by the variable f, then tell that Aggregagor to
    // update itself using f.
    for (int idx = 0; idx < aNames_.size(); ++idx) {
        //Get aggregate name from aName_ -done-
        string name = aNames_[idx]; //-done- -was missing _ L-
        //This is how we might use a simple version of toString() in our development process

#ifdef DBG
        if (name == CAN) {

           cout << "Trace: " << aFilter_[name]->agg->toString() << endl;
        }
#endif

        /*
        *  something is off in this part:
        *  if (country.compare(name) == 0) { (aFilter_[country]->agg->add(name) }
        */
        if (country.compare(name) == 0 || province.compare(name) == 0) {
            //mp Add to totals for countries and states configured as
            //   Aggregator objects.
            //                               key     value
            //                               name   Grp_spec*  calls Aggregator.add(f)
            //use for inspiration: aFilter_[Terra]->agg->add(f); -not sure about this one-
            aFilter_[name]->agg->add(f); //-not sure about this one- -key is name, add(f) done L-
        } //if we are aggregating stats for that country or state
    } //for all Aggretator objects

    string county = f[COUNTY];
    Grp_spec *gs = NULL;

    //Bay Area matches are difficult!
    // The Bay Area is not something Johns Hopkins defines, it's an
    //  entity we creared to represent an aspect of the data that interests us.
    //  We create, in cfg, our bFilter key/value pairs representing
    //  name/Grouping for each object. e.g., "Marin/Grouping *"
    //  When we encounter a DB record for a Bay Area county, two things need
    //  to happen:
    //    1.  we need add the DB rec totals to the totals for that county
    //    2.  we need add the DB rec totals to the totals for the Bay Area
    //        Aggregator


    //The unordered_map method .find(key) returns an iterator.
    //if that iterator == .end(). then the key was not found
    //  bFilter_ is the key/values pairs for the Bay Area counties
    if (bFilter_.find(county) != bFilter_.end()){
        //.find did NOT return .end(), so the county field in the
        // DB record matched a Bay Area county name in bFilter_.
        //mp HW 3: Add totals to Bay Area region
        // We are adding totals -- for an Aggregator representing
        //  the Bay area
        // Use this for inspiration: aFilter_[Terra]->agg->add(f); -not too sure about this one either-
        aFilter_[BA]->agg->add(f); //-not too sure about this one either- -changed key to BA for bay area done L-

        //mp  HW 3: Set the Grp_spec pointer for the county
        // It's a Bay Area county, so we meed a pointer to the Grouping
        //  object that represents that county.
        //  It's the value in bFilter_ associated with the key county -done-
        //
        gs = bFilter_[county]; //-done-
    } //if it's a Bay Area county

    else { return false; } //else we have no more interest in DB record

    //At this point in CSV::update, we're done with the Aggregator object update,
    // and now need to update the Grouping object (a Bay Area county)
    // indicated by the DB rec

    if (gs->grp == NULL) {
        //Depending on the cfg logic, we may need to constuct the Grouping
        // object
        gs->grp = new Grouping(county,f[PROVINCE],f[COUNTRY],stof(f[LATITUDE]),stof(f[LONGTITUDE]),gs->population);
    } //if we need to create new grouping

    //Create new sample -- Grouping object like the Bay Area counties only
    // have one Sample per CSV File -- and each CSV file represents one date.
    // So to update a BA county, we create a new Sample, and append it to the
    // samples vector for that county.  And we also need to update the Bay
    // Bay Area Aggregator for each county


    //mp HW : the f[LAST_UPDATE] time stamp field looks like this;
    //  2020-04-25 06:30:53
    // The next two lines set dateStr to the YYYY-MM-DD portion -I think I got this-
    //
    int blankPos = f[LAST_UPDATE].find(BLANK); //-I think I got this- -yes you did, didn't need a 0 though done L-
    string dateStr = f[LAST_UPDATE].substr(0,blankPos); //-I think I got this- -yes you did done L-
  
    time_t timeStamp = CSV::parseDateTime(f[LAST_UPDATE]);
    if (timeStamp == DB_ERROR) {
        cout << "CSV::update(): invalid timestamp" << endl;
        profile(f);
    }

    Sample *sample;
    try {
        sample = new Sample(stoi(f[CONFIRMED]),stoi(f[DECEASED]), stoi(f[RECOVERED]), stoi(f[ACTIVE]), timeStamp,dateStr);
    } catch(exception &e) {
        //stoi will incur an exception on trying to covert a non-numeric string
        // to an integer
        cout << "CSV::update()/new sample:" << e.what() << endl;
        //show profile of DB rec
        profile(f);
    } //catch

    //mp HW 3: add DB rec totals to Grouping -I believe this is right-
    gs->grp->add(*sample); //-I believe this is right- -add sample, dereferenced the pointer done L-
    return true;
} //update()

void nextDay(int &m, int &d, int &y) {
    switch(m) {      
    case 4: case 6: case 9: case 11:
        //30 day months are April, June, September, November
        if ( d < 30) { d++; return; }
        else { d = 1; m++; return; }
        break;
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        //31 days months Jan, Mar, May, Jul, Aug, Oct, Dec
        if ( d < 31) { d++; return; }
        else if (m < 12)  { d = 1; m++; return; }
        else {
            d = 1;
            m = 1;
            y++;
            return;
        } //else it's New Years Day
        break;
    case 2:
        //February has 28 days, except if has 29 on leap years.
        //A leap year is year such that y % 4 = 0 and y %100 != 0
        // except if y % 400 = 0;
        if (d < 28) { d++; return;}
        else if (d == 29) {m++; d =1; return;  }
        else {
            if (y % 4 ==0 && (y % 100 != 0 || y % 400 == 0 ) ) { 
                d++;
                return;
            } //leap year
            else    { d = 1; m++; return; }  //not a leap year

        } //else
    } //switch
    
} //nextDay()

string makeNextFileName() {
    static int mm = -1;
    static int dd;
    static int yy;
    static int numDays;
    static int curDay;

    if (mm == -1) {
        //in your program you will prompt the user for values
        //  but for now we will set test values
        string response, dateStr, mmStr, ddStr, yyStr;
        int delimPos;

        while (true) {
            bool validationFail = false, valid_day = false;

            cout << "Enter the starting date (MM/DD/YYYY): ";
            getline(cin,response);
            dateStr = response;

            delimPos = dateStr.find(SLASH);
            if (delimPos == string::npos) {
                cout << "\"" << response << "\" is in an invalid format\n" << endl;
                continue;
            } // if
            mmStr = dateStr.substr(0,delimPos); // month string

            dateStr = dateStr.substr(delimPos+1,dateStr.length() - delimPos);
            delimPos = dateStr.find(SLASH);
            if (delimPos == string::npos) {
                cout << "\"" << response << "\" is in an invalid format\n" << endl;
                continue;
            } // if
            ddStr = dateStr.substr(0,delimPos); // day string
            yyStr = dateStr.substr(delimPos+1,dateStr.length() - delimPos); // year string

            try { mm = stoi(mmStr); }
            catch (exception &e) {
                cout << "\"" << mmStr << "\" is non-numric for month" << endl;
                validationFail = true;
            } // catch
            try { dd = stoi(ddStr); }
            catch (exception &e) {
                cout << "\"" << ddStr << "\" is non-numric for day" << endl;
                validationFail = true;
            } // catch
            try { yy = stoi(yyStr); }
            catch (exception &e) {
                cout << "\"" << yyStr << "\" is non- for year" << endl;
                validationFail = true;
            } // catch

            if (validationFail) { 
                cout << endl;
                continue; 
            } // if: any stoi fail, lets all error messages display before restarting loop

            if (yy < 1 || yy > 9999){
                cout << "the year \"" << yyStr << "\" is out of range" << endl;
                validationFail = true;                
            } // if: check for positive year that is 4 digits or less
            if (mm < 1 || mm > 12){
                cout << "\"" << mmStr << "\" is not a valid month" << endl;
                validationFail = true;
            } // if: check for valid month

            if (validationFail == true){
                cout << endl;
                continue;
            } // if: any value out of range, let all error message display before restarting loop

            switch(mm) {
                //30 day months are Apr, Jun, Sep, Nov
            case 4: case 6: case 9: case 11:
                if ( dd < 31 && dd > 0) { valid_day = true; }
                break;
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                //31 days months Jan, Mar, May, Jul, Aug, Oct, Dec
                if ( dd < 32 && dd > 0) { valid_day = true; }
                break;
            case 2:
                // 1-28 day is valid
                if (dd < 29 && dd > 0 ) { valid_day = true; }
                // 29th is valid on leap year
                else if (dd == 29 && (yy % 4 ==0 && (yy % 100 != 0 || yy % 400 == 0 ) )) { valid_day = true; }
                // non-leap year 29th entry
                else if (dd == 29){ cout << yyStr << " is not a leap year. ";}
            } //switch

            if (not valid_day){ 
                cout << "\"" << ddStr << "\" is not a valid day for the month" << endl;
                continue;
            } // if: display error message before restarting loop
            
            break;
        } // while: Date

        while (true) {
            cout << "Enter the number of days: ";
            getline(cin,response);
            try { numDays = stoi(response); }
            catch (exception &e) {
                cout << "\"" << response << "\" is non-numric" << endl;
                continue;
            } // catch
            if (numDays < 1){
                cout << "\"" << numDays <<"\" is not a positive number" << endl;
                continue;
            }
            break;
        } // while: number of days

        curDay = 0;
        return NULL_STRING;
    } //if we are not initialized

    else {
        if (curDay == numDays) {
        return NULL_STRING;
        } //if we're done with the analysis interval

        string csvFileName;
        char cStrBuffer[100];

        //Create a file with the format MM-DD-YYYYY.csv
        sprintf(cStrBuffer,"%02d-%02d-%04d.csv", mm,  dd,  yy);
        
        csvFileName = cStrBuffer;
        ++curDay;
        nextDay(mm,dd,yy);
        
        return csvFileName;
    } 
    
} //makeNextFileName()

//called from cfg to make sure cf file is ok
void testFileOpen(ifstream &f, const string name) {
    if (f.fail()) {
        cout << "Config file \"" << name << "\" could not be opened." << endl;
        exit(IO_FAILURE);
    } //if

} //testFileOpen()


void cfg(Directory &bFilter_,  Directory &aFilter_, TextList &bNames_, TextList &aNames_) {
    long long baPopulation = 0;
    //v1.0 selects Bay Area counties, broadly construed.
    ifstream baCfgFile; baCfgFile.open(BA_COUNTY_CFG_FILE);
    testFileOpen(baCfgFile,BA_COUNTY_CFG_FILE);

    string county;
    long long countyPopulation;
    while (true) {
        getline(baCfgFile, county);
        if (baCfgFile.eof()) { break; }
        bNames_.push_back(county);

        string popStr;
        getline(baCfgFile,popStr);
        countyPopulation = stoll(popStr);
        baPopulation += countyPopulation;

        bFilter_[county] = new Grp_spec(countyPopulation);
    }  //while reading in BA counties
    baCfgFile.close();
  
    long long aggregatePopulation;
    string aggName;
    Aggregator *terra, *us, *ca, *agg;

    ifstream aggCfgFile; aggCfgFile.open(AGGREGATES_CFG_FILE);
    testFileOpen(aggCfgFile,AGGREGATES_CFG_FILE);

    bool configuredState;
    while (true) {
        configuredState = false;
        getline(aggCfgFile, aggName);
        if (aggCfgFile.eof()) { break; }
        //check to see if the user specified a state
        //in the config file with the "STATE" prefix
        int blankPos = aggName.find(BLANK);
        if (blankPos != string::npos) {
            string pfx = aggName.substr(0,blankPos);
            if (pfx == STATE_PFX) {
                //state specified in config file
                configuredState = true;
                ++blankPos;
                aggName = aggName.substr(blankPos, aggName.length() - blankPos);
            } //if configured state specified
        } //if the aggregate name contained a ' '

        aNames_.push_back(aggName);

        string popStr;
        getline(aggCfgFile,popStr);
        aggregatePopulation = stoll(popStr);
        if (aggName == Terra) { //Planet-wide
            agg = new Aggregator(NULL,aggName);
            terra = agg;
        } else if (aggName == US) {  //United States
            agg = new Aggregator(terra, "", aggName);
            us = agg;
        } else if (aggName == CAN) {  //Canada
            agg = new Aggregator(terra, "", aggName);
        } else if (aggName == CA) {   // California
            agg = new Aggregator(us, "", "", aggName);
            ca = agg;
        } else if (aggName == BA) {   // Bay Area
            agg = new Aggregator(ca, "", "", "", aggName);
            aggregatePopulation = baPopulation;
        } else {
            //might be state or country
            Aggregator *parent = terra;
            string country = aggName;
            string province = NULL_STRING;
            if (configuredState) {
                parent = us;
                province = aggName;
                country = NULL_STRING;
            }
            agg = new Aggregator(parent, "", country, province);
        } //else it's another aggregate
        agg->setPopulation(aggregatePopulation);
        aFilter_[aggName] = new Grp_spec(aggregatePopulation,agg);
    }  //while reading aggregates
    aggCfgFile.close();  
}//cfg()

int main( ) {
    Directory bFilter,aFilter;
    TextList bNames,oNames,aNames;
    //configure the BA counties; any other counties;
    // and the aggrgates
    cfg(bFilter,aFilter,bNames,aNames);
    vector<TextList> names;
    names.push_back(bNames);
    names.push_back(aNames);
    vector<Directory> filters;
    filters.push_back(bFilter);
    filters.push_back(aFilter);
    int sampleCount = 0, startSampleCount;
    string fn;
    CSV *csv = NULL;
    int intervalCount = 0;

    makeNextFileName(); //prompt user initialize analysis interval
    while(true) {
        startSampleCount = sampleCount;
        if (csv != NULL) { delete csv; csv = NULL; }    
        fn = makeNextFileName(); //Get next CSV file
        if (fn == NULL_STRING)  {
            break;
        }//if no more files in interval of interest
        csv = new CSV(fn);
        if (!csv->file_exists() ) {
            cout << "File \"" << fn << "\" not yet available" << endl;
            break;
        } //if
        csv->get(); //skip past header line
        while(csv->getFields() ) {
            //Use DB rec to update Groupings and Aggregators
            csv->update(filters, aNames);  
        } //while processing CSV file
        csv->close();

    }//while processing CSV files

    cout << "\nGroupings: " << Grouping::getNumGroupings() << endl;
    cout << "Samples: "   << Sample::getNumSamples() << endl << endl;  
    sampleCount += Sample::getNumSamples();
    if (startSampleCount == sampleCount) {
        cout << "No DB records found in interval " << endl;
    } //if no Samples taken

    //mp HW 3 part3: display the accumulated stats using the Aggregator and Grouping
    //toString methods.
    // ___________________________________;
    // …;
    for (int idx = 0; idx < aNames.size() ; ++idx){
        cout << aFilter[aNames[idx]]->agg->toString() << endl;
    }

#ifdef DBG
    cout << "bNames size: " << bNames.size() << endl;
#endif
    for (int idx = 0; idx < bNames.size() ; ++idx){
        cout << bFilter[bNames[idx]]->grp->toString() << endl;
    }

    cout << "Goodbye for now.\n" << endl;  

} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:

Enter the starting date (MM/DD/YYYY): 05/01/2020
Enter the number of days: 2

Groupings: 12
Samples: 34

Name: Terra          | Start Date: 2020-05-02 | Infection Rate:  0.044% | Cases:   3343777 | Deceased:    238650

                     | End Date:   2020-05-03 | Infection rate:  0.046% | Cases:   3427343 | Deceased:    243808

Cases Avg Increase:              2.499% 
Cases Days to Double:            28.080 
Deceased Avg Increase:           2.161% 
Deceased Days to Double:         32.416

Name: Canada         | Start Date: 2020-05-02 | Infection Rate:  0.150% | Cases:     56343 | Deceased:      3537

                     | End Date:   2020-05-03 | Infection rate:  0.154% | Cases:     57926 | Deceased:      3684

Cases Avg Increase:              2.810% 
Cases Days to Double:            25.016 
Deceased Avg Increase:           4.156% 
Deceased Days to Double:         17.022

Name: US             | Start Date: 2020-05-02 | Infection Rate:  0.337% | Cases:   1103461 | Deceased:     64943

                     | End Date:   2020-05-03 | Infection rate:  0.346% | Cases:   1132539 | Deceased:     66369

Cases Avg Increase:              2.635% 
Cases Days to Double:            26.649 
Deceased Avg Increase:           2.196% 
Deceased Days to Double:         31.913

Name: California     | Start Date: 2020-05-02 | Infection Rate:  0.132% | Cases:     52026 | Deceased:      2126

                     | End Date:   2020-05-03 | Infection rate:  0.135% | Cases:     53347 | Deceased:      2180

Cases Avg Increase:              2.539% 
Cases Days to Double:            27.644 
Deceased Avg Increase:           2.540% 
Deceased Days to Double:         27.635

Name: Bay Area       | Start Date: 2020-05-02 | Infection Rate:  0.098% | Cases:     10284 | Deceased:       384

                     | End Date:   2020-05-03 | Infection rate:  0.100% | Cases:     10491 | Deceased:       387

Cases Avg Increase:              2.013% 
Cases Days to Double:            34.782 
Deceased Avg Increase:           0.781% 
Deceased Days to Double:         89.069

Name: Alameda        | Start Date: 2020-05-02 | Infection Rate:  0.098% | Cases:      1636 | Deceased:        62

                     | End Date:   2020-05-03 | Infection rate:  0.103% | Cases:      1706 | Deceased:        63

Cases Avg Increase:              4.279% 
Cases Days to Double:            16.544 
Deceased Avg Increase:           1.613% 
Deceased Days to Double:         43.321

Name: Contra Costa   | Start Date: 2020-05-02 | Infection Rate:  0.079% | Cases:       907 | Deceased:        28

                     | End Date:   2020-05-03 | Infection rate:  0.081% | Cases:       934 | Deceased:        28

Cases Avg Increase:              2.977% 
Cases Days to Double:            23.629 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Marin          | Start Date: 2020-05-02 | Infection Rate:  0.091% | Cases:       237 | Deceased:        13

                     | End Date:   2020-05-03 | Infection rate:  0.092% | Cases:       239 | Deceased:        13

Cases Avg Increase:              0.844% 
Cases Days to Double:            82.484 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Napa           | Start Date: 2020-05-02 | Infection Rate:  0.048% | Cases:        68 | Deceased:         2

                     | End Date:   2020-05-03 | Infection rate:  0.050% | Cases:        70 | Deceased:         2

Cases Avg Increase:              2.941% 
Cases Days to Double:            23.912 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Sacramento     | Start Date: 2020-05-02 | Infection Rate:  0.071% | Cases:      1090 | Deceased:        42

                     | End Date:   2020-05-03 | Infection rate:  0.072% | Cases:      1107 | Deceased:        42

Cases Avg Increase:              1.560% 
Cases Days to Double:            44.788 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: San Francisco  | Start Date: 2020-05-02 | Infection Rate:  0.172% | Cases:      1523 | Deceased:        28

                     | End Date:   2020-05-03 | Infection rate:  0.174% | Cases:      1543 | Deceased:        29

Cases Avg Increase:              1.313% 
Cases Days to Double:            53.129 
Deceased Avg Increase:           3.571% 
Deceased Days to Double:         19.753

Name: San Joaquin    | Start Date: 2020-05-02 | Infection Rate:  0.075% | Cases:       557 | Deceased:        25

                     | End Date:   2020-05-03 | Infection rate:  0.075% | Cases:       560 | Deceased:        25

Cases Avg Increase:              0.539% 
Cases Days to Double:            129.041 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: San Mateo      | Start Date: 2020-05-02 | Infection Rate:  0.164% | Cases:      1197 | Deceased:        51

                     | End Date:   2020-05-03 | Infection rate:  0.169% | Cases:      1233 | Deceased:        51

Cases Avg Increase:              3.008% 
Cases Days to Double:            23.392 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Santa Clara    | Start Date: 2020-05-02 | Infection Rate:  0.112% | Cases:      2179 | Deceased:       113

                     | End Date:   2020-05-03 | Infection rate:  0.114% | Cases:      2205 | Deceased:       114

Cases Avg Increase:              1.193% 
Cases Days to Double:            58.437 
Deceased Avg Increase:           0.885% 
Deceased Days to Double:         78.672

Name: Solano         | Start Date: 2020-05-02 | Infection Rate:  0.060% | Cases:       266 | Deceased:         5

                     | End Date:   2020-05-03 | Infection rate:  0.060% | Cases:       266 | Deceased:         5

Cases Avg Increase:              0.000% 
Cases Days to Double:            inf 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Sonoma         | Start Date: 2020-05-02 | Infection Rate:  0.048% | Cases:       244 | Deceased:         2

                     | End Date:   2020-05-03 | Infection rate:  0.049% | Cases:       248 | Deceased:         2

Cases Avg Increase:              1.639% 
Cases Days to Double:            42.628 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Name: Stanislaus     | Start Date: 2020-05-02 | Infection Rate:  0.069% | Cases:       380 | Deceased:        13

                     | End Date:   2020-05-03 | Infection rate:  0.069% | Cases:       380 | Deceased:        13

Cases Avg Increase:              0.000% 
Cases Days to Double:            inf 
Deceased Avg Increase:           0.000% 
Deceased Days to Double:         inf

Goodbye for now.        

**************************************************************************/ 