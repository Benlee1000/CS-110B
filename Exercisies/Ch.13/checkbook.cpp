/*
A checkbook class that takes entries of numbers
When total() is called, returns total of those entries
*/

#include <iostream>
#undef DBG

using namespace std;

class checkbook {
    private:
        int entries[2]; //for some reason the array has to be initialized with a set number...not dynamic
        int sum = 0;
        int count = 0;
    public:
        void add_item(int amount) {
            entries[count] = amount;
            count++;
        }
        int total() {
            for (int idx = 0; idx < count; idx++) {
                sum += entries[idx];
            }
            return sum;
        }
};

int main() {
    checkbook acheckbook;
    int user_entry;

#ifdef DBG
cout << acheckbook.total() << endl;
#endif
    
    acheckbook.add_item(100);
    acheckbook.add_item(50);

    cout << "Your total is " << acheckbook.total() << endl;
}