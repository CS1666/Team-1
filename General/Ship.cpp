
#include "Ship.h"

    Ship::Ship(): Sprite() {};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim): Sprite(dBox, aTex, anim) {};

    Ship::Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass): Sprite(dBox, aTex, anim), mass{mass} {};

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
    void Ship::setPosition(vector<int> newPosition)
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
    
    vector<int> Ship::getPosition()
    {
        return position;
    }

    void Ship::setDestination(vector<int> newDestination)
    {
        destination = newDestination;
    }

    vector<int> Ship::getDestination()
    {
        return destination;
    }

    void Ship::setPath(Queue thePath)
    {
    	path = thePath;
        pathComplete=false;
    }

    int Ship::getMaxVelocity()
    {
        return maxVelocity;
    }

    //ai follows path assigned to it by ai class
    void Ship::followPath()
    {
	    while(!path.isEmpty())
	    {
		  char key=path.pop();
		  //do some stuff...
	    }
	    pathComplete=true;
    }

    bool Ship::getPathComplete()
    {
    	return pathComplete;
    }

	int Ship::getMass()
	{
		return mass;	
	}
