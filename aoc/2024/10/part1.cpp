#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>

#define START 0
#define END 9

using namespace std;

struct Coord {
    int x, y;

    bool operator==(const Coord &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct CoordHash
{
    size_t operator()(const Coord& c) const noexcept
    {
        return hash<int>{}(c.x) ^ (hash<int>{}(c.y) << 1);
    }
};

class Map
{
    private:
    const Coord m_directions[4] = {{-1, 0}, {1, 0}, {0, 1},  {0, -1}};
    vector<vector<int>> m_map;
    int m_n, m_m;

    public:
    Map(vector<vector<int>> map)
    {
        m_map = map;
        m_n = map.size();
        m_m = map[0].size();
    }

    int n() const
    {
        return m_n;
    }

    int m() const
    {
        return m_m;
    }

    bool isInBounds(Coord c) const
    {
        return c.x >= 0 && c.x < m_n && c.y >= 0 && c.y < m_m;
    }

    int at(Coord c) const {
        return m_map[c.x][c.y];
    }

    bool isEnd(Coord c) const {
        return at(c) == END;
    }

    vector<Coord> getStarts() const
    {
        vector<Coord> starts;

        for(int i = 0; i < m_n; i++)
        {
            for(int j = 0; j < m_m; j++)
            {
                if(m_map[i][j] == START)
                    starts.push_back({i,j});
            }
        }

        return starts;
    }

    vector<Coord> getNeighbours(Coord c) const
    {
        vector<Coord> neighbours;

        for(Coord dir: m_directions)
        {
            Coord neighbour = {c.x + dir.x, c.y + dir.y};

            if(isInBounds(neighbour) && m_map[neighbour.x][neighbour.y] == m_map[c.x][c.y] + 1)
                neighbours.push_back(neighbour);
        }

        return neighbours;
    }
};

Map readInput(string file)
{
    ifstream stream(file);
    vector<vector<int>> map;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return map;
    }

    string line;
    while(!stream.eof())
    {
        getline(stream, line);
        if(line.empty())
            break;

        stringstream sstream(line);
        vector<int> row;
        char c;

        while(sstream >> c)
            row.push_back(c - '0');

        map.push_back(row);
    }

    stream.close();
    return Map(map);
}

int doHikingTrail(Map map, Coord start)
{
    int count = 0;
    unordered_set<Coord, CoordHash> excludedEnds;
    queue<Coord> queue;
    queue.push(start);

    while(!queue.empty())
    {
        Coord c = queue.front();
        queue.pop();

        if(map.isEnd(c))
        {
            if(excludedEnds.insert(c).second)
                count++;

            continue;
        }

        for(Coord neighbour: map.getNeighbours(c))
            queue.push(neighbour);
    }

    return count;
}

long run(string file)
{
    Map map = readInput(file);
    int sum = 0;

    for(Coord start: map.getStarts())
        sum += doHikingTrail(map, start);

    return sum;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 10 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}