#include "AI.h"
  
        void AI::setShips(vector<Ship> newShips)
        {
            __ships = newShips;
        }

        void AI::setShipPath(Ship *shipToPath)
        {
        	//somebody could get rid of this
        	//get start and end points
        	vector<int> start = shipToPath->getPosition();
        	vector<int> destination = shipToPath->getDestination();

        	int distance = calculateDistance(start, destination);

        	int g = 0;

        	//using built in queue c++ data structure for now
        	priority_queue <vector<int> > open;
            priority_queue <vector<int> > closed;
            set <vector<int> > check_closed;
            set <vector<int> > check_open;

        	open.push({start[0], start[1], g + distance});
            check_open.insert({start[0], start[1]});

        	while (open.size() != 0)
        	{

        		vector<int> s = open.pop();

                if (s == destination)
                {
                    return;
                }

                closed.push(s);
                check_closed.insert({s[0], s[1]});

                for (int i = -1; i <= 1; i = i + 2)
                {
                    for (int j = -1; j <= 1; j = j + 2)
                    {
                        if (s[0] + i >=0 && s[1] + j >=0 && s[0] + i < storedMapState.size() && s[0] + j < storedMapState[0].size())
                        {
                            if (check_closed.find() == check_closed.end())
                            {
                                int gScore = 0;
                                if (check_closed.find() == check_closed.end())
                                {
                                    gscore = 2147483627;
                                }
                                
                                vector<int> neigbor = {s[0]+i, s[1]+j};
                                updateVertex(s, neighbor);
                            }
                        }
                    }
                }


        		
        	}

        }

        void AI::updateVertex(vector<int> s, vector<int> neighbor)
        {
            
        }

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

    		vector<vector<int> > newStoredMapState (sectorSize[0], std::vector<int>(sectorSize[1], 0));

            vector<Star> stars = currentSector.getStars();
            
            for (Star star : stars)
            {
                vector<int> starSize = star.getSize();

                vector<int> starPosition = star.getPosition();

                for (int x = starPosition[0]; x < starPosition[0] + starSize[0]; x++)
                {
                    newStoredMapState[x][starPosition[1]] = 1;
                    newStoredMapState[x][starPosition[1] - starSize[1]] = 1;
                }

                for (int y = starPosition[1]; y < starPosition[0] - starSize[0]; y--)
                {
                    newStoredMapState[starPosition[0]][y] = 1;
                    newStoredMapState[starPosition[0] + starSize[0]][y] = 1;
                }
            }
            
            AI::storedMapState = newStoredMapState;

    	}

		//true if different, false if same
		bool AI::checkMapState(vector<vector<int> > newState)
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
