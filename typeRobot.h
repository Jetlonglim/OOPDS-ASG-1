//typeRobot.h
#ifndef typeROBOT_H
#define typeROBOT_H
#include "robot.h"

#include <iostream>

using namespace std;

class RoboCop : public MovingRobot, public ShootingRobot, public SeeingRobot {
public:
    RoboCop(const std::string& name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), ShootingRobot(name, x, y), SeeingRobot(name, x, y) {}
    void look() override {
        // Implementation of look
    }
    void move() override {
        // Implementation of move
    }
    void fire() override {
        // Implementation of fire
    }
};

class Terminator : public MovingRobot, public SeeingRobot, public SteppingRobot {
public:
    Terminator(const std::string& name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), SeeingRobot(name, x, y), SteppingRobot(name, x, y) {}
    void look() override {
        // Implementation of look
    }
    void move() override {
        // Implementation of move
    }
    void fire() override {
        // Terminator does not fire
    }
};

class TerminatorRoboCop : public Terminator, public RoboCop {
public:
    void move() override{
        Terminator::move(); // Use the look() function from Terminator
    }
    void look() override{
        RoboCop::look(); // Use the look() function from RoboCop
    }
    void fire() override{
        RoboCop::move(); // Use the look() function from RoboCop
    }
};

class BlueThunder : public ShootingRobot{
    BlueThunder(const std::string& name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y) {}
};

class MadBot : public ShootingRobot{
    MadBot(const std::string& name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y) {}
};

class RoboTank : public ShootingRobot{
    RoboTank(const std::string& name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y) {}
};

class UltimateRobot : public MovingRobot,  public ShootingRobot, public SteppingRobot {
    UltimateRobot(const std::string& name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y) {}
};

#endif
