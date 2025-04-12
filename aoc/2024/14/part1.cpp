#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#define MOVE_N_TIMES 100

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

long run(string file, pos_t space)
{
    vector<robot_t> robots = readInput(file);
    
    for(robot_t& robot: robots)
        moveRobotNTimes(robot, space, MOVE_N_TIMES);

    int halfX = space.x / 2;
    int halfY = space.y / 2;
    return countRobots(robots, {0, 0}, {halfX, halfY})
        * countRobots(robots, {space.x - halfX, 0}, {space.x, halfY})
        * countRobots(robots, {0, space.y - halfY}, {halfX, space.y})
        * countRobots(robots, {space.x - halfX, space.y - halfY}, space);
}

pos_t askSpace(string filename)
{
    pos_t space = {-1, -1};

    while(space.x < 0 || space.y < 0)
    {
        cout << '[' << filename << "] Enter puzzle space as \"<x> <y>\" :" << endl;
        cin >> space.x;
        cin >> space.y;
    }

    return space;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 14 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
    {
        pos_t space = askSpace(argv[i]);
        cout << argv[i] << ": " << run(argv[i], space) << endl;
    }

    return 0;
}