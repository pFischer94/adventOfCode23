#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "LongVectors.cc"

int main() {
    MethodFrame mF("Day8.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input9.txt").getLines();

    vector<long> newRightValues;

    vector<vector<long>> longVectors = readLongVectors(lines);

    for (vector<long> longVector : longVectors) {
        vector<vector<long>> pyramidOfDifferences = getPyramidOfDifferences(longVector);

        long newRightValueWithoutStartingVector = getNewRightValueOfPyramid(pyramidOfDifferences);
        long newRightValue = newRightValueWithoutStartingVector + longVector.back();
        newRightValues.emplace_back(newRightValue);
    }

    long sumRightValues = sumVector(newRightValues);

    cout << "sumRightValues: " << sumRightValues << endl;

    mF.printEnd();
    return 0;
}
