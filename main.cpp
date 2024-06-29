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

const int MAP_X = 10; // map width
const int MAP_Y = 10; // map height
const int MAX_ROBOTS = 100; // maximum number of robots that can be added to the battlefield

// Function to print the current state of the battlefield
void printBattlefield(Battlefield &battlefield) {
    char battlefieldMap[MAP_Y][MAP_X];
    
    // Initialize the battlefield with '.'
    for (int i = 0; i < MAP_Y; ++i) {
        for (int j = 0; j < MAP_X; ++j) {
            battlefieldMap[i][j] = '.';
        }
    }
    
    // Get the robots from the linked list and place them on the battlefield
    Node* current = battlefield.getRobots().getHead();
    while (current != nullptr) {
        Robot* robot = current->getData();
        if (robot->isAlive()) {
            char robotInitial = robot->getName()[0];
            battlefieldMap[robot->getPosY()][robot->getPosX()] = robotInitial;
        }
        current = current->getNext();
    }

    // Print the battlefield
    for (int i = 0; i < MAP_Y; ++i) {
        for (int j = 0; j < MAP_X; ++j) {
            cout << battlefieldMap[i][j] << ' ';
        }
        cout << endl;
    }
}

Robot* createRobot(const string& type, const string& name, const string& x, const string& y, int kills) {
    int posX = x == "random" ? rand() % MAP_X : stoi(x);
    int posY = y == "random" ? rand() % MAP_Y : stoi(y);
    
    if (type == "R") {
        return new RoboCop(name, posX, posY, kills);
    } else if (type == "M") {
        return new MadBot(name, posX, posY, kills);
    } else if (type == "T") {
        return new Terminator(name, posX, posY, kills);
    } else if (type == "B") {
        return new BlueThunder(name, posX, posY, kills);
    } else if (type == "K") {
        return new RoboTank(name, posX, posY, kills);
    } else {
        cerr << "Unknown robot type: " << type << endl;
        exit(1);
    }
}

int main() {
    srand(time(0));
    ofstream logFile("battlefield_log.txt");

    // Create a battlefield object
    Battlefield battlefield;

    // User input for number of robots
    int numRobots;
    cout << "Enter the number of robots: ";
    cin >> numRobots;
    cout << endl;

    for (int i = 0; i < numRobots; ++i) {
        string type, name, x, y;
        cout << "Enter the type of robot (RoboCop[R], MadBot[M], Terminator[T], BlueThunder[B], RoboTank[T]): ";
        cin >> type;
        cout << "Enter the name of the robot: ";
        cin >> name;
        cout << "Enter the initial x position of the robot: ";
        cin >> x;
        cout << "Enter the initial y position of the robot: ";
        cin >> y;

        Robot* robot = createRobot(type, name, x, y, 0);
        battlefield.addRobot(robot);
    }
    // Simulation loop
    bool running = true;
    int turn = 0;

    while (running) {
        cout << "Round " << turn + 1 << endl;
        printBattlefield(battlefield);

        // Simulate actions for all robots
        battlefield.simulateWar();

        // Print robot statuses
        Node* current = battlefield.getRobots().getHead();
        while (current != nullptr) {
            Robot* robot = current->getData();
            cout << robot->getName() << " position: (" << robot->getPosX() << ", " << robot->getPosY() << ")" << endl;
            cout << robot->getName() << " kills: " << robot->getKill() << endl;
            current = current->getNext();
        }

        logFile << "M by N: " << MAP_X << " " << MAP_Y << endl;
        logFile << "steps: " << turn + 1 << endl; // Steps start from 1
        logFile << "robots: " << numRobots << endl;

        current = battlefield.getRobots().getHead();
        while (current != nullptr) {
            Robot* robot = current->getData();
            logFile << robot->getType() << " " << robot->getName() << " ("
                 << robot->getPosX() << ", " << robot->getPosY() << ")" << endl;
            current = current->getNext();
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

    return 0;
}
