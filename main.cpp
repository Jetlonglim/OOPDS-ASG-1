#include "battlefield.h"
#include "battlefield.cpp"
#include "robot.h"
#include "typeRobot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// Function to print the current state of the battlefield
void printBattlefield(Battlefield &battlefield, Robot* robots[], int numRobots) {
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

int main() {
    srand(time(0));
    ofstream logFile("battlefield_log.txt");

    // Create a battlefield object
    Battlefield battlefield;

    // Array to hold robots
    Robot* robots[MAX_ROBOTS];

    // User input for number of robots
    int numRobots;
    cout << "Enter the number of robots: ";
    cin >> numRobots;
    cout <<  endl;

    for (int i = 0; i < numRobots; ++i) {
        string name, type;
        cout << "Enter the name for robot " << i + 1 << ": ";
        cin >> name;
        cout << "Enter the type for robot " << i + 1 << " (RoboCop/Terminator/TerminatorRoboCop): ";
        cin >> type;

        if (type == "RoboCop") {
            robots[i] = new RoboCop(name, "random", "random", 0);
        } else if (type == "Terminator") {
            robots[i] = new Terminator(name, "random", "random", 0);
        } else if (type == "TerminatorRoboCop") {
            robots[i] = new TerminatorRoboCop(name, "random", "random", 0);
        } else {
            cout << "Unknown robot type. Exiting." << endl;
            return 1;
        }

        robots[i]->setAlive(true);
    }

    bool running = true;
    int posX, posY;
    int turn = 0;

    while (running) {
        cout << "Round " << turn + 1 << endl;
        printBattlefield(battlefield, robots, numRobots);

        // Input and move the first MovingRobot found
        for (int i = 0; i < numRobots; ++i) {
            if (MovingRobot* movingRobot = dynamic_cast<MovingRobot*>(robots[i])) {
                cout << "Enter movement for " << movingRobot->getName() << " (posX(1 to move right, -1 to move left, 0 to stay) posY(1 to move up, -1 to move down, 0 to stay)): ";
                cin >> posX >> posY;
                if (posX >= -1 && posX <= 1 && posY >= -1 && posY <= 1) {
                    movingRobot->move(&robots[0], posX, posY);
                } else {
                    cout << "Invalid movement. Try again." << endl;
                }
                break; // Move only the first MovingRobot found
            }
        }

            // Simulate actions for all ShootingRobots
            for (int i = 0; i < numRobots; ++i) {
                if (ShootingRobot* shootingRobot = dynamic_cast<ShootingRobot*>(robots[i])) {
                    shootingRobot->fire(&robots[0], mapX, mapY);
                }
            }

            // Simulate the battlefield
            battlefield.simulateWar();

            // Print robot statuses
            for (int i = 0; i < numRobots; ++i) {
                cout << robots[i]->getName() << " position: (" << robots[i]->getPosX() << ", " << robots[i]->getPosY() << ")" << endl;
                cout << robots[i]->getName() << " kills: " << robots[i]->getKill() << endl;
            }

            logFile << "M by N: " << mapX << " " << mapY << endl;
            logFile << "steps:"<< turn << endl;// Starting step starts from 1 depends on the turn
            logFile << "robots: " << numRobots << endl;
            
            for (int i = 0; i < numRobots; ++i) {
                logFile << robots[i]->getType() << " " << robots[i]->getName() << " ("
                     << robots[i]->getPosX() << ", " << robots[i]->getPosY() << ")" << endl;
    }

        cout << "Do you want to continue to the next turn? (Press Enter to continue, type 'n' to stop): ";
        string choice;
        cin.ignore();
        getline(cin, choice);

        if (choice == "n") {
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
