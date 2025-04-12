class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k)
    {
        int n = nums.size();
        int res = 0;
        int start = 0;

        sort(nums.begin(), nums.end());

        for(int end = 0; end < n; end++)
        {
            while(nums[end] - nums[start] > 2 * k)
                start++;
                
            res = max(res, end - start + 1);
        }

        return res;
    }
};