#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include "robot.h"
#include "linkedlist.h"

using namespace std;

// Class representing a battlefield
class Battlefield {
private:
    // Constants
    static const int mapX = 10;  // Width of the battlefield
    static const int mapY = 10;  // Height of the battlefield
    static const int MAX_ROBOTS = 100;  // Maximum number of robots that can be added to the battlefield
    static const int MAX_RESPAWNS = 3;  // Maximum number of times a robot can be respawned

    LinkedList robots;  // Linked list to store the robots on the battlefield
    char battlefieldMap[mapY][mapX];  // Matrix to represent the battlefield
    queue<Robot*> respawnQueue;  // Queue to store robots that are ready to be respawned
    map<Robot*, int> respawnCount;  // Map to store the number of times a robot has been respawned

    // Function to remove robots from the battlefield that are not alive
    void clearDeadRobots();

public:
    // Constructor that initializes the battlefield
    Battlefield();

    // Function to initialize the battlefield with '.'
    void initializeBattlefield();

    // Function to add a robot to the battlefield
    void addRobot(Robot* robot);

    // Function to simulate a war on the battlefield
    void simulateWar();

    // Function to respawn robots from the respawn queue
    void respawnRobots();

    // Function to print the current state of the battlefield
    void printBattlefield();

    // Function to remove a robot from the battlefield
    void removeRobot(Robot* robot);

    LinkedList& getRobots() { 
        return robots;
    }

    // Destructor that deletes all robots on the battlefield
    ~Battlefield();
};

#endif // BATTLEFIELD_H
