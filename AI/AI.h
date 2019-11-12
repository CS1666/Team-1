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
typedef std::pair<int,int> Point;
typedef std::queue<Point>* Path;

class AI
{
    private:
        vector<AIShip*>* ships;
        Pathfinder* pathfinder;
        Sector sect;
        vector<vector<bool>> storedMapState;
        Path calculatePath(AIShip* theShip);
        void followPlayer(AIShip* ship);
        Hero* playerShip;

    public:
        AI(vector<AIShip*>* ships, Sector sect);
        void handleShipsActions();
        void setShips(vector<AIShip*>* newShips);
        void setShipPath(AIShip *shipToPath, Path path);
        void setPathfinder(Pathfinder* npf);

        bool createMapState(Sector currentSector);
        bool checkMapState(vector<vector<bool> > newState); //change mapstate
        vector<vector<bool>>* getMapState();
        void lineOfSight();
        void updatePlayerState(Hero* nplayerShip);
        
        void orderShip(AIShip theShip, Ship playerShip);//note: idk if this is best place to put this method
	    int calculateDistance(pair<int,int> start, pair<int,int>stop);
	
};
