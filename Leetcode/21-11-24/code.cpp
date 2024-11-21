#include <iostream>

using namespace std;

struct Cell {
    bool garded;
    bool occupied;
};

class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        int count = m * n - guards.size() - walls.size();
        Cell grid[m][n];
        memset(grid, false, sizeof(Cell) * m * n);

        for(int i = 0; i < guards.size(); i++)
            grid[guards[i][0]][guards[i][1]].occupied = true;

        for(int i = 0; i < walls.size(); i++)
            grid[walls[i][0]][walls[i][1]].occupied = true;

        for(int i = 0; i < guards.size(); i++) {
            int x = guards[i][0] + 1;
            int y = guards[i][1];

            while(x < m && !grid[x][y].occupied) {
                if(!grid[x][y].garded) {
                    grid[x][y].garded = true;
                    count--;
                }

                x++;
            }

            x = guards[i][0] - 1;
            while(x >= 0 && !grid[x][y].occupied) {
                if(!grid[x][y].garded) {
                    grid[x][y].garded = true;
                    count--;
                }

                x--;
            }

            x = guards[i][0];
            y = guards[i][1] + 1;
            while(y < n && !grid[x][y].occupied) {
                if(!grid[x][y].garded) {
                    grid[x][y].garded = true;
                    count--;
                }

                y++;
            }

            y = guards[i][1] - 1;
            while(y >= 0 && !grid[x][y].occupied) {
                if(!grid[x][y].garded) {
                    grid[x][y].garded = true;
                    count--;
                }

                y--;
            }
        }

        return count;
    }
};