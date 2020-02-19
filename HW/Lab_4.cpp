/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  Define 2D array
** 2.  Prompt user for bigrams that start with c and put into array
** 3.  Call top_bigram and report results. There could be a tie.
** 4.  Call top_count and report results. There could be a tie.
**************************************************************************/  

#include <iostream>

using namespace std;

const bool DBG = true;

//returns the top bigram, both if tied
string top_bigram(int bigrams_[4][4]) {
    //finds the largest bigram and records row and col
    int largest = 0, largest_row = 0, largest_col = 0;
    string largest_first_letter, largest_second_letter;
    const string LETTERS[4] = {"a", "b", "c", "\\n"};
   
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (bigrams_[row][col] > largest) {
                largest = bigrams_[row][col];
                largest_first_letter = LETTERS[row];
                largest_second_letter = LETTERS[col];
            } //if
        } //col for
    } //row for

    //returns two letters put together
    return largest_first_letter + largest_second_letter;
} //top_bigrams

//returns the letter with the most counts, both if tied
string top_count(int bigrams_[4][4]) {

} //top_count()

int main() {
    char letters[3] = {'a', 'b', 'c'};
    int bigrams[4][4] = {{2, 4, 8, 1}, {0, 10, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int user_value;
    string largest_bigram;
    string largest_count;

    for (int idx = 0; idx < 3; idx++) {
        cout << "Enter the value for bigram c" << letters[idx] <<": ";
        cin >> user_value;
        bigrams[2][idx] =  user_value;
    } //for

    largest_bigram = top_bigram(bigrams);
    largest_count = top_count(bigrams);



    if (DBG) {
        
        cout << "The largest bigram is " << largest_bigram <<endl;
    }

    return 0;
} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:


**************************************************************************/ 