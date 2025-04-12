#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> readInput(string file)
{
    ifstream stream(file);
    vector<vector<int>> reports;
    string line;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return reports;
    }

    while(!stream.eof())
    {
        getline(stream, line);

        if(line.empty())
            continue;

        stringstream sStream(line);
        vector<int> report;
        int v;

        while(sStream >> v)
            report.push_back(v);

        reports.push_back(report);
    }

    stream.close();
    return reports;
}

long run(string file)
{
    vector<vector<int>> reports = readInput(file);
    long totalSafe = 0;
    
    for(vector<int>& report : reports)
    {
        int a = report[0];
        int b = report[1];
        int n = report.size();
        int diff = a - b;
        bool ascending, ok;

        if(diff < -3 || diff == 0 || diff > 3)
            continue;
        
        ascending = diff < 0;
        ok = true;

        for(int i = 2; i < n; i++)
        {
            int diff = report[i - 1] - report[i];

            if(diff < -3 || diff == 0 || diff > 3 || (diff < 0) != ascending)
            {
                ok = false;
                break;
            }
        }

        if(ok)
            totalSafe++;
    }

    return totalSafe;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 02 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}