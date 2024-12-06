#include <iostream>
#include <fstream>
#include <vector>

#define EMPTY 0
#define GUARD_PASSED 1
#define WALL 2

using namespace std;

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
            default:
                row.push_back(EMPTY);
                break;
        }
    }

    stream.close();

    int n = grid.size();
    int m = grid[0].size();
    int count = 0;
    pair<int,int> nextPos;

    // Move guard
    while(isInBounds(n, m, guardPos)) {
        if(grid[guardPos.first][guardPos.second] == EMPTY) {
            grid[guardPos.first][guardPos.second] = GUARD_PASSED;
            count++;
        }

        nextPos = applyRotation(guardPos, guardDir);
        
        // Rotate guard
        while(isInBounds(n, m, nextPos) && grid[nextPos.first][nextPos.second] == WALL) {
            guardDir = rotate(guardDir);
            nextPos = applyRotation(guardPos, guardDir);
        }

        guardPos = nextPos;
    }

    cout << "Result : " << count << endl;
    return 0;
}