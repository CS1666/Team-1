#include <iostream>
#include <string>
#include <tuple>
#include "planet.h"
using namespace std;



Planet::Planet(): Sprite() {};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 2;};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass): Sprite(dBox, aTex), mass{mass} {renderOrder = 2;};
Planet::Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass, Star sun): Sprite(dBox, aTex), mass{mass} {initVelocity(sun); renderOrder = 2;};
void Planet::initVelocity(Star& star)
{
	sun = star;
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
	//float vel = std::sqrt(1000/std::sqrt(((bodyX-planetX)*(bodyX-planetX)*1.0 + (bodyY-planetY)*(bodyY-planetY)*1.0)));
	float vel = 100;
	vx = vel*cos(angle);
	vy = vel*sin(angle);
	std::cout << angle * 180 / 3.1415926 << std::endl;
	std::cout << vx << std::endl;
	std::cout << vy << std::endl;
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
	std::vector<float> gravs = calulateGravity(sun);
	fx = gravs[0];
	fy = gravs[1];
	std::cout << "fx : " << fx << std::endl;
	std::cout << "fy : " << fy << std::endl;
	std::cout << "vx : " << vx << std::endl;
	std::cout << "vy : " << vy << std::endl;
	vx += fx*TimeData::get_timestep();
	vy += fy*TimeData::get_timestep();
	this->setX((float)(this->getTrueX() + vx*TimeData::get_timestep()));
	this->setY((float)(this->getTrueY() + vy*TimeData::get_timestep()));
	std::cout << "planet X: " << this->getTrueX() << std::endl;
	std::cout << "planet Y: " << this->getTrueY() << std::endl;
}
//for now only calculate the gravity contribution from the sun
std::vector<float> Planet::calulateGravity(Star& sun)
{
	planetX = getTrueX() + getW()/2.0;
	planetY = getTrueY() + getH()/2.0;
	bodyX = sun.getTrueX() + sun.getW()/2.0;
	bodyY = sun.getTrueY() + sun.getH()/2.0;
	pointSlope = (bodyY - planetY)/(bodyX - planetX);
	pointAngle = atan(pointSlope);
	if(planetX > bodyX)
	{
		pointAngle += 3.1415926;
	}
	std::cout << "Star planet angle: " << pointAngle *180/3.14<< std::endl;
	float grav = 10000.0/600; //std::sqrt((bodyX-planetX)*(bodyX-planetX)*1.0 + (bodyY-planetY)*(bodyY-planetY)*1.0);
	//grav *= TimeData::get_timestep()*TimeData::get_timestep();
	float gravX = grav*cos(pointAngle);
	float gravY = grav*sin(pointAngle);
	return {gravX, gravY};
}

