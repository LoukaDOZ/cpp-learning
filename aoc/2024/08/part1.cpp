#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct scan_t
{
    map<char, vector<pair<int,int>>> antennas;
    int n, m;

    bool isInBounds(pair<int,int>& pos)
    {
        return pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m;
    }
};

scan_t readInput(string file)
{
    ifstream stream(file);
    scan_t scan = {{}, 0, 0};
    string line;
    int n = 0, m = 0;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return scan;
    }

    while(!stream.eof())
    {
        getline(stream, line);

        if(line.empty())
            continue;

        scan.m = line.size();

        for(int i = 0; i < scan.m; i++)
        {
            if(line[i] != '.')
                scan.antennas[line[i]].push_back({scan.n, i});
        }

        scan.n++;
    }

    stream.close();
    return scan;
}

int run(string file)
{
    scan_t scan = readInput(file);
    set<pair<int,int>, greater<pair<int,int>>> antinodes;
    int count = 0;

    for(pair<char,vector<pair<int,int>>> a: scan.antennas)
    {
        for(pair<int,int> antenna: a.second)
        {
            for(pair<int,int> antenna2: a.second)
            {
                if(antenna == antenna2)
                    continue;

                int disty = antenna.first - antenna2.first;
                int distx = antenna.second - antenna2.second;
                pair<int,int> antinode1 = {antenna.first + disty, antenna.second + distx};
                pair<int,int> antinode2 = {antenna2.first - disty, antenna2.second - distx};

                if(scan.isInBounds(antinode1) && !antinodes.count(antinode1))
                {
                    count++;
                    antinodes.insert(antinode1);
                }

                if(scan.isInBounds(antinode2) && !antinodes.count(antinode2))
                {
                    count++;
                    antinodes.insert(antinode2);
                }
            }
        }
    }

    return count;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 08 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}