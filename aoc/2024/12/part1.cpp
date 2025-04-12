#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const pair<int,int> DIRECTIONS[4] = {{0,-1}, {0, 1}, {1, 0}, {-1, 0}};

struct pairHashFunction 
{ 
    size_t operator()(const pair<int,int> &x) const
    { 
        return x.first ^ x.second; 
    } 
}; 

struct Map
{
    vector<vector<char>> map;
    int n, m;

    char at(int x, int y)
    {
        return map[x][y];
    }

    char at(pair<int,int> pos)
    {
        return at(pos.first, pos.second);
    }

    bool isInBounds(int x, int y)
    {
        return x >= 0 && x < n && y >= 0 && y < m;
    }

    bool isInBounds(pair<int,int> pos)
    {
        return isInBounds(pos.first, pos.second);
    }
};

struct Region
{
    int area, perimeter;
};

using pair_set = unordered_set<pair<int,int>, pairHashFunction>;

Map readInput(string file)
{
    ifstream stream(file);
    Map map;
    vector<vector<char>> grid;

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
        vector<char> row;
        char c;

        while(sstream >> c)
            row.push_back(c);

        grid.push_back(row);
    }

    stream.close();
    map.map = grid;
    map.n = grid.size();
    map.m = grid[0].size();
    return map;
}

Region buildRegion(pair_set& plots)
{
    int area = 0, perimeter = 0;

    for(pair<int,int> plot: plots)
    {
        int count = 0;

        for(pair<int,int> dir: DIRECTIONS)
            count += plots.count({plot.first + dir.first, plot.second + dir.second});

        perimeter += 4 - count;
        area++;
    }

    return {area, perimeter};
}

vector<Region> getRegions(Map& map)
{
    vector<Region> regions;

    for(int i = 0; i < map.n; i++)
    {
        for(int j = 0; j < map.m; j++)
        {
            char c = map.at(i,j);

            if(c == '.')
                continue;

            pair_set plots;
            queue<pair<int,int>> queue;
            queue.push({i,j});

            while(!queue.empty())
            {
                pair<int,int> pos = queue.front();
                queue.pop();

                if(!map.isInBounds(pos) || map.at(pos) != c || !plots.insert(pos).second)
                    continue;

                map.map[pos.first][pos.second] = '.';

                for(pair<int,int> dir: DIRECTIONS)
                    queue.push({pos.first + dir.first, pos.second + dir.second});
            }

            regions.push_back(buildRegion(plots));
        }
    }

    return regions;
}

int fencing(vector<Region>& regions)
{
    int sum = 0;

    for(Region region: regions)
        sum += region.area * region.perimeter;

    return sum;
}

int run(string file)
{
    Map map = readInput(file);
    vector<Region> regions  = getRegions(map);
    return fencing(regions);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 12 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}