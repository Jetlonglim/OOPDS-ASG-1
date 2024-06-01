#include "battlefield.h"
#include "robot.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Battlefield::Battlefield()
{
    numRobots = 0;
}

void Battlefield::addRobot(Robot *robot)
{
    if (numRobots < MAX_ROBOTS)
    {
        robots[numRobots] = robot;
        numRobots++;
    }
    else
    {
        cout << "Battlefield is full. Cannot add more robots." << endl;
    }
}

void Battlefield::simulateWar()
{
    srand(time(0));
    ofstream logFile("battlefield_log.txt");

    for (int turn = 0; turn < 10; ++turn)
    { // Example: Simulate 10 turns in 1 Round
        cout << "Turn " << turn + 1 << endl;
        logFile << "Turn " << turn + 1;

        update();
        display(logFile);

        logFile << endl;
        cout << endl;

        // Output the battlefield map
        for (int i = 0; i < mapY; ++i)
        {
            for (int j = 0; j < mapX; ++j)
            {
                battlefieldMap[i][j] = '*';
                cout << battlefieldMap[i][j];
            }
            cout << endl;
        }

            // Print the battlefield map
            for (int i = 0; i < mapY; ++i)
            {
                for (int j = 0; j < mapX; ++j)
                {
                    cout << battlefieldMap[i][j];
                }
                cout << endl;
            }

            // Log the battlefield status
            logFile << "Displaying battlefield:" << endl;
            for (int i = 0; i < numRobots; ++i)
            {
                if (robots[i]->isAlive())
                { // Check if the robot is alive
                    logFile << "Robot " << i + 1 << " - Position: ("
                            << robots[i]->getPosX() << ", "
                            << robots[i]->getPosY() << ")" << endl;
                }
            }
        }

        for (int i = 0; i < numRobots; i++)
        {
            for (int j = i + 1; j < numRobots; j++)
            {
                Robot *robot1 = robots[i];
                Robot *robot2 = robots[j];
                if (robot1->getPosX() == robot2->getPosX() && robot1->getPosY() == robot2->getPosY())
                {
                    if (ShootingRobot *sr1 = dynamic_cast<ShootingRobot *>(robot1))
                    {
                        sr1->fire(mapX, mapY);
                    }
                    if (ShootingRobot *sr2 = dynamic_cast<ShootingRobot *>(robot2))
                    {
                        sr2->fire(mapX, mapY);
                    }
                }
            }
        }
    

    logFile.close(); // Close the log file
};

void Battlefield::update()
{
    cout << "Updating battlefield..." << endl;
    for (int i = 0; i < numRobots; ++i)
    {
        // Example update logic
        // Here we can add logic to move robots, handle collisions, etc.
        if (MovingRobot *mr = dynamic_cast<MovingRobot *>(robots[i]))
        {
            int newX = rand() % 3 - 1; // Random movement in X direction
            int newY = rand() % 3 - 1; // Random movement in Y direction

            // Ensure new position is within the boundaries of the map
            newX = max(0, std::min(newX, mapX - 1));
            newY = max(0, std::min(newY, mapX - 1));
            mr->moving(to_string(newX), to_string(newY));

        }
    }
}
void Battlefield::display(ofstream &logFile)
{
    cout << "Displaying battlefield:" << endl;
    for (int i = 0; i < numRobots; ++i)
    {
        cout << "Robot " << i + 1 << " - Position: ("
             << robots[i]->getPosX() << ", "
             << robots[i]->getPosY() << ")" << endl;
    }
    
}
