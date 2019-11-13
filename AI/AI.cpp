#include "AI.h"


        
        void AI::executeAIActions(){

            for(AIShip* ship : *ships){
            	radar(*ship);
                followPlayer(ship);
            }

        }

        void AI::followPlayer(AIShip* ship){

            if(!ship->isPathSet()){
                ship->setPath(calculatePath(*ship));
            }
            
            ship->setDestination(getPlayerShip()->getPosition());
            ship->followPath();
            if(ship->getPathComplete())
            {
                ship->setPath(calculatePath(*ship));
                ship->setDestination(getPlayerShip()->getPosition());
            }
        }
        void AI::setShips(vector<AIShip*>* newShips)
        {
            ships = newShips;
        }

        void AI::setShipPath(AIShip *shipToPath)
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

                for (int x = object[0] - buffer; x < object[0] + object[2] + buffer; x++)
                {
                    for (int y = object[1] - buffer; y < object[1] + object[3] + buffer; y++)
                    {
                        if (x >= 0 && x < newStoredMapState.size() && y >=0 && y < newStoredMapState[0].size())
                        {
                            newStoredMapState[x][y] = 1;
                        }

                    }
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
           if(storedMapState.empty()){
                return true;
           }

           for(int x = 0; x < newState.size(); x++){
                for(int y = 0; y <newState[x].size(); y++){
                    if(newState[x][y] != storedMapState[x][y]){
                        return true;
                    }
                }
            }               
                    
         return false;
		}
        //calculate the path for a ship and destination
        queue<pair<int,int>>* AI::calculatePath(AIShip& theShip)
        {
            pair<int,int> curPos=theShip.getPosition();
            pair<int,int> curDest=theShip.getDestination();
            //cout<<curPos.first<<endl;
            //cout<<curPos.second<<endl;
            queue<pair<int,int>>* pth = pathfinder->pathfind(curPos,curDest);
            return pth;
        }


        Hero* AI::getPlayerShip(){
            return playerShip;
        }

        void AI::setPlayerShip(Hero* nplayerShip){
            playerShip = nplayerShip;
        }
        void AI::setPathfinder(Pathfinder* npf){
            pathfinder = npf;
        }

void AI::orderShip(AIShip theShip, Ship player)
{
    if(theShip.getGoal()==0)//follow player
    {
    theShip.setDestination(player.getPosition());
    //do pathfinding here? idk
    }
}

	pair<int, int> AI::radar(AIShip aiship)
	{
		const double pi = 3.14152965358979323846;
		pair<int, int> enemyPositions;
		pair<int, int> shipPosition = aiship.getPosition();
		pair<int, int> shipSize = aiship.getSize();

		int radarSize =  100;

		std::cout << "radar" <<std::endl;

		for (double theta = 0; theta < 2.0*pi; theta += 1.0/16.0 * pi)
		{
			double m = tan(theta);

			double b = shipPosition.second / (m*shipPosition.first);

			std::cout << radarSize << std::endl;

			if (theta >= 0 && theta < 1.0/2.0*pi)
			{
				double z = 0;

				std::cout << "1" << std::endl;

				for (int x = shipPosition.first; z < radarSize; x++)
				{
					std::cout << "2" << std::endl;
					double y = m * x + b;
					std::cout << "3" << std::endl;
					z = sqrt(pow((shipPosition.first - x), 2.0) + pow((shipPosition.second - y), 2.0));
					std::cout << "4" << std::endl;
					std::cout << z<<std::endl;
					if (checkBounds(int(x), int(y)) && storedMapState[int(x)][int(y)] == 1)
					{
						//enemyPositions.push_back(make_pair(theta, z));
					}
				}

			}
			else if (theta > 1.0/2.0*pi && theta <= 1.0*pi)
			{
				double z = 0;

				for (int x = shipPosition.first; z < radarSize; x--)
				{
					double y = m * x + b;
					z = (pow(shipPosition.first - x, 2.0) + pow(shipPosition.second - y, 2.0));

					if (checkBounds(int(x), int(y)) && storedMapState[int(x)][int(y)] == 1)
					{
						//enemyPositions.push_back(make_pair(theta, z));
					}
				}

			}
			else if (theta > 1.0 && theta < 3.0/2.0*pi)
			{
				double z = 0;

				for (int x = shipPosition.first; z < radarSize; x--)
				{
					double y = m * x + b;
					z = (pow(shipPosition.first - x, 2.0) + pow(shipPosition.second - y, 2.0));

					if (checkBounds(int(x), int(y)) && storedMapState[int(x)][int(y)] == 1)
					{
						//enemyPositions.push_back(make_pair(theta, z));
					}
				}
			}
			else if (theta > 3/2*pi && theta < 2*pi)
			{
				double z = 0;

				for (int x = shipPosition.first; z < radarSize; x++)
				{
					double y = m * x + b;
					z = (pow(shipPosition.first - x, 2.0) + pow(shipPosition.second - y, 2.0));

					if (checkBounds(int(x), int(y)) && storedMapState[int(x)][int(y)] == 1)
					{
						//enemyPositions.push_back(make_pair(theta, z));
					}
				}
			}

		}

		return enemyPositions;

	}

	bool AI::checkBounds(int x, int y)
	{
		if (x >= 0 && x < storedMapState.size() && y >= 0 && y < storedMapState[0].size())
		{
			return true;
		}

		return false;
	}