#include <iostream>
using namespace std;

vector<vector<long>> readLongVectors(const vector<string>& lines);          // tested iO
vector<vector<long>> getPyramidOfDifferences(const vector<long>& nums);     // tested iO
vector<long> getDifferences(const vector<long>& nums);                      // tested iO
bool isAll0s(const vector<long>& nums);                                     // tested iO
long getNewRightValueOfPyramid(const vector<vector<long>>& pyramid);        // tested iO
long getNewLeftValueOfPyramid(const vector<vector<long>>& pyramid);         // 
long sumVector(const vector<long>& nums);                                   // tested iO
void printPyramid(const vector<vector<long>>& pyramid);                     // not tested

vector<vector<long>> readLongVectors(const vector<string> &lines)
{
    vector<vector<long>> numVectors;

    for (string line : lines) {
        vector<long> numVector;
        char* numStr = strtok((char*) line.c_str(), " ");
        while (numStr != NULL) {
            numVector.emplace_back(stol(numStr));
            numStr = strtok(NULL, " ");
        }
        numVectors.emplace_back(numVector);
    }

    return numVectors;
}

vector<vector<long>> getPyramidOfDifferences(const vector<long> &nums)
{
    vector<vector<long>> pyramid;

    pyramid.emplace_back(getDifferences(nums));

    while (!isAll0s(pyramid.back())) {
        pyramid.emplace_back(getDifferences(pyramid.back()));
    }

    return pyramid;
}

vector<long> getDifferences(const vector<long> &nums)
{
    vector<long> differences;

    for (int i = 1; i < nums.size(); i++) {
        differences.emplace_back(nums[i] - nums[i - 1]);
    }
    
    return differences;
}

bool isAll0s(const vector<long>& nums)
{
    for (long num : nums) {
        if (num != 0) {
            return false;
        }
    }
    return true;
}

long getNewRightValueOfPyramid(const vector<vector<long>> &pyramid)
{
    long newValue = 0;
        for (int i = pyramid.size() - 1; i >= 0; i--) {
            long lastValue = pyramid[i].back();
            newValue += lastValue;
        }
    return newValue;
}

long getNewLeftValueOfPyramid(const vector<vector<long>> &pyramid)
{
    long newValue = 0;
        for (int i = 0; i < pyramid.size(); i++) {
            long firstValue = pyramid[i].front();
            if (i % 2 == 0) {
                newValue += firstValue;
            } else {
                newValue -= firstValue;
            }
        }
    return newValue;
}

long sumVector(const vector<long> &nums)
{
    long sum = 0;
    for (long num : nums) {
        sum += num;
    }
    return sum;
}

void printPyramid(const vector<vector<long>>& pyramid)
{
    for (vector<long> nums : pyramid) {
        for (long num : nums) {
            cout << num << ", ";
        }
        cout << endl;
    }
}
