#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include "../General/Ship.h"
#include "AIShip.h"
#include "../General/Sector.h"
#include "theta.h"

#include <math.h>

//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<AIShip> __ships;
        vector<vector<bool> > storedMapState; //probably needs to be changed

    public:
        void setShips(vector<AIShip> newShips);
		bool checkMapState(vector<vector<bool> > newState); //change mapstate
        void setShipPath(AIShip *shipToPath);
        vector<vector<bool>> getMapState();
        void lineOfSight();
        bool createMapState(Sector currentSector);
        queue<pair<int,int>>* calculatePath(AIShip theShip, Pathfinder Path);
        void orderShip(AIShip theShip, Ship playerShip);//note: idk if this is best place to put this method
	   int calculateDistance(pair<int,int> start, pair<int,int>stop);
       pair<int, int> radar(AIShip aiship);
       bool checkBounds(int x, int y);
	
};
