//Question 3 - TEST stack Sizes
// Umar Kagzi

#include <iostream> 
#include <time.h>
#include <chrono>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stack>
#include "arrayLL.h"

using namespace std;
using namespace std::chrono;


int main() {

    // Create max size for array stack and LL stack
    int size = 1000000;
    // declare srand to use the timing function
    srand(time(nullptr));

    // Testing LL stack here:
    auto start1 = high_resolution_clock::now();
    //declare stack
    linkedStackType<int> stackLL;

    //Add a rand num to every spot in stack
    for (int i = 0; i < size; i++) {
        int arrNum1 = rand() % 100;
        stackLL.push(arrNum1);
    }
    //End timer
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::microseconds>(end1 - start1);
    cout << "\nThe LL stack fill-up took: " << duration1.count() << " microseconds" << endl;


    // Array Based stack Testing
    auto start2 = high_resolution_clock::now();
    //Declare array stack
    arrayStack<int> stackArray(size);

    //Insert random num into every stack index
    for (int i = 0; i < size; i++) {
        int arrNum2 = rand() % 100;
        stackArray.push(arrNum2);
    }

    //End timer and calculate timing
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<std::chrono::microseconds>(end2 - start2);
    cout << "\nThe array stack fill-up took: " << duration2.count() << " microseconds" << endl;


    return 0;

}