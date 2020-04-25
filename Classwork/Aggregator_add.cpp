//Create a new sample if the date has changed
// or just update latest sample if it hasn't.
void Aggregator::add(vector<string> f) {
  string newDateStr = CSV::makeDateStr(f);
  string curDateStr = NULL_STRING;
  Sample *curSample;

  if (this->getSampleSize() > 0) {
    curSample = &this->samples[this->samples.size() -1];
    curDateStr = this->samples[this->samples.size() -1].getDateStr();
  } //if aggregator has at least one sample  

  Sample *sample;
  if (   (curDateStr.compare(NULL_STRING) == 0)
	 || (newDateStr.compare(curDateStr) > 0)) {

    time_t timeStamp = CSV::parseDateTime(f[LAST_UPDATE]);
    if (timeStamp == DB_ERROR) {
      cout << "Aggregator::add()/new sample: invalid timestamp" << endl;
      profile(f);
    }

    try {
      sample = new Sample(stoi(f[CONFIRMED]),stoi(f[DECEASED]),
  			      stoi(f[RECOVERED]), stoi(f[ACTIVE]),
			      timeStamp,newDateStr);
    } catch(exception &e) {
      cout << "Aggregator::add()/new sample:" << e.what() << endl;
      profile(f);
    }
				       
  //This is the definition of Grouping::add()
  //void add(Sample sample) {this->samples.push_back(sample);}
  this->Grouping::add(*sample);
    
  } //if this is the first sample, or the date has changd
  else if (newDateStr.compare(curDateStr) == 0) {

    try {
      curSample->update(stoi(f[CONFIRMED]),stoi(f[DECEASED]),
		      stoi(f[RECOVERED]), stoi(f[ACTIVE]));
    } catch(exception &e) {
      cout << "Aggregator::add()/update sample:" << e.what() << endl;
      profile(f);
    }
      
  } //the date hasn't changed, just update totals
  else {
    cout << "DB record has decreasing date\n"
	 << "Latest date: " << curDateStr << "\n";
    profile(f);  //display the database reocrd
  } //else contrary to expectation, a previous DB record has a
  // a more recent date than the current one.
} //Aggregator::add()
