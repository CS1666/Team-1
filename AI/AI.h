#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>
#include <vector>

#include "../General/Ship.h"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<Ship> ships;

    public:
        void setShips(vector<Ship> newShips);

        void setShipMovement();
};