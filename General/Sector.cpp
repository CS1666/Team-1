
#include "Sector.h"

void Sector::setPlanets(vector<Planet *> newPlanets)
{
	__planets = newPlanets;
}

vector<Planet *> Sector::getPlanets()
{
	return __planets;
}

void Sector::addPlanet(Planet* newPlanet)
{
	__planets.push_back(newPlanet);
}

void Sector::setAsteroids(vector<Asteroid *> newAsteroids)
{
	__asteroids = newAsteroids;
}

vector<Asteroid *> Sector::getAsteroids()
{
	return __asteroids;
}

void Sector::addAsteroid(Asteroid* newAsteroid)
{
	__asteroids.push_back(newAsteroid);
}

void Sector::setBlackHoles(vector<BlackHole *> newBlackHoles)
{
	__blackholes = newBlackHoles;
}

vector<BlackHole *> Sector::getBlackHoles()
{
	return __blackholes;
}

void Sector::addBlackHole(BlackHole* newBlackHole)
{
	__blackholes.push_back(newBlackHole);
}

vector<Star* > Sector::getStars()
{
	return __stars;
}

void Sector::setStars(vector<Star*> newStars)
{
	__stars = newStars;
}

vector<Ship *> Sector::getShips()
{
	return __ships;
}

void Sector::setShips(vector<Ship *> newShips)
{
	__ships = newShips;
}

void Sector::setSize(vector<int> newSize)
{
	__size = newSize;
}

vector<int> Sector::getSize()
{
	return __size;
}

vector<vector<int> > Sector::getState()
{
	std::vector<std::vector<int> > currentState;
	
	for (Star* star : __stars)
	{
		
		vector<int> size = star->getSize();
		vector<int> position = star->getPosition();
		currentState.push_back({position[0], position[1], size[0], size[1]});
	}
	/*
	std::cout << "1" << std::endl;
	if (!__ships.empty())
	{
std::cout << "2" << std::endl;
		for (Ship *ship : __ships)
		{
			std::cout << "3" << std::endl;
			pair<int, int> size = ship->getSize();
			std::cout << "4" << std::endl;
			int x = (int)ship->getTrueX();
			std::cout << "5" << std::endl;
			int y = (int)ship->getTrueY();

			std::cout << "6" << std::endl;

			currentState.push_back({x, y, size.first, size.second});

			std::cout << "7" << std::endl;
		}
	}
	*/
	return currentState;
}

int  Sector::getNumAlly(){
	return num_ally;
}
int  Sector::getNumEnemy(){
	return num_enemy;
}
void Sector::setNumAlly(int numa){
	num_ally = numa;
}
void Sector::setNumEnemy(int nume){
	num_enemy = nume;
}

void Sector::setSpaceStation(SpaceStation* nss){
	ss = nss;
}

SpaceStation* Sector::getSpaceStation(){
	return ss;
}

vector<pair<int,int>> Sector::getEnemySpawn(int spawnloc){

	switch(spawnloc){

		//top
		case 0:

			return {pair<int,int>((3840/2) - 25 , 50), pair<int,int>((3840/2) + 50 , 50), pair<int,int>((3840/2) - 100 , 50)};

		//left
		case 1:

			return {pair<int,int>(3840 - 50 , (2160/2) - 25), pair<int,int>(3840 - 50 , (2160/2) + 50), pair<int,int>(3840 - 50 , (2160/2) - 100)};

		//bottom
		case 2:

			return {pair<int,int>((3840/2) - 25 , 2160 - 50), pair<int,int>((3840/2) + 50 , 2160 - 50), pair<int,int>((3840/2) - 100, 2160 - 50)};

		//right
		case 3:

			return {pair<int,int>(50 , (2160/2) - 25), pair<int,int>(50 , (2160/2)+ 50), pair<int,int>(50, (2160/2) - 100)};

	}




}


vector<pair<int,int>> Sector::getAllySpawn(){
	std::cout << "1" << std::endl;
	vector<int> sspos = ss->getPosition();
	std::cout << "2" <<  std::endl;
	std::cout << sspos[0] <<  std::endl;
	std::cout << sspos[1] <<  std::endl;

	//                            left                               top                                     right										bottom
	return {pair<int,int>(sspos[0] - 100, sspos[1]), pair<int,int>(sspos[0], sspos[1] - 100),  pair<int,int>(sspos[0] + 100, sspos[1]), pair<int,int>(sspos[0],  sspos[1] + 100) };
}