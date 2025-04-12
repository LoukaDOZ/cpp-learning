#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> readInput(string file)
{
    ifstream stream(file);
    vector<int> list1, list2;
    int id;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return {};
    }

    while(!stream.eof())
    {
        if(stream >> id)
            list1.push_back(id);

        if(stream >> id)
            list2.push_back(id);
    }

    stream.close();
    return {list1, list2};
}

long run(string file)
{
    vector<vector<int>> lists = readInput(file);
    vector<int>& list1 = lists[0];
    vector<int>& list2 = lists[1];
    unordered_map<int, int> counts;
    int similarity = 0;

    for(int i: list2)
    {
        if(counts.find(i) != counts.end())
            counts[i]++;
        else
            counts[i] = 1;
    }

    for(int i: list1)
        similarity += i * counts[i];

    return similarity;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 01 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}