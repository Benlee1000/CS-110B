#include <iostream>
#include <string>


using namespace std;

/*
    Report the number of vowels, constonants, and other characters in user input
    e.g. "Didn't" >> one vowel, 4 constonants, and one other character
*/

int main() {
    string text;

    while (true) {
        cout << "Enter text to analyze, or hit return to quit: ";
        getline(cin, text);

        if (!text.length()) {
            break;
        }
        //cout << text[0] << endl;

        int num_v = 0, num_c = 0, num_o = 0;

        for (int idx = 0; idx < text.length(); idx++) {
            char ch = toupper(text[idx]);
            switch (ch)
            {
            case 'A':
            case 'E': 
            case 'I': 
            case 'O': 
            case 'U': 
                ++num_v;
                break; 
                
            case 'B': 
            case 'C': 
            case 'D': 
            case 'F': 
            case 'G': 
            case 'H': 
            case 'J': 
            case 'K': 
            case 'L': 
            case 'M': 
            case 'N': 
            case 'P': 
            case 'Q': 
            case 'R': 
            case 'S': 
            case 'T': 
            case 'V': 
            case 'W': 
            case 'X': 
            case 'Y': 
            case 'Z':
                ++num_c;
                break;
            
            default:
                ++num_o;
                
            }

        }// for

        cout << "There are " << num_v << " vowels, " << num_c << " constonants, and " << num_o << " other charcters." << endl;

    }//while
    cout << "Goodbye" << endl;
} //main
