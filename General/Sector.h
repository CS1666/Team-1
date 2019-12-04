#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include "../General/Star.h"
#include "../General/Ship.h"
#include "../General/planet.h"
#include "../General/asteroid.h"
#include "../General/BlackHole.h"
#include "../General/SpaceStation.h"
#include "../General/gpRender.h"
#include "../General/Sprite.h"
#include "../General/Constants.h"
#include "../AI/theta.h"
#include "../AI/AIShip.h"



class Sector
{
	private:

		Pathfinder* pf;
		vector<Sprite *>* __SectEnts;
		vector<Star *>    __stars;
		vector<Ship *>    __ships;
		vector<Planet *>  __planets;

		vector<Asteroid *> __asteroids;
		vector<BlackHole *> __blackholes;
		vector<int> __size;
		SpaceStation* ss;
		int num_ally = 0;
		int num_enemy = 0;
		int curEnemy = SHIP_ENEMY_SECTOR_INIT_LIMIT;
		vector<int> sunPos;
		SDL_Rect star_rect = {0};
		SDL_Texture* star_tex;
		vector<SDL_Texture *> planet_tex;
		vector<SDL_Rect> planet_rect;
		vector<Sprite *> bodySprites;
		Star* star;
	public:

		Sector();
		vector<Sprite *> getBodySprites();
		Star * getStar();
		void init(gpRender * g, int winWidth, int winHeight);
		vector<Sprite *>* getSectEnts();
		void setPlanets(vector<Planet *> newPlanets);
		vector<Planet *> getPlanets();
		void addPlanet(Planet* newPlanet);
		void setCurEnemy(int num);
		int getCurEnemy();
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
		vector<vector<int> > getShipState();
		vector<Ship *> getShips();

		void setSize(vector<int> newSize);
		vector<int> getSize();

		vector<vector<int> > getState();
		void clearDeadEnts();
	
		int getNumAlly();
		int getNumEnemy();
		void setNumAlly(int numa);
		void setNumEnemy(int nume);
		void setSpaceStation(SpaceStation* nss);
		SpaceStation* getSpaceStation();
		vector<pair<int,int>> getEnemySpawn(int spawnloc);
		vector<pair<int,int>> getAllySpawn();
		Pathfinder* getPathfinder();
};
