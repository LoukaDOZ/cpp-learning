#include <iostream>
#include <fstream>
#include <vector>

#define FREE_SPACE -1

using namespace std;

vector<int> readInput(string file)
{
    ifstream stream(file);
    vector<int> diskMap;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return diskMap;
    }

    int id = 0;
    char c;
    bool isFile = true;

    while(stream >> c)
    {
        int v = isFile ? id : FREE_SPACE;
        int num = c - '0';

        for(int i = 0; i < num; i++)
            diskMap.push_back(v);

        if(isFile) id++;
        isFile = !isFile;
    }

    stream.close();
    return diskMap;
}

void compact(vector<int>& diskMap) {
    int freeSpaceI = 0, fileI = diskMap.size() - 1;

    while(true)
    {
        while(diskMap[freeSpaceI] != FREE_SPACE) freeSpaceI++;
        while(diskMap[fileI] == FREE_SPACE) fileI--;

        if(freeSpaceI >= fileI)
            break;

        int tmp = diskMap[freeSpaceI];
        diskMap[freeSpaceI] = diskMap[fileI];
        diskMap[fileI] = tmp;
    }
}

long checksum(vector<int>& diskMap) {
    long sum = 0;
    for(int i = 0; i < diskMap.size(); i++)
    {
        if(diskMap[i] == FREE_SPACE)
            break;

        sum += i * diskMap[i];
    }

    return sum;
}

long run(string file)
{
    vector<int> diskMap = readInput(file);
    compact(diskMap);
    return checksum(diskMap);
}

int main()
{
    cout << "----- PART 1 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;

    return 0;
}