struct Comparator
{
    bool operator()(pair<int,int>& a, pair<int,int>& b) const
    {
        return a.first > b.first || (a.first == b.first && a.second > b.second);
    }
};

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, Comparator> queue;
        int n = nums.size();

        for(int i = 0; i < n; i++)
            queue.push({nums[i], i});
        
        for(int i = 0; i < k; i++)
        {
            pair<int,int> p = queue.top();
            queue.pop();

            nums[p.second] *= multiplier;
            queue.push({nums[p.second], p.second});
        }

        return nums;
    }
};