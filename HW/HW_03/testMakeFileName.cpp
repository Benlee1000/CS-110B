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
            cout << "Enter the year: ";
            getline(cin,response);
            try { yy = stoi(response); }
            catch (exception &e) {
                cout << "\"" << response << "\" is non-numric" << endl;
                continue;
            }
            if (yy < 1 || yy > 9999){
                cout << "the year \"" << response << "\" is out of range" << endl;
                continue;
            }
            break;
        } // yy

        while (true) {
            cout << "Enter the month: ";
            getline(cin,response);
            try { mm = stoi(response); }
            catch (exception &e) {
                cout << "\"" << response << "\" is non-numric" << endl;
                continue;
            }
            if (mm < 1 || mm > 12){
                cout << "\"" << response << "\" is not a valid month" << endl;
                continue;
            }
            break;
        //if we have not validated the mm is a legal value --
        //we don't want except valus < 1 or > 12
        } // mm

        while (true) {
            bool valid_day = false;

            cout << "Enter the day: ";
            getline(cin,response);
            try { dd = stoi(response); }
            catch (exception &e) {
                cout << "\"" << response << "\" is non-numric" << endl;
                continue;
            } // catch

            switch(mm) {
                //30 day months are April, June, September, November
            case 4: case 6: case 9: case 11:
                if ( dd < 31 && dd > 0) { valid_day = true; }
                break;
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                //31 days months Jan, Mar, May, Jul, Aug, Oct, Dec
                if ( dd < 32 && dd > 0) { valid_day = true; }
                break;
            case 2:
                // 28 day is valid
                if (dd < 29 && dd > 0 ) { valid_day = true; }
                // 29 day is valid on leap year
                else if (dd == 29 && (yy % 4 ==0 && (yy % 100 != 0 || yy % 400 == 0 ) )) { valid_day = true; }
            } //switch

            if (not valid_day){ 
                cout << "\"" << response << "\" is not a valid day for the month" << endl;
                continue; }
            break;
        } // dd

        while (true) {
            cout << "Enter the number of days: ";
            getline(cin,response);
            try { numDays = stoi(response); }
            catch (exception &e) {
                cout << "\"" << response << "\" is non-numric" << endl;
                continue;
            }
            break;
        } // mm

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
