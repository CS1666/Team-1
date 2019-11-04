#include "Ship.h"
#include <SDL.h> //temp
#include <iostream>
#include <math.h>
#include "../Physics/TimeData.h"
#include "../Physics/BasicGravity.h"

#define PI 3.14159265

constexpr double ACCEL = 60.0;
constexpr double ROTATION_ACCEL = 7200.0;
constexpr float MAX_SPEED = 6;
constexpr float MAX_DELTAV = 1;
constexpr float MAX_ROTATIONSPEED = 6;
constexpr float MAX_ROTATIONRATE = 2;

Ship::Ship(): Sprite() {};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 1;};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim): Sprite(dBox, aTex, anim) {renderOrder = 1;};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass): Sprite(dBox, aTex, anim), mass{mass} {renderOrder = 1;};

Ship::~Ship()
{
	SDL_DestroyTexture(assetTex);
	assetTex = nullptr;
}

void Ship::setSprite(string newSprite)
{
	sprite = newSprite;
}

string Ship::getSprite()
{
	return sprite;
}

void Ship::checkPhysics()
{

}

void Ship::setSpeedX(float speed)
{
	speedX = speed;
}
void Ship::setSpeedY(float speed)
{
	speedY = speed;
}

//integrate BasicMovementFPSlimit.cpp
void Ship::setPosition(pair<int,int> newPosition)
{
	position = newPosition;
}

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
	for(int i = 1;  i < osSprite.size(); i++){
		//so, one of these should result in collison if they are the same box
		isCollision |= check_collision(a, osSprite.at(i)->getDrawBox());
		//std::cout << "Is last command Illegal?" << std::endl;
		//std::cout << "Checked collisions: " << i << std::endl;
	}
	return isCollision;
}

void Ship::updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT)
{
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

	//std::cout << getVX() << ", " << getVY() <<std::endl;
	setAngle(getAngle() + rotationSpeed);
	float speedX = speed*cos((getAngle() - 90.0)*PI/180);
	float speedY = speed*sin((getAngle() - 90.0)*PI/180);
	// Try to move Horizontally

	std::vector<float> gravPulls = calculateGravityPull(*this, *osSprite[1]);
	speedX = speedX+gravPulls[0];
	speedY = speedY+gravPulls[1];
	setSpeedX(speedX);
	setSpeedY(speedY);
	setX(getTrueX() + speedX);
	if(getTrueX() < 0 

		|| (getX() + getW() > ZONE_WIDTH)
		|| check_all_collisions(getDrawBox(), osSprite)){

		setX(getTrueX() - speedX);
	}
	setY(getTrueY() + speedY);
	if(getY() < 0 
		|| (getY() + getH() > ZONE_HEIGHT)
		|| check_all_collisions(getDrawBox(), osSprite)){

		setY(getTrueY() - speedY);
	}
}

void Ship::updateHull(int newHull)
{
	hull = newHull;
}

pair<int,int> Ship::getPosition()
{
	return position;
}

void Ship::setDestination(pair<int,int> newDestination)
{
	destination = newDestination;
}

pair<int,int> Ship::getDestination()
{
	return destination;
}

