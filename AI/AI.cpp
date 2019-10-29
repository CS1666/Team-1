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

        int AI::calculateDistance(pair<int,int> start, pair<int,int> stop)
        {
        	int x = stop.first - start.first;
        	int y = stop.second - start.second;

        	int z = sqrt(x*x + y*y);

        	return z;
        }

    	void AI::lineOfSight()
    	{

    	}

    	bool AI::createMapState(Sector currentSector)
    	{
    		// Buffer in pixels
    		const int buffer = 50;

    		// Gets sector size and sets mesh size to be the size of the sector
    		vector<int> sectorSize = currentSector.getSize();

    		// Gets the positions and sizes of everything within the sector
			vector<vector<int> > currentState = currentSector.getState();

			// Creates a new map state with everything equal to zero
    		vector<vector<bool> > newStoredMapState (sectorSize[0], std::vector<bool>(sectorSize[1], 0));

    		// Puts 1's at the edges of objecys within the sector + the size of the buffer
            for (vector<int> object : currentState)
            {

                for (int x = object[0]; x < object[0] + object[2]; x++)
                {
                	
                    newStoredMapState[x][object[1] - buffer] = 0;

                    newStoredMapState[x][object[1] + object[3] + buffer] = 0;
                }

                for (int y = object[1]; y < object[0] - object[2]; y--)
                {
                    newStoredMapState[object[0] - buffer][y] = 0;
                    newStoredMapState[object[0] + object[2] + buffer][y] = 0;
                }
            }
            
            if(checkMapState(newStoredMapState))
            {
                storedMapState=newStoredMapState;
                return true;
            }
            return false;

    	}

        vector<vector<bool>> AI::getMapState(){
            return storedMapState;
        }

		//true if different, false if same
		bool AI::checkMapState(vector<vector<bool> > newState)
		{
		    if(storedMapState==newState){
                return false;
            }
			     

		    return true;
		}
		//calculate the path for a ship and destination
		queue<pair<int,int>>* AI::calculatePath(Ship theShip, Pathfinder path )
		{
		    pair<int,int> curPos=theShip.getPosition();
		    cout<<curPos.first<<endl;
		    cout<<curPos.second<<endl;
		    queue<pair<int,int>>* pth = path.pathfind(theShip.getPosition(), theShip.getDestination());
		    return pth;
		}
