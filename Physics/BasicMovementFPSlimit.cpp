#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"
constexpr int MAX_SPEED = 5;
constexpr int MAX_DELTAV = 2;

//movement is handled by increasing and decreasing the thrust (acceleration) in a particular direction and is capped by a max speed and acceleration
int speedX = 0;
int speedY = 0;
int deltaVX = 0;
int deltaVY = 0;

//General wrapper function to handle Key evenets
bool handleKeyEvents(SDL_Event e, gpEntity &ent){
	if (e.type == SDL_QUIT) {
		return  false;
	}
	else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		handleKeyDownEvent(e, ent);
	}
	else if(e.type == SDL_KEYUP){
		handleKeyUpEvent(e, ent);
	}

	return true;
	
}

//Handles Up Key Events
void handleKeyUpEvent(SDL_Event e, gpEntity &ent){
	if(e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
			case SDLK_w:
				//std::cout <<  (ent.getVY() - MAX_SPEED) << std::endl;
				//if(ent.getVY() != 0){

					//ent.setVY(ent.getVY() + MAX_SPEED);
				//}
				//break;

			case SDLK_s:
				//if(ent.getVY() != 0){
					//ent.setVY(ent.getVY() - MAX_SPEED);
				//}
				deltaVY = 0;
				break;
			case SDLK_a:
				//if(ent.getVX() != 0){
					//ent.setVX(ent.getVX() + MAX_SPEED);
				//}
				//break;
			case SDLK_d:
				//if(ent.getVX() != 0){
					//ent.setVX(ent.getVX() - MAX_SPEED);
				//}
				deltaVX = 0;
				break;
		}
	
	}
}

//Handles down Key Events
void handleKeyDownEvent(SDL_Event e, gpEntity &ent){
	switch(e.key.keysym.sym) {
		case SDLK_w:
			
			//ent.setVY(ent.getVY() - MAX_SPEED);
			deltaVY--;
			
			break;

		case SDLK_a:

			//ent.setVX(ent.getVX() - MAX_SPEED);
			deltaVX--;
			break;

		case SDLK_s:
		
			//ent.setVY(ent.getVY() + MAX_SPEED);
			deltaVY++;
			break;

		case SDLK_d:
			
			//ent.setVX(ent.getVX() + MAX_SPEED);
			deltaVX++;
			break;
		
	}
	if(deltaVX > MAX_DELTAV)
	{
		deltaVX = MAX_DELTAV;
	}
	else if(deltaVX < -MAX_DELTAV)
	{
		deltaVX = -MAX_DELTAV;
	}
	if(deltaVY > MAX_DELTAV)
	{
		deltaVY = MAX_DELTAV;
	}
	else if(deltaVY < -MAX_DELTAV)
	{
		deltaVY = -MAX_DELTAV;
	}
}


void updatePosition(gpEntity &ent)
{
	speedX += deltaVX;
	speedY += deltaVY;
	if(speedX >MAX_SPEED)
	{
		speedX = MAX_SPEED;
	}
	else if(speedX <-MAX_SPEED)
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
	std::cout << ent.getVX() << ", " << ent.getVY() <<std::endl;
	ent.setX(ent.getX() + speedX);
	ent.setY(ent.getY() + speedY);
}


