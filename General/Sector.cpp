
#include "Sector.h"

vector<Star> Sector::getStars()
{
	return __stars;
}

void Sector::setStars(vector<Star> newStars)
{
	__stars = newStars;
}

void Sector::setShips(vector<Ship *> newShips)
{
	__ships = newShips;
}

vector<Ship *> Sector::getShips()
{
	return __ships;
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