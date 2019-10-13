#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicGravity.h"
#include "../Physics/BasicMovementFPSlimit.h"

#define PI 3.14159265

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
SDL_Point playerCenter;
SDL_Point bodyCenter;
double pointDistance;
double pointAngle;
double pointSlope;

// function to handle gravitational pull
void gravity_pull(Sprite &playerent, Sprite &bodyent){
	playerCenter.x = playerent.getX() + playerent.getW()/2;
	playerCenter.y = playerent.getY() - playerent.getH()/2;
	bodyCenter.x = bodyent.getX() + bodyent.getW()/2;
	bodyCenter.y = bodyent.getX() - bodyent.getH()/2;
	pointDistance = sqrt((bodyCenter.x - playerCenter.x)*(bodyCenter.x - playerCenter.x) + (bodyCenter.y - playerCenter.y)*(bodyCenter.y - playerCenter.y));
	//pointSlope = (bodyCenter.y - playerCenter.y)/(bodyCenter.x - playerCenter.x);
	//pointAngle = atan(pointSlope);
	if(pointDistance < bodyent.getW()*1.5 || pointDistance < bodyent.getH()*1.5){
		if((playerent.getX() + playerent.getW()/2) < (bodyent.getX() + bodyent.getW()/2)){
			deltaX = deltaX + .5;
			
		}else if((playerent.getX() + playerent.getW()/2) > (bodyent.getX() + bodyent.getW()/2)){
			deltaX = deltaX - .5;
		}

		if((playerent.getY() + playerent.getW()/2) < (bodyent.getY() + bodyent.getW()/2)){
			
			deltaY++;
		}else if((playerent.getY() + playerent.getW()/2) > (bodyent.getY() + bodyent.getW()/2)){
			
			deltaY--;
		}
	}else if(pointDistance < bodyent.getW() || pointDistance < bodyent.getH()){
		if((playerent.getX() + playerent.getW()/2) < (bodyent.getX() + bodyent.getW()/2)){
			deltaX++;
			
		}else if((playerent.getX() + playerent.getW()/2) > (bodyent.getX() + bodyent.getW()/2)){
			deltaX--;
		}

		if((playerent.getY() + playerent.getW()/2) < (bodyent.getY() + bodyent.getW()/2)){
			
			deltaY++;
		}else if((playerent.getY() + playerent.getW()/2) > (bodyent.getY() + bodyent.getW()/2)){
			
			deltaY--;
		}

	}else{
		deltaX = 0;
		deltaY = 0;
		speedX = 0;
		speedY = 0;
	}

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
	std::cout << "Width: " << bodyent.getW()*1.5 << std::endl;
	std::cout << "Height: " << bodyent.getH()*1.5 << std::endl;
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
	
	
	
	ent.setY(ent.getY() + (int)speedY);
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

	
}


