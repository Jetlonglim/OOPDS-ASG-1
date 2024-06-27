#include "battlefield.h"
#include "robot.h"
#include "linkedlist.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

Battlefield::Battlefield() {
    srand(time(0));
    initializeBattlefield();
}

void Battlefield::initializeBattlefield() {
    for (int i = 0; i < mapY; ++i) {
        for (int j = 0; j < mapX; ++j) {
            battlefieldMap[i][j] = '.';
        }
    }
}

void Battlefield::addRobot(Robot* robot) {
    if (robots.getSize() < MAX_ROBOTS) {
        robots.insert(robot);
    } else {
        cout << "Maximum number of robots reached." << endl;
    }
}

void Battlefield::clearDeadRobots() {
    Node* current = robots.getHead();
    Node* prev = nullptr;
    while (current != nullptr) {
        Robot* robot = current->getData();
        if (!robot->isAlive()) {
            if (respawnCount[robot] < MAX_RESPAWNS) {
                respawnQueue.push(robot);
                respawnCount[robot]++;
            } else {
                delete robot;
                if (prev) {
                    prev->setNext(current->getNext());
                } else {
                    robots.setHead(current->getNext());
                }
                Node* toDelete = current;
                current = current->getNext();                
                delete current;
            }
        } else {
            prev = current;
            current = current->getNext();
        }        
    }
}

void Battlefield::removeRobot(Robot* robot) {
    Node* current = robots.getHead();
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->robot == robot) {
            if (prev) {
                prev->next = current->next;
            } else {
                robots.setHead(current->next);
            }
            delete current->robot;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void Battlefield::simulateWar() {
    Node* current = robots.getHead();
    while (current != nullptr) {
        Robot* currentRobot = current->getData();
        if (currentRobot->isAlive()) {
            Node* opponent = robots.getHead();
            while (opponent != nullptr) {
                Robot* opponentRobot = opponent->getData();
                if (opponentRobot->isAlive() && currentRobot != opponentRobot) {
                    currentRobot->interact(opponentRobot, mapX, mapY);
                }
                opponent = opponent->getNext();
            }
        }
        current = current->getNext();
    }
    clearDeadRobots();
}

void Battlefield::respawnRobots() {
    while (!respawnQueue.empty()) {
        Robot* robot = respawnQueue.front();
        respawnQueue.pop();
        robot->resetPosition(mapX, mapY);  // Reset position and re-enter the battlefield
        robot->setAlive(true);  // Make sure the robot is set to alive
        robots.insert(robot);  // Insert respawned robot into the linked list
    }
}

void Battlefield::printBattlefield() {
    cout << "Current Battlefield State:" << endl;
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            cout << battlefieldMap[i][j] << ' ';
        }
        cout << endl;
    }
}

Battlefield::~Battlefield() {
    Node* current = robots.getHead();
    while (current != nullptr) {
        Node* next = current->getNext();
        delete current->getData();  // Delete the Robot object
        delete current;             // Delete the Node
        current = next;
    }
}
