#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Star.h"
#include "Ship.h"

using namespace std;

class Sector
{
	private:

		vector<Star> __stars;
		vextor<Ship> __ships;
		vector<int> __size;

	public:
		void setStars(vector<Star> newStars);
		vector<Star> getStars();
		void setShips(vector<Ship> newShips);
		vector<Ship> getShips();
		void setSize(vector<int> newSize);
		vector<int> getSize();
		vector<vector<int> > getState();

};