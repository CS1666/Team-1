
#include "Sector.h"


vector<Star> Sector::getStars()
{
	return __stars;
}

void Sector::setStars(vector<Star> newStars)
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

	for (Star star : __stars)
	{
		vector<int> size = star.getSize();
		vector<int> position = star.getPosition();

		currentState.push_back({position[0], position[1], size[0], size[1]});

	}

	if (!__ships.empty())
	{
		for (Ship *ship : __ships)
		{
			pair<int, int> size = ship->getSize();
			double x = ship->getTrueX();
			double y = ship->getTrueX();

			currentState.push_back({(int)x, (int)y, size.first, size.second});
		}
	}

	return currentState;
}

vector<vector<int> > Sector::getShipState()
{
	std::vector<std::vector<int> > currentState;


	if (!__ships.empty())
	{
		for (Ship *ship : __ships)
		{
			pair<int, int> size = ship->getSize();
			double x = ship->getTrueX();
			double y = ship->getTrueX();

			currentState.push_back({(int)x, (int)y, size.first, size.second});
		}
	}

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

void Sector::setSpaceStation(SpaceStation nss){
	ss = nss;
}

SpaceStation Sector::getSpaceStation(){
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

	vector<int> sspos = ss.getPosition();
	//                            left                               top                                     right										bottom
	return {pair<int,int>(sspos[0] - 100, sspos[1]), pair<int,int>(sspos[0], sspos[1] - 100),  pair<int,int>(sspos[0] + 100, sspos[1]), pair<int,int>(sspos[0],  sspos[1] + 100) };
}