void Ship::setPath(queue<pair<int,int>>* thePath)
    {
	//fullstops ship when setting path
	//cout<<"something"<<endl;
	xVelocity=0;
	yVelocity=0;
	rotation=0;
	maxVelocity=10;
	maxRotation=10;
	rotationSet=false;
    	path = thePath;
        pathComplete=false;
    }

    int Ship::getMaxVelocity()
    {
        return maxVelocity;
    }

    int Ship::getCurrHp()
    {
       return currHp;    
    }

    void Ship::setCurrHp(int newCurrHp)
    {
       currHp = newCurrHp;    
    }

    int Ship::getMaxHp()
    {
	   return maxHp;    
    }

    void Ship::setMaxHp(int newMaxHp)
    {
	   maxHp = newMaxHp;    
    }

    pair<int, int> Ship::getSize()
    {
        return size;
    }

    void Ship::setSize(pair<int, int> newSize)
    {
        size = newSize;
    }

    //ai follows path assigned to it by ai class
    void Ship::followPath(Sprite& entity)
    {
	    //note: change the path in Ship.h to whatever is returned.
	    if(!path->empty())
	    {
		//note: assumed whatever we're using is some (x,y)
		pair<int,int> coords=path->front();
		int x_coord=coords.first;
		int y_coord=coords.second;
		int cur_x=position.first;
		int cur_y=position.second;
		double xSlope=x_coord-cur_x;
		double ySlope=y_coord-cur_y;
		//get angle of destination
		if(!rotationSet)
		{
			//if(y_coord>cur_y)
			curRotation= atan2(-ySlope,xSlope);
			if(curRotation<0)
			    curRotation+=2*PI;
			//cout<<"radian cur: "<<curRotation<<endl;
			char n;
			if(xSlope==0&&ySlope<0)
			    curRotation=0;
			else if(ySlope==0&&xSlope<0)
			    curRotation=270;
			else if(xSlope==0&&ySlope>0)
			    curRotation=180;
			else if(ySlope==0&&xSlope>0)
			    curRotation=90;
			else if(curRotation>0&&curRotation<PI/2)
			{
			    curRotation=(int)std::floor(curRotation*180/PI);
			//	cout<<"first quad"<<endl;
			//	cin>>n;
			}
			else if(curRotation>PI/2&&curRotation<3*PI/2 && ySlope>0)
			{
			    curRotation=(int)std::floor(curRotation*180/PI);
			//	cout<<"second quad"<<endl;
			//	cin>>n;
			}
			else if(curRotation>3*PI/2&&curRotation<2*PI)
			{
			    curRotation=(int)floor(curRotation*180/PI-180);
				//cout<<"third quad"<<endl;
				//cin>>n;
			}
			else
			{
			    curRotation=(int)std::floor(curRotation*180/PI+180);
			    //cout<<"fourth quad"<<endl;
			   //cin>>n;
			}
			//cout<<"rotation: "<<curRotation<<endl;
			//int n;
			//cin>>n;
			rotationSet=true;
		}
		double angle=entity.getAngle();
		//cout<<"currotation:"<<curRotation<<endl;
		//cout<<"cur angle: "<<angle<<endl;
		bool angleChanged=false;
		if(curRotation>angle)
		{
		    //pretty shit acceleration stuff tbh
		    if(curRotation>angle+maxRotation)
		    {
			if(maxRotation>rotation)
			    entity.setAngle(angle+rotation++);
			else
			    entity.setAngle(angle+rotation);
		    }
		    else
		        entity.setAngle(angle+1);
		    angleChanged=true;
		}
		else if(angle>curRotation)
		{
		    if(angle-maxRotation>curRotation)
		    {
			if(maxRotation>rotation)
			    entity.setAngle(angle-(rotation++));
			else
			    entity.setAngle(angle-rotation);
		    }
		    else
			entity.setAngle(angle-1);
		    angleChanged=true;
		}
		if(abs(entity.getAngle()>360))
		    entity.setAngle((int)entity.getAngle()%360);
		//entity.setAngle(122);
	//cout<<"cur_x: "<<cur_x<<" cur_y : "<<cur_y<<endl;
        //std::cout << "x: " << x_coord << " y: " << y_coord << "points remaing: " << path->size() << endl;
		//note: since we don't have updateMovement implemented, most
		//of the stuff here can probably be removed/handled by that
		//simulate turning, acceleration of ship
		if(!angleChanged&&(cur_x != x_coord || cur_y != y_coord))
		{
		    if(cur_x-maxVelocity>x_coord)
		    {
			if(maxVelocity>xVelocity)
			    cur_x-=xVelocity++;
			else
			    cur_x-=xVelocity;
		    }
		    else if(cur_x>x_coord)
		    {
			cur_x=x_coord; //skipped
			rotationSet=false;
		    }
		    else if(cur_x+maxVelocity<x_coord)
		    {
			if(maxVelocity>xVelocity)
			    cur_x+=xVelocity++;
			else
			    cur_x+=xVelocity;
		    }
		    else if(cur_x<x_coord)
		    {
			cur_x=x_coord; //skipped
			rotationSet=false;
		    }
		    if(cur_y-maxVelocity>y_coord)
		    {
			if(maxVelocity>yVelocity)
			    cur_y-=yVelocity++;
			else
			    cur_y-=yVelocity;
		    }
		    else if(cur_y>y_coord)
		    {
			cur_y=y_coord; //skipped
			rotationSet=false;
		    }
		    else if(cur_y+maxVelocity<y_coord)
		    {
			if(maxVelocity>yVelocity)
			    cur_y+=yVelocity++;
			else
			    cur_y+=yVelocity;
		    }
		    else if(cur_y<y_coord)
		    {
			cur_y=y_coord; //skipped
			rotationSet=false;
		    }
		    entity.setX(cur_x);
		    entity.setY(cur_y);
		    position.first=cur_x;
		    position.second=cur_y;
		}
		else if(cur_x==x_coord&&cur_y==y_coord)
		{
		    path->pop();
		    rotationSet=false;
		}
	    }
	    else
	    {
		setSpeedY(0);
		setSpeedX(0);
	        pathComplete=true;
	    }
	}

