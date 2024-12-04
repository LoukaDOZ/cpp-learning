#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ifstream stream("inputs/input");
    unordered_map<int, int> counts;
    vector<int> list2;
    long totalSimilarity = 0;
    int id;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        stream >> id;
        counts[id] = 0;

        stream >> id;
        list2.push_back(id);
    }

    stream.close();

    for(int i: list2) {
        if(counts.find(i) != counts.end())
            counts[i]++;
    }

    for(pair<int, int> count: counts) {
        totalSimilarity += count.first * count.second;
    }

    cout << "Similarity: " << totalSimilarity << endl;
    return 0;
}