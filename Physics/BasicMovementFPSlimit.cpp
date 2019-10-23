#include "BasicMovementFPSlimit.h"

#define PI 3.14159265

constexpr float MAX_SPEED = 6;
constexpr float MAX_DELTAV = 2;
constexpr float MAX_ROTATIONSPEED = 6;
constexpr float MAX_ROTATIONRATE = 2;
/*
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;*/

//movement is handled by increasing and decreasing the thrust (acceleration) in a particular direction and is capped by a max speed and acceleration
float speed = 0;
float deltaV = 0;
//int acceleration = 0;
float rotationRate = 0;
float rotationSpeed = 0;
float direction;


//General wrapper function to handle Key evenets
bool handleKeyEvents(SDL_Event e, Sprite &ent){
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
void handleKeyUpEvent(SDL_Event e, Sprite &ent){
	if(e.type == SDL_KEYUP){
		switch(e.key.keysym.sym){
				//std::cout <<  (ent.getVY() - MAX_SPEED) << std::endl;
				//if(ent.getVY() != 0){

					//ent.setVY(ent.getVY() + MAX_SPEED);
				//}
				//break;

			case SDLK_s:
				//if(ent.getVY() != 0){
					//ent.setVY(ent.getVY() - MAX_SPEED);
				//}
								
				deltaV = 0;
				break;
			case SDLK_a:
				//if(ent.getVX() != 0){
					//ent.setVX(ent.getVX() + MAX_SPEED);
				//}
			case SDLK_d:
				//if(ent.getVX() != 0){
					//ent.setVX(ent.getVX() - MAX_SPEED);
				//}
				rotationRate = 0;
				

				break;
		}
	
	}
}

//Handles down Key Events
void handleKeyDownEvent(SDL_Event e, Sprite &ent){
	direction = (ent.getAngle() - 90.0)*PI/180;	

	switch(e.key.keysym.sym) {
		case SDLK_w:
			
			//ent.setVY(ent.getVY() - MAX_SPEED);
			deltaV++;
			break;

		case SDLK_a:

			//ent.setVX(ent.getVX() - MAX_SPEED);
			rotationRate -= 2.0;
			break;

		case SDLK_s:
		
			//ent.setVY(ent.getVY() + MAX_SPEED);
			
			deltaV--;
			break;

		case SDLK_d:
			
			//ent.setVX(ent.getVX() + MAX_SPEED);
			rotationRate += 2.0;
			break;
		case SDLK_x:
			speed = 0;
			deltaV = 0;
		case SDLK_SPACE:
			//Fire laser
			break;
		
	}
	if(deltaV > MAX_DELTAV)
	{
		deltaV = MAX_DELTAV;
	}
	else if(deltaV < -MAX_DELTAV)
	{
		deltaV = -MAX_DELTAV;
	}
	if(rotationRate > MAX_ROTATIONRATE)
	{
		rotationRate = MAX_ROTATIONRATE;
	}
	else if(rotationRate < -MAX_ROTATIONRATE)
	{
		rotationRate = -MAX_ROTATIONRATE;
	}
	
}

//tis is te simple collision check from the examples
bool check_collision(SDL_Rect* a, SDL_Rect* b) {
	// Check vertical overlap
	if (a->y + a->h <= b->y)
		return false;
	if (a->y >= b->y + b->h)
		return false;

	// Check horizontal overlap
	if (a->x >= b->x + b->w)
		return false;
	if (a->x + a->w <= b->x)
		return false;

	// Must overlap in both
	return true;
}

bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite){
	bool isCollision = false;
	//std::cout << "osEntity.size() = " << osEntity.size() << std::endl;
	for(int i = 0;  i < osSprite.size(); i++){
		//so, one of these should result in collison if they are the same box
		isCollision = check_collision(a, osSprite.at(i)->getDrawBox());
		//std::cout << "Is last command Illegal?" << std::endl;
		//std::cout << "Checked collisions: " << i << std::endl;
	}
	return isCollision;
}


