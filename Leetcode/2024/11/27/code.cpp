class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<pair<int,vector<int>>> graph(n, {0, vector<int>()});
        vector<int> res;

        for(int i = 0; i < n - 1; i++) {
            graph[i].first = i;
            graph[i].second.push_back(i + 1);
        }
        graph[n - 1].first = n - 1;

        for(vector<int> query: queries) {
            graph[query[0]].second.push_back(query[1]);

            queue<int> queue;
            set<int> excluded;

            queue.push(0);
            excluded.insert(0);

            while(!queue.empty()) {
                int city = queue.front();
                queue.pop();

                for(int next: graph[city].second) {
                    if(excluded.insert(next).second) {
                        graph[next].first = graph[city].first + 1;
                        queue.push(next);
                    }
                }
            }
            
            res.push_back(graph[n - 1].first);
        }

        return res;
    }
};