class Solution {
public:
    long long continuousSubarrays(vector<int>& nums)
    {
        int n = nums.size();
        long long count = 0;
        multiset<int> set;

        for(int end = 0, start = 0; end < n; end++)
        {
            set.insert(nums[end]);

            while(start < end && *(set.rbegin()) - *(set.begin()) > 2)
            {
                set.erase(set.find(nums[start]));
                start++;
            }

            count += end - start + 1;
        }
        
        return count;
    }
};