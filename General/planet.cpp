#include <iostream>
#include <string>
#include <tuple>
#include "planet.h"
using namespace std;



Planet::Planet(): Sprite() {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass): Sprite(dBox, aTex), mass{mass} {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass, Star sun): Sprite(dBox, aTex), mass{mass} {initVelocity(sun);};
void Planet::initVelocity(Star sun)
{
	planetX = this->getTrueX() + this->getW()/2.0;
	planetY = this->getTrueY() + this->getH()/2.0;
	bodyX = sun.getTrueX() + sun.getW()/2.0;
	bodyY = sun.getTrueY() + sun.getH()/2.0;
	pointSlope = (bodyY - planetY)/(bodyX - planetX);
	pointAngle = atan(pointSlope);
	if(planetX > bodyX)
	{
		pointAngle += 3.1415926;
	}
	angle += 1.57079632679;
	float vel = std::sqrt(100000/std::sqrt(((bodyX-planetX)*(bodyX-planetX)*1.0 + (bodyY-planetY)*(bodyY-planetY)*1.0)));
	vx = vel*cos(angle);
	vy = vel*sin(angle);
}

int Planet::getRadius()
{
	return radius;
}

tuple<float, float> Planet::getCenterPosition()
{
	return {planetX,planetY};
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

void Planet::updatePosition()
{

}
//for now only calculate the gravity contribution from the sun
std::vector<float> Planet::calulateGravity(Star sun)
{
	planetX = getTrueX() + getW()/2.0;
	planetY = getTrueY() + getH()/2.0;
	bodyX = sun.getTrueX() + sun.getW()/2.0;
	bodyY = sun.getTrueY() + sun.getH()/2.0;
	//make fix 	pointSlope = (bodyY - planetY)/(bodyX - planetX);
	pointAngle = atan(pointSlope);
	if(planetX > bodyX)
	{
		pointAngle += 3.1415926;
	}
	float grav = 100000/((bodyX-planetX)*(bodyX-planetX)*1.0 + (bodyY-planetY)*(bodyY-planetY)*1.0);
	float gravX = grav*cos(pointAngle);
	float gravY = grav*sin(pointAngle);
	return {gravX, gravY};
}

