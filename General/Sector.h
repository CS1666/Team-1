#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Star.h"

using namespace std;

class Sector
{
	private:

		vector<Star> __stars;
		vector<int> __size;

	public:
		void setStars(vector<Star> newStars);
		vector<Star> getStars();
		void setSize(vector<int> newSize);
		vector<int> getSize();

};