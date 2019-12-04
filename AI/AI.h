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
#include <pthread.h>

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
    	vector<Sprite*>* osSprite;
    	vector<SDL_Texture*>* allTextures;
    	pair<int,int> sectorSize; //width, height
        Sector* sector;
        pair<int,int> ChooseBorderSpawn();
        pair<int,int> ChooseSSSpawn();
        void followShip(AIShip* fship);
        void followEnemy(AIShip* ship);
        void followPlayer(AIShip* ship);
        void findShip(AIShip* ship, int routine);
        Uint32 timeSpawn;
    	Uint32 timeAttack;
      	Sector* attackSector; //which sector attacking from
    	Sector* targetSector; //which sector to be attacked
    	bool isAttacking; //if currently attacking a sector
    public:
    	void setTimeSpawn(Uint32 time);
    	Uint32 getTimeSpawn();
    	void setTimeAttack(Uint32 time);
    	Uint32 getTimeAttack();
    	Sector* getAttackSector();
    	void setAttackSector(Sector* newSector);
    	Sector* getTargetSector();
    	bool getAttackStatus();
    	void attackFlip();
	    void setTargetSector(Sector* newSector);
        void setCurrentSector(Sector* newSector, bool change);
        void setShips(vector<AIShip*>* newShips);
      //change mapstate
        void setShipPath(AIShip *shipToPath);
        vector<vector<bool>> getMapState();
    	void setSprites(vector<Sprite*>* sprites);
    	void setTextures(vector<SDL_Texture*>* textures);
        queue<pair<int,int>>* calculatePath(AIShip& theShip);
        void orderShip(AIShip theShip, Ship playerShip);//note: idk if this is best place to put this method
        void setPlayerShip(Hero* playerShip);
        void setPathfinder(Pathfinder* npf);
        Hero* getPlayerShip();
        void executeAIActions();
        int calculateDistance(pair<int,int> start, pair<int,int>stop);
    	//generates coordinates based on the three parameters
    	//1 = pursue
    	//2 = flee
    	//3 = roam
    	pair<int,int> generateCoordinate(pair<int,int> start,pair<int,int> stop, int typeGen);
    	pair<int,int> getSectorSize();
    	void setSectorSize(pair<int,int> sector);
    	void defendPosition(AIShip* ship);
    	void pursueShip(AIShip* ship);
    	void fleeToCorner(AIShip* ship);
    	void roamAround(AIShip* ship);
    	void doNothing(AIShip* ship);
    	vector<AIShip*>* getShips();
        pair<int, int> radar(AIShip& aiship);
        bool checkBounds(int x, int y);
        void createShip(bool isAlly,int goal);
        bool occupied(pair<int,int> spawn);
};
