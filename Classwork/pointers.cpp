#include <iostream>

using namespace std;

void inc(int val) {
    //pass by value: when you pass an argument to a function
    //by value, thee argument cannot change
    val++;
} //inc()

void inc_addr(int *  val) { //initialize as a pointer, now val = address of num, *val = value in num
    *val = *val + 1; //dereferencing
} //inc_addr()

void inc_reference(int &  val) { //val and num refer to the same value, spacing for clarity
    val++;
} //inc_reference()

void f(int * n1, int * n2) {
    n2 = n1; //n2 now points to what n1 points to
    *n2 = *n2 + 1; //set value in n2 to n2 + 1
} //f

void f_ref(int & n1, int & n2) { // n1 and num refer to 6, n2 and num2 refer to -1
    n1 = n2; //now n1, n2, and num refer to -1
    n1 = n1 + 1; //then n1, n2, and num are all set to 0
}

int main() {
    int num = 3;
    inc(num);
    cout << "Pass by value:"<< num << endl;
    inc_addr(&num); //pass the address
    cout << "Pass by address: " << num << endl;
    inc_reference(num); 
    cout << "Pass by reference: " << num << endl;

    int num2 = -1;
    f(&num, &num2);
    cout << "\nNum after f call becomes: " << num << endl; //now num is 6
    f_ref(num, num2);
    cout << "Num after f_ref call becomes: " << num << endl;
    cout << "Addresses: " << &num << " " << &num2 << endl;
} //main