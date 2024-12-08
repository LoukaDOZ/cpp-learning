#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#define EMPTY 4
#define GUARD_PASSED 1
#define WALL 5

using namespace std;

const char AAA[7] = {'^', '>', 'v', '<', '.', '#', 'O'};
const vector<pair<int,int>> DIRECTIONS = {{-1,0}, {0,1}, {1,0}, {0,-1}};

int rotate(int currentDir) {
    return currentDir == 3 ? 0 : currentDir + 1;
}

pair<int,int> applyRotation(pair<int,int>& pos, int dir) {
    return {pos.first + DIRECTIONS[dir].first, pos.second + DIRECTIONS[dir].second};
}

bool isInBounds(int n, int m, pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m;
}

void printg(vector<vector<int>>& grid) {
    for(vector<int> r: grid) {
        for(int i: r) {
            cout << AAA[i];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ifstream stream("inputs/input");
    vector<vector<int>> grid;
    vector<int> row;
    pair<int,int> guardPos;
    int guardDir;
    char c;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    // Build grid
    while(true) {
        stream.get(c);

        if(stream.eof())
            break;

        switch(c) {
            case '#':
                row.push_back(WALL);
                break;
            case '\n':
                grid.push_back(row);
                row.clear();
                break;
            case '^':
                guardPos = {grid.size(), row.size()};
                guardDir = 0;
                row.push_back(guardDir);
                break;
            default:
                row.push_back(EMPTY);
                break;
        }
    }

    stream.close();

    int n = grid.size();
    int m = grid[0].size();
    pair<int,int> nextPos;
    unordered_map<int, unordered_set<int>> path;
    unordered_set<int> sss;
    int count = 0;

    // Move guard
    while(isInBounds(n, m, guardPos)) {
        grid[guardPos.first][guardPos.second] = guardDir;
        path[guardPos.first * n + guardPos.second].insert(guardDir);

        nextPos = applyRotation(guardPos, guardDir);
        pair<int,int> wp = nextPos;
        cout << "TEST: " << nextPos.first << ',' << nextPos.second << endl;
        
        if(isInBounds(n, m, nextPos) && grid[nextPos.first][nextPos.second] != WALL) {
            int newDir = rotate(guardDir);
            nextPos = applyRotation(guardPos, newDir);

            while(isInBounds(n, m, nextPos) && grid[nextPos.first][nextPos.second] != WALL) {
                cout << "CHECK: " << nextPos.first << ',' << nextPos.second << endl;
                if(path[nextPos.first * n + nextPos.second].count(newDir)) {
                    cout << '{' << nextPos.first << ',' << nextPos.second << "}(" << AAA[newDir] << ')' << endl;
                    count++;

                    int a = grid[wp.first][wp.second];
                    grid[wp.first][wp.second] = 6;
                    printg(grid);
                    grid[wp.first][wp.second] = a;
                    break;
                }
                
                nextPos = applyRotation(nextPos, newDir);
            }
            cout << "END CHECK" << endl << endl;
        }

        nextPos = applyRotation(guardPos, guardDir);
        
        // Rotate guard
        while(isInBounds(n, m, nextPos) && grid[nextPos.first][nextPos.second] == WALL) {
            guardDir = rotate(guardDir);
            nextPos = applyRotation(guardPos, guardDir);
        }

        guardPos = nextPos;
    }
    printg(grid);
    
    cout << "Result : " << count << endl;
    return 0;
}