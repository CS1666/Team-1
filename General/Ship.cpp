
#include "Ship.h"
#include <SDL.h> //temp
#include <iostream>
#include <math.h>
    Ship::Ship(): Sprite() {};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 1;};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim): Sprite(dBox, aTex, anim) {renderOrder = 1;};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass): Sprite(dBox, aTex, anim), mass{mass} {renderOrder = 1;};

    Ship::~Ship()
    {
        SDL_DestroyTexture(assetTex);
        assetTex = nullptr;
    }

    void Ship::setSprite(string newSprite)
    {
        sprite = newSprite;
    }

    string Ship::getSprite()
    {
        return sprite;
    }

    void Ship::checkPhysics()
    {

    }

    void Ship::setSpeedX(float speed)
    {
        speedX = speed;
    }
    void Ship::setSpeedY(float speed)
    {
        speedY = speed;
    }

    //integrate BasicMovementFPSlimit.cpp
    void Ship::setPosition(pair<int,int> newPosition)
    {
        position = newPosition;
    }

    //integrate BasicMovementFPSlimit.cpp
    void Ship::updateMovement()
    {
        
    }

    void Ship::checkAction(/*stream*/)
    {

    }

    void Ship::updateHull(int newHull)
    {
        hull = newHull;
    }
    
    pair<int,int> Ship::getPosition()
    {
        return position;
    }

    void Ship::setDestination(pair<int,int> newDestination)
    {
        destination = newDestination;
    }

    pair<int,int> Ship::getDestination()
    {
        return destination;
    }

    void Ship::setPath(queue<pair<int,int>>* thePath)
    {
	//fullstops ship when setting path
	cout<<"something"<<endl;
	xVelocity=0;
	yVelocity=0;
	rotation=0;
	maxVelocity=10;
	maxRotation=10;
	rotationSet=false;
    	path = thePath;
        pathComplete=false;
    }

    int Ship::getMaxVelocity()
    {
        return maxVelocity;
    }

    int Ship::getCurrHp()
    {
       return currHp;    
    }

    void Ship::setCurrHp(int newCurrHp)
    {
       currHp = newCurrHp;    
    }

    int Ship::getMaxHp()
    {
	   return maxHp;    
    }

    void Ship::setMaxHp(int newMaxHp)
    {
	   maxHp = newMaxHp;    
    }

    pair<int, int> Ship::getSize()
    {
        return size;
    }

    void Ship::setSize(pair<int, int> newSize)
    {
        size = newSize;
    }

    //ai follows path assigned to it by ai class
    void Ship::followPath(Sprite& entity)
    {
	    //note: change the path in Ship.h to whatever is returned.
	    if(!path->empty())
	    {
		//note: assumed whatever we're using is some (x,y)
		pair<int,int> coords=path->front();
		int x_coord=coords.first;
		int y_coord=coords.second;
		int cur_x=position.first;
		int cur_y=position.second;
		//get angle of destination
		if(!rotationSet)
		{
			curRotation= atan2((double)-y_coord,(double)x_coord);
			curRotation=(int)std::floor(curRotation*180/3.14+180);
			rotationSet=true;
		}
		double angle=entity.getAngle();
		cout<<"currotation:"<<curRotation<<endl;
		cout<<"cur angle: "<<angle<<endl;
		bool angleChanged=false;
		if(curRotation>angle)
		{
		    //pretty shit acceleration stuff tbh
		    if(curRotation>angle+maxRotation)
		    {
			if(maxRotation>rotation)
			    entity.setAngle(angle+rotation++);
			else
			    entity.setAngle(angle+rotation);
		    }
		    else
		        entity.setAngle(angle+1);
		    angleChanged=true;
		}
		else if(angle>curRotation)
		{
		    if(angle-maxRotation>curRotation)
		    {
			if(maxRotation>rotation)
			    entity.setAngle(angle-(rotation++));
			else
			    entity.setAngle(angle-rotation);
		    }
		    else
			entity.setAngle(angle-1);
		    angleChanged=true;
		}
		//entity.setAngle(122);
	//cout<<"cur_x: "<<cur_x<<" cur_y : "<<cur_y<<endl;
        std::cout << "x: " << x_coord << " y: " << y_coord << "points remaing: " << path->size() << endl;
		//note: since we don't have updateMovement implemented, most
		//of the stuff here can probably be removed/handled by that
		//simulate turning, acceleration of ship
		if(!angleChanged&&(cur_x != x_coord || cur_y != y_coord))
		{
		    if(cur_x-maxVelocity>x_coord)
		    {
			if(maxVelocity>xVelocity)
			    cur_x-=xVelocity++;
			else
			    cur_x-=xVelocity;
		    }
		    else if(cur_x>x_coord)
			cur_x=x_coord; //skipped
		    else if(cur_x+maxVelocity<x_coord)
		    {
			if(maxVelocity>xVelocity)
			    cur_x+=xVelocity++;
			else
			    cur_x+=xVelocity;
		    }
		    else if(cur_x<x_coord)
			cur_x=x_coord; //skipped
		    if(cur_y-maxVelocity>y_coord)
		    {
			if(maxVelocity>yVelocity)
			    cur_y-=yVelocity++;
			else
			    cur_y-=yVelocity;
		    }
		    else if(cur_y>y_coord)
			cur_y=y_coord; //skipped
		    else if(cur_y+maxVelocity<y_coord)
		    {
			if(maxVelocity>yVelocity)
			    cur_y+=yVelocity++;
			else
			    cur_y+=yVelocity;
		    }
		    else if(cur_y<y_coord)
			cur_y=y_coord; //skipped
		    entity.setX(cur_x);
		    entity.setY(cur_y);
		    position.first=cur_x;
		    position.second=cur_y;
		}
		else if(cur_x==x_coord&&cur_y==y_coord)
		{
		    path->pop();
		    rotationSet=false;
		}
	    }
	    else
	    {
		setSpeedY(0);
		setSpeedX(0);
	        pathComplete=true;
	    }
    }

    bool Ship::getPathComplete()
    {
    	return pathComplete;
    }

	int Ship::getMass()
	{
		return mass;	
	}
