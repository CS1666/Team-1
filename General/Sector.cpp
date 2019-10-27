
#include "Sector.h"

vector<Star> Sector::getStars()
{
	return __stars;
}

void Sector::setStars(vector<Star> newStars)
{
	__stars = newStars;
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

	return currentState;
}