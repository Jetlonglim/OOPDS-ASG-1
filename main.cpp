#include "battlefield.h"
#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;

void printBattlefield(Battlefield &battlefield, Robot* robots[], int numRobots) {
    char battlefieldMap[mapY][mapX];
    
    // Initialize the battlefield with '*'
    for (int i = 0; i < mapY; ++i) {
        for (int j = 0; j < mapX; ++j) {
            battlefieldMap[i][j] = '*';
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
            cout << battlefieldMap[i][j];
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    // Create a battlefield object
    Battlefield battlefield;

    // Create and add robots to the battlefield
    Robot* robots[MAX_ROBOTS];
    robots[0] = new MovingRobot("Bot1", "random", "random", 0);
    robots[1] = new ShootingRobot("Bot2", "random", "random", 0);

    battlefield.addRobot(robots[0]);
    battlefield.addRobot(robots[1]);

    int posX, posY;

    for (int turn = 0; turn < 10; ++turn) {
        cout << "Turn " << turn + 1 << endl;
        printBattlefield(battlefield, robots, 2);

        cout << "Enter movement for Bot1 (posX posY): ";
        cin >> posX >> posY;

        // Update positions based on input
        if (posX != 0 || posY != 0) {
            dynamic_cast<MovingRobot*>(robots[0])->moving(to_string(posX), to_string(posY));
        }

        // Simulate shooting for Bot2
        dynamic_cast<ShootingRobot*>(robots[1])->fire(mapX, mapY);

        // Simulate war
        battlefield.simulateWar();

        cout << "Bot1 position: (" << robots[0]->getPosX() << ", " << robots[0]->getPosY() << ")" << endl;
        cout << "Bot2 position: (" << robots[1]->getPosX() << ", " << robots[1]->getPosY() << ")" << endl;
        cout << "Bot1 kills: " << robots[0]->getKill() << endl;
        cout << "Bot2 kills: " << robots[1]->getKill() << endl;

        cout << endl;
    }

    // Clean up the memory
    delete robots[0];
    delete robots[1];

    return 0;
}
