#include <iostream>
#include <string>
#include <tuple>
#include "planet.h"
using namespace std;

Planet::Planet(): Sprite() {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass): Sprite(dBox, aTex), mass{mass} {};


int Planet::getRadius()
{
	return radius;
}

int Planet::getVelocity()
{
	return velocity;
}

float Planet::getDirection()
{
	return direction;
}

int Planet::getGravity()
{
	return gravity;
}

tuple<float, float> Planet::getPosition()
{
	return position;
}

string Planet::getSprite()
{
	return sprite;
}

void Planet::setRadius(int r)
{
	radius = r;
}

void Planet::setVelocity(int v)
{
	velocity = v;
}

void Planet::setDirection(float d)
{
	direction = d;
}

void Planet::setGravity(int g)
{
	gravity = g;
}

void Planet::setPosition(tuple<int, int> newPos)
{
	position = newPos;
}

void Planet::setSprite(string s)
{
	sprite = s;
}

int Planet::getMass()
{
	return mass;	
}

void Planet::setMass(int newMass)
{
	mass = newMass;	
}

