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
		vector<int> position;
		string sprite;
		int mass;
		vector<int> size;

	public:
		Star();
		Star(SDL_Rect dBox, SDL_Texture* aTex);
		Star(SDL_Rect dBox, SDL_Texture* aTex, int mass);
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
		int getMass();
		void setMass(int newMass);
		vector<int> getSize();
		void setSize(vector<int> newSize);
};