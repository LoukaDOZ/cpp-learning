class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries)
    {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> queue;
        vector<vector<vector<int>>> storeQueries(heights.size());
        vector<int> ans(queries.size(), -1);
        int n = heights.size();
        int m = queries.size();

        for(int i = 0; i < m; i++)
        {
            int alice = queries[i][0];
            int bob = queries[i][1];
            int aliceH = heights[alice];
            int bobH = heights[bob];

            if(alice == bob || (alice < bob && aliceH < bobH) || (alice > bob && aliceH > bobH))
            {
                ans[i] = max(alice, bob);
                continue;
            }

            storeQueries[max(alice, bob)].push_back({max(aliceH, bobH), i});
        }

        for(int i = 0; i < n; i++)
        {
            while(!queue.empty() && queue.top()[0] < heights[i])
            {
                ans[queue.top()[1]] = i;
                queue.pop();
            }

            for(vector<int>& query : storeQueries[i])
                queue.push(query);
        }

        return ans;
    }
};