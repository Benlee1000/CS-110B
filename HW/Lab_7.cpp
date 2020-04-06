/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.  
** 2.
** 3. 
**************************************************************************/

/*
    CSV -- comma separated value. You can export an excel spreadsheet or
    some other DB into a text file, in which the entries of each row in 
    the base are seprated by commas.

    Notes:
    Made set fields to separate string
    Lines 69,70,72 have errors that I don't know how to fix
    Waiting for Mr. Pico to give us the data to break up
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CSV {
    string line;
    vector<string> fields;
    int starting_point = 0;
    
    public:
        CSV(string line_) {
            this->line = line_;
        } //constuctor
        vector<string> getFields() {return this->fields;}
        void setFields() {
            for (int idx = 0; idx < line.length(); idx++) {
                if (line[idx] == ',') {
                    //if there is a comma, create a substring from start to comma, not including commma
                    fields.push_back(line.substr(starting_point, idx - starting_point));
                    //increase field_number for next entry, set new starting point to after comma
                    starting_point = idx + 1; 
                }
                else if (idx == line.length() - 1) {
                    //create one more field for last item in CSV
                    fields.push_back(line.substr(starting_point, idx - starting_point));
                }
            }

            /*
            parse this->line into fields
            e.g. suppose line was: "San Francisco, 123, 5.72"
            Then setFields would intialize the fields string vector with 
            3 strings: this->fields.at(0) would be "San Francisco",
                       this->fields.at(1) would be "123"
                       this->fields.at(2) would be "5.72"
            */
        }
};


int main() {
    string fromDB = "06075,San Francisco,California,US,2020-04-01 21:58:49,37.75215114";
    CSV * csv = new CSV(fromDB);
    csv->setFields();
    vector<string> f = csv->getFields();
    for (int idx = 0; idx < f.size(); ++idx) {
        cout << idx << ". " << f.at(idx) << endl;
    } //for
    
}

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:


**************************************************************************/ 