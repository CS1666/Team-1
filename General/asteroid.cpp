#include "../General/asteroid.h"
using namespace std;


Asteroid::Asteroid(): Sprite() {};
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 2; isAst = true;};

int Asteroid::getRadius()
{
	return radius;
}

int Asteroid::getVelocity()
{
	return velocity;
}

float Asteroid::getDirection()
{
	return direction;
}

long Asteroid::getMass()
{
	return mass;	
}

pair<int, int> Asteroid::getPosition()
{
	return position;
}

string Asteroid::getSprite()
{
	return sprite;
}

void Asteroid::setRadius(int r)
{
	radius = r;
}

void Asteroid::setVelocity(int v)
{
	velocity = v;
}

void Asteroid::setDirection(float d)
{
	direction = d;
}

void Asteroid::setPosition(pair<int, int> newPos)
{
	position = newPos;
}

void Asteroid::setSprite(string s)
{
	sprite = s;
}

void Asteroid::setMass(long m)
{
	mass = m;	
}

float Asteroid::getVeloX(){
	return veloX;
}

float Asteroid::getVeloY(){
	return veloY;
}

void Asteroid::setVeloX(float vX){
	veloX = vX;
}

void Asteroid::setVeloY(float vY){
	veloY = vY;
}

void Asteroid::updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT)
{	
	
	setVeloX(veloX);
	setVeloY(veloY);
	setX(getTrueX() + veloX);
	collision_checker(getDrawBox(), osSprite, 0);
	setY(getTrueY() + veloY);	
	collision_checker(getDrawBox(), osSprite, 1);

}

void Asteroid::collision_checker(SDL_Rect* a, std::vector<Sprite*> &osSprite, int mode){		
	
	for (int i = 1; i < osSprite.size(); i++) {
		//so, one of these should result in collison if they are the same box
		if (osSprite.at(i)->isCircEnt()){
			
			if(mode == 0){
				if(check_collision(a, osSprite.at(i)->getCollisionCirc())){
					setX(getTrueX() - veloX);
				}
			}else if(mode == 1){
				if(check_collision(a, osSprite.at(i)->getCollisionCirc())){
					setY(getTrueY() - veloY);
				}
			}
						
		}else{

			if(mode == 0){
				if(check_collision(a, osSprite.at(i)->getCollisionCirc())){
					if(!osSprite.at(i)->getIsAsteroid()){
						setX(getTrueX() - veloX);
					}else{
						
					}
				}
			}else if(mode == 1){
				if(check_collision(a, osSprite.at(i)->getCollisionCirc())){
					if(!osSprite.at(i)->getIsAsteroid()){
						setY(getTrueY() - veloY);
					}else{

					}
				}
			}

		}
		
	}	
}

