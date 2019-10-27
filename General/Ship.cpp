
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
		double newAngle= atan((double)-y_coord/(double)x_coord);
		cout<<"new angle: "<<newAngle*180/3.14<<endl;
		double angle=entity.getAngle();
		entity.setAngle(newAngle*180/3.14+180);
	//cout<<"cur_x: "<<cur_x<<" cur_y : "<<cur_y<<endl;
        std::cout << "x: " << x_coord << " y: " << y_coord << "points remaing: " << path->size() << endl;
		//note: since we don't have updateMovement implemented, most
		//of the stuff here can probably be removed/handled by that
		//currently will literally go 1 pixel at a time.
		//also, need to render the ship in this method or something.
		if(cur_x != x_coord || cur_y != y_coord)
		{
		    if(cur_x>x_coord)
			cur_x--;
		    else if(cur_x<x_coord)
			cur_x++;
		    if(cur_y>y_coord)
			cur_y--;
		    else if(cur_y<y_coord)
			cur_y++;
		    entity.setX(cur_x);
		    entity.setY(cur_y);
		    position.first=cur_x;
		    position.second=cur_y;
		}
		else
		    path->pop();
	    }
	    else
	        pathComplete=true;
	    cout<<pathComplete<<endl;
    }

    bool Ship::getPathComplete()
    {
    	return pathComplete;
    }

	int Ship::getMass()
	{
		return mass;	
	}
