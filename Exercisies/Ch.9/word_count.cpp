/*
 *  Create a program that counts the number 
 *  of words in a string 
 * 
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

    for (int idx = 0; idx < response.length(); idx++) {
        //increase words if there is a space not at the end of the string
        if (response[idx] == ' ' && idx < response.length() - 1) {
            words++;
        }
    } //for

    cout << "There are " << words << " words";
 
} //main