#include <iostream>
using namespace std;

long lcm(long a, long b);
long lcmOfVector(vector<int> nums);
long productOfVector(vector<int> nums);
int gcd(long a, long b);
int gcdOfVector(vector<int> nums);

long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
}

long lcmOfVector(vector<int> nums)
{
    long result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        result = lcm(nums[i], result);
        cout << "lcm: " << result << endl;
    }
    return result;
}

long productOfVector(vector<int> nums)
{
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        res *= nums[i];
    }
    return res;
}

int gcd(long a, long b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int gcdOfVector(vector<int> nums) {
    int result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        result = gcd(nums[i], result);

        if (result == 1) {
            return 1;
        }
    }
    return result;
}