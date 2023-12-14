#include "LongVectorsTests.h"
using namespace std;

int main() {
    LongVectorsTests tester;
    cout << left << endl;

    tester.testReadLongVectors();
    tester.testGetPyramidOfDifferences();
    tester.testGetDifferences();
    tester.testIsAll0s();
    tester.testGetNewRightValueOfPyramid();
    tester.testSumVectors();
    
    cout << endl;
    return 0;
}

void LongVectorsTests::testReadLongVectors() {
    vector<string> lines = { "8 10 9 -2 -17 8 190 771 2208 5345 11753 24409 49063 97014 190779 375658 743112 1477240 2945141 5868120 11637263",
            "-9 -16 -26 -42 -67 -89 -41 278 1345 4163 10710 24787 53710 111805 227699 459451 925644 1868703 3782952 7672020 15562542",
            "28 51 96 170 284 469 798 1415 2573 4692 8485 15300 28049 53554 108059 229471 503402 1116673 2463878 5353430 11394522" };
    vector<vector<long>> longVectors = readLongVectors(lines);
    vector<vector<long>> expected = { { 8, 10, 9, -2, -17, 8, 190, 771, 2208, 5345, 11753, 24409, 49063, 97014, 190779, 375658, 743112, 1477240, 2945141, 5868120, 11637263 },
            { -9, -16, -26, -42, -67, -89, -41, 278, 1345, 4163, 10710, 24787, 53710, 111805, 227699, 459451, 925644, 1868703, 3782952, 7672020, 15562542 },
            { 28, 51, 96, 170, 284, 469, 798, 1415, 2573, 4692, 8485, 15300, 28049, 53554, 108059, 229471, 503402, 1116673, 2463878, 5353430, 11394522 } };

    if (longVectors == expected) {
        cout << GREEN << setw(WIDTH) << "  testReadLongVectors" << " iO" << RESET  << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testReadLongVectors" << "niO" << RESET  << endl;
    }
}

void LongVectorsTests::testGetPyramidOfDifferences()
{
    vector<long> nums = {1,2,3,4,5,6};
    vector<vector<long>> pyramid = getPyramidOfDifferences(nums);
    vector<vector<long>> expected = { {1,1,1,1,1}, {0,0,0,0} };

    if (pyramid == expected) {
        cout << GREEN << setw(WIDTH) << "  testGetPyramidOfDifferences" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testGetPyramidOfDifferences" << "niO" << RESET << endl;
    }
}

void LongVectorsTests::testGetDifferences() {
    vector<long> nums = {1,2,3,4,5,6};
    vector<long> differences = getDifferences(nums);
    vector<long> expected = {1,1,1,1,1};

    if (differences == expected) {
        cout << GREEN << setw(WIDTH) << "  testGetDifferences" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testGetDifferences" << "niO" << RESET << endl;
    }
}

void LongVectorsTests::testIsAll0s()
{
    vector<long> nums1 = {1,2,3,4,5,6};
    vector<long> nums2 = {0,0,0,0};
    bool b1 = isAll0s(nums1);
    bool b2 = isAll0s(nums2);

    if (!b1 && b2) {
        cout << GREEN << setw(WIDTH) << "  testIsAll0s" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testIsAll0s" << "niO" << RESET << endl;
    }
}

void LongVectorsTests::testSumVectors()
{
    vector<long> nums1 = {1,2,3,4,5,6};
    long sum = sumVector(nums1);
    long expected = 21;

    if (sum == expected) {
        cout << GREEN << setw(WIDTH) << "  testSumVectors" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testSumVectors" << "niO" << RESET << endl;
    }
}

void LongVectorsTests::testGetNewRightValueOfPyramid()
{
    vector<vector<long>> pyramid = { {1,2,3,4,5,6}, {1,1,1,1,1}, {0,0,0,0} };
    long newValue = getNewRightValueOfPyramid(pyramid);
    long expected = 7;

    if (newValue == expected) {
        cout << GREEN << setw(WIDTH) << "  testGetNewRightValueOfPyramid" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testGetNewRightValueOfPyramid" << "niO" << RESET << endl;
    }
}
