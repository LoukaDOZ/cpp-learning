#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

bool pathExists(unordered_map<int, vector<int>>& graph, int start, int end) {
    queue<int> queue;
    set<int> excluded;

    queue.push(start);

    while(!queue.empty()) {
        int v = queue.front();
        queue.pop();

        if(start == 74 && end == 48)
            cout << v << " --> ";

        if(v == end) {
            if(start == 74 && end == 48)
                cout << "TRUE" << endl << endl;
            return true;
        }

        if(!excluded.insert(v).second)
            continue;

        for(int next: graph[v])
            queue.push(next);
    }

    if(start == 74 && end == 48)
        cout << "FALSE" << endl << endl;
    return false;
}

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
                    int tmp = pages[j];
                    pages[j] = pages[i];
                    pages[i] = tmp;
                    ok = false;
                    i--;
                    break;
                }
            }
        }

        if(!ok)
            middleSum += pages[pages.size() / 2];
    }

    stream.close();

    cout << "Result : " << middleSum << endl;
    return 0;
}