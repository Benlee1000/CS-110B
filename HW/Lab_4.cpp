/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  Define 2D array
** 2.  Prompt user for bigrams that start with c and put into array
** 3.  Call top_bigram and report results. They're could be a tie.
** 4.  Call top_count and report results. They're could be a tie.
**************************************************************************/  

#include <iostream>

using namespace std;

int main() {
    char letters[3] = {'a', 'b', 'c'};
    int bigrams[4][4] = {{2, 4, 8, 1}, {0, 10, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int user_value;
    
    for (int idx = 0; idx < 3; idx++) {
        cout << "Enter the value for bigram c" << letters[idx] <<":";
        cin >> user_value;
        bigrams[2][idx] =  user_value;
    } //for
  
  return 0;
} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:


**************************************************************************/ 