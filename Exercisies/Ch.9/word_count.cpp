/*
 *  Create a program that counts the number 
 *  of words in a string 
 *  
 *  Use spaces to indicate a new word
 */

#include <iostream>

using namespace std;

int main () {
    string response;
    int words = 1; //start with 1 because first word has no space

    cout << "Please enter a string of words separated by spaces: ";
    getline(cin, response);

    while (response[response.length() - 1] == ' ' || response[0] == ' ') {
        cout << "Please do not enter a space at the beginning or end of the string" << endl;
        cout << "Please enter a string of words separated by spaces: ";
        getline(cin, response);
    }

    for (int idx = 0; idx < response.length(); idx++) {
        //increase words if there is a space 
        if (response[idx] == ' ') {
            words++;
        }
    } //for

    cout << "There are " << words << " words";
 
} //main