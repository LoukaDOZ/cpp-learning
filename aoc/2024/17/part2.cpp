#include <iostream>
#include <fstream>
#include <vector>

#define R_A 0
#define R_B 1
#define R_C 2

#define I_ADV 0
#define I_BXL 1
#define I_BST 2
#define I_JNZ 3
#define I_BXC 4
#define I_OUT 5
#define I_BDV 6
#define I_CDV 7

#define OP_0 0
#define OP_1 1
#define OP_2 2
#define OP_3 3
#define OP_4 4
#define OP_5 5
#define OP_6 6
#define OP_7 7

#define NB_REGISTERS 3
#define DEFAULT_JUMP 2
#define NOT_SET -1

using namespace std;

vector<int> readInput(string file)
{
    ifstream stream(file);
    vector<int> program;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return program;
    }

    int v;

    stream.ignore(12);
    stream >> v;

    stream.ignore(12);
    stream >> v;

    stream.ignore(12);
    stream >> v;

    stream.ignore(10);
    while(stream >> v)
    {
        program.push_back(v);
        stream.ignore(1, ',');
    }
    
    stream.close();
    return program;
}

unsigned long comboOperand(vector<unsigned long>& registers, int operand)
{
    switch(operand)
    {
        case OP_0:
        case OP_1:
        case OP_2:
        case OP_3:
            return operand;
        case OP_4:
            return registers[R_A];
        case OP_5:
            return registers[R_B];
        case OP_6:
            return registers[R_C];
        case OP_7:
            cout << "We have a problem I guess..." << endl;
            return -1;
        default:
            cout << "Unknown operand ???" << endl;
            return -1;
    }
}

pair<int,int> runInstruction(vector<unsigned long>& registers, int upcode, int operand)
{
    pair<int,int> iReturn {NOT_SET, NOT_SET};

    switch(upcode)
    {
        case I_ADV:
            registers[R_A] >>= comboOperand(registers, operand);
            break;
        case I_BXL:
            registers[R_B] ^= operand;
            break;
        case I_BST:
            registers[R_B] = comboOperand(registers, operand) % 8;
            break;
        case I_JNZ:
            if(registers[R_A] != 0)
                iReturn.second = operand;
            break;
        case I_BXC:
            registers[R_B] ^= registers[R_C];
            break;
        case I_OUT:
            iReturn.first = comboOperand(registers, operand) % 8;
            break;
        case I_BDV:
            registers[R_B] = registers[R_A] >> comboOperand(registers, operand);
            break;
        case I_CDV:
            registers[R_C] = registers[R_A] >> comboOperand(registers, operand);
            break;
        default:
            cout << "Unknown instruction ????" << endl;
    }

    return iReturn;
}

void runProgram(vector<int>& program, vector<int>& output, unsigned long valueRA)
{
    vector<unsigned long> registers(NB_REGISTERS, 0);
    int i = 0, n = program.size();

    registers[R_A] = valueRA;

    while(i + 1 < n)
    {
        pair<int,int> iReturn = runInstruction(registers, program[i], program[i + 1]);
        i = iReturn.second >= 0 ? iReturn.second : i + DEFAULT_JUMP;

        if(iReturn.first != NOT_SET)
            output.push_back(iReturn.first);
    }
}

bool arraysEqual(vector<int>& a, vector<int>& b)
{
    int n = a.size();

    if(n != b.size())
        return false;

    for(int i = 0; i < n; i++)
    {
        if(a[i] != b[i])
            return false;
    }

    return true;
}

unsigned long run(string file)
{
    vector<int> program = readInput(file);
    unsigned long valueRA = 0;
    int n = program.size();

    for(int i = 0; i < n; i++)
    {
        valueRA <<= 3;
        vector<int> truncProgram(program.begin() + n - i - 1, program.end());
        vector<int> output;

        while(true)
        {
            output.clear();
            runProgram(program, output, valueRA);

            if(arraysEqual(truncProgram, output))
                break;

            valueRA++;
        }
    }

    return valueRA;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 17 : PART 2 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}