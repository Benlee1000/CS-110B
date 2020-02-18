#include <iostream>
#include <ctype.h>
/*
 * 1. prompt the user to enter stuff, numbering each round of
 * text entry --if the user enters Q/q, exit and say goodbye
 * if the user enters nothing, reprompt.
 */
using namespace std;
const bool DBG = false;

bool quit(string answer_) {
    if (answer_.length() == 1 && toupper(answer_[0]) == 'Q') {
        return true;
    }
    return false;
} //quit()
bool no_response(string answer_) {
    if (answer_.length() == 0) {
        return true;
    }
    return false;
} //no_response()

const int NUM_VOWELS = 5;
const int A = 0, E = 1, I = 2, O = 3, U = 4;

void count_vowels(string answer_, int vcounts_[]) {
    for (int idx = 0; idx < answer_.length() ; ++idx ) {
        char ch = toupper(answer_[idx]);
        switch(ch) {    
            case 'A': ++vcounts_[A]; break;
            case 'E': ++vcounts_[E]; break;
            case 'I': ++vcounts_[I]; break;
            case 'O': ++vcounts_[O]; break;
            case 'U': ++vcounts_[U]; break;

            default:
                if(DBG) {
                    cout << "'" << answer_[idx] << "' is not a vowel" << endl;
                }
        } //switch
    } //for
} //count_vowels()

/*
 * find the largest number(s) in vcounts_, and associate that with
 * the corresponding vowels, and reports.
 * if all the numbers in vcounts_ are zero, say something special.
 * start by assuming the first element in vcounts_ is the biggest, 
 * and update as needed.
 */
void show_top(int vcounts_[] ) {
    int max_idx = 0; //start by assuming largest is first
    string max_vowels = "A";
    string VOWELS[5] = {"A","E","I","O","U"};

    for (int idx = 1; idx < NUM_VOWELS; idx++) {
        if (vcounts_[idx] > vcounts_[max_idx]) {
            max_idx = idx;
            max_vowels = VOWELS[idx];
        }
        else if (vcounts_[idx] == vcounts_[max_idx]) {
            //max_vowels += ", " + VOWELS[idx]; //append the current vowel to max vowels
            max_vowels += VOWELS[idx];
        }

    } //for

    if (vcounts_[max_idx] == 0) {
        cout << "There were no vowels in the input" << endl;
    }
    else if (max_vowels.length() == 1) {
        cout << "The vowel with the high count is \"" << max_vowels << "\", count = " << vcounts_[max_idx] << endl;
    }
    else {
        if (max_vowels.length() == 2) {
            string result = "";
            result.push_back(max_vowels[0]);
            result += " and ";
            result.push_back(max_vowels[1]);
            cout << "The vowels with the high count are " << result << ", count = " << vcounts_[max_idx] << endl;
        } //if there are two top vowels
        else {
            //create a result string like; E, O, and U
            string result = "";
            result.push_back(max_vowels[0]);
            result += ", ";
            //result could be "E, "
            for (int idx = 1; idx < max_vowels.length() -1; ++idx) {
                //append a vowel to the result string
                result.push_back(max_vowels[idx]);
                result += ", ";
            } //for
            //append the last vowel to the result string

            cout << "The vowels with the high count are " << result << ", count = " << vcounts_[max_idx] << endl;
        } //there are more than two max vowels
    } //else there is more than one top vowel

} //show_top()

string get_text() { 
    string answer;
    static int round = 1;
    while (true) {
        cout << "Round " << round << ". Enter text: ";
        getline(cin,answer);
        if (no_response(answer)) {
            cout << "Please respond to the prompt." << endl;
            continue; //go back to top of the loop
        }
        break; // outta here
    } // while
    ++round; // equivalent to: round++, round += 1, or round = round + 1;
    return answer;
} //get_text()

int main () {
    cout << "*** Welcome to Feb 11 in class demo ***\n" << endl;
    int round = 0;
    string answer;
    int vcounts[NUM_VOWELS] = {0,0,0,0,0};
    while (true) {
        answer = get_text();
        if (quit(answer)) {
            break; //outta here
        }
        count_vowels(answer,vcounts);
    } //while
    
    show_top(vcounts);

} //main() 