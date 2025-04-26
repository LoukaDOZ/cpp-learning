#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

#define POS_0 0
#define EMPTY -1
#define CORRUPTED -2

using namespace std;

struct pos_t
{
    int x, y;

    bool operator==(const pos_t& p) const
    { 
        return p.x == x && p.y == y; 
    }
};

struct grid_t
{
    vector<vector<int>> grid;
    int size;

    bool isValid(const pos_t& pos) const
    {
        return pos.x >= 0 && pos.x < size && pos.y >= 0 && pos.y < size && grid[pos.x][pos.y] != CORRUPTED;
    }
};

const pos_t DIRECTIONS[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vector<pos_t> readInput(string file)
{
    ifstream stream(file);
    vector<pos_t> fallingBytes;
    string line;
    int commaPos;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return fallingBytes;
    }

    while(!stream.eof())
    {
        getline(stream, line);

        if(line.empty())
            break;

        commaPos = line.find(',');
        fallingBytes.push_back(
            {
                stoi(line.substr(0, commaPos)),
                stoi(line.substr(commaPos + 1, line.size() - 1))
            }
        );
    }
    
    stream.close();
    return fallingBytes;
}

grid_t createGrid(const vector<pos_t>& fallingBytes, int memorySpace, int byteSize)
{
    grid_t grid = {vector(memorySpace + 1, vector(memorySpace + 1, EMPTY)), memorySpace + 1};
    int n = fallingBytes.size();

    for(int i = 0; i < n && i < byteSize; i++)
        grid.grid[fallingBytes[i].x][fallingBytes[i].y] = CORRUPTED;

    return grid;
}

int shortestPath(const vector<pos_t>& fallingBytes, int memorySpace, int byteSize)
{
    grid_t grid = createGrid(fallingBytes, memorySpace, byteSize);
    pos_t exit = {memorySpace, memorySpace};
    queue<pos_t> queue;

    queue.push({POS_0, POS_0});
    grid.grid[POS_0][POS_0] = 0;

    while(!queue.empty())
    {
        const pos_t pos = queue.front();
        queue.pop();

        if(pos == exit)
            continue;

        for(const pos_t& dir : DIRECTIONS)
        {
            const pos_t next = {pos.x + dir.x, pos.y + dir.y};

            if(!grid.isValid(next) || (grid.grid[next.x][next.y] != EMPTY && grid.grid[next.x][next.y] <= grid.grid[pos.x][pos.y] + 1))
                continue;

            grid.grid[next.x][next.y] = grid.grid[pos.x][pos.y] + 1;
            queue.push(next);
        }
    }

    return grid.grid[exit.x][exit.y];
}

int run(string file, int memorySpace, int byteSize)
{
    const vector<pos_t> fallingBytes = readInput(file);
    return shortestPath(fallingBytes, memorySpace, byteSize);
}

pair<int,int> askParams(string filename)
{
    int space = -1;
    int bytes = -1;

    while(space < 0)
    {
        cout << '[' << filename << "] Enter puzzle space and byte size as \"<space> <bytes>\" :" << endl;
        cin >> space;
        cin >> bytes;
    }

    return {space, bytes};
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 18 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
    {
        const pair<int,int> params = askParams(argv[i]);
        cout << argv[i] << ": " << run(argv[i], params.first, params.second) << endl;
    }

    return 0;
}