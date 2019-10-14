#include "AI.h"
  
        void AI::setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void AI::setShipPath(Ship shipToPath)
        {
        	//get start and end points
        	vector<int> start = shipToPath.getPosition();
        	vector<int> destination = shipToPath.getDestination();

        	//using built in queue c++ data structure for now
        	std::queue<vector<int> > open;

        	open.push(start);

        	while (open.size() != 0)
        	{
        		vector<int> s = open.pop();

        		if (s == destination)
        		{
        			return;
        		}

        		
        	}

        }

    	void AI::lineOfSight()
    	{

    	}

        bool checkMapState(vector<vector<int> > newState)
        {

        	return false;

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
