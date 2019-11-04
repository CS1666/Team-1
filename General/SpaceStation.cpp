#include "SpaceStation.h"
SpaceStation::SpaceStation(): Sprite() {};
SpaceStation::SpaceStation(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex){renderOrder = 1;};

SpaceStation::SpaceStation(SDL_Rect dBox, SDL_Texture* aTex, int mass): Sprite(dBox, aTex), mass{mass}{renderOrder = 1;};

	int SpaceStation::getRadius()
	{
		return radius;
	}

	int SpaceStation::getGravity()
	{
		return gravity;
	}

	string SpaceStation::getType()
	{
		return type;
	}

	vector<int> SpaceStation::getPosition()
	{
		return position;
	}

	string SpaceStation::getSprite()
	{
		return sprite;
	}

	void SpaceStation::setRadius(int r)
	{
		radius = r;
	}

	void SpaceStation::setGravity(int g)
	{
		gravity = g;
	}

	void SpaceStation::setType(string t)
	{
		type = t;
	}

	void SpaceStation::setPosition(vector<int> newPos)
	{
		position = newPos;
	}

	void SpaceStation::setSprite(string s)
	{
		sprite = s;
	}
		
	int SpaceStation::getMass(){
		return mass;	
	}

	void SpaceStation::setMass(int newMass){
		mass = newMass;	
	}

	vector<int> SpaceStation::getSize()
	{
		return size;
	}

	void SpaceStation::setSize(vector<int> newSize)
	{
		size = newSize;
	}
