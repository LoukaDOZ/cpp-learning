class Solution {
public:
    int findTargetRec(vector<int>& nums, int target, int i, int sum)
    {
        if(i >= nums.size())
            return sum == target;
        
        return findTargetRec(nums, target, i + 1, sum + nums[i]) + findTargetRec(nums, target, i + 1, sum - nums[i]);
    }

    int findTargetSumWays(vector<int>& nums, int target)
    {
        return findTargetRec(nums, target, 0, 0);
    }
};