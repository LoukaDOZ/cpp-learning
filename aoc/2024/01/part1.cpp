#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main() {
    ifstream stream("inputs/input");
    priority_queue<int> list1, list2;
    long totalDistance = 0;
    int id;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        stream >> id;
        list1.push(id);

        stream >> id;
        list2.push(id);
    }

    stream.close();

    while(!list1.empty()) {
        totalDistance += abs(list1.top() - list2.top());
        list1.pop();
        list2.pop();
    }

    cout << "Distance: " << totalDistance << endl;
    return 0;
}