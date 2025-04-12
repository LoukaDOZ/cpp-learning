class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> distances(m, vector<int>(n, INT_MAX));
        deque<pair<int,int>> queue;
        vector<pair<int,int>> nextPos = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        distances[0][0] = 0;
        queue.push_front({0, 0});

        while(!queue.empty())
        {
            pair<int,int> pos = queue.front();
            queue.pop_front();

            for(pair<int,int> next: nextPos)
            {
                int x = pos.first + next.first;
                int y = pos.second + next.second;

                if(x >= 0 && x < m && y >= 0 && y < n)
                {
                    int dist = distances[pos.first][pos.second] + grid[x][y];

                    if(dist < distances[x][y])
                    {
                        distances[x][y] = dist;

                        if(grid[x][y] == 1)
                            queue.push_back({x, y});
                        else
                            queue.push_front({x, y});
                    }
                }
            }
        }

        return distances[m - 1][n - 1];
    }
};