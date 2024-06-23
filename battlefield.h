#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "robot.h"

using namespace std;

const int mapX = 10;
const int mapY = 10;
const int MAX_ROBOTS = 100;

class Robot;

class Battlefield {
private:
    Robot* robots[MAX_ROBOTS];
    int numRobots;
    char battlefieldMap[mapY][mapX];
    void initializeBattlefield();
    void updateBattlefield();
    void printBattlefield(Robot* robots[], int numRobots, int mapX, int mapY);
    void clearDeadRobots();
public:
    Battlefield();
    void addRobot(Robot* robot);
    void simulateWar(Robot* robots[], int numRobots, int mapX, int mapY);
    void display(ofstream& logFile);
};

#endif // BATTLEFIELD_H
