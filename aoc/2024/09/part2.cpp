#include <iostream>
#include <fstream>
#include <vector>

#define FREE_SPACE -1

using namespace std;

vector<vector<int>> readInput(string file)
{
    ifstream stream(file);
    vector<vector<int>> diskMap;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return diskMap;
    }

    int id = 0, pos = 0;
    char c;
    bool isFile = true;

    while(stream >> c)
    {
        int num = c - '0';

        if(isFile)
        {            
            diskMap.push_back({id, pos, num});
            id++;
        }

        pos += num;
        isFile = !isFile;
    }

    stream.close();
    return diskMap;
}

void compact(vector<vector<int>>& diskMap)
{
    for(int fileI = diskMap.size() - 1; fileI >= 0; fileI--)
    {
        vector<int> file = diskMap[fileI];

        for(int i = 1; i <= fileI; i++)
        {
            int prevFileEnd = diskMap[i - 1][1] + diskMap[i - 1][2];
            int size = diskMap[i][1] - prevFileEnd;

            if(size >= diskMap[fileI][2])
            {
                diskMap.erase(diskMap.begin() + fileI);
                file[1] = prevFileEnd;
                diskMap.insert(diskMap.begin() + i, file);
                fileI++;
                break;
            }
        }
    }
}

long checksum(vector<vector<int>>& diskMap)
{
    long sum = 0;

    for(int i = 0; i < diskMap.size(); i++)
    {
        for(int j = 0; j < diskMap[i][2]; j++)
            sum += (diskMap[i][1] + j) * diskMap[i][0];
    }

    return sum;
}

long run(string file)
{
    vector<vector<int>> diskMap = readInput(file);
    compact(diskMap);
    return checksum(diskMap);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 09 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}