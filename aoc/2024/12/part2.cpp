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
    int area, faces;
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

int cornerCount(pair_set& plots, pair<int,int> pos)
{
    int topLeft = plots.count(pos);
    int topRight = plots.count({pos.first, pos.second + 1});
    int bottomLeft = plots.count({pos.first + 1, pos.second});
    int bottomRight = plots.count({pos.first + 1, pos.second + 1});
    int count = topLeft + topRight + bottomLeft + bottomRight;

    if(count == 1 || count == 3)
        return 1;

    if(count == 2 && ((topLeft && bottomRight) || (topRight && bottomLeft)))
        return 2;

    return 0;
}

Region buildRegion(pair_set& plots)
{
    pair_set excluded;
    int area = 0, corners = 0;

    for(pair<int,int> plot: plots)
    {
        pair<int,int> tl = {plot.first - 1, plot.second - 1};
        pair<int,int> tr = {plot.first - 1, plot.second};
        pair<int,int> bl = {plot.first, plot.second - 1};
        pair<int,int> br = plot;

        if(excluded.insert(tl).second)
            corners += cornerCount(plots, tl);

        if(excluded.insert(tr).second)
            corners += cornerCount(plots, tr);

        if(excluded.insert(bl).second)
            corners += cornerCount(plots, bl);

        if(excluded.insert(br).second)
            corners += cornerCount(plots, br);

        area++;
    }

    return {(int) plots.size(), corners};
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
        sum += region.area * region.faces;

    return sum;
}

int run(string file)
{
    Map map = readInput(file);
    vector<Region> regions = getRegions(map);
    return fencing(regions);
}

int main()
{
    cout << "----- PART 2 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;
    return 0;
}