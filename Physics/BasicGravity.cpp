#include "BasicGravity.h"
#include "../General/Sprite.h"
#define PI 3.14159265

#define G .00000000006674

constexpr double MAX_SPEED = 3;
constexpr double MAX_DELTAV = 2;

/*
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;*/

//movement is handled by increasing and decreasing the thrust (acceleration) in a particular direction and is capped by a max speed and acceleration
double speedX = 0;
double speedY = 0;
double deltaX = 0;
double deltaY = 0;
float playerX = 0;
float playerY = 0;
float bodyX = 0;
float bodyY = 0;
SDL_Point playerCenter;
SDL_Point bodyCenter;
double pointDistance;
float pointAngle;
float pointSlope;
long mass1 = 20000;
long mass2 = 4385000000;

// function to handle gravitational pull
//want max to be like 1 m/frame^2 min to be 0
std::vector<float> calculateGravityPull(Sprite &playerent,  std::vector<Sprite*> &osSprite){
	playerX = playerent.getTrueX() + playerent.getW()/2.0;
	playerY = playerent.getTrueY() + playerent.getH()/2.0;
	float gravX = 0.0;
	float gravY = 0.0;
	for(auto bodyent : osSprite)
	{	
		bodyX = bodyent->getTrueX() + bodyent->getW()/2.0;
		bodyY = bodyent->getTrueY() + bodyent->getH()/2.0;
		if(bodyent->getRenderOrder() ==2 )
		{
			//std::cout<< "mass: " << (bodyent)->getMass() << std::endl;
			//make fix this
			pointSlope = (bodyY - playerY)/(bodyX - playerX);
			pointAngle = atan(pointSlope);
			if(playerX > bodyX)
			{
				pointAngle += 3.1415926;
			}
			//std::cout << "angle: " << pointAngle * 180/ 3.14<< std::endl;
			float grav = 1000*bodyent->getMass()/((bodyX-playerX)*(bodyX-playerX)*1.0 + (bodyY-playerY)*(bodyY-playerY)*1.0);
			
			if(grav > 1.5 && !bodyent->isHole())
			{
				grav = 1.5;
			}
			//std::cout << "grav: " << grav << std::endl;
			gravX += grav*cos(pointAngle);
			gravY += grav*sin(pointAngle);
		}
	}
	 
	return {gravX, gravY};
}

