#ifndef TYPE_ROBOT_H
#define TYPE_ROBOT_H

#include "robot.h"
#include <iostream>

using namespace std;

// Base class for robots with movement capability
class MovingRobot : virtual public Robot {
public:
    using Robot::Robot;
    virtual void move(Robot* robots[], int mapX, int mapY) = 0;
};

// Base class for robots with shooting capability
class ShootingRobot : virtual public Robot {
public:
    using Robot::Robot;
    virtual void fire(Robot* robots[], int mapX, int mapY) = 0;
};

// Base class for robots with seeing capability
class SeeingRobot : virtual public Robot {
public:
    using Robot::Robot;
    virtual void look(Robot* robots[], int mapX, int mapY) = 0;
};

// Base class for robots with stepping capability
class SteppingRobot : virtual public Robot {
public:
    using Robot::Robot;
    virtual void step(Robot* robots[], int mapX, int mapY) = 0;
};

// RoboCop can move, shoot, and see
class RoboCop : public MovingRobot, public ShootingRobot, public SeeingRobot {
public:
    using MovingRobot::MovingRobot;  // Constructor inheritance
    void look(Robot* robots[], int mapX, int mapY) override {
        // Implementation of look
        int posX = getPosX();
        int posY = getPosY();
        cout << Name << " is looking around its position: (" << posX << ", " << posY << ")\n";
        for (int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
                cout << "(" << (posX + i) << ", " << (posY + j) << ") ";
            }
            cout << endl;
        }
    }
    void move(Robot* robots[], int mapX, int mapY) override {
        // Implementation of move
        int newX = mapX;
        int newY = mapY;
        int posX = getPosX();
        int posY = getPosY();

        if (newX > 0) posX++;
        else if (newX < 0) posX--;
        
        if (newY > 0) posY++;
        else if (newY < 0) posY--;

        setPosX(posX);
        setPosY(posY);

        cout << "New position: (" << posX << ", " << posY << ")" << endl;
    }
    void fire(Robot* robots[], int mapX, int mapY) override {
        // Implementation of fire
        // Fire at random positions with maximum city block distance of 10
        srand(time(0));
        int killCount = 0;
        for (int i = 0; i < 3; ++i) {
            int targetX = getPosX() + (rand() % 21 - 10);
            int targetY = getPosY() + (rand() % 21 - 10);
            if (abs(targetX - getPosX()) + abs(targetY - getPosY()) <= 10) {
                for (int j = 0; j < 10; ++j) {
                    if (robots[j]->isAlive() && robots[j]->getPosX() == targetX && robots[j]->getPosY() == targetY) {
                        robots[j]->setAlive(false);
                        AddKill();
                        killCount++;
                        break;
                    }
                }
            }
        }
        if (killCount >= 3) {
            // Upgrade logic to TerminatorRoboCop
        }
    }
    string getType() const override { return "RoboCop"; }
};

// Terminator can move and see, and step on robots
class Terminator : public MovingRobot, public SeeingRobot, public SteppingRobot {
public:
    using MovingRobot::MovingRobot;  // Constructor inheritance
    void look(Robot* robots[], int mapX, int mapY) override {
        // Implementation of look
        int posX = getPosX();
        int posY = getPosY();
        cout << Name << " is looking around its position: (" << posX << ", " << posY << ")\n";
        for (int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
                cout << "(" << (posX + i) << ", " << (posY + j) << ") ";
            }
            cout << endl;
        }
    }
    void move(Robot* robots[], int mapX, int mapY) override {
        // Implementation of move
        int newX = mapX;
        int newY = mapY;
        int posX = getPosX();
        int posY = getPosY();

        if (newX > 0) posX++;
        else if (newX < 0) posX--;
        
        if (newY > 0) posY++;
        else if (newY < 0) posY--;

        setPosX(posX);
        setPosY(posY);

        cout << "New position: (" << posX << ", " << posY << ")" << endl;
    }
    void step(Robot* robots[], int mapX, int mapY) override {
        // Implementation of stepping on robots
        cout << Name << " is stepping on robots" << endl;
    }
    string getType() const override { return "Terminator"; }
};

