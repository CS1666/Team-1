#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../General/Ship.h"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<Ship> __ships;

    public:
        void setShips(vector<Ship> newShips);

        void setShipPath(Ship shipToPath);
};