#include <iostream>
#include <string>
#include <vector>
//#include "AI.h"
#include "../General/Ship.cpp"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<Ship> __ships;

    public:
        void setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void setShipPath()
        {

        }
};