#include "battlefield.h"
#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Battlefield::Battlefield() {
    numRobots = 0;
}

void Battlefield::addRobot(Robot* robot) {
    if (numRobots < MAX_ROBOTS) {
        robots[numRobots] = robot;
        numRobots++;
    } else {
        std::cout << "Battlefield is full. Cannot add more robots." << std::endl;
    }
}

void Battlefield::simulateWar() {
    srand(time(0));

    for (int i = 0; i < numRobots; i++) {
        for (int j = i + 1; j < numRobots; j++) {
            Robot *robot1 = robots[i];
            Robot *robot2 = robots[j];
            if (robots[i]->getPosX() == robots[j]->getPosX() && robots[i]->getPosY() == robots[j]->getPosY()) {
                robots[i]->fire(BATTLEFIELD_ROWS, BATTLEFIELD_COLUMNS);
                robots[j]->fire(BATTLEFIELD_ROWS, BATTLEFIELD_COLUMNS);
            }
        }
    }
};
