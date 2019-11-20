#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../General/Star.h"
#include "../General/Ship.h"
#include "../General/planet.h"
#include "../General/asteroid.h"
#include "../General/BlackHole.h"
#include "../General/SpaceStation.h"



class Sector
{
	private:

		vector<Star *> __stars;
		vector<Ship *> __ships;
		vector<Planet *> __planets;
		vector<Asteroid *> __asteroids;
		vector<BlackHole *> __blackholes;
		vector<int> __size;
		SpaceStation* ss;
		int num_ally = 0;
		int num_enemy = 0;
		

	public:
		void setPlanets(vector<Planet *> newPlanets);
		vector<Planet *> getPlanets();
		void addPlanet(Planet* newPlanet);
		void setAsteroids(vector<Asteroid *> newAsteroids);
		vector<Asteroid *> getAsteroids();
		void addAsteroid(Asteroid* newAsteroid);
		void setBlackHoles(vector<BlackHole *> newBlackHoles);
		vector<BlackHole *> getBlackHoles();
		void addBlackHole(BlackHole* newBlackHole);
		void setStars(vector<Star *> newStars);
		vector<Star *> getStars();
		void addStars(Star* newStar);
		void setShips(vector<Ship *> newShips);

		void addShips(Ship* newShip);
		void setSize(vector<int> newSize);
		vector<int> getSize();
		vector<vector<int> > getState();
		vector<vector<int> > getShipState();
		vector<Ship *> getShips();
		int getNumAlly();
		int getNumEnemy();
		void setNumAlly(int numa);
		void setNumEnemy(int nume);
		void setSpaceStation(SpaceStation* nss);
		SpaceStation* getSpaceStation();
		vector<pair<int,int>> getEnemySpawn(int spawnloc);
		vector<pair<int,int>> getAllySpawn();
};