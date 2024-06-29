#ifndef TYPE_ROBOT_H
#define TYPE_ROBOT_H

#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Base class for robots with movement capability
class MovingRobot : virtual public Robot {
public:
    MovingRobot(const Robot& robot): Robot(robot) {
        // Initialize MovingRobot specific members if needed
    }
    using Robot::Robot;
    virtual void move(Robot* robots[], int mapX, int mapY) = 0;
};

// Base class for robots with shooting capability
class ShootingRobot : virtual public Robot {
public:
    ShootingRobot(const Robot& robot) : Robot(robot) {
        // Initialize ShootingRobot specific members if needed
    }
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
    SteppingRobot(const Robot& robot) : Robot(robot) {
        // Initialize SteppingRobot specific members if needed
    }
    using Robot::Robot;
    virtual void step(Robot* robots[], int mapX, int mapY) = 0;
};

// RoboCop can move, shoot, and see
class RoboCop : public MovingRobot, public ShootingRobot, public SeeingRobot {
public:
    using MovingRobot::MovingRobot;
    RoboCop(string name, int x, int y, int kills) 
        : Robot(name, x, y, kills), MovingRobot(name, x, y, kills), ShootingRobot(name, x, y, kills), SeeingRobot(name, x, y, kills) {}

    void look(Robot* robots[], int mapX, int mapY) override {
        int posX = getPosX();
        int posY = getPosY();
        cout << getName() << " is looking around its position: (" << posX << ", " << posY << ")\n";
        for (int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
                cout << "(" << (posX + i) << ", " << (posY + j) << ") ";
            }
            cout << endl;
        }
    }

    void move(Robot* robots[], int mapX, int mapY) override {
        int posX = getPosX();
        int posY = getPosY();
        int direction = rand() % 4;

        switch (direction) {
            case 0: if (posX > 0) posX--; break; // Move left
            case 1: if (posX < mapX - 1) posX++; break; // Move right
            case 2: if (posY > 0) posY--; break; // Move up
            case 3: if (posY < mapY - 1) posY++; break; // Move down
        }

        setPosX(posX);
        setPosY(posY);

        cout << getName() << " moved to position: (" << posX << ", " << posY << ")" << endl;
    }


    void fire(Robot* robots[], int mapX, int mapY) override {
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
        // if (killCount >= 3) {
        //     // Upgrade logic to TerminatorRoboCop
        //     upgradeToTerminatorRoboCop(robots);
        // }
    }

    string getType() const override { return "RoboCop"; }

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            fire(&other, mapX, mapY);
        }
    }

    // void upgradeToTerminatorRoboCop(Robot* robots[]) {
    //     // Create a new instance of TerminatorRoboCop
    //     TerminatorRoboCop* upgradedRobot = new TerminatorRoboCop(*this);

    //     // Find the current RoboCop instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current RoboCop with the new TerminatorRoboCop instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old RoboCop instance
    //             break;
    //         }
    //     }

    //     cout << "RoboCop has been upgraded to TerminatorRoboCop!" << endl;
    // }
};

// Terminator can move and see, and step on robots
class Terminator : public MovingRobot, public SeeingRobot, public SteppingRobot {
public:
    Terminator(string name, int x, int y, int kills) 
        : Robot(name, x, y, kills), MovingRobot(name, x, y, kills), SeeingRobot(name, x, y, kills), SteppingRobot(name, x, y, kills) {}

    Terminator(const RoboCop& roboCop) : Robot(roboCop), MovingRobot(roboCop), SeeingRobot(roboCop), SteppingRobot(roboCop) {
        // Additional initialization if needed
    }

    void look(Robot* robots[], int mapX, int mapY) override {
        int posX = getPosX();
        int posY = getPosY();
        cout << getName() << " is looking around its position: (" << posX << ", " << posY << ")\n";
        for (int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
                cout << "(" << (posX + i) << ", " << (posY + j) << ") ";
            }
            cout << endl;
        }
    }

    void move(Robot* robots[], int mapX, int mapY) override {
        // Implementation of move
        int posX = getPosX();
        int posY = getPosY();
        int direction = rand() % 4;

        switch (direction) {
            case 0: if (posX > 0) posX--; break;
            case 1: if (posX < mapX - 1) posX++; break;
            case 2: if (posY > 0) posY--; break;
            case 3: if (posY < mapY - 1) posY++; break;
        }

        setPosX(posX);
        setPosY(posY);

        cout << getName() << " moved to position: (" << posX << ", " << posY << ")" << endl;
    }

    void step(Robot* robots[], int mapX, int mapY) override {
        // Implementation of stepping on robots
        cout << getName() << " is stepping on robots" << endl;
        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && abs(robots[i]->getPosX() - getPosX()) <= 1 && abs(robots[i]->getPosY() - getPosY()) <= 1) {
                robots[i]->setAlive(false);
                AddKill();
                cout << getName() << " stepped on " << robots[i]->getName() << endl;
            }
        }
        // if (getKill() >= 3) {
        //     // Upgrade logic to TerminatorRoboCop
        //     upgradeToTerminatorRoboCop(robots);
        // }
    }

    string getType() const override { return "Terminator"; }

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            step(&other, mapX, mapY);
        }
    }

    // void upgradeToTerminatorRoboCop(Robot* robots[]) {
    //     // Create a new instance of TerminatorRoboCop
    //     TerminatorRoboCop* upgradedRobot = new TerminatorRoboCop(*this);

    //     // Find the current Terminator instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current Terminator with the new TerminatorRoboCop instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old Terminator instance
    //             break;
    //         }
    //     }

    //     cout << "Terminator has been upgraded to TerminatorRoboCop!" << endl;
    // }
};

