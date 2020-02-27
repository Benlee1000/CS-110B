#include <iostream>

using namespace std;

bool is_prime(int n, int div = 2) {
    //base case
    if (n % div != 0) {
        return true;
    }
    //recursive case
    else if (n % div == 0) {
        return false;
    }
    return is_prime(n, ++div);
}

int main() {
    int num_in;
    cout << "Enter a number: ";
    cin >> num_in;

    
    if (is_prime(num_in)) {
        cout << "The number " << num_in << " is prime"<< endl;
    }
    else {
        cout << "The number " << num_in << " is not prime" << endl;
    }


}