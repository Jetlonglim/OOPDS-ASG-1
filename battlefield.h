#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "robot.h"

const int mapX = 30;
const int mapY = 30;
const int MAX_ROBOTS = 100;

class Robot;

class Battlefield {
private:
    Robot* robots[MAX_ROBOTS];
    int numRobots;
public:
    Battlefield();
    void addRobot(Robot* robot);
    void simulateWar();
    void update();
    void display(std::ofstream& logFile);
};

#endif // BATTLEFIELD_H
