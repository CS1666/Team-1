#include "../AI/AIShip.h"
#include "Ship.h"
#include "Projectile.h"
#include <SDL.h> //temp
#include <iostream>
#include <math.h>
#include "../Physics/TimeData.h"
#include "../Physics/BasicGravity.h"
#include "../Physics/Momentum.h"

#define PI 3.14159265

constexpr double ACCEL = 60.0;
constexpr double ROTATION_ACCEL = 7200.0;
constexpr float MAX_SPEED = 6;
constexpr float MAX_DELTAV = 1;
constexpr float MAX_ROTATIONSPEED = 6;
constexpr float MAX_ROTATIONRATE = 2;

Ship::Ship(): Sprite() {};

Ship::Ship(const Ship& ship){

	
	currKey = ship.currKey;

    hull = ship.hull;
    weaponType = ship.weaponType;
    maxVelocity = ship.maxVelocity;

    xVelocity = ship.xVelocity;
    yVelocity = ship.yVelocity;
    currHp = ship.currHp;;
    maxHp = ship.maxHp;
    mass = ship.mass;
   

    curRotation = ship.curRotation;
    rotation = ship.rotation;
    maxRotation = ship.maxRotation;
    speedX = ship.speedX;
    speedY = ship.speedY;
    newAngle = ship.newAngle;

    damageTaken = ship.damageTaken;
    rotationSet = ship.rotationSet;
   	isUser = ship.isUser;
  	isAlly = ship.isAlly;

    sprite = ship.sprite;
    size = ship.size;
    position = ship.position;

    speed = ship.speed;
    deltaV = ship.deltaV;
    rotationRate = ship.rotationRate;
    rotationSpeed = ship.rotationSpeed;
    direction = ship.direction;

};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {weaponType = 1; renderOrder = 1; type = 1;};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim): Sprite(dBox, aTex, anim) {weaponType = 1; renderOrder = 1; type = 1;maxHp=50;currHp=maxHp;};

Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass): Sprite(dBox, aTex, anim), mass{mass} {weaponType = 1; renderOrder = 1; type = 1;};

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

bool Ship::getIsAlly()
{
	return isAlly;
}

void Ship::checkPhysics()
{

}

void Ship::setMaxDelta(float new_accel){
	max_deltaV = new_accel;
}

void Ship::setSpeedX(float speed)
{
	speedX = speed;
}
void Ship::setSpeedY(float speed)
{
	speedY = speed;
}

float Ship::getSpeedX(){
	return speedX;
}

float Ship::getSpeedY(){
	return speedY;
}

//integrate BasicMovementFPSlimit.cpp
void Ship::setPosition(pair<int,int> newPosition)
{
	setX(newPosition.first);
	setY(newPosition.second);
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
	else if(speed < 0)
	{
		speed = 0;
	}
	if(rotationSpeed > MAX_ROTATIONSPEED)
	{
		rotationSpeed = MAX_ROTATIONSPEED;
	}
	else if(rotationSpeed < -MAX_ROTATIONSPEED)
	{
		rotationSpeed = -MAX_ROTATIONSPEED;
	}

	//////std::cout << getVX() << ", " << getVY() <<std::endl;
	setAngle(getAngle() + rotationSpeed);
	float speedX = speed*cos((getAngle() - 90.0)*PI/180);
	float speedY = speed*sin((getAngle() - 90.0)*PI/180);
	// Try to move Horizontally

	std::vector<float> gravPulls = calculateGravityPull(*this, osSprite);
	speedX = speedX+gravPulls[0];
	speedY = speedY+gravPulls[1];
	setSpeedX(speedX);
	setSpeedY(speedY);
	setX(getTrueX() + speedX);

	
	if(check_all_collisions(getDrawBox(), osSprite)){

		setX(getTrueX() - speedX);
	}
	setY(getTrueY() + speedY);
	if(check_all_collisions(getDrawBox(), osSprite)){

		setY(getTrueY() - speedY);
	}
}

void Ship::updateMovement(std::vector<Sprite*> &osSprite,std::vector<Sprite*> otherSprites, int ZONE_WIDTH, int ZONE_HEIGHT)
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
	else if(speed < 0)
	{
		speed = 0;
	}
	if(rotationSpeed > MAX_ROTATIONSPEED)
	{
		rotationSpeed = MAX_ROTATIONSPEED;
	}
	else if(rotationSpeed < -MAX_ROTATIONSPEED)
	{
		rotationSpeed = -MAX_ROTATIONSPEED;
	}

	//////std::cout << getVX() << ", " << getVY() <<std::endl;
	setAngle(getAngle() + rotationSpeed);
	float speedX = speed*cos((getAngle() - 90.0)*PI/180);
	float speedY = speed*sin((getAngle() - 90.0)*PI/180);
	// Try to move Horizontally

	std::vector<float> gravPulls = calculateGravityPull(*this, otherSprites);
	speedX = speedX+gravPulls[0];
	speedY = speedY+gravPulls[1];
	setSpeedX(speedX);
	setSpeedY(speedY);
	setX(getTrueX() + speedX);
	setY(getTrueY() + speedY);
	
	if(check_all_collisions(getDrawBox(), osSprite) || check_all_collisions(getDrawBox(), otherSprites)){

		setX(getTrueX() - speedX);
		setY(getTrueY() - speedY);
	}
	
}

