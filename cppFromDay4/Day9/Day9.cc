#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "LongVectors.cc"

int main() {
    MethodFrame mF("Day9.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input9.txt").getLines();

    vector<vector<long>> longVectors = readLongVectors(lines);
    vector<long> newRightValues;
    vector<long> newLeftValues;

    for (vector<long> longVector : longVectors) {
        vector<vector<long>> pyramidOfDifferences = getPyramidOfDifferences(longVector);

        long newRightValueWithoutStartingVector = getNewRightValueOfPyramid(pyramidOfDifferences);
        long newRightValue = longVector.back() + newRightValueWithoutStartingVector;
        newRightValues.emplace_back(newRightValue);

        long newLeftValueWithoutStartingVector = getNewLeftValueOfPyramid(pyramidOfDifferences);
        long newLeftValue = longVector.front() - newLeftValueWithoutStartingVector;
        newLeftValues.emplace_back(newLeftValue);
    }

    long sumRightValues = sumVector(newRightValues);
    long sumLeftValues = sumVector(newLeftValues);

    cout << "sumRightValues: " << sumRightValues << endl;
    cout << "sumLeftValues:  " << sumLeftValues << endl;

    mF.printEnd();
    return 0;
}
