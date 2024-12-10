#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

vector<priority_queue<int>> readInput(string file)
{
    ifstream stream(file);
    priority_queue<int> list1, list2;
    int id;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return {};
    }

    while(!stream.eof())
    {
        stream >> id;
        list1.push(id);

        stream >> id;
        list2.push(id);
    }

    stream.close();
    return {list1, list2};
}

long run(string file)
{
    vector<priority_queue<int>> lists = readInput(file);
    priority_queue<int>& list1 = lists[0];
    priority_queue<int>& list2 = lists[1];
    int distanceSum = 0;

    while(!list1.empty())
    {
        distanceSum += abs(list1.top() - list2.top());
        list1.pop();
        list2.pop();
    }

    return distanceSum;
}

int main()
{
    cout << "----- PART 1 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;

    return 0;
}