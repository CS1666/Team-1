#include "BasicGravity.h"
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
std::vector<float> calculateGravityPull(Sprite &playerent, Sprite &bodyent){
	playerX = playerent.getTrueX() + playerent.getW()/2.0;
	playerY = playerent.getTrueY() + playerent.getH()/2.0;
	bodyX = bodyent.getTrueX() + bodyent.getW()/2.0;
	bodyY = bodyent.getTrueY() + bodyent.getH()/2.0;
	//make fix this
	pointSlope = (bodyY - playerY)/(bodyX - playerX);
	pointAngle = atan(pointSlope);
	if(playerX > bodyX)
	{
		pointAngle += 3.1415926;
	}
	std::cout << "angle: " << pointAngle * 180/ 3.14<< std::endl;
	float grav = 100000/((bodyX-playerX)*(bodyX-playerX)*1.0 + (bodyY-playerY)*(bodyY-playerY)*1.0);
	std::cout << "grav: " << grav << std::endl;
	float gravX = grav*cos(pointAngle);
	float gravY = grav*sin(pointAngle);
	return {gravX, gravY};
}

void gravity_pull(Sprite &playerent, Sprite &bodyent){
	playerCenter.x = playerent.getX() + playerent.getW()/2;
	playerCenter.y = playerent.getY() + playerent.getH()/2;
	bodyCenter.x = bodyent.getX() + bodyent.getW()/2;
	bodyCenter.y = bodyent.getX() + bodyent.getH()/2;
	pointDistance = sqrt((bodyCenter.x - playerCenter.x)*(bodyCenter.x - playerCenter.x) + (bodyCenter.y - playerCenter.y)*(bodyCenter.y - playerCenter.y));
	//pointSlope = (bodyCenter.y - playerCenter.y)/(bodyCenter.x - playerCenter.x);
	//pointAngle = atan(pointSlope);
	/*double gravForce = G*(mass1 * mass2)/(pointDistance*pointDistance);
	
	if((playerent.getX() + playerent.getW()/2) < (bodyent.getX() + bodyent.getW()/2) && (playerent.getY() + playerent.getW()/2) < (bodyent.getY() + bodyent.getW()/2)){
		deltaX = deltaX + gravForce;
		deltaY = deltaY + gravForce;
			
	}else if((playerent.getX() + playerent.getW()/2) > (bodyent.getX() + bodyent.getW()/2) && (playerent.getY() + playerent.getW()/2) < (bodyent.getY() + bodyent.getW()/2)){
		deltaX = deltaX - gravForce;
		deltaY = deltaY + gravForce;

	}else if((playerent.getX() + playerent.getW()/2) > (bodyent.getX() + bodyent.getW()/2) && (playerent.getY() + playerent.getW()/2) < (bodyent.getY() + bodyent.getW()/2)){	
		deltaX = deltaX - gravForce;		
		deltaY = deltaY + gravForce;

	}else if((playerent.getX() + playerent.getW()/2) < (bodyent.getX() + bodyent.getW()/2) && (playerent.getY() + playerent.getW()/2) > (bodyent.getY() + bodyent.getW()/2)){
		deltaX = deltaX + gravForce;	
		deltaY = deltaY - gravForce;
	}
	*/
	
	if(deltaX > MAX_DELTAV)
	{
		deltaX = MAX_DELTAV;
	}
	else if(deltaX < -MAX_DELTAV)
	{
		deltaX = -MAX_DELTAV;
	}

	if(deltaY > MAX_DELTAV)
	{
		deltaY = MAX_DELTAV;
	}
	else if(deltaY < -MAX_DELTAV)
	{
		deltaY = -MAX_DELTAV;
	}
	//std::cout << "GForce: " << gravForce << std::endl;
	std::cout << "deltaX: " << deltaX << std::endl;
	std::cout << "deltaY: " << deltaY << std::endl;
	std::cout << "distance: " << pointDistance << std::endl;
	std::cout << "angle: " << pointAngle << std::endl;
	
}


void updatePositionGrav(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT){

	speedX += deltaX;
	speedY += deltaY;
	
	if(speedX >MAX_SPEED)
	{
		speedX = MAX_SPEED;
	}
	else if(speedX < -MAX_SPEED)
	{
		speedX = -MAX_SPEED;
	}

	if(speedY >MAX_SPEED)
	{
		speedY = MAX_SPEED;
	}
	else if(speedY < -MAX_SPEED)
	{
		speedY = -MAX_SPEED;
	}
	
	
	
	ent.setX(ent.getX() + (int)speedX);
	//std::cout << "Things work up until here?" << std::endl;
	if(ent.getX() < 0 
		|| (ent.getX() + ent.getW() > ZONE_WIDTH) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setX(ent.getX() - (int)speedX);
	}
	ent.setY(ent.getY() + (int)speedY);
	if(ent.getY() < 0 
		|| (ent.getY() + ent.getH() > ZONE_HEIGHT) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setY(ent.getY() - (int)speedY);
	}

	std::cout << "x: " << ent.getX()  << std::endl;	
	std::cout << "y: " << ent.getY()  << std::endl;
	std::cout << "x speed: " << speedX  << std::endl;	
	std::cout << "y speed: " << speedY  << std::endl;

	
}


