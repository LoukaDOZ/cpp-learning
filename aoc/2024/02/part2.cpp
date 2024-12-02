#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int check(vector<int>& report, int ignore = -1) {
    int i = 0, j = 1, diff;

    if(ignore == 0) {
        i = 1;
        j = 2;
    } else if(ignore == 1)
        j = 2;

    bool asc = report[i] - report[j] < 0;
    
    while(j < report.size()) {
        diff = report[i] - report[j];

        if(diff < -3 || diff == 0 || diff > 3 || (diff < 0) != asc)
            return j;

        i = j;
        j += 1 + (j == ignore);
    }

    return -1;
}

int main() {
    ifstream stream("inputs/reports");
    long totalSafe = 0;
    string report;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        getline(stream, report);

        stringstream sStream(report);
        vector<int> reportValues;
        int x, erri;

        while(!sStream.eof()) {
            sStream >> x;
            reportValues.push_back(x);
        }

        erri = check(reportValues);

        if(erri < 0) {
            totalSafe++;
            continue;
        }

        for(int i = 0; i <= erri; i++) {
            if(check(reportValues, i) < 0) {
                totalSafe++;
                break;
            }
        }
    }

    stream.close();

    cout << "Safe reports: " << totalSafe << endl;
    return 0;
}