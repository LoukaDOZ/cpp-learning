#include <iostream>
#include <fstream>
#include <vector>

#define XMAS_SIZE 4

using namespace std;

const vector<pair<int,int>> DIRECTIONS = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
const char XMAS[XMAS_SIZE] = {'X', 'M', 'A', 'S'};

vector<vector<char>> readInput(string file)
{
    ifstream stream(file);
    vector<vector<char>> grid;
    vector<char> row;
    char c;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return grid;
    }

    while(true)
    {
        stream.get(c);

        if(stream.eof())
            break;

        if(c == '\n')
        {
            grid.push_back(row);
            row.clear();
        }
        else
            row.push_back(c);
        
    }

    if(!row.empty())
        grid.push_back(row);

    stream.close();
    return grid;
}

bool hasXMAS(vector<vector<char>>& grid, int x, int y, pair<int,int>& dir)
{
    int n = grid.size(), m = grid[0].size();

    for(int i = 0; i < XMAS_SIZE; i++)
    {
        if(x < 0 || y >= m || y < 0 || y >= n || grid[y][x] != XMAS[i])
            return false;

        x += dir.first;
        y += dir.second;
    }

    return true;
}

long run(string file)
{
    vector<vector<char>> grid = readInput(file);
    long count = 0;
    int n = grid.size(), m = grid[0].size();

    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < m; x++)
        {
            for(pair<int,int> dir: DIRECTIONS)
            {
                if(hasXMAS(grid, x, y, dir))
                    count++;
            }
        }
    }

    return count;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 04 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}