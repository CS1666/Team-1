#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Star.h"
#include "Ship.h"
#include "SpaceStation.h"

using namespace std;

class Sector
{
	private:

		vector<Star *> __stars;
		vector<Ship *> __ships;
		vector<int> __size;
		SpaceStation ss;
		int num_ally;
		int num_enemy;
		

	public:
		void setStars(vector<Star *> newStars);
		vector<Star *> getStars();
		void setShips(vector<Ship *> newShips);
		void setSize(vector<int> newSize);
		vector<int> getSize();
		vector<vector<int> > getState();
		vector<vector<int> > getShipState();
		vector<Ship *> getShips();
		int getNumAlly();
		int getNumEnemy();
		void setNumAlly(int numa);
		void setNumEnemy(int nume);
		void setSpaceStation(SpaceStation nss);
		SpaceStation getSpaceStation();
		vector<pair<int,int>> getEnemySpawn(int spawnloc);
		vector<pair<int,int>> getAllySpawn();
};