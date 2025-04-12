#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

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

    bool operator==(const pos_t& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct PosHash
{
    size_t operator()(const pos_t& p) const noexcept
    {
        return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1);
    }
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

struct path_t
{
    unordered_set<pos_t, PosHash> path;
    dir_pos_t pos;
    int moves;
    int rotates;
};

const int DIRECTIONS_SIZE = 4;
const pos_t DIRECTIONS[DIRECTIONS_SIZE] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

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

vector<path_t> getPaths(map_t& map)
{
    vector<path_t> paths;
    queue<path_t> queue;
    queue.push({{}, {map.start.x, map.start.y, 1}, 0, 0});

    while(!queue.empty())
    {
        path_t path = queue.front();
        queue.pop();

        path.path.insert(path.pos.pos);

        cout << "PATH(" << path.pos.pos.x << ", " << path.pos.pos.y << ", " << path.pos.dir << ", " << path.moves << ", " << path.rotates << ")" << endl;

        if(map.isEnd(path.pos.pos))
        {
            paths.push_back(path);
            continue;
        }

        // Clockwise
        int dir = (path.pos.dir + 1) % 4;
        pos_t newPos = {path.pos.pos.x + DIRECTIONS[dir].x, path.pos.pos.y + DIRECTIONS[dir].y};

        if(map.isReachable(newPos) && !path.path.count(newPos))
            queue.push({unordered_set<pos_t, PosHash>(path.path), {newPos, dir}, path.moves + 1, path.rotates + 1});

        // Counterclockwise
        dir = (path.pos.dir + 4 - 1) % 4;
        newPos = {path.pos.pos.x + DIRECTIONS[dir].x, path.pos.pos.y + DIRECTIONS[dir].y};

        if(map.isReachable(newPos) && !path.path.count(newPos))
            queue.push({unordered_set<pos_t, PosHash>(path.path), {newPos, dir}, path.moves + 1, path.rotates + 1});

        // Forward
        newPos = {path.pos.pos.x + DIRECTIONS[path.pos.dir].x, path.pos.pos.y + DIRECTIONS[path.pos.dir].y};

        if(map.isReachable(newPos) && !path.path.count(newPos))
        {
            path.pos.pos = newPos;
            path.moves += 1;
            queue.push(path);
        }
    }

    return paths;
}

bool sortPaths(path_t& a, path_t& b)
{
    return (a.moves * MOVE_SCORE + a.rotates * ROTATE_SCORE) < (b.moves * MOVE_SCORE + b.rotates * ROTATE_SCORE);
}

vector<vector<long>> getScores(map_t& map)
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

    return scores;
}

int distance(pos_t& a, pos_t& b, int dir)
{
    return abs((b.x - a.x) * DIRECTIONS[dir].x + (b.y - a.y) * DIRECTIONS[dir].y);
}

int countPlaces(map_t& map)
{
    vector<vector<long>> scores = getScores(map);
    unordered_set<pos_t, PosHash> places;
    queue<dir_pos_t> queue;

    for(int i = 0; i < DIRECTIONS_SIZE; i++)
        queue.push({map.end, i});

    while(!queue.empty())
    {
        dir_pos_t pos = queue.front();
        places.insert(pos.pos);
        queue.pop();

        pos_t next = {pos.pos.x, pos.pos.y};
        while(true)
        {
            next.x += DIRECTIONS[pos.dir].x;
            next.y += DIRECTIONS[pos.dir].y;
            int dist = distance(pos.pos, next, pos.dir);

            if(map.isReachable(next) && scores[next.y][next.x] <= scores[pos.pos.y][pos.pos.x] - dist)
            {
                int clockwise_dir = (pos.dir + 1) % DIRECTIONS_SIZE;
                int counterclockwise_dir = (pos.dir + 4 - 1) % DIRECTIONS_SIZE;
                dir_pos_t clockwise = {{next.x + DIRECTIONS[clockwise_dir].x, next.y + DIRECTIONS[clockwise_dir].y}, clockwise_dir};
                dir_pos_t counterclockwise = {{next.x + DIRECTIONS[counterclockwise_dir].x, next.y + DIRECTIONS[counterclockwise_dir].y}, counterclockwise_dir};
                places.insert(next);

                if(map.isReachable(clockwise.pos) && scores[clockwise.pos.y][clockwise.pos.x] == scores[next.y][next.x] - MOVE_SCORE)
                    queue.push(clockwise);

                if(map.isReachable(counterclockwise.pos) && scores[counterclockwise.pos.y][counterclockwise.pos.x] == scores[next.y][next.x] - MOVE_SCORE)
                    queue.push(counterclockwise);
            }
            else break;
        }
    }

    return places.size();
}

int run(string file)
{
    map_t map = readInput(file);
    return countPlaces(map);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 16 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}