struct comparator
{
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const
    {
        return a.first > b.first || (a.first == b.first && a.second > b.second);
    }
};

class Solution {
public:
    long long findScore(vector<int>& nums)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> queue;
        bitset<100000> marked;
        int n = nums.size() - 1;
        long long score = 0;

        for(int i = 0; i <= n; i++)
            queue.push({nums[i], i});

        while(!queue.empty())
        {
            pair<int,int> e = queue.top();
            queue.pop();

            if(marked[e.second])
                continue;
            
            score += e.first;
            marked.set(e.second);
            
            if(e.second > 0)
                marked.set(e.second - 1);
            
            if(e.second < n)
                marked.set(e.second + 1);
        }

        return score;
    }
};