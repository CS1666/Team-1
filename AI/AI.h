#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include "../General/Ship.h"
#include "../General/Sector.h"
#include "theta.h"

#include <math.h>

//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<Ship> __ships;
        vector<vector<bool> > storedMapState; //probably needs to be changed

    public:
        void setShips(vector<Ship> newShips);
		bool checkMapState(vector<vector<bool> > newState); //change mapstate
        void setShipPath(Ship *shipToPath);
        vector<vector<bool>> getMapState();
        void lineOfSight();
        bool createMapState(Sector currentSector);
        queue<pair<int,int>>* calculatePath(Ship theShip, Pathfinder Path);
        int calculateDistance(pair<int,int> start, pair<int,int>stop);
	
};
