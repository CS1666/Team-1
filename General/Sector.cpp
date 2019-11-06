
#include "Sector.h"
#include "../General/Sprite.h"

vector<Star> Sector::getStars()
{
	return __stars;
}

void Sector::setStars(vector<Star> newStars)
{
	__stars = newStars;
}

void Sector::setSize(pair<int,int> newSize)
{
	__size = newSize;
}

pair<int,int> Sector::getSize()
{
	return __size;
}

vector<vector<int> > Sector::getState()
{
	std::vector<std::vector<int> > currentState;

	for (Star star : __stars)
	{
		pair<int,int> size = star.getSize();
		pair<int,int> position = star.getPosition();

		currentState.push_back({position.first, position.second, size.first, size.second});

	}

	for (Ship ship : __ships)
	{
		pair<int, int> size = ship.getSize();
		pair<int, int> position = ship.getPosition();

		currentState.push_back({position.first, position.second, size.first, size.second});
	}

	return currentState;
}