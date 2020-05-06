#include "pandemicTracker.hpp"

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
Aggregagtor::toString() {

  //mp How would we get the Aggregator name?
  
    _______________________;
    …;
} //Aggregator::toString() 


//mp HW 3: part 3: supply a body for toString that returns the specified
// information in a string 
Grouping::toString() {
    char text[4000];  //create C-string buffer for sprintf()
    char text2[4000];  //Create another C-string buffer

    sprintf(text," … ", …, …);
    strcpy(text2,text);

    sprintf(text,"%s  …",text2, …, …);
    strcpy(text2,text);

    sprintf(text,"%s  …",text2, …, …);

    string description = text; //Convert C to C++style string
    return description;
} //toString() ?? not sure what this is

  
  

  

  _______________________;
  …;
} //Grouping::toString() 


//Create a new sample if the date has changed
// or just update latest sample if it hasn't.
void Aggregator::add(vector<string> f) {
    string newDateStr = CSV::makeDateStr(f);
    string curDateStr = NULL_STRING;
    Sample *curSample;

    if (this->getSampleSize() > 0) {
        //mp HW #3: set curSample to a pointer to the last (most recent) Sample
        // object in this->samples
        curSample = ___________________________________________________;

        //mp HW #3: get the date string from curSample
        curDateStr = __________________________________________________________
    } //if aggregator has at least one sample  

    Sample *sample;
    // mp HW #3: Construct a boolean that is true if the Aggregator object
    // doesn't have any samples yet, OR the date in the DB rec is more recent 
    // than the date of the last (and therefore most recent sample.
  if (   (____________________________________) || (__________________________________)) {
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
        //  the same name as a derived method?
        this->____________________________________ ;
    
    } //if this is the first sample, or the date has changd
    else if (newDateStr.compare(curDateStr) == 0) {

        try {
            //mp HW 3: Increase the last (most recent) Aggregator object 
            // sample with by the amounts in the DB rec.
            ____________->__________(stoi(f[CONFIRMED]),stoi(f[DECEASED]), stoi(f[RECOVERED]), stoi(f[ACTIVE]));
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
        //Get aggregate name from aName_
        string name = aNames[idx];


        /*
            *                                  something is off in this part
            *  if (country.compare(name) == 0) { (aFilter_[country]->agg->add(name) }
            */
        if (country.compare(name) == 0 || province.compare(name) == 0) {
            //mp Add to totals for countries and states configured as
            //   Aggregator objects.
            //                               key     value
            //                               name   Grp_spec*  calls Aggregator.add(f)
            //use for inspiration: aFilter_[Terra]->agg->add(f);
            ______________________________________________;
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
        // Use this for inspiration: aFilter_[Terra]->agg->add(f);
        _________________________________________________________;

        //mp  HW 3: Set the Grp_spec pointer for the county
        // It's a Bay Area county, so we meed a pointer to the Grouping
        //  object that represents that county.
        //  It's the value in bFilter_ associated with the key county
        //
        gs = bFilter_[county] ;
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
    // The next two lines set dateStr to the YYYY-MM-DD portion 
    //
    int blankPos = f[LAST_UPDATE].________________________________;
    string dateStr = f[LAST_UPDATE].______________________________;
  
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

    //mp HW 3: add DB rec totals to Grouping
    gs->grp->_____________________________________;
    return true;
} //update()


//mp HW3 part 1 is to complete the definition of makeNextFileName  
string makeNextFileName() {
    static string csvFileName = NULL_STRING;    
    //if not initialized, set up the analysis interval and return NULL_STRING
    //if called after being initialized, return the next CSV file in the analysis
    // interval if there is one, or NULL_STRING if there is not.
    
    if (csvFileName == NULL_STRING) {
        csvFileName = "04-30-2020.csv";
        return NULL_STRING;
    } else if (csvFileName == "04-30-2020.csv") {
        csvFileName = "05-01-2020.csv";
        return "04-30-2020.csv";
    } else if (csvFileName == "05-01-2020.csv") {
        csvFileName = "Done";
        return "05-01-2020.csv";
    } else {return NULL_STRING;}

}//makeNextFileName()


//called from cfg to make sure cf file is ok
void testFileOpen(ifstream &f, const string name) {
    if (f.fail()) {
        cout << "Config file \"" << name << "\" could not be opened." << endl;
        exit(IO_FAILURE);
    } //if

} //testFileOpen()


void cfg(Directory &bFilter_,  Directory &aFilter_, TextList &bNames_, TextList &aNames_) {
    long baPopulation = 0;
    //v1.0 selects Bay Area counties, broadly construed.
    ifstream baCfgFile; baCfgFile.open(BA_COUNTY_CFG_FILE);
    testFileOpen(baCfgFile,BA_COUNTY_CFG_FILE);

    string county;
    long countyPopulation;
    while (true) {
        getline(baCfgFile, county);
        if (baCfgFile.eof()) { break; }
        bNames_.push_back(county);

        string popStr;
        getline(baCfgFile,popStr);
        countyPopulation = stol(popStr);
        baPopulation += countyPopulation;

        bFilter_[county] = new Grp_spec(countyPopulation);
    }  //while reading in BA counties
    baCfgFile.close();
  
    long aggregatePopulation;
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
        aggregatePopulation = stol(popStr);
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

    cout << "Groupings: " << Grouping::getNumGroupings() << endl;
    cout << "Samples: "   << Sample::getNumSamples() << endl;  
    sampleCount += Sample::getNumSamples();
    if (startSampleCount == sampleCount) {
        cout << "No DB records found in interval " << endl;
    } //if no Samples taken

    //mp HW 3 part3: display the accumulated stats using the Aggregator and Grouping
    //toString methods.
    ___________________________________;
    …;
  
} //main

