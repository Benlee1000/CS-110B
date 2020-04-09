/************************************************************************** 
**************************    Honor Code Affirmation **********************
**   We, Benjamin Lee and Leighton Yan, have not given or received 
**   inappropriate help with this assignment. 
** 
*************************************************************************** 
**********************************    Design    *************************** 
** 1.   In setField, make a while loop
** 2.   Use .find method to look for ',' delimiter's index position
** 3.   If no additional separators are found, add remainder of string to 
        vector fields with push_back and exit while loop
** 4.   If separator is found, make a substring from start of string with 
        a length of the delimiter's index position. Add substring to 
        vector fields with push_back
** 5.   Replace line with line removing the previous substring along with 
        the ','
** 6.   If the modified line is empty, break to exit loop
**************************************************************************/

/*
    CSV -- comma separated value. You can export an excel spreadsheet or
    some other DB into a text file, in which the entries of each row in 
    the base are seprated by commas.
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
            /*
            parse this->line into fields
            e.g. suppose line was: "San Francisco, 123, 5.72"
            Then setFields would intialize the fields string vector with 
            3 strings: this->fields.at(0) would be "San Francisco",
                       this->fields.at(1) would be "123"
                       this->fields.at(2) would be "5.72"
            */

            /* Old code using for loop before learning the use of find method
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
            */

            while(true){
                int delim_point = line.find(','); // index position of ','
                if (delim_point == string::npos){
                    fields.push_back(line);
                    break;
                } // if: can't find ',' place line in last vector postion and break
                else{
                    // create substring from beginning of line up to before the ',' and place in vector
                    // index position is one less than number of characters, so delim_point as number of chars excludes ','
                    fields.push_back(line.substr(starting_point, delim_point++));
                    // replace line with line removing the previous substring along with the ','
                    line = line.substr(delim_point, line.length() - delim_point);
                } // else
                if (line.empty()){
                    break;
                } // if: line after ',' is empty, break
            }

        }
        string getLine() { return this->line; }
};


int main() {
  
    string fromDB =
    //  0      1           2        3            4             5
    "06075,San Francisco,California,US,2020-04-01 21:58:49,37.75215114";

    //initialize a new CSV object, using the string fromDB
    CSV * csv = new CSV(fromDB);
    cout << "The text stored in the csv object is \"" << csv->getLine() << "\"" << endl;

    //for the lab, I want you to complete the getFields method started up above
    csv->setFields();

    //And then after you get them, retrieve them with the getFields method
    vector<string> f = csv->getFields();

    //cout << f.at(4) << endl;

    for (int idx = 0; idx < f.size(); ++idx) {
        cout << idx << ". " << f.at(idx) << endl;
    }
    /* 
     * The outut should look like this:
     * 0.  06075
     * 1.  San Francisco
     * 2.  California
     * 3.  US
     * 4. 2020-04-01 21:58:49
     * 5. 37.75214114
     */
  
}

/************************************************************************** 
************************   Test Report   ********************************** 
** Worked as designed, as shown by a transcript of program execution:

The text stored in the csv object is "06075,San Francisco,California,US,2020-04-01 21:58:49,37.75215114"
0. 06075
1. San Francisco
2. California
3. US
4. 2020-04-01 21:58:49
5. 37.75215114

**************************************************************************/ 