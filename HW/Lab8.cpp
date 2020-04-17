#include "pandemicTracker.hpp"

Aggregator::Aggregator(Aggregator *parent, string planet, string country,
	   string province,string region) {
    this->parent = parent;
    this->planet = planet;
    this->country = country;
    this->province = province;
    this->region = region;
} //Constructor


//called from cfg to make sure cf file is ok
void testFileOpen(ifstream &f, const string name) {
  if (f.bad()) {
    cout << "Config file \"" << name
	 << "\" could not be opened." << endl;
    exit(IO_FAILURE);
  } //if

} //testFileOpen()


void cfg(Directory &bFilter_,  Directory &aFilter_,
	 TextList &bNames_, TextList &aNames_) {
  long baPopulation = 0;
  //v1.0 selects Bay Area counties, broadly construed.
  ifstream baCfgFile;
  //Lab 8: open baCfgFile using the name BA_COUNTY_CFG_FILE
  testFileOpen(baCfgFile,BA_COUNTY_CFG_FILE);


  string county;
  long countyPopulation;
  while (true) {
    //Lab8: Try to read a from baCfgFile into county
    if (baCfgFile.eof()) { break; }
    //Lab 8: supply line for adding to bNames_
	
    string popStr;
    //Lab 8: read a line from baCfgFile into popStr
    countyPopulation = stol(popStr);
    baPopulation += countyPopulation;

    //Lab 8: complete line for adding county to directory
    //bFilter_[ ?? ] = ?? 
  }  //while reading in BA counties
  //Lab8: close baCfgFile

  long aggregatePopulation;
  string aggName;
  Aggregator *terra, *us, *ca, *agg;

  ifstream aggCfgFile;
  //Lab 8: open for aggCfgFile for reading using name AGGREGATES_CFG_FILE
  testFileOpen(aggCfgFile,AGGREGATES_CFG_FILE);

  while (true) {
    //Lab 8: Try to read a line from aggCfgFile into aggName
    if (aggCfgFile.eof()) { break; }
    //Lab 8: supply line for adding to aNames_
	
    string popStr;
    //Lab 8: Try to read a line from aggCfgFile into popStr
    aggregatePopulation = stol(popStr);    //convert string to long
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
    } else {                    //by default it's a country
      agg = new Aggregator(terra, "", aggName);
    }

    //Lab 8: add two lines needed to set agg population and add
    // the aggregate to the aFilter_ directory 
    //agg->??
    //aFilter_[ ?? ] = ??
  }  //while reading in aggregates
    aggCfgFile.close();  
}//cfg()

int main( ) {
  Directory bFilter, aFilter;
  TextList bNames, aNames;
  //Lab 8: restore the call to cfg to set up the directory and name lists.
  //cfg(bFilter, aFilter,bNames, aNames);

  //Lab 8:comment out the 4 lines below
  bNames.push_back("Generic B");    
  bFilter[bNames.at(0)] = new Grp_spec(123);
  aNames.push_back("Generic A");
  aFilter[aNames.at(0)] = new Grp_spec(456);
  
  string name = bNames.at(0);
  long population = bFilter[name]->getPopulation();
  //"The estimated population of Alameda County is 1663000."
  cout << "The estimated population of " << name
       << " County is " << population << "." << endl;


  name = aNames.at(0);
  population = aFilter[name]->getPopulation();
  //The estimated population of Terra is 7530000000.
  cout << "The estimated population of " << name
       << " is " << population << "." << endl;

} //main

