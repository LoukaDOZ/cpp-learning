#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#define BLINK_COUNT 25

using namespace std;

vector<long> readInput(string file)
{
    ifstream stream(file);
    vector<long> stones;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return stones;
    }

    long num;
    while(stream >> num)
    {
        stones.push_back(num);
    }

    stream.close();
    return stones;
}

void blink(vector<long>& stones)
{
    int n = stones.size();

    for(int i = 0; i < n; i++)
    {
        long s = stones[i];

        if(s == 0)
        {
            stones[i] = 1;
            continue;
        }

        string sstone = to_string(s);

        if(sstone.size() % 2 == 0)
        {
            stones[i] = stoll(sstone.substr(0, sstone.size() / 2));
            stones.push_back(stoll(sstone.substr(sstone.size() / 2)));
            continue;
        }
        
        stones[i] *= 2024;
    }
}

int run(string file)
{
    vector<long> stones = readInput(file);

    for(int i = 0; i < BLINK_COUNT; i++)
        blink(stones);

    return stones.size();
}

int main()
{
    cout << "----- PART 1 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;
    return 0;
}