#pragma once
#include "../General/Ship.h"

class AIShip: public Ship{
	public:
		AIShip();
		AIShip(SDL_Rect dbox,SDL_Texture* aTex);
		void followPath();
		void setGoal(int newGoal);
		int getGoal();
		bool getPathComplete();
		void setDestination(pair<int,int> newDestination);
		pair<int,int> getDestination();
		void setPath(queue<pair<int,int>>* thePath);
		Projectile attackShip(pair<int,int> otherShip, SDL_Texture* laser);

	private:
		void calculateNewAngle(pair<int,int> destination);
		bool rotateToAngle();
		bool pathComplete;
		pair<int,int> destination;
        std::queue<pair<int,int>>* path;
        int curGoal;//'modes' of ai: follow, defend, attack, flee = {0,1,2,3} for now
		

};
