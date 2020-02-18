/*
This program takes 2 dates from the user and finds the days between them

1. Take the dates from the user in form mm/dd/yyyy
2. Find total days for each year
3. Return difference in days

*/
#include <iostream>
#include <string>

using namespace std;

int main() {

    int month, day, year, second_month, second_day, second_year, years, date_1_days, date_2_days;
    char slash;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    cout << "*** Welcome to the day finder program ***\n\n";

    cout << "Enter date #1 [mm/dd/yyyy]: ";
    cin >> month >> slash >> day >> slash >> year;
 
    cout << "Enter date #2 [mm/dd/yyyy]: ";
    cin >> second_month >> slash >> second_day >> slash >> second_year;

    date_1_days = year * 365 + month * 30 + day;
    date_2_days = second_year * 365 + second_month * 30 + second_day; 
   
    cout << "These days are " << date_2_days - date_1_days << " days between the 2 dates";

    return 0;

} //main 