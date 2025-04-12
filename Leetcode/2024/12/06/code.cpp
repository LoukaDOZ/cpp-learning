class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum)
    {
        int count = 0;
        unordered_set<int> ban;

        for(int b: banned)
        {
            if(b <= n)
                ban.insert(b);
        }

        for(int i = 1; i <= n && maxSum - i >= 0; i++)
        {
            if(ban.count(i))
                continue;
            
            maxSum -= i;
            count++;
        }

        return count;
    }
};