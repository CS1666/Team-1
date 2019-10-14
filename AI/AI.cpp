#include "AI.h"
  
        void AI::setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void AI::setShipPath(Ship shipToPath)
        {

        }
	//true if different, false if same
	bool AI::checkMapState(vector<vector<int>> newState)
	{
	    if(storedMapState==newState)
		return false;
	    storedMapState=newState;
	    return false;
	}
	//calculate the path for a ship and destination
	Queue AI::calculatePath(Ship theShip, vector<int> destination)
	{
	    vector<int> curPos=theShip.getPosition();
	    Queue path=Queue(10);
	    //insert pathfinding algorithm here to get actions 

	    return path;
	}
