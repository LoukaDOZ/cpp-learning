#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream stream("inputs/input");
    vector<vector<pair<int,int>>> directions = {
        {{0,0}, {0,1}, {0,2}, {0,3}},
        {{0,0}, {0,-1}, {0,-2}, {0,-3}},
        {{0,0}, {1,0}, {2,0}, {3,0}},
        {{0,0}, {-1,0}, {-2,0}, {-3,0}},
        {{0,0}, {1,1}, {2,2}, {3,3}},
        {{0,0}, {1,-1}, {2,-2}, {3,-3}},
        {{0,0}, {-1,1}, {-2,2}, {-3,3}},
        {{0,0}, {-1,-1}, {-2,-2}, {-3,-3}}
    };
    char XMAS[4] = {'X', 'M', 'A', 'S'};

    vector<vector<char>> grid;
    vector<char> row;
    long count = 0;
    int n, m;
    char c;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(true) {
        stream.get(c);

        if(stream.eof())
            break;
        else if(c == '\n') {
            grid.push_back(row);
            row.clear();
        } else
            row.push_back(c);
    }

    stream.close();
    n = grid.size();
    m = grid[0].size(); 

    for(int y = 0; y < n; y++) {
        for(int x = 0; x < m; x++) {
            for(vector<pair<int,int>> direction: directions) {
                bool ok = true;

                for(int i = 0; i < 4; i++) {
                    pair<int,int> dir = direction[i];
                    int px = x + dir.first;
                    int py = y + dir.second;

                    if(px < 0 || px >= m || py < 0 || py >= n || grid[py][px] != XMAS[i]) {
                        ok = false;
                        break;
                    }
                }

                if(ok)
                    count++;
            }
        }
    }

    cout << "XMAS appears " << count << " times" << endl;
    return 0;
}