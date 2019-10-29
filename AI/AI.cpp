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
    		vector<int> sectorSize = currentSector.getSize();

			vector<vector<int> > currentState = currentSector.getState();

    		vector<vector<bool> > newStoredMapState (sectorSize[0], std::vector<bool>(sectorSize[1], 0));

            for (vector<int> object : currentState)
            {

                for (int x = object[0]; x < object[0] + object[2]; x++)
                {

                    for (int y = object[1]; y < object[1] + object[3]; y++)
                        {
                            newStoredMapState[x][y] = 1;
                        }
                }

            }
            
            if(checkMapState(newStoredMapState))
            {
                std::cout << "New Map State" << std::endl;
                storedMapState=newStoredMapState;
                return true;
            }

            //std::cout << "Same Map State" << std::endl;
            return false;

    	}

        vector<vector<bool>> AI::getMapState(){
            return storedMapState;
        }

		//true if different, false if same
		bool AI::checkMapState(vector<vector<bool> > newState)
		{
            if(storedMapState.empty()){
                return true;
            }
            for(int x = 0; x < newState.size(); x++){
                for(int y = 0; y <newState[x].size(); y++){
                    //std::cout << "x: " << x << " y: " << y << std::endl;
                    if(newState[x][y] != storedMapState[x][y]){
                        return true;
                    }
                }
            }
		 

		    return false;
		}
		//calculate the path for a ship and destination
		queue<pair<int,int>>* AI::calculatePath(Ship theShip, Pathfinder path )
		{
		    pair<int,int> curPos=theShip.getPosition();
		    //cout<<curPos.first<<endl;
		    //cout<<curPos.second<<endl;
		    queue<pair<int,int>>* pth = path.pathfind(theShip.getPosition(), theShip.getDestination());
		    return pth;
		}
