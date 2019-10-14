#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicGravity.h"
#include "../Physics/BasicMovementFPSlimit.h"

#define PI 3.14159265
#definte G .00000000006674

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
SDL_Point body1Center;
SDL_Point body2Center;
double pointDistance;
double pointAngle;
double pointSlope;
double gravForce;
long mass1 = 0;
long mass2 = 0;

// function to handle gravitational pull
void gravity_pull(Sprite &body1, Sprite &body2){
	body1Center.x = body1.getX() + body1.getW()/2;
	body1Center.y = body1.getY() - body1.getH()/2;
	body2Center.x = body2.getX() + body2.getW()/2;
	body2Center.y = body2.getX() - body2.getH()/2;
	pointDistance = sqrt((body2Center.x - body1Center.x)*(body2Center.x - body1Center.x) + (body2Center.y - body1Center.y)*(body2Center.y - body1Center.y));
	//pointSlope = (bodyCenter.y - playerCenter.y)/(bodyCenter.x - playerCenter.x);
	//pointAngle = atan(pointSlope);
	gravForce = G*(mass1 * mass2)/(pointDistance*pointDistance);
	if(pointDistance < body2.getW()*1.5 || pointDistance < body2.getH()*1.5){
		if((body1.getX() + body1.getW()/2) < (body2.getX() + body2.getW()/2)){
			deltaX = deltaX + .5;
			
		}else if((playerent.getX() + playerent.getW()/2) > (body2.getX() + body2.getW()/2)){
			deltaX = deltaX - .5;
		}

		if((body1.getY() + body1.getW()/2) < (body2.getY() + body2.getW()/2)){
			
			deltaY++;
		}else if((body1.getY() + body1.getW()/2) > (body2.getY() + body2.getW()/2)){
			
			deltaY--;
		}
	}else if(pointDistance < body2.getW() || pointDistance < body2.getH()){
		if((body1.getX() + body1.getW()/2) < (body2.getX() + body2.getW()/2)){
			deltaX++;
			
		}else if((body1.getX() + body1.getW()/2) > (body2.getX() + body2.getW()/2)){
			deltaX--;
		}

		if((body1.getY() + body1.getW()/2) < (body2.getY() + body2.getW()/2)){
			
			deltaY++;
		}else if((body1.getY() + body1.getW()/2) > (body2.getY() + body2.getW()/2)){
			
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
	std::cout << "Width: " << body2.getW()*1.5 << std::endl;
	std::cout << "Height: " << body2.getH()*1.5 << std::endl;
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


