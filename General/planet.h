#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include "Sprite.h"
#include "Star.h"
#include <cmath>
#include "../Physics/TimeData.h"

class Planet : public Sprite
{
public:
	Planet();
	Planet(SDL_Rect dBox, SDL_Texture* aTex);
	Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass);
	Planet(SDL_Rect dBox, SDL_Texture* aTex, int mass, Star sun);
	void initVelocity(Star& sun);
	int getRadius();
	tuple<float, float> getCenterPosition();
	string getSprite();
	void setRadius(int r);
	void setVelocity(int v);
	void setSprite(string s);
	int getMass();
	void setMass(int newMass);
	void updatePosition();
	//for now only calculate the gravity contribution from the sun
	std::vector<float> calulateGravity(Star& sun);
private:
	int radius;
	int velocity;
	float direction;
	float fx;
	float fy;
	float vx;
	float vy;
	//float totalGrav;
	string sprite;
	Star sun;
	int mass;
	float planetX = 0;
	float planetY = 0;
	float bodyX = 0;
	float bodyY = 0;
	float pointAngle;
	float pointSlope;
};