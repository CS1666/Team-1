#include "Star.h"
Star::Star(): Sprite() {};
Star::Star(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex){renderOrder = 2;};

Star::Star(SDL_Rect dBox, SDL_Texture* aTex, int mass): Sprite(dBox, aTex), mass{mass}{renderOrder = 2;};

	int Star::getRadius()
	{
		return radius;
	}

	int Star::getGravity()
	{
		return gravity;
	}

	string Star::getType()
	{
		return type;
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

	void Star::setType(string t)
	{
		type = t;
	}

	void Star::setPosition(vector<int> newPos)
	{
		position = newPos;
	}

	void Star::setSprite(string s)
	{
		sprite = s;
	}
		
	int Star::getMass(){
		return mass;	
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