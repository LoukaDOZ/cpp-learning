#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#define BLINK_COUNT 75

using namespace std;

void map_add(unordered_map<long, long>& map, long v, long amount = 1)
{
    if(map.find(v) != map.end())
        map[v] += amount;
    else
        map[v] = amount;
}

unordered_map<long, long> readInput(string file)
{
    ifstream stream(file);
    unordered_map<long, long> stones;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return stones;
    }

    long num;
    while(stream >> num)
        map_add(stones, num);

    stream.close();
    return stones;
}

void blink(unordered_map<long, long>& stones)
{
    const auto stonesIt = stones;
    stones.clear();

    for(const pair<long, long> stone: stonesIt)
    {
        if(stone.first == 0)
        {
            map_add(stones, 1, stone.second);
            continue;
        }

        string sstone = to_string(stone.first);

        if(sstone.size() % 2 == 0)
        {
            map_add(stones, stoll(sstone.substr(0, sstone.size() / 2)), stone.second);
            map_add(stones, stoll(sstone.substr(sstone.size() / 2)), stone.second);
            continue;
        }
        
        map_add(stones, stone.first * 2024, stone.second);
    }
}

long run(string file)
{
    unordered_map<long, long> stones = readInput(file);
    long count = 0;

    for(int i = 0; i < BLINK_COUNT; i++)
        blink(stones);

    for(const pair<long, long> stone: stones)
        count += stone.second;

    return count;
}

int main()
{
    cout << "----- PART 2 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;
    return 0;
}