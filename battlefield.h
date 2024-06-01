#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

const int BATTLEFIELD_ROWS = 30;
const int BATTLEFIELD_COLUMNS = 80;
const int MAX_ROBOTS = 100;

class Robot;

class Battlefield {
public:
    Battlefield();
    void addRobot(Robot* robot);
    void simulateWar();

private:
    Robot* robots[MAX_ROBOTS];
    int numRobots;
};

#endif // BATTLEFIELD_H
