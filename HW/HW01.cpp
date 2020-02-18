/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Ben and Leighton, have not given or received inappropriate help
**   with this assignment. 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  Have the user enter speed and kilometers
** 2.  Convert the data into standard values
** 3.  Display the time per kilometer and number of kilometers
** 4.  Display the time per mile and number of miles
**************************************************************************/  

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    int hours, minutes, seconds, total_seconds, total_seconds_per_mile, hours_per_mile, minutes_per_mile, seconds_per_mile;
    double kilometers, miles;
    char c;
    
    cout << "*** Welcome to the Metric speed/distance conversion program ***\n\n";

    //aks the user for speed and distance in kilometers
    //aks for multiple varibles in cin to easier process the input data
    cout << "Enter speed in format hh:mm:ss ";
    cin >> hours >> c >> minutes >> c >> seconds;
    cout << "Enter distance in kilometers: ";
    cin >> kilometers;

    //gets the distance in miles 
    miles = kilometers * 0.6213719223;
    
    //gets the speed (hours/minutes/seconds per mile)
    total_seconds = hours * 3600 + minutes * 60 + seconds;
    total_seconds_per_mile = total_seconds * 1.61;
    hours_per_mile = total_seconds_per_mile / 3600;
    minutes_per_mile = total_seconds_per_mile % 3600 / 60;
    seconds_per_mile = total_seconds_per_mile % 60;


    //prints out speed for kilometers in hh:mm:ss format, distance in kilometers,
    //speed for miles in hh:mm:ss format, and distance in miles
    printf("%02d:%02d:%02d", hours, minutes, seconds);
    cout << " per kilometer over ";
    printf("%.2f", kilometers);
    cout << " kilometers = "; 
    printf("%02d:%02d:%02d", hours_per_mile, minutes_per_mile, seconds_per_mile); 
    cout << " per mile over ";
    printf("%.2f", miles);
    cout << " miles\n";
    cout << "\nBye for now.";

}

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution,
** taken from the eclipse console window:

*** Welcome to the Metric speed/distance conversion program ***

Enter speed in format hh:mm:ss 0:6:0
Enter distance in kilometers: 1
00:06:00 per kilometer over 1.00 kilometers = 00:09:39 per mile over 0.62 miles

Bye for now.
**************************************************************************/ 