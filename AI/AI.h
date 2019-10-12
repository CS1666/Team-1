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
//	vector<int,int> storedMapState; //probably needs to be changed

    public:
        void setShips(vector<Ship> newShips);
//	bool checkMapState(vector <int,int> newState); //change mapstate
        void setShipPath(Ship shipToPath);
};
