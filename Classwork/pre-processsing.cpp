#include "pre-processing.h"

int main() {
    // 4 2 1
    // 0 1 1  3 = 1 * 2 + 1 * 1 
    int j = 3;
    // 8 4 2 1
    // 1 0 0 1
    int k = 9;

    // 0 0 1 1
    // 1 0 0 1

    // 0 0 0 0 for bitwise &
    int g = BitAnd(j,k);






#ifdef DBG
    cout << g << endl;
#endif
} //main