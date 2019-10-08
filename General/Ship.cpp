#include <iostream>
#include <string>
#include <vector>
//#include "Ship.h"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship
{
    private:
        int hull;
        string sprite;
        vector<int> position;
        int velocity;
        float rotation;
        int weaponType;
        bool damageTaken;
        string currKey;

        //ai
        vector<vector<int> > path;
        bool isUser;
        bool isAlly;
        bool pathComplete;

    public:
        void setSprite(string newSprite)
        {
            sprite = newSprite;
        }

        string getSprite()
        {
            return sprite;
        }

        void checkPhysics()
        {

        }

        //integrate BasicMovementFPSlimit.cpp
        void updatePosition(vector<int> newPos)
        {
            position = newPos;
        }

        //integrate BasicMovementFPSlimit.cpp
        void updateMovement()
        {
            
        }

        void checkAction(/*stream*/)
        {

        }

        void updateHull(int newHull)
        {
            hull = newHull;
        }

        vector<int> getPosition()
        {
            return position;
        }

        void setPath(vector<vector<int> > newPath)
        {
        	path = newPath;
        }

        //ai follows path assigned to it by ai class
        void followPath()
        {

        }

        bool getPathComplete()
        {
        	return pathComplete;
        }


};

class Hero:Ship{};

class Fighter:Ship{};

class Cruiser:Ship{};

class Capital:Ship{};