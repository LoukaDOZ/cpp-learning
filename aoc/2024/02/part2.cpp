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

int check(vector<int>& report, int ignore = -1)
{
    int i = 0, j = 1, diff;

    if(ignore == 0)
    {
        i = 1;
        j = 2;
    } else if(ignore == 1)
        j = 2;

    bool asc = report[i] - report[j] < 0;
    
    while(j < report.size())
    {
        diff = report[i] - report[j];

        if(diff < -3 || diff == 0 || diff > 3 || (diff < 0) != asc)
            return j;

        i = j;
        j += 1 + (j == ignore);
    }

    return -1;
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
        int erri;
        bool ascending, ok;

        erri = check(report);

        if(erri < 0)
        {
            totalSafe++;
            continue;
        }

        for(int i = 0; i <= erri; i++)
        {
            if(check(report, i) < 0)
            {
                totalSafe++;
                break;
            }
        }
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

    cout << "----- AOC 2024 DAY 02 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}