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

Map readInput(string file) {
    ifstream stream(file);
    Map map;
    int x = 0, y = 0;

    while(true) {
        string line;

        getline(stream, line);
        if(line.empty())
            break;

        stringstream sstream(line);
        char c;
        y = 0;

        while(sstream >> c) {
            if(c == '#')
                map.obstacles.insert({x,y});
            else if(c == '^') {
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

void debugMap(Map map, unordered_set<DirectedPos, DirectedPosHash> path) {
    cout << map.n << ' ' << map.m << endl;
    for(int i = 0; i < map.n; i++) {
        for(int j = 0; j < map.m; j++) {
            if(path.count({i,j,UP}))
                cout << '^';
            else if(path.count({i,j,DOWN}))
                cout << 'v';
            else if(path.count({i,j,LEFT}))
                cout << '<';
            else if(path.count({i,j,RIGHT}))
                cout << '>';
            else if(map.obstacles.count({i,j}))
                cout << "#";
            else if(map.guardPos.x == i && map.guardPos.y == j)
                cout << "^";
            else
                cout << ".";
        }
        cout << endl;
    }
}

bool isInBounds(Map map, Pos pos) {
    return pos.x >= 0 && pos.x < map.n && pos.y >= 0 && pos.y < map.m;
}

int rotate90(Dir dir) {
    if(dir == LEFT)
        return UP;
    
    return dir + 1;
}

Pos move(Pos pos, Dir dir) {
    switch(dir) {
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

unordered_set<Pos, PosHash> patrol(Map map) {
    unordered_set<Pos, PosHash> path;
    Pos pos = map.guardPos;
    Dir dir = map.guardDir;

    while(isInBounds(map, pos)) {
        Pos nextPos = pos;
        Dir nextDir = dir;
        path.insert(pos);

        nextPos = move(nextPos, nextDir);
        while(map.obstacles.count(nextPos)) {
            nextDir = rotate90(nextDir);
            nextPos = move(pos, nextDir);
        }

        pos = nextPos;
        dir = nextDir;
    }

    return path;
}

int part1(string input) {
    Map map = readInput(input);
    return patrol(map).size();
}

int part2(string input) {
    Map map = readInput(input);
    unordered_set<Pos, PosHash> path = patrol(map);
    path.erase(map.guardPos);
    int count = 0;
    int i = 0;

    for(Pos pathPos: path) {
        Map mapCpy = map;
        mapCpy.obstacles.insert(pathPos);

        // Patrol again but with loop detection
        unordered_set<DirectedPos, DirectedPosHash> newPath;
        Pos pos = mapCpy.guardPos;
        Dir dir = mapCpy.guardDir;

        while(isInBounds(mapCpy, pos)) {
            Pos nextPos = pos;
            Dir nextDir = dir;

            DirectedPos nextDirPos = {pos.x, pos.y, dir};
            if(!newPath.insert(nextDirPos).second) {
                count++;
                break;
            }

            nextPos = move(nextPos, nextDir);
            while(mapCpy.obstacles.count(nextPos)) {
                nextDir = rotate90(nextDir);
                nextPos = move(pos, nextDir);
            }

            pos = nextPos;
            dir = nextDir;
        }
        i++;
    }

    return count;
}

int main()
{
    cout << "----- PART 1 -----" << endl;
    cout << "Example: " << part1("inputs/example") << endl;
    cout << "Input:\t " << part1("inputs/input") << endl;

    cout << endl << "----- PART 2 -----" << endl;
    cout << "Example: " << part2("inputs/example") << endl;
    cout << "(Go make yourself a warm hot chocolate cause this is gonna take a while)" << endl;
    cout << "Input:\t " << part2("inputs/input") << endl;

    return 0;
}