#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

char get(ifstream& stream) {
    char c;
    stream.get(c);
    return c;
}

bool isChar(ifstream& stream, char c) {
    return get(stream) == c;
}

bool isStr(ifstream& stream, string str) {    
    for(int i = 0; i < str.length(); i++) {
        if(!isChar(stream, str.at(i)))
            return false;
    }

    return true;
}

bool isInt(ifstream& stream, int* dest) {
    char c;
    vector<int> ints;

    for(int i = 0; i < 3; i++) {
        c = get(stream);

        if(c < 48 || c > 57) {
            stream.seekg(-1, ios::cur);
            break;
        }

        ints.push_back((c - 48));
    }

    int res = 0;
    for(int i = 0; i < ints.size(); i++) {
        res += ints[i] * pow(10, ints.size() - i - 1);
    }

    *dest = res;
    return !ints.empty();
}

bool isMul(ifstream& stream, int* x, int* y) {
    return isStr(stream, "mul") && isChar(stream, '(') && isInt(stream, x) && isChar(stream, ',') && isInt(stream, y) && isChar(stream, ')');
}

int main() {
    ifstream stream("inputs/input");
    long total = 0;
    int x, y;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        if(isMul(stream, &x, &y))
            total += x * y;
    }

    stream.close();

    cout << "Result: " << total << endl;
    return 0;
}