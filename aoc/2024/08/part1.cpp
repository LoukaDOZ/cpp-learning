#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool inBounds(int n, int m, pair<int,int>& pos) {
    return pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m;
}

int main() {
    ifstream stream("inputs/input");

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    map<char, vector<pair<int,int>>> antennas;
    char c;
    int n = 0, m = 0;

    while(true) {
        stream.get(c);

        if(stream.eof())
            break;

        if(c == '\n') {
            n++;
            m = 0;
            continue;
        }

        if(c != '.')
            antennas[c].push_back({n,m});

        m++;
    }

    n++;
    stream.close();

    int count = 0;
    set<pair<int,int>, greater<pair<int,int>>> antinodes;
    for(pair<char,vector<pair<int,int>>> a: antennas) {
        for(pair<int,int> antenna: a.second) {
            for(pair<int,int> antenna2: a.second) {
                if(antenna == antenna2)
                    continue;

                int disty = antenna.first - antenna2.first;
                int distx = antenna.second - antenna2.second;
                pair<int,int> antinode1 = {antenna.first + disty, antenna.second + distx};
                pair<int,int> antinode2 = {antenna2.first - disty, antenna2.second - distx};

                if(inBounds(n, m, antinode1) && !antinodes.count(antinode1)) {
                    count++;
                    antinodes.insert(antinode1);
                }

                if(inBounds(n, m, antinode2) && !antinodes.count(antinode2)) {
                    count++;
                    antinodes.insert(antinode2);
                }
            }
        }
    }

    cout << "Result : " << count << endl;
    return 0;
}