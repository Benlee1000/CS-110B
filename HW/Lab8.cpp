/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  Fill out commented sections 
** 2.  So that the program prints out the values from the cfgBA.txt file
** 3. 
**************************************************************************/

#include "pandemicTracker.hpp"

//#define DBG

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


void cfg(Directory &bFilter_,  Directory &aFilter_, TextList &bNames_, TextList &aNames_) {
  long baPopulation = 0;
  //v1.0 selects Bay Area counties, broadly construed.
  ifstream baCfgFile;
  //Lab 8: open baCfgFile using the name BA_COUNTY_CFG_FILE -done-
  baCfgFile.open(BA_COUNTY_CFG_FILE);
  testFileOpen(baCfgFile,BA_COUNTY_CFG_FILE);
  
  string county;
  long countyPopulation;
  while (true) {
    //Lab8: Try to read a from baCfgFile into county -done- L
    getline(baCfgFile, county);
    if (baCfgFile.eof()) { break; }
#ifdef DBG
    cout << county << endl;
#endif
    //Lab 8: supply line for adding to bNames_ -done- L
    bNames_.push_back(county);

    string popStr;
    //Lab 8: read a line from baCfgFile into popStr -done-
    getline(baCfgFile, popStr);
#ifdef DBG
    cout << popStr << endl;
#endif
    countyPopulation = stol(popStr);
    baPopulation += countyPopulation;

    //Lab 8: complete line for adding county to directory ?? -done- L
    //bFilter_[ ?? ] = ??
    bFilter_[county] = new Grp_spec(countyPopulation);
  }  //while reading in BA counties

  //Lab8: close baCfgFile -done-
  baCfgFile.close();

  long long aggregatePopulation;
  string aggName;
  Aggregator *terra, *us, *ca, *agg;

  ifstream aggCfgFile;
  //Lab 8: open for aggCfgFile for reading using name AGGREGATES_CFG_FILE -done-
  aggCfgFile.open(AGGREGATES_CFG_FILE);  
  testFileOpen(aggCfgFile,AGGREGATES_CFG_FILE);

  while (true) {
    //Lab 8: Try to read a line from aggCfgFile into aggName -done-
    getline(aggCfgFile, aggName);
    if (aggCfgFile.eof()) { break; }
#ifdef DBG
    cout << aggName << endl;
#endif
    //Lab 8: supply line for adding to aNames_ -done-
    aNames_.push_back(aggName);
	
    string popStr;
    //Lab 8: Try to read a line from aggCfgFile into popStr -done-
    getline(aggCfgFile, popStr);
#ifdef DBG
    cout << popStr << endl;
#endif
    aggregatePopulation = stoll(popStr);    //convert string to long, changed to stoll
#ifdef DBG
    cout << "After Stoll, agg "<< aggregatePopulation << endl;
#endif
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

    //Lab 8: add two lines needed to set agg population and add ?? -done-? L
    //the aggregate to the aFilter_ directory ??
    
    //agg->??
    agg->setPopulation(aggregatePopulation);
    //aFilter_[ ?? ] = ??
    aFilter_[aggName] = new Grp_spec(agg->getPopulation(), agg);

  }  //while reading in aggregates
    aggCfgFile.close();  
}//cfg()

int main( ) {
  Directory bFilter, aFilter;
  TextList bNames, aNames;
  //Lab 8: restore the call to cfg to set up the directory and name lists. -done-
  cfg(bFilter, aFilter, bNames, aNames);

  //Lab 8:comment out the 4 lines below -done-
  //bNames.push_back("Generic B");    
  //bFilter[bNames.at(0)] = new Grp_spec(123);
  //aNames.push_back("Generic A");
  //aFilter[aNames.at(0)] = new Grp_spec(456);
  
  string name = bNames.at(0);
  long long population = bFilter[name]->getPopulation();
  //"The estimated population of Alameda County is 1663000."
  cout << "The estimated population of " << name
       << " County is " << population << "." << endl;


  name = aNames.at(0);
  population = aFilter[name]->getPopulation();
  //The estimated population of Terra is 7530000000.
  cout << "The estimated population of " << name
       << " is " << population << "." << endl;

} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:


**************************************************************************/ 

