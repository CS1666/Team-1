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
		vector<int> position;
		string sprite;
		vector<int> size;

	public:
		Star();
		Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc);
		Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int mass);
		//to be deprecated
		Star(SDL_Rect dBox, SDL_Texture* aTex);
		Star(SDL_Rect dBox, SDL_Texture* aTex, int mass);
		void initMass();
		int getRadius();
		int getGravity();
		string getType();
		vector<int> getPosition();
		string getSprite();
		void setRadius(int r);
		void setGravity(int g);
		void setType(string t);
		void setPosition(vector<int> newPos);
		void setSprite(string s);
		void setMass(int newMass);
		vector<int> getSize();
		void setSize(vector<int> newSize);
};