void Ship::updateMovementShips(std::vector<Sprite*> &osSprite, std::vector<Ship*> &osShip, int ZONE_WIDTH, int ZONE_HEIGHT)
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

	std::vector<float> gravPulls = calculateGravityPull(*this, osSprite);
	speedX = speedX+gravPulls[0];
	speedY = speedY+gravPulls[1];
	
	setSpeedX(speedX);
	setSpeedY(speedY);

	
	if(getTrueX() < 0 || (getX() + getW() > ZONE_WIDTH) || check_all_collisions_ships(getDrawBox(), osSprite)){
		setX(getTrueX() - speedX);
	}	
			
	
	if(getTrueY() < 0 || (getY() + getH() > ZONE_WIDTH) || check_all_collisions_ships(getDrawBox(), osSprite)){
		setY(getTrueY() - speedY);
	}
			
	for(int i = 1; i < osShip.size(); i++){
		if(this != osShip.at(i)){
			if(check_collision(getDrawBox(), osShip.at(i)->getDrawBox())){
				deltaV = 0;
				setMaxDelta(0);
				shipCollisionHandler(*this, *osShip.at(i));
			}else{
				setMaxDelta(1);
			}
		}
	}

	setX(getTrueX() + speedX);
	setY(getTrueY() + speedY);
		
}

void Ship::updateHull(int newHull)
{
	hull = newHull;
}

pair<int,int> Ship::getPosition()
{
	pair<int,int> temp;
	temp.first=getX();
	temp.second=getY();
	return temp;
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
    if(currHp>maxHp)
	currHp=maxHp;
    if (currHp <= 0){
	remove = true;
    }
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


int Ship::getMass()
{
	return mass;	
}

void Ship::fireWeapon()
{
	if (SDL_GetTicks() - getFireLastTime() > 500) {	
		fired = true;
		setFireLastTime();
	}
}

void Ship::getFired(std::vector<Sprite*> &osSprite, SDL_Texture* texture){
	if(fired){
		int X = getTrueX() + (getW()/2.0);// + (getH()/2.0)+  (getH()/2.0)*sin(getAngle()*1.1*.0174533) + 10*sin(getAngle()*1.1*.0174533);
		int Y = getTrueY() + (getH()/2.0);// + (getW()/2.0)+ (getW()/2.0)*-cos(getAngle()*1.1*.0174533) - 10*cos(getAngle()*1.1*.0174533);
		
		//std::cout << "Angle: " << getAngle() << std::endl;
		//std::cout << "Sin: " << sin(getAngle() *.0174533) << std::endl;
		//std::cout << "Cos: " << cos(getAngle() *.0174533) << std::endl;
		//std::cout << "Ship X: " << getTrueX() << std::endl;
		//std::cout << "Ship Y: " << getTrueY() << std::endl;
		//std::cout << "Laser X: " << X << std::endl;
		//std::cout << "Laser Y: " << Y << std::endl;
		SDL_Rect projBox = {X, Y, 2, 10};
		Projectile* laser = new Projectile(projBox, texture, weaponType, this);	
		laser->setAngle(getAngle());
		osSprite.push_back(laser);
		fired = false;
		Audio::play_laser_sound();
	}
}

/*Projectile Ship::fireWeaponatme(SDL_Texture* texture)
{
	int X = getTrueX() + (getH()/2.0)+  (getH()/2.0)*1.1*sin(getAngle()*.0174533);
	int Y = getTrueY()+ (getW()/2.0)+ (getW()/2.0)*1.1*-cos(getAngle()*.0174533);
	SDL_Rect ldb = {X, Y, 2, 10};
	Projectile laser(ldb, texture, weaponType);	
	laser.setAngle(getAngle()+180);
	setFireLastTime();
	return laser;
}*/


Uint32 Ship::getFireLastTime(){
		return fireLastTime;
}

void Ship::setFireLastTime(){
	fireLastTime = SDL_GetTicks();
}

Hero::Hero(SDL_Rect dBox, SDL_Texture* aTex): Ship(dBox, aTex, 2) {weaponType = 13; renderOrder = 1; isAlly = true; shipType=0;};

int Hero::getType()
{
    return shipType;
}
void Hero::upgradeType()
{
    shipType++;
    weaponType = weaponType*2;
	setF2(getF().second + 2);
}
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
			case SDLK_w:
				setAnimate(false);
				setF1(0);

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
			setAnimate(true);
			Audio::play_thrust_sound();
			break;

		case SDLK_a:

			rotationRate -= (ROTATION_ACCEL * TimeData::get_timestep());
			Audio::play_thrust_sound();
			break;

		case SDLK_s:
		
			//setVY(getVY() + MAX_SPEED);
			
			deltaV -= (ACCEL * TimeData::get_timestep());
			Audio::play_thrust_sound();
			break;

		case SDLK_d:
			
			//setVX(getVX() + MAX_SPEED);
			rotationRate += (ROTATION_ACCEL * TimeData::get_timestep());
			Audio::play_thrust_sound();
			break;
		case SDLK_x:
			speed = 0;
			deltaV = 0;
		
		case SDLK_g:
			if(getCurrHp() != getMaxHp())	
				setCurrHp(getCurrHp() + 5);
			////std::cout << "Current hp: " << getCurrHp() << std::endl;
			break;
		case SDLK_f:
			setCurrHp(getCurrHp() - 5);
			////std::cout << "Current hp: " << getCurrHp() << std::endl;
			break;
		case SDLK_SPACE:
			//fireWeapon();
			break;
	}
	
	if(deltaV > max_deltaV)
	{
		deltaV = max_deltaV;
	}
	else if(deltaV < -max_deltaV)
	{
		deltaV = -max_deltaV;
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

/*Fighter::Fighter(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 2, ally) {weaponType = 1;} ;

Cruiser::Cruiser(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 4, ally) {weaponType = 3;} ;

Capital::Capital(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 6, ally) {weaponType = 4;} ;*/

