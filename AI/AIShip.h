#pragma once
#include "../General/Ship.h"

typedef std::pair<int,int> Point;
typedef std::queue<Point>* Path;
class AIShip: public Ship{
	public:
		AIShip();
		AIShip(const AIShip& aiship);
		AIShip(SDL_Rect dbox,SDL_Texture* aTex);
		void followPath();
		void setGoal(int newGoal);
		int getGoal();
		bool getPathComplete();
		bool hasPath();
		void setDestination(pair<int,int> newDestination);
		pair<int,int> getDestination();
		void setPath(queue<pair<int,int>>* thePath);

	private:
		
		bool pathComplete;
		pair<int,int> destination;
        Path path;
        int curGoal;//'modes' of ai: follow, defend, attack, flee = {0,1,2,3} for now
		

};