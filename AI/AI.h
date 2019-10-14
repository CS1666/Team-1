#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "./Queue.h"
#include "../General/Ship.h"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<Ship> __ships;
        vector<vector<int> > storedMapState; //probably needs to be changed

    public:
        void setShips(vector<Ship> newShips);
		bool checkMapState(vector<vector<int> > newState); //change mapstate
        void setShipPath(Ship shipToPath);
        void lineOfSight();
        Queue calculatePath(Ship theShip, vector<int> destination);
	
};
