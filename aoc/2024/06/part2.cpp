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

struct DirectedPos
{
    int x, y, dir;

    bool operator==(const DirectedPos &other) const
    {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

struct DirectedPosHash
{
    size_t operator()(const DirectedPos& p) const noexcept
    {
        return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1) ^ (hash<int>{}(p.dir) << 1);
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

vector<DirectedPos> patrol(Map map)
{
    vector<DirectedPos> path;
    Pos pos = map.guardPos;
    Dir dir = map.guardDir;

    while(isInBounds(map, pos))
    {
        Pos nextPos = pos;
        Dir nextDir = dir;
        path.push_back({pos.x, pos.y, dir});

        nextPos = move(nextPos, nextDir);
        while(map.obstacles.count(nextPos))
        {
            nextDir = rotate90(nextDir);
            nextPos = move(pos, nextDir);
        }

        pos = nextPos;
        dir = nextDir;
    }

    return path;
}

int run(string input)
{
    Map map = readInput(input);
    vector<DirectedPos> path = patrol(map);
    unordered_set<Pos, PosHash> ignoredObstacles;
    int count = 0;

    ignoredObstacles.insert(map.guardPos);

    for(int i = 1; i < path.size(); i++)
    {
        Pos pathPos = {path[i].x, path[i].y};

        if(!ignoredObstacles.insert(pathPos).second)
            continue;

        // Patrol again but with loop detection
        unordered_set<DirectedPos, DirectedPosHash> newPath(path.begin(), path.begin() + i - 1);
        Map mapCpy = map;
        DirectedPos dirPos = path[i - 1];

        mapCpy.obstacles.insert(pathPos);

        while(true)
        {
            Pos pos = {dirPos.x, dirPos.y};
            
            if(!isInBounds(mapCpy, pos))
                break;

            if(!newPath.insert(dirPos).second)
            {
                count++;
                break;
            }

            Dir nextDir = dirPos.dir;
            Pos nextPos = move(pos, nextDir);
            while(mapCpy.obstacles.count(nextPos))
            {
                nextDir = rotate90(nextDir);
                nextPos = move(pos, nextDir);
            }

            dirPos.x = nextPos.x;
            dirPos.y = nextPos.y;
            dirPos.dir = nextDir;
        }
    }

    return count;
}

int main()
{
    cout << "----- PART 2 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "(Go grab yourself a warm hot chocolate 'cause this is gonna take a while)" << endl;
    cout << "Input:\t " << run("inputs/input") << endl;

    return 0;
}