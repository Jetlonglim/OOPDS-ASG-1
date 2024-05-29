// robot.h
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
	int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
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
	
		
};

class MovingRobot: public Robot{
	public:
		MovingRobot(string name, string x, string y, int kills): Robot(name, x, y, kills){
			int mapX = 10;
			int mapY = 10;
			if (x == "random" && y== "random"){// if input robot postion in random then it will be place randomly
				srand(time(0)); // Seed the random number generator
				setPosX(rand() % mapX);
            	setPosY(rand() % mapY);
			}
			else if (stoi(x) <= mapX && stoi(y)<= mapY){//it will input the robot to the position
				int posX = stoi(x);
            	int posY = stoi(y);
			}
			else{
				cout << "Invalid input. Please Try Again\n" ;// Invalid input
			}
		}

		void moving(const string &x, const string &y) {
        int newX = stoi(x);
        int newY = stoi(y);
		int posX = getPosX();
        int posY = getPosY();

        if (newX > 0) { // move right
            posX += 1;
        } else if (newX < 0) { // move left
            posX -= 1;
        } else if (newX == 0) { // move left
            posX;
        }

        if (newY > 0) { // move upward
            posY += 1;
        } else if (newY < 0) { // move downward
            posY -= 1;
        } else if (newY == 0) { // move downward
            posY;
        }

		setPosX(posX);
        setPosY(posY);

        cout << "New position: (" << posX << ", " << posY << ")" << endl;
    }
};

class ShootingRobot : public MovingRobot {
public:
    ShootingRobot(string name, string x, string y, int kills) : MovingRobot(name, x, y, kills) {}

    void fire(int mapX, int mapY) {
        srand(time(0)); // Seed the random number generator

		int posX = getPosX();
        int posY = getPosY();

        cout << Name << " is shooting 3 bullets randomly around its position within a 10x10 block\n";

        for (int i = 0; i < 3; ++i) {
            int bulletX = posX + (rand() % 10 - 5);
            int bulletY = posY + (rand() % 10 - 5);
            cout << "Bullet " << i + 1 << " location: (" << bulletX << ", " << bulletY << ")\n";
        }
    }

	
};

class SeeingRobot: public Robot{
public: 
	SeeingRobot(string name, string x, string y, int kills) : Robot(name, x, y, kills){}

	void look(int offsetX, int offsetY){
		int posX = getPosX();
        int posY = getPosY();

		cout << Name << " is looking a 9-square area centered on ("
			<< (posX + offsetX) << ", " << (posY + offsetY) << ":\n";

		for (int i = -1; i <= 1; ++i){
			for(int j = -1; j <= 1; ++j){
				cout << "(" << (posX + offsetX + i) << ", " << (posY + offsetY + j) << ") ";
			}
			cout << endl;
		}
	}
};

class SteppingRobot: public MovingRobot{
public:
    SteppingRobot(string name, string x, string y, int kills) : MovingRobot(name, x, y, kills) {}

	void stepping(int newX, int newY, int enemies[][2], int &numEnemies){
		int posX = getPosX();
        int posY = getPosY();

        setPosX(newX);
        setPosY(newY);

		// Check for enemies at the new position
        for (int i = 0; i < numEnemies; ++i) {
            if (enemies[i][0] == newX && enemies[i][1] == newY) {
                AddKill();
                // Remove the enemy by shifting the rest of the array
                for (int j = i; j < numEnemies - 1; ++j) {
                    enemies[j][0] = enemies[j + 1][0];
                    enemies[j][1] = enemies[j + 1][1];
                }
                numEnemies--; // Decrease the count of enemies
                break;
            }
        }
	}
};
#endif
