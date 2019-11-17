#include "Momentum.h"
#include "../General/Sprite.h"

std::vector<float> calculateMomentumConserv(Ship &shipOne, std::vector<Ship*> &osShip){
	float shipOneXspd = shipOne.getSpeedX();
	float shipOneYspd = shipOne.getSpeedY();
	float shipTwoXspd;
	float shipTwoYspd;
	float shipOneResX = 0;
	float shipOneResY = 0;
	float shipTwoResX = 0;
	float shipTwoResY = 0;
	bool isCollision = false;
	for(int i = 1; i < osShip.size(); i++){
		if(&shipOne != osShip.at(i)){
			isCollision = check_collision2(shipOne.getDrawBox(), osShip.at(i)->getDrawBox());
			std::cout << "Collision: " << isCollision << std::endl;
			if(isCollision == true){
				shipTwoXspd = osShip.at(i)->getSpeedX();
				shipTwoYspd = osShip.at(i)->getSpeedY();
				shipOneResX = (shipOneXspd + shipTwoXspd)/2;
				shipOneResY = (shipOneYspd + shipTwoYspd)/2;
				shipTwoResX = (shipOneXspd + shipTwoXspd)/2;
				shipTwoResY = (shipOneYspd + shipTwoYspd)/2;

				osShip.at(i)->setSpeedX(shipTwoResX);
				osShip.at(i)->setSpeedY(shipTwoResY);
				osShip.at(i)->setX(osShip.at(i)->getTrueX() + (int)shipTwoResX);
				osShip.at(i)->setY(osShip.at(i)->getTrueY() + (int)shipTwoResY);

				osShip.at(i)->speed = sqrt(pow(shipTwoXspd, 2) + pow(shipTwoYspd, 2));
			}
		}
	}

	return {shipOneResX, shipOneResY};
}
