#include <iostream>
#include <set>

using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int num, start = 0;
        long long bestSum = 0, currentSum = 0;
        set<int> subarray;

        for(int i = 0; i < nums.size(); i++) {
            num = nums[i];

            while(!subarray.insert(num).second) {
                currentSum -= nums[start];
                subarray.erase(nums[start]);
                start++;
            }

            currentSum += num;

            if(subarray.size() == k) {
                bestSum = max(bestSum, currentSum);
                currentSum -= nums[start];
                subarray.erase(nums[start]);
                start++;
            }
        }

        return bestSum;
    }
};