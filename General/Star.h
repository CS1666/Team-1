#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include <SDL.h>
using namespace std;

class Star : public Sprite
{
	private:
		int radius;
		int gravity;
		string type;
		string sprite;
		int mass;

	public:
		Star();
		Star(SDL_Rect dBox, SDL_Texture* aTex);
		Star(SDL_Rect dBox, SDL_Texture* aTex, int mass);
		Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc);
		Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int mass);
		int getRadius();
		int getGravity();
		string getType();
		string getSprite();
		void setRadius(int r);
		void setGravity(int g);
		void setType(string t);
		void setSprite(string s);
		int getMass();
		void setMass(int newMass);
		//vector<int> getSize();
		//void setSize(vector<int> newSize);
		//void setPosition(std::vector<int> newPos);
		//std::vector<int> getPosition();
};