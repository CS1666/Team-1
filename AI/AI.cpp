#include "AI.h"
  
        void AI::setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void AI::setShipPath(Ship shipToPath)
        {
        	//somebody could get rid of this
        	//get start and end points
        	vector<int> start = shipToPath.getPosition();
        	vector<int> destination = shipToPath.getDestination();

        	double distance = calculateDistance(start, destination);

        	double g = 0;

        	//using built in queue c++ data structure for now
        	std::queue <vector<int> > open;

        	open.push({start[0], start[1], static_cast<int>(g + distance)});

        	while (open.size() != 0)
        	{

        		//vector<int> s = open.pop();


        		
        	}

        }

        double AI::calculateDistance(vector<int> start, vector<int> stop)
        {
        	double x = stop[0] - start[0];
        	double y = stop[1] - start[1];

        	double z = sqrt(x*x + y*y);

        	return z;
        }

    	void AI::lineOfSight()
    	{

    	}

    	void createMapState(Sector currentSector)
    	{

    		vector<int> sectorSize = currentSector.getSize();

    		vector<vector<int> > storedMapState (sectorSize[0], std::vector<int>(sectorSize[1], 0));

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
