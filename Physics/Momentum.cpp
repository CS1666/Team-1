#include "Momentum.h"
#include "../General/Sprite.h"

std::vector<float> calculateMomentumConserv(Ship &playerent, std::vector<Ship*> &osShip){
	float playerXspd = playerent.getSpeedX();
	float playerYspd = playerent.getSpeedY();
	float otherXspd;
	float otherYspd;
	float playerResX = 0;
	float playerResY = 0;
	float otherResX = 0;
	float otherResY = 0;
	bool isCollision = false;
	for(int i = 1; i < osShip.size(); i++){
		isCollision = check_collision2(playerent.getDrawBox(), osShip.at(i)->getDrawBox());
		std::cout << "Collision: " << isCollision << std::endl;
		if(isCollision == true){
			otherXspd = osShip.at(i)->getSpeedX();
			otherYspd = osShip.at(i)->getSpeedY();
			playerResX = (playerXspd + otherXspd)/2;
			playerResY = (playerYspd + otherYspd)/2;
			otherResX = (playerXspd + otherXspd)/2;
			otherResY = (playerYspd + otherYspd)/2;

			osShip.at(i)->setSpeedX(otherResX);
			osShip.at(i)->setSpeedY(otherResY);
			osShip.at(i)->setX(osShip.at(i)->getTrueX() + (int)otherResX);
			osShip.at(i)->setY(osShip.at(i)->getTrueY() + (int)otherResY);
		}
	}

	return {playerResX, playerResY};
}