// TerminatorRoboCop combines capabilities of Terminator and RoboCop
class TerminatorRoboCop : public Terminator, public RoboCop {
public:
    using Terminator::Terminator;
    using RoboCop::RoboCop;  // Constructor inheritance
    TerminatorRoboCop(const string& name, int x, int y, int kills) 
        : Robot(name, x, y, kills), Terminator(name, x, y, kills), RoboCop(name, x, y, kills) {}

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
        // if (getKill() >= 3) {
        //     // Upgrade logic to UltimateRobot
        //     upgradeToUltimateRobot(robots);
        // }
    }

    string getType() const override { return "TerminatorRoboCop"; }

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            step(&other, mapX, mapY);
        }
    }

    // void upgradeToUltimateRobot(Robot* robots[]) {
    //     // Create a new instance of TerminatorRoboCop
    //     UltimateRobot* upgradedRobot = new UltimateRobot(*this);

    //     // Find the current Terminator instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current Terminator with the new UltimateRobot instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old Terminator instance
    //             break;
    //         }
    //     }

    //     cout << "Terminator has been upgraded to TerminatorRoboCop!" << endl;
    // }
};

// BlueThunder can shoot
class BlueThunder : public ShootingRobot {
public:
    using ShootingRobot::ShootingRobot;
    // BlueThunder(const string& name, int x, int y, int kills) 
    //     : Robot(name, x, y, kills), ShootingRobot(name, x, y, kills), fireSequenceIndex(0) {}


    void move(Robot* robots[], int mapX, int mapY) override {
        // MadBot does not move, so we provide an empty implementation.
    }
    void fire(Robot* robots[], int mapX, int mapY) override {
        // Define the firing sequence (clockwise starting from up)
        static const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        static const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

        int posX = getPosX();
        int posY = getPosY();


        // Increment fire sequence index and wrap around using modulo
        fireSequenceIndex = (fireSequenceIndex + 1) % 8;
        // Get target coordinates
        int targetX = posX + dx[fireSequenceIndex];
        int targetY = posY + dy[fireSequenceIndex];

        cout << Name << " is firing at position: (" << targetX << ", " << targetY << ")\n";

        // Check if there's any robot at the target location and shoot
        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == targetX && robots[i]->getPosY() == targetY) {
                robots[i]->setAlive(false);
                AddKill();
                // if (getKill() >= 3) {
                //     // Upgrade to MadBot
                //     upgradeToMadBot(robots);
                // }
                break;
            }
        }
    }

    string getType() const override { return "BlueThunder"; }

    int fireSequenceIndex;  // Track the current fire sequence index

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            fire(&other, mapX, mapY);
        }
    }
    // void upgradeToMadBot(Robot* robots[]) {
    //     MadBot* upgradedRobot = new MadBot(*this);

    //     // Find the current BlueThunder instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current BlueThunder with the new MadBot instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old BlueThunder instance
    //             break;
    //         }
    //     }

    //     cout << "BlueThunder has been upgraded to MadBot!" << endl;
    // }
};


// MadBot can shoot
class MadBot : public ShootingRobot {
public:
    using ShootingRobot::ShootingRobot;


    void move(Robot* robots[], int mapX, int mapY) override {
        // MadBot does not move, so we provide an empty implementation.
    }