bool Ship::getPathComplete()
{
	return pathComplete;
}

int Ship::getMass()
{
	return mass;	
}

Projectile Ship::fireWeapon(SDL_Texture* texture)
{
	//float speedX = speed*cos((getAngle() - 90.0)*PI/180);
	//float speedY = speed*sin((getAngle() - 90.0)*PI/180);


	std::cout << "Firing Angle: " << getAngle() << std::endl;
	int X = getTrueX() + (getW()/2);//*cos(getAngle());
	int Y = getTrueY();// + (getW()/2)*sin(getAngle());
	std::cout << "Ship X: " << getTrueX() << std::endl;
	std::cout << "Ship Y: " << getTrueY() << std::endl;
	std::cout << "Laser X: " << X << std::endl;
	std::cout << "Laser Y: " << Y << std::endl;
	SDL_Rect ldb = {X, Y, 2, 10};
	Projectile laser(ldb, texture);
	laser.setAngle(getAngle());
	return laser;
}

Hero::Hero(SDL_Rect dBox, SDL_Texture* aTex): Ship(dBox, aTex, 0) {renderOrder = 0;};


//General wrapper function to handle Key evenets
bool Hero::handleKeyEvents(SDL_Event e){
	if (e.type == SDL_QUIT) {
		return  false;
	}
	else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		handleKeyDownEvent(e);
	}
	else if(e.type == SDL_KEYUP){
		handleKeyUpEvent(e);
	}

	return true;
	
}

//Handles Up Key Events
void Hero::handleKeyUpEvent(SDL_Event e){
	if(e.type == SDL_KEYUP){
		switch(e.key.keysym.sym){
			

			case SDLK_s:
							
				deltaV = 0;
				break;
			case SDLK_a:
				
			case SDLK_d:
				
				rotationRate = 0;
			
				break;	
		}
	
	}
}

//Handles down Key Events
void Hero::handleKeyDownEvent(SDL_Event e){
	//direction = (getAngle() - 90.0)*PI/180;

	switch(e.key.keysym.sym) {
		case SDLK_w:
			
			deltaV += (ACCEL * TimeData::get_timestep());
			break;

		case SDLK_a:

			rotationRate -= (ROTATION_ACCEL * TimeData::get_timestep());
			break;

		case SDLK_s:
		
			//setVY(getVY() + MAX_SPEED);
			
			deltaV -= (ACCEL * TimeData::get_timestep());
			break;

		case SDLK_d:
			
			//setVX(getVX() + MAX_SPEED);
			rotationRate += (ROTATION_ACCEL * TimeData::get_timestep());
			break;
		case SDLK_x:
			speed = 0;
			deltaV = 0;
		
		case SDLK_g:
			if(getCurrHp() != getMaxHp())	
				setCurrHp(getCurrHp() + 5);
			std::cout << "Current hp: " << getCurrHp() << std::endl;
			break;
		case SDLK_f:
			setCurrHp(getCurrHp() - 5);
			std::cout << "Current hp: " << getCurrHp() << std::endl;
			break;
		case SDLK_SPACE:
			//fireWeapon();
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
