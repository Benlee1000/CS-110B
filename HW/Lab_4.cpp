/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  Define 2D array
** 2.  Prompt user for bigrams that start with c and put into array
** 3.  Display bigram table
** 4.  Call top_bigram and report results. There could be a tie.
** 5.  Call top_count and report results. There could be a tie.
**************************************************************************/  

#include <iostream>
#include <string>

using namespace std;

const bool DBG = true;
const string LETTERS[] = {"a", "b", "c", "\\n"};
const int NUM_OF_LETTERS = 4;

void show_bigrams_table(int bigrams_[4][4]) {
    //display header of table
    cout << "\n\t" << LETTERS[0] << "\t" << LETTERS[1] << "\t" << LETTERS[2] << "\t" << LETTERS[3] << endl;
    
    //display letter and values of bigrams in table
    for (int idx = 0; idx < NUM_OF_LETTERS; idx++) {
        cout << LETTERS[idx] << "\t" << bigrams_[idx][0] << "\t" << bigrams_[idx][1] << "\t" << bigrams_[idx][2] << "\t" << bigrams_[idx][3] << endl;
        //display extra space at end of table
        if (idx == NUM_OF_LETTERS - 1) {
            cout << "\n";
        }
    }
} //show_bigrams_table

//returns the top bigram, both if tied
string top_bigram(int bigrams_[4][4]) {
    int largest_value = 0, largest_row = 0, largest_col = 0, num_bigrams = 0;
    string largest_bigram;

    for (int row = 0; row < NUM_OF_LETTERS; row++) {
        for (int col = 0; col < NUM_OF_LETTERS; col++) {
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
    int letter_count[4] = {0, 0, 0, 0};
    int highest = 0;
    string top_letter;

    //count each letter and put into letter_count array
    for (int idx = 0; idx < NUM_OF_LETTERS; idx++) {
        letter_count[idx] = bigrams_[idx][0] + bigrams_[idx][1] + bigrams_[idx][2] + bigrams_[idx][3];
    } //for

    //search for most common letter
    for (int idx = 0; idx < NUM_OF_LETTERS; idx++) {
        if (letter_count[idx] > highest) {
            highest = letter_count[idx];
            top_letter = LETTERS[idx]; 
        } //for
        //if there are two, add it on
        else if (letter_count[idx] == highest) {
            top_letter += LETTERS[idx];
        } //else if
    } //top_count()

    return top_letter; 
} //top_count()

void display_largest_bigram(string largest_bigram_) {
    string bigram_1, bigram_2;
    if (largest_bigram_.length() == 2) {  //this works as long as /n is not single the largest bigram, which it never is
        cout << "The largest bigram is \"" << largest_bigram_ << "\"" <<endl;
    } //if

    //for a tie, splits them up and displays a different message
    else {
        bigram_1 = largest_bigram_.substr(0,2);
        bigram_2 = largest_bigram_.substr(2, largest_bigram_.length() - 2); //this allows the \n to be displayed
        cout << "The largest bigrams are \"" << bigram_1 << "\" and \"" << bigram_2 << "\"" << endl;
    } //else
} //display_largest_bigram()

void display_most_common_letter(string largest_count_) {
    string letter_1, letter_2;
    if (largest_count_.length() == 1) {  //this works as long as /n is not the single most common character, which it never is
        cout << "The most common letter is \"" << largest_count_ << "\"" << endl;
    } //if

    //for a tie, splits the characters up and displays a different message
    else {
        letter_1 = largest_count_[0];
        letter_2 = largest_count_.substr(1, largest_count_.length() - 1); //this allows the \n to be displayed
        cout << "The most common letters are \"" << letter_1 << "\" and \"" << letter_2 << "\"" << endl;
    } //else
} //display_largest_bigram()

int main() {
    int bigrams[4][4] = {{2, 4, 8, 1}, {0, 10, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int user_value;
    string largest_bigram;
    string largest_count;

    //ask user for c bigrams
    for (int idx = 0; idx < 3; idx++) {
        cout << "Enter the value for bigram c" << LETTERS[idx] <<": ";
        cin >> user_value;
        bigrams[2][idx] =  user_value;
    } //for

    show_bigrams_table(bigrams);

    largest_bigram = top_bigram(bigrams);
    largest_count = top_count(bigrams);

    display_largest_bigram(largest_bigram);
    display_most_common_letter(largest_count);

    if (DBG) {

    }

    return 0;
} //main

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:

Enter the value for bigram ca: 1
Enter the value for bigram cb: 7
Enter the value for bigram cc: 7

        a       b       c       \n
a       2       4       8       1
b       0       10      2       0
c       1       7       7       0
\n      0       0       0       0

The largest bigram is "bb"
The most common letters are "a" and "c"

Enter the value for bigram ca: 20
Enter the value for bigram cb: 20
Enter the value for bigram cc: 1

        a       b       c       \n
a       2       4       8       1
b       0       10      2       0
c       20      20      1       0
\n      0       0       0       0

The largest bigrams are "ca" and "cb"
The most common letter is "c"

**************************************************************************/ 