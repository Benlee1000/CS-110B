/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  If first call of makeNextFileName start while loop, prompt user for starting date
** 2.  Make copy of the user input to slice into substring for month, day, and year
** 3.  If delimiter not found, display format error and restart loop
** 4.  Try to stoi the three substrings, display error if caught and restart loop
** 5.  Check for valid year and month with if statements, restart loop if invalid
** 6.  Check for valid day depending on month and leap year, restart loop if invalid
** 7.  Break out of loop if entry pass all validation
** 8.  Within while loop, prompt user for number of days to make
** 9.  Try stoi the user input, restart loop if invalid
** 10. Check for positive number, restart loop if not
** 11. Set curDay to 0 and return NULL_String for initial run

** 12. Else subsequent run, compare curDay to numDays, return NULL_STRING if equal
** 13. use sprintf to store formated string with month, day, year into cStrBuffer
** 14. store cStrBuffer as csvFileName to convert to string
** 15. Increment curDay and call nextDay with mm, dd, yy to change to next day values
** 16. Return the csvFileName
**************************************************************************/  

#include "pandemicTracker.hpp"

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

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:

Enter the starting date (MM/DD/YYYY): 
" " is in an invalid format

Enter the starting date (MM/DD/YYYY): 1-2-3
"1-2-3" is in an invalid format       

Enter the starting date (MM/DD/YYYY): 2/30/2020
"30" is not a valid day for the month 
Enter the starting date (MM/DD/YYYY): 13/1/3
"13" is not a valid month

Enter the starting date (MM/DD/YYYY): 2/29/2019
2019 is not a leap year. "29" is not a valid day for the month
Enter the starting date (MM/DD/YYYY): 2/29/2020
Enter the number of days: a
"a" is non-numric
Enter the number of days: -1
"-1" is not a positive number
Enter the number of days: 5
02-29-2020.csv
03-01-2020.csv
03-02-2020.csv
03-03-2020.csv
03-04-2020.csv
End of test suite

**************************************************************************/ 