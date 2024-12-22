class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k)
    {
        if(n == 1)
            return 1;

        unordered_map<int, unordered_set<int>> neighbours;
        queue<int> leafs;
        int componentCount = 0;

        for(vector<int>& e: edges)
        {
            neighbours[e[0]].insert(e[1]);
            neighbours[e[1]].insert(e[0]);
        }

        for(int i = 0; i < n; i++)
        {
            if(neighbours[i].size() <= 1)
                leafs.push(i);
            
            values[i] %= k;
        }

        while(!leafs.empty())
        {
            int leaf = leafs.front();
            leafs.pop();

            if(values[leaf] == 0)
                componentCount++;

            if(neighbours[leaf].size() > 0)
            {
                int parent = *(neighbours[leaf].begin());
                neighbours[parent].erase(leaf);
                values[parent] = (values[parent] + values[leaf]) % k;

                if(neighbours[parent].size() == 1)
                    leafs.push(parent);
            }
        }

        return componentCount;
    }
};