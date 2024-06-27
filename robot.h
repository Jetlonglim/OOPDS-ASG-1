#ifndef ROBOT_H
#define ROBOT_H
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>


using namespace std;

class Robot //created a robot class to store
{			// and initialise a few variables and their responses of commands

protected:
	string Name;
    string type;
	int Lives;
	int Kills = 0;
	int posX, posY;
    int Respawns;

public: 
	Robot(string name, int x, int y, int kills){// Constructor Method
		Name = name;
		posX =x;
		posY = y;
		Kills= kills;
        Lives= 3;
        Respawns = 3;
	}
    virtual void move(Robot* robots[], int mapX, int mapY) = 0;
    virtual void interact(Robot* other, int mapX, int mapY) = 0; 
    virtual string getType() const =0;
    virtual ~Robot() {}

    string getName() const{ return Name; }
	int getPosX() const { return posX;}
    int getPosY() const { return posY;}
    int getLives() const { return Lives; }
    int getRespawn() const { return Respawns;}
    int getKill() const { return Kills;}
    bool isAlive() const { return Lives>0;}

	void setPosX(int x) {posX = x;}
    void setPosY(int y) {posY = y;}
    void setAlive(bool alive) {
        Lives = alive ? 3 : 0;
    }   
	void AddKill(){
		Kills++;
		cout << Name << " has killed an enemy. Total kills: " << Kills << endl;
	}

    void resetPosition(int mapX, int mapY) {
        posX = rand() % mapX;
        posY = rand() % mapY;
    }
    
	
    void respawn() {
        if(Respawns > 0) {
            Lives = 3;
            Respawns--;
            cout << Name << " has respawned. Remaining respawns: " << Respawns << endl;
        }
    }
    void takeDamage() {
        if (Lives > 0) {
            Lives--;
            if (Lives == 0 && Respawns > 0) {
                respawn();
            }
        }
    }
};

#endif
