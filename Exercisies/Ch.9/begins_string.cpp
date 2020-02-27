/*
 * This program takes two strings and finds out if the first string is the start of the second
 */

#include <iostream>

using namespace std;

bool begins(string s1, string s2) {
    for (int idx = 0; idx < s1.length(); idx++) {
        if (s1[idx] != s2[idx]) {
            return false;
        }
    }
    return true;
} //begins

int main() {
    string string1, string2;
    bool string_begins;

    cout << "Enter the first string: ";
    cin >> string1;
    cout << "Enter the second string: ";
    cin >> string2;

    string_begins = begins(string1, string2);

    if (string_begins) {
        cout << "The first string starts the second";
    }
    else {
        cout << "The first string does not start the second";
    }

}