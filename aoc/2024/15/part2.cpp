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
#define CHAR_BOX_L '['
#define CHAR_BOX_R ']'
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
    int x = 0, y = 0;
    char c;

    while(true)
    {
        stream.get(c);

        if(c == '\n')
        {
            map.grid.push_back(row);
            row.clear();
            y++;

            stream.get(c);
            if(c == '\n')
                break;

            x = 0;
        }

        if(c == CHAR_ROBOT)
        {
            map.robot.x = x;
            map.robot.y = y;
            row.push_back(CHAR_ROBOT);
            row.push_back(CHAR_EMPTY);
        }
        else if(c == CHAR_EMPTY)
        {
            row.push_back(CHAR_EMPTY);
            row.push_back(CHAR_EMPTY);
        }
        else if(c == CHAR_BOX)
        {
            row.push_back(CHAR_BOX_L);
            row.push_back(CHAR_BOX_R);
        }
        else if(c == CHAR_WALL)
        {
            row.push_back(CHAR_WALL);
            row.push_back(CHAR_WALL);
        }
        
        x += 2;
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
    map.size.x = x;
    map.size.y = y;
    return map;
}

pos_t applyMovement(pos_t pos, int dir)
{
    return {pos.x + DIRECTIONS[dir].x, pos.y + DIRECTIONS[dir].y};
}

bool canMoveUpDown(map_t& map, pos_t pos, int dir)
{
    char c = map.grid[pos.y][pos.x];

    if(c == CHAR_EMPTY)
        return true;

    if(c == CHAR_WALL)
        return false;

    pos_t nextPos = applyMovement(pos, dir);

    if(c == CHAR_BOX_L)
    {
        pos_t boxR = {pos.x + 1, pos.y};
        pos_t boxRNext = applyMovement(boxR, dir);
        return canMoveUpDown(map, nextPos, dir) && canMoveUpDown(map, boxRNext, dir);
    }

    if(c == CHAR_BOX_R)
    {
        pos_t boxL = {pos.x - 1, pos.y};
        pos_t boxLNext = applyMovement(boxL, dir);
        return canMoveUpDown(map, nextPos, dir) && canMoveUpDown(map, boxLNext, dir);
    }

    return canMoveUpDown(map, nextPos, dir);
}

bool tryMoveUpDown(map_t& map, pos_t pos, int dir)
{
    char c = map.grid[pos.y][pos.x];

    if(c == CHAR_EMPTY)
        return true;

    if(c == CHAR_WALL)
        return false;

    bool canMove;
    pos_t nextPos = applyMovement(pos, dir);

    if(c == CHAR_BOX_L)
    {
        pos_t boxR = {pos.x + 1, pos.y};
        pos_t boxRNext = applyMovement(boxR, dir);
        canMove = tryMoveUpDown(map, nextPos, dir) && tryMoveUpDown(map, boxRNext, dir);

        if(canMove)
        {
            map.grid[boxRNext.y][boxRNext.x] = map.grid[boxR.y][boxR.x];
            map.grid[boxR.y][boxR.x] = CHAR_EMPTY;
        }
    }
    else if(c == CHAR_BOX_R)
    {
        pos_t boxL = {pos.x - 1, pos.y};
        pos_t boxLNext = applyMovement(boxL, dir);
        canMove = tryMoveUpDown(map, nextPos, dir) && tryMoveUpDown(map, boxLNext, dir);

        if(canMove)
        {
            map.grid[boxLNext.y][boxLNext.x] = map.grid[boxL.y][boxL.x];
            map.grid[boxL.y][boxL.x] = CHAR_EMPTY;
        }
    }
    else
        canMove = tryMoveUpDown(map, nextPos, dir);
    
    if(canMove)
    {
        map.grid[nextPos.y][nextPos.x] = map.grid[pos.y][pos.x];
        map.grid[pos.y][pos.x] = CHAR_EMPTY;
        return true;
    }

    return false;
}

bool tryMoveRightLeft(map_t& map, pos_t pos, int dir)
{
    char c = map.grid[pos.y][pos.x];

    if(c == CHAR_EMPTY)
        return true;

    if(c == CHAR_WALL)
        return false;

    pos_t nextPos = applyMovement(pos, dir);

    if(tryMoveRightLeft(map, nextPos, dir))
    {
        map.grid[nextPos.y][nextPos.x] = map.grid[pos.y][pos.x];
        map.grid[pos.y][pos.x] = CHAR_EMPTY;
        return true;
    }

    return false;
}

bool tryMove(map_t& map, int move)
{
    if(move == RIGHT || move == LEFT)
        return tryMoveRightLeft(map, map.robot, move);

    if(canMoveUpDown(map, map.robot, move))
    {
        tryMoveUpDown(map, map.robot, move);
        return true;
    }

    return false;
}

void simulate(map_t& map)
{
    for(const int move: map.moves)
    {
        if(tryMove(map, move))
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
            if(map.grid[i][j] == CHAR_BOX_L)
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

    cout << "----- AOC 2024 DAY 15 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}