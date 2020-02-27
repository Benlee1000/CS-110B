#include <iostream>

using namespace std;
const bool DBG = false;

char Max(string s, int pos, char max_ch) {
    if (pos == s.length()) {
        return max_ch;
    }
    
    if (DBG){
        cout << "before if/else " << max_ch << endl;
    }
    char ch = (s[pos] > max_ch)?s[pos]:max_ch; //combo of an if, else and assignment
    if (DBG){
        cout << "after if/else " << ch << endl;
    }
    return Max(s, ++pos, ch);
    
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;
    // string s = "campus";
    if (DBG){
        cout << "in main" << endl;
    }
    char m = Max(s, 0, '\0');
    cout << "Largest character: " << m;
} 