    void fire(Robot* robots[], int mapX, int mapY) override {
        // Define the possible target offsets (immediate neighbors)
        static const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        static const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

        int posX = getPosX();
        int posY = getPosY();

        // Randomly select one of the neighboring positions
        srand(time(0));
        int randomIndex = rand() % 8;
        int targetX = posX + dx[randomIndex];
        int targetY = posY + dy[randomIndex];

        cout << getName() << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

        // Check if there's any robot at the target location and shoot
        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == targetX && robots[i]->getPosY() == targetY) {
                robots[i]->setAlive(false);
                AddKill();
                // if (getKill() >= 3) {
                //     // Upgrade to RoboTank
                //     upgradeToRoboTank(robots);
                // }
                break;
            }
        }
    }

    string getType() const override { return "MadBot"; }

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            fire(&other, mapX, mapY);
        }
    }
    // void upgradeToRoboTank(Robot* robots[]) {
    //     RoboTank* upgradedRobot = new RoboTank(*this);

    //     // Find the current MadBot instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current MadBot with the new RoboTank instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old MadBot instance
    //             break;
    //         }
    //     }

    //     cout << "MadBot has been upgraded to RoboTank!" << endl;
    // }
};


// RoboTank can shoot
class RoboTank : public ShootingRobot{
public:
    using ShootingRobot::ShootingRobot;
    // RoboTank(const string& name, int x, int y, int kills) 
    //     : Robot(name, x, y, kills), ShootingRobot(name, x, y, kills) {}
    
    void move(Robot* robots[], int mapX, int mapY) override {
        // MadBot does not move, so we provide an empty implementation.
    }
    void fire(Robot* robots[], int mapX, int mapY) override {
        srand(time(0));
        int targetX = rand() % mapX;
        int targetY = rand() % mapY;

        cout << getName() << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == targetX && robots[i]->getPosY() == targetY) {
                robots[i]->setAlive(false);
                AddKill();
                // if (getKill() >= 3) {
                //     // Upgrade to UltimateRobot
                //     upgradeToUltimateRobot(robots);
                // }
                break;
            }
        }
    }

    string getType() const override { return "RoboTank"; }

    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            fire(&other, mapX, mapY);
        }
    }
    // void upgradeToUltimateRobot(Robot* robots[]) {
    //     UltimateRobot* upgradedRobot = new UltimateRobot(*this);

    //     // Find the current RoboTank instance in the robots array
    //     for (int i = 0; i < 10; ++i) {
    //         if (robots[i] == this) {
    //             // Replace the current RoboTank with the new UltimateRobot instance
    //             robots[i] = upgradedRobot;
    //             delete this;  // Free the memory of the old RoboTank instance
    //             break;
    //         }
    //     }

    //     cout << "RoboTank has been upgraded to UltimateRobot!" << endl;
    // }
};


// UltimateRobot has all capabilities
class UltimateRobot : public MovingRobot, public ShootingRobot, public SteppingRobot, public SeeingRobot {
public:
    using MovingRobot::MovingRobot;
    UltimateRobot(const string& name, int x, int y, int kills) 
        : Robot(name, x, y, kills), MovingRobot(name, x, y, kills), ShootingRobot(name, x, y, kills), SteppingRobot(name, x, y, kills) {}

    void move(Robot* robots[], int mapX, int mapY) override {
        int newX = mapX;
        int newY = mapY;
        int posX = getPosX();
        int posY = getPosY();

        // Simple move logic: moves towards a corner (bottom-right) as a placeholder
        if (newX > 0) posX++;
        else if (newX < 0) posX--;
        
        if (newY > 0) posY++;
        else if (newY < 0) posY--;

        setPosX(posX);
        setPosY(posY);

        cout << getName() << " moved to new position: (" << posX << ", " << posY << ")" << endl;
    }

    void fire(Robot* robots[], int mapX, int mapY) override {
        srand(time(0));
        for (int i = 0; i < 3; ++i) {
            int targetX = rand() % mapX;
            int targetY = rand() % mapY;

            cout << getName() << " is firing at random position: (" << targetX << ", " << targetY << ")\n";

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
        // Step on robots in the current position
        int posX = getPosX();
        int posY = getPosY();

        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i]->getPosX() == posX && robots[i]->getPosY() == posY) {
                robots[i]->setAlive(false);
                cout << getName() << " is stepping on robots" << endl;
                AddKill();
            }
        }
    }
    void look(Robot* robots[], int mapX, int mapY) override {
        cout << getName() << " is looking around.\n";
        int posX = getPosX();
        int posY = getPosY();
        for (int i = 0; i < 10; ++i) {
            if (robots[i]->isAlive() && robots[i] != this) {
                int distanceX = abs(robots[i]->getPosX() - posX);
                int distanceY = abs(robots[i]->getPosY() - posY);
                if (distanceX <= 5 && distanceY <= 5) {
                    cout << "Detected " << robots[i]->getType() << " at position (" << robots[i]->getPosX() << ", " << robots[i]->getPosY() << ")\n";
                }
            }
        }
    }
    void interact(Robot* other, int mapX, int mapY) override {
        if (isAlive() && other->isAlive()) {
            fire(&other, mapX, mapY);
        }
    }

    string getType() const override { return "UltimateRobot"; }
};

#endif // TYPE_ROBOT_H
