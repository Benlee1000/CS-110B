/*
A class that counts every time put() is called
test() returns true if number of calls is even and vice-versa
*/
#include <iostream>

using namespace std;

class parity {
    private:
        int counter;
    public:
        void put() {
            counter++;
        }
        bool test() {
            if (counter % 2 == 0) {
                return true;
            }
            else {
                return false;
            }
        }
};

int main() {
    parity aparity;
    aparity.put();
    aparity.put();
    aparity.put();
    if (aparity.test()) {
        cout << "Even number of calls";
    }
    else {
        cout << "Odd number of calls";
    }

}

