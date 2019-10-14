
#include "Ship.h"

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
        void Ship::updatePosition(vector<int> newPos)
        {
            position = newPos;
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
	void Ship::setPosition(vector<int> pos)
	{
	    position=pos;
	}
        vector<int> Ship::getPosition()
        {
            return position;
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
