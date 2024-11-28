struct Node {
    int x, y, nbObstaclesRemoved, score;
};

class Compare {
public:
    bool operator()(Node below, Node above) {
        return below.score < above.score;
    }
};

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int endx = grid.size() - 1;
        int endy = grid[0].size() - 1;
        int bestObstaclesRemoved = INT_MAX;

        set<pair<int,int>> excluded;
        priority_queue<Node, vector<Node>, Compare> queue;
        queue.push({0, 0, 0, 0});

        while(!queue.empty()) {
            Node node = queue.top();
            queue.pop();

            if(node.x == endx && node.y == endy) {
                bestObstaclesRemoved = node.nbObstaclesRemoved;
                break;
            }

            if(!excluded.insert({node.x, node.y}).second)
                continue;
            
            vector<Node> nexts;

            if(node.x > 0)
                nexts.push_back({node.x - 1, node.y, node.nbObstaclesRemoved + grid[node.x - 1][node.y], 0});
            
            if(node.x < endx)
                nexts.push_back({node.x + 1, node.y, node.nbObstaclesRemoved + grid[node.x + 1][node.y], 0});
            
            if(node.y > 0)
                nexts.push_back({node.x, node.y - 1, node.nbObstaclesRemoved + grid[node.x][node.y - 1], 0});
            
            if(node.y < endy)
                nexts.push_back({node.x, node.y + 1, node.nbObstaclesRemoved + grid[node.x][node.y + 1], 0});

            for(Node n: nexts) {
                n.score = nodeScore(n);
                queue.push(n);
            }
        }

        return bestObstaclesRemoved;
    }

    int nodeScore(Node& node) {
        return node.nbObstaclesRemoved * -1;
    }
};