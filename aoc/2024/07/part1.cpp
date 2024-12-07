#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool validateRec(long testValue, vector<int>& nums, int i, long total) {
    if(i >= nums.size())
        return total == testValue;

    if(total > testValue)
        return false;

    return validateRec(testValue, nums, i + 1, total + nums[i]) || validateRec(testValue, nums, i + 1, total * nums[i]);
}

bool validate(long testValue, vector<int>& nums) {
    return validateRec(testValue, nums, 1, nums[0]);
}

int main() {
    ifstream stream("inputs/input");
    long sum = 0;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        string line;
        getline(stream, line);

        stringstream sstream(line);
        vector<int> nums;
        long testValue;
        int num;

        sstream >> testValue;
        sstream.ignore(1, ':');

        while(sstream >> num)
            nums.push_back(num);

        if(validate(testValue, nums))
            sum += testValue;
    }

    stream.close();

    cout << "Result : " << sum << endl;
    return 0;
}