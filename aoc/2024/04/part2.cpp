#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream stream("inputs/input");
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

    for(int y = 1; y < n - 1; y++) {
        for(int x = 1; x < m - 1; x++) {
            if(grid[y][x] != 'A')
                continue;

            char tl = grid[y - 1][x - 1];
            char tr = grid[y - 1][x + 1];
            char bl = grid[y + 1][x - 1];
            char br = grid[y + 1][x + 1];

            if(((tl == 'M' && br == 'S') || (tl == 'S' && br == 'M')) && ((tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M')))
                count++;
        }
    }

    cout << "X-MAS appears " << count << " times" << endl;
    return 0;
}