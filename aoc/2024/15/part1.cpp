#include <iostream>
#include <fstream>
#include <vector>

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define CHAR_UP '^'
#define CHAR_DOWN 'v'
#define CHAR_RIGHT '>'
#define CHAR_LEFT '<'
#define CHAR_ROBOT '@'
#define CHAR_BOX 'O'
#define CHAR_WALL '#'
#define CHAR_EMPTY '.'

using namespace std;

struct pos_t
{
    int x, y;
};

struct map_t
{
    vector<vector<char>> grid;
    vector<short> moves;
    pos_t size;
    pos_t robot;
};

const pos_t DIRECTIONS[4] = {{0,-1}, {0,1}, {1,0}, {-1,0}};

map_t readInput(string file)
{
    ifstream stream(file);
    map_t map;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return map;
    }

    vector<char> row;
    char c;

    while(true)
    {
        stream.get(c);

        if(c == '\n')
        {
            map.grid.push_back(row);
            row.clear();

            stream.get(c);
            if(c == '\n')
                break;
        }

        if(c == CHAR_ROBOT)
        {
            map.robot.x = row.size();
            map.robot.y = map.grid.size();
        }
        
        row.push_back(c);
    }

    while(stream >> c)
    {
        switch(c)
        {
            case CHAR_UP:
                map.moves.push_back(0);
                break;
            case CHAR_DOWN:
                map.moves.push_back(1);
                break;
            case CHAR_RIGHT:
                map.moves.push_back(2);
                break;
            case CHAR_LEFT:
                map.moves.push_back(3);
                break;
        }
    }

    stream.close();
    map.size.x = map.grid[0].size();
    map.size.y = map.grid.size();
    return map;
}

pos_t applyMovement(pos_t pos, int dir)
{
    return {pos.x + DIRECTIONS[dir].x, pos.y + DIRECTIONS[dir].y};
}

bool tryMove(map_t& map, pos_t pos, int dir)
{
    char c = map.grid[pos.y][pos.x];

    if(c == CHAR_EMPTY)
        return true;

    if(c == CHAR_WALL)
        return false;

    pos_t nextPos = applyMovement(pos, dir);

    if(tryMove(map, nextPos, dir))
    {
        map.grid[nextPos.y][nextPos.x] = map.grid[pos.y][pos.x];
        map.grid[pos.y][pos.x] = CHAR_EMPTY;
        return true;
    }

    return false;
}

void simulate(map_t& map)
{
    for(const int move: map.moves)
    {
        if(tryMove(map, map.robot, move))
            map.robot = applyMovement(map.robot, move);
    }
}

long sumGPS(map_t& map)
{
    long sum = 0;

    for(int i = 0; i < map.size.y; i++)
    {
        for(int j = 0; j < map.size.x; j++)
        {
            if(map.grid[i][j] == CHAR_BOX)
                sum += i * 100 + j;
        }
    }

    return sum;
}

long run(string file)
{
    map_t map = readInput(file);
    simulate(map);
    return sumGPS(map);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 15 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}