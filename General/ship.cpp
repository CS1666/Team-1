#include <iostream>
#include <string>
#include <tuple>
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship
{
    private:
        int hull;
        string sprite;
        tuple<int, int> position;
        int velocity;
        float rotation;
        int weaponType;
        bool damageTaken;
        string currKey;

    public:
        void checkPhysics()
        {

        }

        //integrate BasicMovementFPSlimit.cpp
        void updatePosition(tuple<int, int> newPos)
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

        tuple<int, int> getPosition()
        {
            return position;
        }
};

class Hero:Ship{};

class Fighter:Ship{};

class Cruiser:Ship{};

class Capital:Ship{};