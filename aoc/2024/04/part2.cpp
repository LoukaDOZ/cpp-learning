#include <iostream>
#include <fstream>
#include <vector>

#define LETTER_M 'M'
#define LETTER_A 'A'
#define LETTER_S 'S'

using namespace std;

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

long run(string file)
{
    vector<vector<char>> grid = readInput(file);
    long count = 0;
    int n = grid.size(), m = grid[0].size();

    for(int y = 1; y < n - 1; y++)
    {
        for(int x = 1; x < m - 1; x++)
        {
            if(grid[y][x] != LETTER_A)
                continue;

            char tl = grid[y - 1][x - 1];
            char tr = grid[y - 1][x + 1];
            char bl = grid[y + 1][x - 1];
            char br = grid[y + 1][x + 1];

            if(((tl == LETTER_M && br == LETTER_S) || (tl == LETTER_S && br == LETTER_M)) && ((tr == LETTER_M && bl == LETTER_S) || (tr == LETTER_S && bl == LETTER_M)))
                count++;
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

    cout << "----- AOC 2024 DAY 04 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}