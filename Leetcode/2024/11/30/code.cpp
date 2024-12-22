class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        vector<vector<int>> res;
        map<int, vector<int>> graph;
        map<int, int> inEdges;

        for(int i = 0; i < pairs.size(); i++) {
            int front = pairs[i][0];
            int back = pairs[i][1];

            if(graph.find(front) == graph.end())
                graph[front] = vector<int>();

            if(graph.find(back) == graph.end())
                graph[back] = vector<int>();

            if(inEdges.find(front) == inEdges.end())
                inEdges[front] = 0;

            if(inEdges.find(back) == inEdges.end())
                inEdges[back] = 0;

            graph[front].push_back(back);
            inEdges[back]++;
        }

        int start = graph.begin()->first;
        for(map<int,int>::iterator it = inEdges.begin(); it != inEdges.end(); ++it) {
            if(graph[it->first].size() - inEdges[it->first] == 1) {
                start = it->first;
                break;
            }
        }

        stack<int> queue;
        int last = 0;
        queue.push(start);

        while(!queue.empty()) {
            int current = queue.top();

            if(graph[current].size() == 0) {
                queue.pop();
                last--;
                continue;
            }

            int next = graph[current].back();
            graph[current].pop_back();
            queue.push(next);

            res.insert(res.begin() + last, {current, next});
            last++;
        }

        return res;
    }
};