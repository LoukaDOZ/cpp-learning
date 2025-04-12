#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<pair<long, vector<int>>> readInput(string file)
{
    ifstream stream(file);
    vector<pair<long, vector<int>>> equations;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return equations;
    }

    while(!stream.eof())
    {
        string line;
        getline(stream, line);

        if(line.empty())
            continue;

        stringstream sstream(line);
        vector<int> nums;
        long testValue;
        int num;

        sstream >> testValue;
        sstream.ignore(1, ':');

        while(sstream >> num)
            nums.push_back(num);

        equations.push_back({testValue, nums});
    }

    stream.close();
    return equations;
}

bool validateRec(long testValue, vector<int>& nums, int i, long total)
{
    if(i >= nums.size())
        return total == testValue;

    if(total > testValue)
        return false;

    if(validateRec(testValue, nums, i + 1, total + nums[i]) || validateRec(testValue, nums, i + 1, total * nums[i]))
        return true;

    long v = stol(to_string(total) + to_string(nums[i]));
    return validateRec(testValue, nums, i + 1, v);
}

bool validate(long testValue, vector<int>& nums)
{
    return validateRec(testValue, nums, 1, nums[0]) || validateRec(testValue, nums, 2, stoi(to_string(nums[0]) + to_string(nums[1])));
}

long run(string file)
{
    vector<pair<long, vector<int>>> equations = readInput(file);
    long sum = 0;

    for(pair<long, vector<int>>& equation : equations)
    {
        if(validate(equation.first, equation.second))
            sum += equation.first;
    }

    return sum;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 07 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}