void updatePosition(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT){
	//needs to be changed to update all objects in the list
	speed += deltaV;
	rotationSpeed += rotationRate;
	if (rotationSpeed < 0)
	{
		rotationSpeed++;
	}
	else if (rotationSpeed > 0)
	{
		rotationSpeed--;
	}
	if(speed >MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	else if(speed < -MAX_SPEED)
	{
		speed = -MAX_SPEED;
	}
	if(rotationSpeed > MAX_ROTATIONSPEED)
	{
		rotationSpeed = MAX_ROTATIONSPEED;
	}
	else if(rotationSpeed < -MAX_ROTATIONSPEED)
	{
		rotationSpeed = -MAX_ROTATIONSPEED;
	}
	
	//std::cout << ent.getVX() << ", " << ent.getVY() <<std::endl;
	ent.setAngle(ent.getAngle() + rotationSpeed);
	float speedX = speed*cos((ent.getAngle() - 90.0)*PI/180);
	float speedY = speed*sin((ent.getAngle() - 90.0)*PI/180);
	// Try to move Horizontally


	ent.setX(ent.getTrueX() + speedX);
	if(ent.getTrueX() < 0 


		|| (ent.getX() + ent.getW() > ZONE_WIDTH) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setX(ent.getTrueX() - speedX);
	}
	ent.setY(ent.getTrueY() + speedY);
	if(ent.getY() < 0 
		|| (ent.getY() + ent.getH() > ZONE_HEIGHT) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setY(ent.getTrueY() - speedY);
	}

	std::cout << ent.getAngle() - 90 << std::endl;
	std::cout << "x: " << ent.getTrueX()  << std::endl;	
	std::cout << "y: " << ent.getTrueY()  << std::endl;
	std::cout << "speedX: " << speedX << std::endl;
	std::cout << "speedY: " << speedY << std::endl;

}
void updatePosition(Ship &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT){
	//needs to be changed to update all objects in the list
	speed += deltaV;
	rotationSpeed += rotationRate;
	if (rotationSpeed < 0)
	{
		rotationSpeed++;
	}
	else if (rotationSpeed > 0)
	{
		rotationSpeed--;
	}
	if(speed >MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	else if(speed < -MAX_SPEED)
	{
		speed = -MAX_SPEED;
	}
	if(rotationSpeed > MAX_ROTATIONSPEED)
	{
		rotationSpeed = MAX_ROTATIONSPEED;
	}
	else if(rotationSpeed < -MAX_ROTATIONSPEED)
	{
		rotationSpeed = -MAX_ROTATIONSPEED;
	}
	
	//std::cout << ent.getVX() << ", " << ent.getVY() <<std::endl;
	ent.setAngle(ent.getAngle() + rotationSpeed);
	float speedX = speed*cos((ent.getAngle() - 90.0)*PI/180);
	float speedY = speed*sin((ent.getAngle() - 90.0)*PI/180);
	// Try to move Horizontally

	std::vector<float> gravPulls = calculateGravityPull(ent, *osSprite[1]);
	speedX = speedX+gravPulls[0];
	speedY = speedY+gravPulls[1];
	ent.setSpeedX(speedX);
	ent.setSpeedY(speedY);

	ent.setX(ent.getTrueX() + speedX);
	if(ent.getTrueX() < 0 


		|| (ent.getX() + ent.getW() > ZONE_WIDTH) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setX(ent.getTrueX() - speedX);
	}
	ent.setY(ent.getTrueY() + speedY);
	if(ent.getY() < 0 
		|| (ent.getY() + ent.getH() > ZONE_HEIGHT) 
		|| check_all_collisions(ent.getDrawBox(), osSprite)){

		ent.setY(ent.getTrueY() - speedY);
	}

	std::cout << ent.getAngle() - 90 << std::endl;
	std::cout << "x: " << ent.getTrueX()  << std::endl;	
	std::cout << "y: " << ent.getTrueY()  << std::endl;
	std::cout << "speedX: " << speedX << std::endl;
	std::cout << "speedY: " << speedY << std::endl;
	std::cout << "Grav x: " << gravPulls[0] << std::endl;
	std::cout << "Grav y: " << gravPulls[1] << std::endl;

}


