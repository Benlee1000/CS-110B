#include "pandemicTracker.hpp"

void nextDay(int &m, int &d, int &y) {
  switch(m) {
    //30 day months are April, June, September, November
  case 4:
  case 6:
  case 9:
  case 11:
    if ( d < 30) { d++; return; }
    else { d = 1; m++; return; }
    break;
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
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
   
} //nextDay

string makeNextFileName() {
  static int mm = -1;
  static int dd;
  static int yy;
  static int numDays;
  static int curDay;

  
  if (mm == -1) {
    //in your program you will prompt the user for values
    //  but for now we will set test values
    string response;
    while (true) {
       cout << "Enter month: ";
       getline(cin,response);
       try { mm = stoi(response); }
       catch (exception &e) {
	 cout << "\"" << response << "\" is non-numric" << endl;
         continue;
       }
       break;
       //if we have not validated the mm is a legal value --
       //we don't want except valus < 1 or > 12
    } 
    dd = 26;
    yy = 2020;
    numDays = 8;
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
    sprintf(cStrBuffer,"%02d-%02d-%04d.csv",
	              mm,  dd,  yy);
    
    csvFileName = cStrBuffer;
    ++curDay;
    nextDay(mm,dd,yy);
    
    return csvFileName;
  } 
  
} //makeNextFileName;

int main () {
  //prompted for start date and length of analysis interval
  makeNextFileName();

  while (true) {
    string csvFn = makeNextFileName();
    if (csvFn == NULL_STRING) {
      //analysis interval over
      break;
    }
    cout << csvFn << endl;
  }

  cout << "End of test suite" << endl;

}
