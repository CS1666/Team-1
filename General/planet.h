#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include "Sprite.h"
#include "Star.h"
class Planet : public Sprite
{
public:
	Planet();
	Planet(SDL_Rect dBox, SDL_Texture* aTex);
	Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass);
	int getRadius();
	int getVelocity();
	float getDirection();
	int getGravity();
	tuple<float, float> getPosition();
	string getSprite();
	void setRadius(int r);
	void setVelocity(int v);
	void setDirection(float d);
	void setGravity(int g);
	void setPosition(tuple<int, int> newPos);
	void setSprite(string s);
	int getMass();
	void setMass(int newMass);
	void updatePosition(Star sun);
private:
	int radius;
	int velocity;
	float direction;
	int gravity;
	tuple<float, float> position;
	string sprite;
	int mass;
};