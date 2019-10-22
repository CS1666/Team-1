
#include "Ship.h"
#include <SDL.h> //temp
    Ship::Ship(): Sprite() {};

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

    void Ship::setPath(queue<vector<int>> thePath)
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
	    //note: change the path in Ship.h to whatever is returned.
	    while(!path.empty())
	    {
		//note: assumed whatever we're using is some (x,y)
		vector<int> coords=path.front();
		path.pop();
		int x_coord=coords[0];
		int y_coord=coords[1];
		int cur_x=position[0];
		int cur_y=position[1];
		//note: since we don't have updateMovement implemented, most
		//of the stuff here can probably be removed/handled by that
		//currently will literally go 1 pixel at a time.
		//also, need to render the ship in this method or something.
		while(cur_x != x_coord && cur_y != y_coord)
		{
		    if(cur_x>x_coord)
			cur_x--;
		    else
			cur_x++;
		    
		}
		while(cur_y != y_coord)
		{
		    if(cur_y>y_coord)
			cur_y--;
		    else
			cur_y++;
		}
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
