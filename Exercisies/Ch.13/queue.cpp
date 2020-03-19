/*
Class queue takes values in and returns them in first-in first-out format
*/

#include <iostream>
using namespace std;

class queue {
    private:
        int numbers[100];
        int count = 0, count_2 = 0, get_num;
    public:
        void put(int value) {
            numbers[count] = value;
            count++;
        }
        int get() {
            get_num = numbers[count_2];
            count_2++;
            return get_num;
        }
};

int main() {
    queue aqueue;
    
    aqueue.put(20);
    aqueue.put(10);
    aqueue.put(0);

    cout << aqueue.get() << endl;
    cout << aqueue.get() << endl;
    cout << aqueue.get() << endl;
}