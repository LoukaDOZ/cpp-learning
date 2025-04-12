#include <iostream>
#include <fstream>
#include <vector>

#define CHAR_COMMA ','
#define CHAR_L_PARENTHESIS '('
#define CHAR_R_PARENTHESIS ')'
#define STR_MUL_LEN 3
#define CHAR_0_CODE 48
#define CHAR_9_CODE 57

using namespace std;

const char STR_MUL[] = {'m', 'u', 'l'};

string readInput(string file)
{
    ifstream stream(file);
    string instructions, line;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return instructions;
    }

    while(!stream.eof())
    {
        getline(stream, line);
        instructions += line;
    }

    stream.close();
    return instructions;
}

bool isChar(string& instructions, int* pointer, char c)
{
    return instructions.at((*pointer)++) == c;
}

bool isStr(string& instructions, int* pointer, string str)
{    
    for(int i = 0; i < str.length(); i++)
    {
        if(!isChar(instructions, pointer, str.at(i)))
            return false;
    }

    return true;
}

bool getInt(string& instructions, int* pointer, int* dest)
{
    int n = instructions.size();
    int value = 0;
    bool ok = false;

    for(int i = 0; i < 3; i++)
    {
        if(*pointer >= n)
            break;

        char c = instructions.at(*pointer);

        if(c < CHAR_0_CODE || c > CHAR_9_CODE)
            break;
        
        value = value * 10 + c - CHAR_0_CODE;
        ok = true;
        (*pointer)++;
    }

    *dest = value;
    return ok;
}

bool isMul(string& instructions, int* pointer, int* x, int* y)
{
    int n = instructions.size();

    for(int i = 0; i < STR_MUL_LEN; i++)
    {
        if(*pointer >= n || instructions.at(*pointer) != STR_MUL[i])
            return false;
        
        (*pointer)++;
    }

    if(*pointer >= n || instructions.at(*pointer) != CHAR_L_PARENTHESIS)
        return false;
    
    (*pointer)++;

    if(!getInt(instructions, pointer, x))
        return false;

    if(*pointer >= n || instructions.at(*pointer) != CHAR_COMMA)
        return false;
    
    (*pointer)++;

    if(!getInt(instructions, pointer, y))
        return false;

    if(*pointer >= n || instructions.at(*pointer) != CHAR_R_PARENTHESIS)
        return false;
        
    return true;
}

long run(string file)
{
    string instructions = readInput(file);
    int x, y, i = 0, n = instructions.length();
    long total = 0;

    while(i < n)
    {
        if(isMul(instructions, &i, &x, &y))
            total += x * y;

        i++;
    }

    return total;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 03 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}