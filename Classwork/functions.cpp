#include <iostream>

using namespace std;

int b2[4][4] = { {2,4,6,0}, {1,3,5,1}, {3,5,8,0}, {0,0,0,0} };

int sum3(int a, int b, int c) {
    return a + b + c;
} //sum3()

//pass by pointer
void change1(int *j) {
    *j = *j * *j;
} //change1()

//pass by value
void change2(int j) {
    j = j * 2;
}

void change3(int m[4][4]) {
    m[0][1] = 2;
}

void change4(int &j) {
    j = j * j;
}


int main () {
    int bigrams[4][4] = { {2,4,6,0}, {1,3,5,1}, {3,5,8,0}, {0,0,0,0} };
    change2(bigrams[0][1]);
    int k = sum3(bigrams[0][0], bigrams[0][1], bigrams[0][2]);
    cout << "k after pass by value: " << k << endl;
    
    change1(&bigrams[0][1]);
    k = sum3(bigrams[0][0], bigrams[0][1], bigrams[0][2]);
    cout << "k after pass by pointer: " << k << endl;

    change3(bigrams);
    k = sum3(bigrams[0][0], bigrams[0][1], bigrams[0][2]);
    cout << "k after pass by array: " << k << endl;

    change4(bigrams[0][1]);
    k = sum3(bigrams[0][0], bigrams[0][1], bigrams[0][2]);
    cout << "k after pass by reference: " << k << endl;

    //best to use functions that are clear and return something, not these 

} //main()