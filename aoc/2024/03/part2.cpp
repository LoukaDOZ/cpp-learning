#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void back(ifstream& stream, int to) {
    stream.seekg(-to, ios::cur);
}

char get(ifstream& stream) {
    char c;
    stream.get(c);
    return c;
}

bool isChar(ifstream& stream, char c) {
    return get(stream) == c;
}

bool isStr(ifstream& stream, string str, int* read = NULL) {    
    for(int i = 0; i < str.length(); i++) {
        if(!isChar(stream, str.at(i))) {
            if(read != NULL)
                *read = i + 1;
            return false;
        }
    }

    return true;
}

bool isInt(ifstream& stream, int* dest) {
    char c;
    vector<int> ints;

    for(int i = 0; i < 3; i++) {
        c = get(stream);

        if(c < 48 || c > 57) {
            back(stream, 1);
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

bool isDo(ifstream& stream, int* read) {
    return isStr(stream, "do()", read);
}

bool isDont(ifstream& stream, int* read) {
    return isStr(stream, "don't()", read);
}

int main() {
    ifstream stream("inputs/program");
    long total = 0;
    int x, y, read;
    bool doMul = true;

    if(!stream) {
        cerr << "Failed to open input file" << endl;
        return 1;
    }

    while(!stream.eof()) {
        if(doMul) {
            if(isDont(stream, &read))
                doMul = false;
            else if(!stream.eof())
                back(stream, read);
            else
                break;
        } else {
            if(isDo(stream, &read))
                doMul = true;
            else if(!stream.eof())
                back(stream, read);
            else
                break;
        }

        if(isMul(stream, &x, &y) && doMul)
            total += x * y;
    }

    stream.close();

    cout << "Result: " << total << endl;
    return 0;
}