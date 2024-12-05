#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ifstream stream("inputs/input");
    unordered_map<int, vector<int>> graph;
    long middleSum = 0;
    string line;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(true) {
        getline(stream, line);

        if(line.empty())
            break;

        stringstream lineStream(line);
        int page, nextPage;

        lineStream >> page;
        lineStream.ignore(1, '|');
        lineStream >> nextPage;
        graph[page].push_back(nextPage);
    }

    while(true) {
        getline(stream, line);

        if(stream.eof())
            break;

        stringstream lineStream(line);
        vector<int> pages;
        int page;
        bool ok = true;

        while(!lineStream.eof()) {
            lineStream >> page;
            lineStream.ignore(1, ',');
            pages.push_back(page);
        }

        for(int i = 1; i < pages.size(); i++) {
            vector<int> nextPages = graph[pages[i]];

            for(int j = 0; j < i; j++) {
                if(find(nextPages.begin(), nextPages.end(), pages[j]) != nextPages.end()) {
                    ok = false;
                    break;
                }
            }
        }

        if(ok)
            middleSum += pages[pages.size() / 2];
    }

    stream.close();

    cout << "Result : " << middleSum << endl;
    return 0;
}