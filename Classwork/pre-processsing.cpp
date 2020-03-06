#include "pre-processing.h"

int main() {
    int bigrams[64][64] = {0};

    // 4 2 1
    // 0 1 1  3 = 1 * 2 + 1 * 1 
    int j = 3;
    // 8 4 2 1
    // 1 0 0 1
    int k = 9;

    // 0 0 1 1
    // 1 0 0 1

    // 0 0 0 1 for bitwise & (and)
    int g = BitAnd(j,k);

    // 1 0 1 1 for bitwise | (or)
    int h = j | k;

    // 1 0 1 0 for bitwise ^ (XOR, exclusive or)
    int i = j ^ k;

    // 1 1 0 0 for bitwise ~ (inverse)
    int l =  ~j;

#ifdef DBG
    cout << g << endl;
    cout << h << endl;
    cout << i << endl;
    cout << l << endl;
#endif
} //main