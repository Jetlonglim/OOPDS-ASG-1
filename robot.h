#ifndef ROBOT_H
#define ROBOT_H
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Robot //created a robot class to store
{			// and initialise a few variables and their responses of commands
private:
	int steps;
	int id;
	int Lives =3;
	int Kills = 0;
	int posX, posY;

protected:
	string Name;

public: 
	Robot(string name, string x, string y, int kills){// Constructor Method
		Name = name;
		posX = stoi(x);
		posY = stoi(y);
		Kills = kills;
	}
    virtual ~Robot() {}
	int getPosX() const {
        return posX;
    }
    int getPosY() const {
        return posY;
    }
    bool isAlive() {
        return Lives > 0;
    }
    void setAlive(bool alive) {
    if (alive) {
        Lives = 3; // Set lives to 3 when the robot is alive
    } else {
        Lives = 0; // Set lives to 0 when the robot dies
    }
}
	void setPosX(int x) {
        posX = x;
    }

    void setPosY(int y) {
        posY = y;
    }
	void AddKill(){
		Kills++;
		cout << Name << " has killed an enemy. Total kills: " << Kills << endl;
	}
    int getKill() const {
        return Kills;
    }
	virtual string getName() const {
        return Name;
    }
    virtual string getType() const =0;
		
    void resetPosition(int mapX, int mapY) {
        posX = rand() % mapX;
        posY = rand() % mapY;
    }
    
};

#endif
