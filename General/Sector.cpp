
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
