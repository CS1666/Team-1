#include "AI.h"
  
        void AI::setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void AI::setShipPath(Ship *shipToPath)
        {

        }

        /*void AI::updateVertex(vector<int> s, vector<int> neighbor)
        {
            
        }*/

        int AI::calculateDistance(vector<int> start, vector<int> stop)
        {
        	int x = stop[0] - start[0];
        	int y = stop[1] - start[1];

        	int z = sqrt(x*x + y*y);

        	return z;
        }

    	void AI::lineOfSight()
    	{

    	}

    	void AI::createMapState(Sector currentSector)
    	{

    		vector<int> sectorSize = currentSector.getSize();

    		vector<vector<bool> > newStoredMapState (sectorSize[0], std::vector<bool>(sectorSize[1], 0));

            vector<Star> stars = currentSector.getStars();
            
            for (Star star : stars)
            {
                vector<int> starSize = star.getSize();

                vector<int> starPosition = star.getPosition();

                for (int x = starPosition[0]; x < starPosition[0] + starSize[0]; x++)
                {
                    newStoredMapState[x][starPosition[1]] = true;
                    newStoredMapState[x][starPosition[1] - starSize[1]] = true;
                }

                for (int y = starPosition[1]; y < starPosition[0] - starSize[0]; y--)
                {
                    newStoredMapState[starPosition[0]][y] = true;
                    newStoredMapState[starPosition[0] + starSize[0]][y] = true;
                }
            }
            
            AI::storedMapState = newStoredMapState;

    	}

		//true if different, false if same
		bool AI::checkMapState(vector<vector<bool> > newState)
		{
		    /*cout<<"storedmap = "<<endl;
		    for(auto x:storedMapState)
			for(auto y:x)
			    cout<<"y = "<<y<<endl;*/
		    if(storedMapState==newState)
			return false;
		    storedMapState=newState;
		    return true;
		}
		//calculate the path for a ship and destination
		queue<vector<int>> AI::calculatePath(Ship theShip, vector<int> destination)
		{
		    vector<int> curPos=theShip.getPosition();
		    queue<vector<int>> path=queue<vector<int>>();
		    //insert pathfinding algorithm here to get actions 

		    return path;
		}
