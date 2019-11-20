#include "../General/asteroid.h"
using namespace std;


Asteroid::Asteroid(): Sprite() {};
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 2;};

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


