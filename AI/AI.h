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
#include "../General/Constants.h"
#include <math.h>

//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class AI
{
    private:
        vector<AIShip*>* ships;
        vector<vector<bool> > storedMapState; //probably needs to be changed
        vector<vector<bool> > storedShipState; //probably needs to be changed
        Hero* playerShip;
        Pathfinder* pathfinder;
	vector<Sprite*> osSprite;
	vector<SDL_Texture*> allTextures;
    public:
        void setShips(vector<AIShip*>* newShips);
        bool checkMapState(vector<vector<bool> > newState); //change mapstate
        void setShipPath(AIShip *shipToPath);
        vector<vector<bool>> getMapState();
	void setSprites(vector<Sprite*>& sprites);
	void setTextures(vector<SDL_Texture*>& textures);
        void lineOfSight();
        bool createMapState(Sector currentSector);
        bool createShipState(Sector currentSector);
        queue<pair<int,int>>* calculatePath(AIShip& theShip);
        void orderShip(AIShip theShip, Ship playerShip);//note: idk if this is best place to put this method
        void setPlayerShip(Hero* playerShip);
        void setPathfinder(Pathfinder* npf);
        Hero* getPlayerShip();
        void executeAIActions();
        int calculateDistance(pair<int,int> start, pair<int,int>stop);


        void followPlayer(AIShip* ship);
        void defendPosition(AIShip* ship);
        void Attack(AIShip* ship);
        void Flee(AIShip* ship);
	void doNothing(AIShip* ship);

        pair<int, int> radar(AIShip aiship);
        bool checkBounds(int x, int y);

};
