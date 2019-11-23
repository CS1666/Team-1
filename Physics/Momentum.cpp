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
			isCollision = check_collision(shipOne.getDrawBox(), osShip.at(i)->getDrawBox());
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

void shipCollisionHandler(Ship &ship1, Ship &ship2){
	// get speeds from the 2 colliding ships
	float ship1Xspd = ship1.getSpeedX();
	float ship2Xspd = ship2.getSpeedX();
	float ship1Yspd = ship1.getSpeedY();
	float ship2Yspd = ship2.getSpeedY();

	// get new x and y for the colliding ships
	float ship1RexX = (ship1Xspd + ship2Xspd)/2;
	float ship1RexY = (ship1Yspd + ship2Yspd)/2;

	float ship2RexX = (ship1Xspd + ship2Xspd)/2;
	float ship2RexY = (ship1Yspd + ship2Yspd)/2;
	std::cout << "speed ship 2 X: " << ship2RexX << std::endl;
	std::cout << "speed ship 2 Y: " << ship2RexY << std::endl;
	
	// set the new speed for the colliding ships
	ship1.setSpeedX(ship1RexX);
	ship2.setSpeedX(ship2RexX);

	ship1.setSpeedY(ship1RexY);
	ship2.setSpeedY(ship2RexY);

	// move the colliding ships
	ship2.setX(ship2.getTrueX() + ship2RexX);
	
	ship2.setY(ship2.getTrueY() + ship2RexY);

}


