class Solution {
public:
    bool binarySearch(vector<pair<int,int>>& specialSubarrays, int qStart, int qEnd)
    {
        int start = 0, end = specialSubarrays.size() - 1, mid;

        while(start <= end)
        {
            mid = start + (end - start) / 2;
            pair<int,int> ssa = specialSubarrays[mid];

            if(qStart >= ssa.first && qEnd <= ssa.second)
                return true;

            if(qStart < ssa.first)
                end = mid - 1;
            else
                start = mid + 1;
        }

        return false;
    }

    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries)
    {
        vector<bool> res;
        int n = nums.size();

        vector<pair<int,int>> specialSubarrays;
        int start = 0;
        for(int i = 0; i < n - 1; i++)
        {
            if(nums[i] % 2 == nums[i + 1] % 2)
            {
                if(i - start >= 1)
                    specialSubarrays.push_back({start, i});

                start = i + 1;
            }
        }
        
        if(n - 1 - start >= 1)
            specialSubarrays.push_back({start, n - 1});

        for(vector<int> q: queries)
        {
            int start = q[0], end = q[1];
            bool ok = false;

            if(start == end)
            {
                res.push_back(true);
                continue;
            }

            res.push_back(binarySearch(specialSubarrays, start, end));
        }

        return res;
    }
};