// TerminatorRoboCop combines capabilities of Terminator and RoboCop
class TerminatorRoboCop : public Terminator, public RoboCop {
public:
    using Terminator::Terminator;  // Constructor inheritance
    void move(Robot* robots[], int mapX, int mapY) override {
        RoboCop::move(robots, mapX, mapY);  // Use the move function from RoboCop
    }
    void look(Robot* robots[], int mapX, int mapY) override {
        RoboCop::look(robots, mapX, mapY);
    }
    void fire(Robot* robots[], int mapX, int mapY) override {
        RoboCop::fire(robots, mapX, mapY);
    }
    void step(Robot* robots[], int mapX, int mapY) override {
        Terminator::step(robots, mapX, mapY);
        if (getKill() >= 3) {
            // Upgrade logic to UltimateRobot
        }
    }
    string getType() const override { return "TerminatorRoboCop"; }
};

class BlueThunder : public ShootingRobot {
public:
    using ShootingRobot::ShootingRobot;
    void fire(Robot* robots[], int mapX, int mapY) override {
        int posX = getPosX();
        int posY = getPosY();

        cout << Name << " is firing at 3x3 blocks around its position: (" << posX << ", " << posY << ")\n";

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int targetX = posX + i;
                int targetY = posY + j;
                for (int k = 0; k < 10; ++k) {
                    if (robots[k]->isAlive() && robots[k]->getPosX() == targetX && robots[k]->getPosY() == targetY) {
                        robots[k]->setAlive(false);
                        AddKill();
                        break;
                    }
                }
            }
        }

        if (getKill() >= 3) {
            // Upgrade to MadBot
        }
    }
    string getType() const override { return "BlueThunder"; }
};

class MadBot : public ShootingRobot {
public:
    using ShootingRobot::ShootingRobot;
    void fire(Robot* robots[], int mapX, int mapY) override {
        srand(time(0));
        int posX = getPosX();
        int posY = getPosY();

        int targetX = posX + (rand() % 3 - 1);
        int targetY = posY + (rand() % 3 - 1);

        cout << Name << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == targetX && robots[i]->getPosY() == targetY) {
                robots[i]->setAlive(false);
                AddKill();
                break;
            }
        }

        if (getKill() >= 3) {
            // Upgrade to UltimateRobot
        }
    }
    string getType() const override { return "MadBot"; }
};

class RoboTank : public ShootingRobot {
public:
    using ShootingRobot::ShootingRobot;
    void fire(Robot* robots[], int mapX, int mapY) override {
        srand(time(0));
        int targetX = rand() % mapX;
        int targetY = rand() % mapY;

        cout << Name << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == targetX && robots[i]->getPosY() == targetY) {
                robots[i]->setAlive(false);
                AddKill();
                break;
            }
        }

        if (getKill() >= 3) {
            // Upgrade to UltimateRobot
        }
    }
    string getType() const override { return "RoboTank"; }
};

class UltimateRobot : public MovingRobot, public ShootingRobot, public SteppingRobot {
public:
    using MovingRobot::MovingRobot;
    void move(Robot* robots[], int mapX, int mapY) override {
        // Implement movement logic similar to TerminatorRoboCop
    }
    void fire(Robot* robots[], int mapX, int mapY) override {
        srand(time(0));
        for (int i = 0; i < 3; ++i) {
            int targetX = rand() % mapX;
            int targetY = rand() % mapY;

            cout << Name << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

            for (int j = 0; j < 10; ++j) {
                if (robots[j]->isAlive() && robots[j]->getPosX() == targetX && robots[j]->getPosY() == targetY) {
                    robots[j]->setAlive(false);
                    AddKill();
                    break;
                }
            }
        }
    }
    void step(Robot* robots[], int mapX, int mapY) override {
        // Implement stepping logic similar to Terminator
    }
    string getType() const override { return "UltimateRobot"; }
};

#endif
