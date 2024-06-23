#include "battlefield.h"
#include "robot.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

Battlefield::Battlefield() {
    srand(time(0));
}

void Battlefield::simulateWar(Robot* robots[], int numRobots, int mapX, int mapY) {
    // Simulate actions for all robots
    for (int i = 0; i < numRobots; ++i) {
        robots[i]->move(robots, mapX, mapY);

        if (RoboCop* robocop = dynamic_cast<RoboCop*>(robots[i])) {
            robocop->look(robots, mapX, mapY);
            robocop->fire(robots, mapX, mapY);
            if (robocop->getKill() >= 3) {
                TerminatorRoboCop* upgradedRobot = new TerminatorRoboCop(robocop->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (Terminator* terminator = dynamic_cast<Terminator*>(robots[i])) {
            terminator->look(robots, mapX, mapY);
            terminator->step(robots, mapX, mapY);
            if (terminator->getKill() >= 3) {
                TerminatorRoboCop* upgradedRobot = new TerminatorRoboCop(terminator->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (TerminatorRoboCop* termRoboCop = dynamic_cast<TerminatorRoboCop*>(robots[i])) {
            termRoboCop->look(robots, mapX, mapY);
            termRoboCop->fire(robots, mapX, mapY);
            termRoboCop->step(robots, mapX, mapY);
            if (termRoboCop->getKill() >= 3) {
                UltimateRobot* upgradedRobot = new UltimateRobot(termRoboCop->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (BlueThunder* blueThunder = dynamic_cast<BlueThunder*>(robots[i])) {
            blueThunder->fire(robots, mapX, mapY);
            if (blueThunder->getKill() >= 3) {
                MadBot* upgradedRobot = new MadBot(blueThunder->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (MadBot* madBot = dynamic_cast<MadBot*>(robots[i])) {
            madBot->fire(robots, mapX, mapY);
            if (madBot->getKill() >= 3) {
                UltimateRobot* upgradedRobot = new UltimateRobot(madBot->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (RoboTank* roboTank = dynamic_cast<RoboTank*>(robots[i])) {
            roboTank->fire(robots, mapX, mapY);
            if (roboTank->getKill() >= 3) {
                UltimateRobot* upgradedRobot = new UltimateRobot(roboTank->getName(), "random", "random", 0);
                upgradedRobot->setAlive(true);
                robots[i] = upgradedRobot;
            }
        } else if (UltimateRobot* ultimateRobot = dynamic_cast<UltimateRobot*>(robots[i])) {
            ultimateRobot->move(robots, mapX, mapY);
            ultimateRobot->fire(robots, mapX, mapY);
            ultimateRobot->step(robots, mapX, mapY);
        }
    }
}

void Battlefield::printBattlefield(Robot* robots[], int numRobots, int mapX, int mapY) {
    char battlefieldMap[mapY][mapX];

    // Initialize the battlefield with '.'
    for (int i = 0; i < mapY; ++i) {
        for (int j = 0; j < mapX; ++j) {
            battlefieldMap[i][j] = '.';
        }
    }

    // Place the robots on the battlefield
    for (int i = 0; i < numRobots; ++i) {
        if (robots[i]->isAlive()) {
            battlefieldMap[robots[i]->getPosY()][robots[i]->getPosX()] = 'R';
        }
    }

    // Print the battlefield
    for (int i = 0; i < mapY; ++i) {
        for (int j = 0; j < mapX; ++j) {
            cout << battlefieldMap[i][j] << ' ';
        }
        cout << endl;
    }
}
