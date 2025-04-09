#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

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

#define DEFAULT_JUMP 2

using namespace std;

struct instruction_return_t
{
    vector<int> output;
    int pointer;
};

pair<vector<int>, vector<int>> readInput(string file)
{
    ifstream stream(file);
    vector<int> registers(3, 0);
    vector<int> program;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return {registers, program};
    }

    stream.ignore(12);
    stream >> registers[R_A];

    stream.ignore(12);
    stream >> registers[R_B];

    stream.ignore(12);
    stream >> registers[R_C];

    int v;
    stream.ignore(10);
    while(stream >> v)
    {
        program.push_back(v);
        stream.ignore(1, ',');
    }
    
    stream.close();
    return {registers, program};
}

int combo_operand(vector<int>& registers, int operand)
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

void advInstruction(vector<int>& registers, int operand)
{
    registers[R_A] /= pow(2, combo_operand(registers, operand));
}

void bxlInstruction(vector<int>& registers, int operand)
{
    registers[R_B] ^= operand;
}

void bstInstruction(vector<int>& registers, int operand)
{
    registers[R_B] = (combo_operand(registers, operand) % 8) & 7;
}

void jnzInstruction(vector<int>& registers, int operand, int& pointer)
{
    if(registers[R_A] == 0)
        return;

    pointer = operand;
}

void bxcInstruction(vector<int>& registers)
{
    registers[R_B] ^= registers[R_C];
}

int outInstruction(vector<int>& registers, int operand)
{
    return combo_operand(registers, operand) % 8;
}

void bdvInstruction(vector<int>& registers, int operand)
{
    registers[R_B] = (int) registers[R_A] / pow(2, combo_operand(registers, operand));
}

void cdvInstruction(vector<int>& registers, int operand)
{
    registers[R_C] = (int) registers[R_A] / pow(2, combo_operand(registers, operand));
}

instruction_return_t runInstruction(vector<int>& registers, int upcode, int operand)
{
    instruction_return_t iReturn {{}, -1};

    switch(upcode)
    {
        case I_ADV:
            advInstruction(registers, operand);
            break;
        case I_BXL:
            bxlInstruction(registers, operand);
            break;
        case I_BST:
            bstInstruction(registers, operand);
            break;
        case I_JNZ:
            jnzInstruction(registers, operand, iReturn.pointer);
            break;
        case I_BXC:
            bxcInstruction(registers);
            break;
        case I_OUT:
            iReturn.output.push_back(outInstruction(registers, operand));
            break;
        case I_BDV:
            bdvInstruction(registers, operand);
            break;
        case I_CDV:
            cdvInstruction(registers, operand);
            break;
        default:
            cout << "Unknown instruction ????" << endl;
    }

    return iReturn;
}

string run(string file)
{
    pair<vector<int>, vector<int>> input = readInput(file);
    vector<int> registers = input.first;
    vector<int> program = input.second;

    string output = "";
    int i = 0;

    while(i + 1 < program.size())
    {
        instruction_return_t iReturn = runInstruction(registers, program[i], program[i + 1]);
        i = iReturn.pointer >= 0 ? iReturn.pointer : i + DEFAULT_JUMP;

        for(int o : iReturn.output)
        {
            if(!output.empty())
                output += ',';

            output += to_string(o);
        }
    }

    return output;
}

int main()
{
    cout << "----- PART 1 -----" << endl;
    cout << "Example: " << run("inputs/example") << endl;
    cout << "Input:\t " << run("inputs/input") << endl;
    return 0;
}