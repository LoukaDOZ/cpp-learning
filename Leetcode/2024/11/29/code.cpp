class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if(grid[0][1] > 1 && grid[1][0] > 1)
            return -1;

        int m = grid.size(), n = grid[0].size();
        queue<pair<int,int>> queue;
        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        vector<vector<int>> times(m, vector<int>(n, INT_MAX));

        times[0][0] = 0;
        queue.push({0,0});

        while(!queue.empty()) {
            pair<int,int> pos = queue.front();
            queue.pop();

            for(pair<int,int> dir: directions) {
                int x = pos.first + dir.first;
                int y = pos.second + dir.second;

                if(x >= 0 && x < m && y >= 0 && y < n) {
                    int ptime = times[pos.first][pos.second];
                    int ngrid = grid[x][y];
                    int time = ptime + 1 >= ngrid ? ptime + 1 : ngrid + ((ngrid - 1 - ptime) % 2);

                    if(time < times[x][y]) {
                        times[x][y] = time;
                        queue.push({x,y});
                    }
                }
                    
            }
        }

        return times[m - 1][n - 1];
    }
};