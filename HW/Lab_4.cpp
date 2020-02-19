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
const string LETTERS[] = {"a", "b", "c", "\\n"};

//returns the top bigram, both if tied
string top_bigram(int bigrams_[4][4]) {
    int largest_value = 0, largest_row = 0, largest_col = 0, num_bigrams = 0;
    string largest_bigram;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (bigrams_[row][col] > largest_value) {
                largest_value = bigrams_[row][col];
                largest_bigram = LETTERS[row];
                largest_bigram += LETTERS[col];
                num_bigrams = 0;
            } //if
            //if there are two largest, add on to largest bigram
            else if (bigrams_[row][col] == largest_value) {
                    largest_bigram += LETTERS[row];
                    largest_bigram += LETTERS[col];
                    num_bigrams++;
            } //else if
        } //col for
    } //row for

    return largest_bigram;
} //top_bigrams

//returns the letter with the most counts, both if tied
string top_count(int bigrams_[4][4]) {

} //top_count()

void display_largest_bigram(string largest_bigram_) {
    string bigram_1, bigram_2;
    if (largest_bigram_.length() == 2) {  //this works as long as /n is not single the largest bigram, which it never is
        cout << "The largest bigram is " << largest_bigram_ << endl;
    } //if

    //for two bigrams, splits them up and displays a different message
    else {
        bigram_1 = largest_bigram_.substr(0,2);
        bigram_2 = largest_bigram_.substr(2, largest_bigram_.length() - 2); //this allows the \n to be displayed
        cout << "The largest bigrams are " << bigram_1 << " and " << bigram_2 << endl;
    } //else
} //display_largest_bigram()

int main() {
    int bigrams[4][4] = {{2, 4, 8, 1}, {0, 10, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int user_value;
    string largest_bigram;
    string largest_count;

    for (int idx = 0; idx < 3; idx++) {
        cout << "Enter the value for bigram c" << LETTERS[idx] <<": ";
        cin >> user_value;
        bigrams[2][idx] =  user_value;
    } //for

    largest_bigram = top_bigram(bigrams);
    largest_count = top_count(bigrams);

    display_largest_bigram(largest_bigram);



    if (DBG) {
        
        
    }

    return 0;
} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:


**************************************************************************/ 