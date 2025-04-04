class Solution {
public:
    pair<int,int> bfs(vector<vector<int>>& graph, int start)
    {
        unordered_set<int> excluded;
        queue<pair<int,int>> queue;
        int maxD = 0;
        queue.push({i, 0});

        while(!queue.empty())
        {
            pair<int,int> edge = queue.front();
            queue.pop();

            if(!excluded.insert(edge.first).second)
                continue;
            
            maxD = max(maxD, edge.second);
            
            for(int e: graph[edge.first])
                queue.push({e, edge.second + 1});
        }

        minDiameter = min(minDiameter, maxD);
        maxDiameter = max(maxDiameter, maxD);
    }

    pair<int,int> getMinDiameter(vector<vector<int>>& edges)
    {
        int n = edges.size() + 1;
        int minDiameter = INT_MAX;
        int maxDiameter = 0;
        vector<vector<int>> graph(n, vector<int>());

        for(vector<int>& edge: edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        for(int i = 0; i < n; i++)
        {
            if(graph[i].size() > 1)
                continue;

            unordered_set<int> excluded;
            queue<pair<int,int>> queue;
            int maxD = 0;
            queue.push({i, 0});

            while(!queue.empty())
            {
                pair<int,int> edge = queue.front();
                queue.pop();

                if(!excluded.insert(edge.first).second)
                    continue;
                
                maxD = max(maxD, edge.second);
                
                for(int e: graph[edge.first])
                    queue.push({e, edge.second + 1});
            }

            minDiameter = min(minDiameter, maxD);
            maxDiameter = max(maxDiameter, maxD);
        }

        return {minDiameter, maxDiameter};
    }

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        pair<int,int> diameter1 = getMinDiameter(edges1);
        pair<int,int> diameter2 = getMinDiameter(edges2);
        int minMerged = diameter1.first + diameter2.first + 1;
        return max(max(minMerged, diameter1.second), diameter2.second);
    }
};