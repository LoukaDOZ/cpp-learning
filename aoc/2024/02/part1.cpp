#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

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
        int a, b, diff;
        bool ascending, ok;

        sStream >> a;
        sStream >> b;
        diff = a - b;

        if(diff < -3 || diff == 0 || diff > 3)
            continue;
        
        ascending = diff < 0;
        ok = true;

        while(!sStream.eof()) {
            a = b;
            sStream >> b;
            diff = a - b;

            if(diff < -3 || diff == 0 || diff > 3 || (diff < 0) != ascending) {
                ok = false;
                break;
            }
        }

        if(ok)
            totalSafe++;
    }

    stream.close();

    cout << "Safe reports: " << totalSafe << endl;
    return 0;
}