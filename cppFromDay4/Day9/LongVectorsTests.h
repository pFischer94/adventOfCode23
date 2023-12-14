#ifndef LONG_VECTORS_TESTS_H
#define LONG_VECTORS_TESTS_H

#include <iomanip>
#include "LongVectorsTests.h"
#include "LongVectors.cc"
using namespace std;

class LongVectorsTests {

    static const int WIDTH = 35;
    inline static const string GREEN = "\033[32m";
    inline static const string RED = "\033[31m";
    inline static const string RESET = "\033[0m";

    void testReadLongVectors();
    void testGetPyramidOfDifferences();
    void testGetDifferences();
    void testIsAll0s();
    void testGetNewRightValueOfPyramid();
    void testSumVectors();
    
    friend int main();

};

#endif