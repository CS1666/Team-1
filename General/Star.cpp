#include "Star.h"
Star::Star(): Sprite() {mass = 100;};
Star::Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc): Sprite(dBox, aTex, dCirc){renderOrder = 2;mass = 100;};
Star::Star(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int m): Sprite(dBox, aTex, dCirc){renderOrder = 2;mass = m;};
//to be deprecated
Star::Star(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex){renderOrder = 2;mass = 100;};
Star::Star(SDL_Rect dBox, SDL_Texture* aTex, int m): Sprite(dBox, aTex){renderOrder = 2;mass = m;};

	int Star::getRadius()
	{
		return radius;
	}

	int Star::getGravity()
	{
		return gravity;
	}


	vector<int> Star::getPosition()
	{
		return position;
	}

	string Star::getSprite()
	{
		return sprite;
	}

	void Star::setRadius(int r)
	{
		radius = r;
	}

	void Star::setGravity(int g)
	{
		gravity = g;
	}


	void Star::setPosition(vector<int> newPos)
	{
		position = newPos;
	}

	void Star::setSprite(string s)
	{
		sprite = s;
	}

	void Star::setMass(int newMass){
		mass = newMass;	
	}

	vector<int> Star::getSize()
	{
		return size;
	}

	void Star::setSize(vector<int> newSize)
	{
		size = newSize;
	}