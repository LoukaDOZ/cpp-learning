#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define CHAR_START 'S'
#define CHAR_END 'E'
#define CHAR_WALL '#'
#define CHAR_EMPTY '.'

#define MOVE_SCORE 1
#define ROTATE_SCORE 1000

using namespace std;

struct pos_t
{
    int x, y;
};

struct dir_pos_t
{
    pos_t pos;
    int dir;
};

struct map_t
{
    vector<vector<char>> grid;
    pos_t size;
    pos_t start;
    pos_t end;

    bool isInBounds(pos_t& pos)
    {
        return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
    }

    bool isReachable(pos_t& pos)
    {
        return isInBounds(pos) && grid[pos.y][pos.x] != CHAR_WALL;
    }

    bool isEnd(pos_t& pos)
    {
        return pos.x == end.x && pos.y == end.y;
    }
};

const pos_t DIRECTIONS[4] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

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

    while(!stream.eof())
    {
        stream.get(c);

        if(c == '\n')
        {
            map.grid.push_back(row);
            row.clear();

            stream.get(c);
        }

        if(c == CHAR_START)
        {
            map.start.x = row.size();
            map.start.y = map.grid.size();
        } else if(c == CHAR_END)
        {
            map.end.x = row.size();
            map.end.y = map.grid.size();
        }
        
        row.push_back(c);
    }

    map.grid.push_back(row);
    stream.close();
    map.size.x = map.grid[0].size();
    map.size.y = map.grid.size();
    return map;
}

long bestScore(map_t& map)
{
    vector<vector<long>> scores(map.size.y, vector<long>(map.size.x, -1));
    queue<pair<dir_pos_t, long>> queue;
    queue.push({{{map.start.x, map.start.y}, 1}, 0});

    while(!queue.empty())
    {
        pair<dir_pos_t, long> p = queue.front();
        dir_pos_t pos = p.first;
        long score = p.second;
        queue.pop();

        if(scores[pos.pos.y][pos.pos.x] >= 0 && score >= scores[pos.pos.y][pos.pos.x])
            continue;

        scores[pos.pos.y][pos.pos.x] = score;

        vector<pair<int, int>> next_dir = {
            {pos.dir, MOVE_SCORE},
            {(pos.dir + 1) % 4, MOVE_SCORE + ROTATE_SCORE},
            {(pos.dir + 4 - 1) % 4, MOVE_SCORE + ROTATE_SCORE}
        };

        for(pair<int, int> dir : next_dir)
        {
            dir_pos_t next_pos = {{pos.pos.x + DIRECTIONS[dir.first].x, pos.pos.y + DIRECTIONS[dir.first].y}, dir.first};
            long next_score = score + dir.second;

            if(map.isReachable(next_pos.pos))
                queue.push({next_pos, next_score});
        }
    }

    return scores[map.end.y][map.end.x];
}

long run(string file)
{
    map_t map = readInput(file);
    return bestScore(map);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 16 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}