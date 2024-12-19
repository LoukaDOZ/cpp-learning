#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <unistd.h>

#define MOVE_N_TIMES 100
#define EXAMPLE_SPACE_X 11
#define EXAMPLE_SPACE_Y 7
#define INPUT_SPACE_X 101
#define INPUT_SPACE_Y 103
#define MIN_CONTINUOUS 30

using namespace std;

struct pos_t
{
    int x, y;
};

struct robot_t
{
    pos_t pos, vel;
};

vector<robot_t> readInput(string file)
{
    ifstream stream(file);
    vector<robot_t> robots;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return robots;
    }

    string line;
    stringstream sstream;
    while(!stream.eof())
    {
        robot_t r;

        getline(stream, line);
        if(line.empty())
            break;

        sstream = stringstream(line);
        
        sstream.ignore(numeric_limits<streamsize>::max(), '=');
        sstream >> r.pos.x;

        sstream.ignore(1);
        sstream >> r.pos.y;
        
        sstream.ignore(numeric_limits<streamsize>::max(), '=');
        sstream >> r.vel.x;

        sstream.ignore(1);
        sstream >> r.vel.y;

        robots.push_back(r);
    }

    stream.close();
    return robots;
}

void moveRobotNTimes(robot_t& robot, pos_t space, int times)
{
    int posX = (robot.pos.x + robot.vel.x * times) % space.x;
    int posY = (robot.pos.y + robot.vel.y * times) % space.y;

    if(posX < 0)
        robot.pos.x = space.x + posX;
    else if(posX >= space.x)
        robot.pos.x = space.x - posX;
    else
        robot.pos.x = posX;

    if(posY < 0)
        robot.pos.y = space.y + posY;
    else if(posY >= space.y)
        robot.pos.y = space.y - posY;
    else
        robot.pos.y = posY;
}

int countRobots(vector<robot_t>& robots, pos_t quadrantTL, pos_t quadrantBR)
{
    int count = 0;

    for(robot_t& robot: robots)
    {
        if(robot.pos.x >= quadrantTL.x && robot.pos.x < quadrantBR.x
                && robot.pos.y >= quadrantTL.y && robot.pos.y < quadrantBR.y)
            count++;
    }

    return count;
}

bool checkTree(vector<vector<int>>& grid)
{
    int maxContinuous = 0;

    for(int i = 0; i < grid.size(); i++)
    {
        int continuous = 0;

        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j] == 0)
            {
                maxContinuous = max(maxContinuous, continuous);
                continuous = 0;
            }

            continuous++;
        }
    }

    return maxContinuous > MIN_CONTINUOUS;
}

void printg(vector<vector<int>>& grid)
{
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            cout<<(grid[i][j] == 0 ? '.' : (char) (48 + grid[i][j]));
        }
        cout<<endl;
    }
    cout<<endl;
}

long run(string file, pos_t space)
{
    vector<robot_t> robots = readInput(file);
    vector<vector<int>> grid(space.y, vector<int>(space.x, 0));
    int seconds = 1;

    for(robot_t& robot: robots)
        grid[robot.pos.y][robot.pos.x] += 1;

    while(true)
    {
        for(robot_t& robot: robots)
        {
            grid[robot.pos.y][robot.pos.x] -= 1;
            moveRobotNTimes(robot, space, 1);
            grid[robot.pos.y][robot.pos.x] += 1;
        }

        if(checkTree(grid))
            break;

        seconds++;
    }
    
    return seconds;
}

int main()
{
    cout << "----- PART 2 -----" << endl;
    cout << "Input:\t " << run("inputs/input", {101, 103}) << endl;
    return 0;
}