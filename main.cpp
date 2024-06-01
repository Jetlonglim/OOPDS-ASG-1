#include "battlefield.h"
#include "battlefield.cpp"
#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to print the current state of the battlefield
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

    // Array to hold robots
    Robot* robots[MAX_ROBOTS];

    // User input for number of robots
    int numRobots;
    cout << "Enter the number of robots: ";
    cin >> numRobots;

    // Check to ensure the number of robots does not exceed the maximum
    if (numRobots > MAX_ROBOTS) {
        cout << "Number of robots exceeds the maximum limit of " << MAX_ROBOTS << "." << endl;
        return 1;
    }

    // Create and add robots to the battlefield based on user input
    for (int i = 0; i < numRobots; ++i) {
        string type;
        cout << "Enter the type for robot " << i + 1 << " (Moving/Shooting/Seeing/Stepping): ";
        cin >> type;

        Robot* robot = nullptr;
        if (type == "Moving") {
            robot = new MovingRobot("Bot" + to_string(i + 1), "0", "0", 0);
        } else if (type == "Shooting") {
            robot = new ShootingRobot("Bot" + to_string(i + 1), "0", "0", 0);
        } else if (type == "Seeing") {
            robot = new SeeingRobot("Bot" + to_string(i + 1), 0, 0, 0);
        } else if (type == "Stepping") {
            robot = new SteppingRobot("Bot" + to_string(i + 1), "0", "0", 0);
        } else {
            cout << "Invalid type. Defaulting to MovingRobot." << endl;
            robot = new MovingRobot("Bot" + to_string(i + 1), "0", "0", 0);
        }

        robots[i] = robot;
        battlefield.addRobot(robot);
    }

    bool running = true; // Flag to control the loop
    int posX, posY;
    int turn = 0;

    while (running) {
        cout << "Round " << turn + 1 << endl;
        printBattlefield(battlefield, robots, numRobots);

        // Input and move the first MovingRobot found
        for (int i = 0; i < numRobots; ++i) {
            if (MovingRobot* movingRobot = dynamic_cast<MovingRobot*>(robots[i])) {
                cout << "Enter movement for " << movingRobot->getName() << " (posX(enter 1 to move right, enter-1 to move left) posY(enter 1 to move up, enter -1 to move down)): ";
                cin >> posX >> posY;
                if (posX >= -1 && posX <= 1 && posY >= -1 && posY <= 1) {
                    movingRobot->moving(to_string(posX), to_string(posY));
                } else {
                    cout << "Invalid movement. Try again." << endl;
                }
                break; // Move only the first MovingRobot found
            }
        }

        // Simulate actions for all ShootingRobots
        for (int i = 0; i < numRobots; ++i) {
            if (ShootingRobot* shootingRobot = dynamic_cast<ShootingRobot*>(robots[i])) {
                shootingRobot->fire(mapX, mapY);
            }
        }

        // Simulate the battlefield
        battlefield.simulateWar();

        // Print robot statuses
        for (int i = 0; i < numRobots; ++i) {
            cout << robots[i]->getName() << " position: (" << robots[i]->getPosX() << ", " << robots[i]->getPosY() << ")" << endl;
            cout << robots[i]->getName() << " kills: " << robots[i]->getKill() << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'n') {
            running = false; // Stop the loop if the user chooses to stop
        }

        cout << endl;
        ++turn; // Increment the turn counter
    }

    // Clean up the memory
    for (int i = 0; i < numRobots; ++i) {
        delete robots[i];
    }

    return 0;
}
