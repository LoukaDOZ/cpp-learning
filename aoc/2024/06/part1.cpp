#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <chrono>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

using Dir = int;

struct Pos
{
    int x, y;

    bool operator==(const Pos &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct PosHash
{
    size_t operator()(const Pos& p) const noexcept
    {
        return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1);
    }
};

struct Map
{
    int n, m;
    Dir guardDir;
    Pos guardPos;
    unordered_set<Pos, PosHash> obstacles;
};

Map readInput(string file)
{
    ifstream stream(file);
    Map map;
    int x = 0, y = 0;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return map;
    }

    while(true)
    {
        string line;

        getline(stream, line);
        if(line.empty())
            break;

        stringstream sstream(line);
        char c;
        y = 0;

        while(sstream >> c)
        {
            if(c == '#')
                map.obstacles.insert({x,y});
            else if(c == '^')
            {
                map.guardPos = {x, y};
                map.guardDir = UP;
            }

            y++;
        }
        
        x++;
    }

    stream.close();
    map.n = x;
    map.m = y;
    return map;
}

bool isInBounds(Map map, Pos pos)
{
    return pos.x >= 0 && pos.x < map.n && pos.y >= 0 && pos.y < map.m;
}

int rotate90(Dir dir)
{
    if(dir == LEFT)
        return UP;
    
    return dir + 1;
}

Pos move(Pos pos, Dir dir)
{
    switch(dir)
    {
        case UP:
            return {pos.x - 1, pos.y};
        case DOWN:
            return {pos.x + 1, pos.y};
        case RIGHT:
            return {pos.x, pos.y + 1};
        case LEFT:
        default:
            return {pos.x, pos.y - 1};
    }
}

int patrol(Map map)
{
    unordered_set<Pos, PosHash> path;
    Pos pos = map.guardPos;
    Dir dir = map.guardDir;

    while(isInBounds(map, pos))
    {
        Pos nextPos = pos;
        Dir nextDir = dir;
        path.insert(pos);

        nextPos = move(nextPos, nextDir);
        while(map.obstacles.count(nextPos))
        {
            nextDir = rotate90(nextDir);
            nextPos = move(pos, nextDir);
        }

        pos = nextPos;
        dir = nextDir;
    }

    return path.size();
}

int run(string input)
{
    return patrol(readInput(input));
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 06 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}