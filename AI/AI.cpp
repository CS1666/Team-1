#include "AI.h"
typedef std::pair<int,int> Point;
typedef std::queue<Point>* Path;



AI::AI(vector<AIShip*>* ship, Sector nsect) : ships{ship}, sect{nsect} {

    createMapState(nsect);
    pathfinder = new Pathfinder(getMapState(), 10);

};

void AI::updatePlayerState(Hero* nplayerShip){
    playerShip = nplayerShip;
}

void AI::handleShipsActions(){
    followPlayer(ships->at(0));
    followPlayer(ships->at(1));
    //checkMapState()
    
}

void AI::followPlayer(AIShip* ship){
    //std::cout << "Following Player" << std::endl;
    if(ship->hasPath()){
        //std::cout << "Following Path" << std::endl;
        ship->followPath();
    }
    else{
        //std::cout << "Generating Path" << std::endl;
        setShipPath(ship, calculatePath(ship));
        ship->followPath();
    }
    //std::cout << "Completed path?" << std::endl;
    if(ship->getPathComplete())
    {
        //std::cout << "Completed Path" << std::endl;
        ship->setDestination(playerShip->getPosition());
        setShipPath(ship, calculatePath(ship));
    }

}
void AI::setShips(vector<AIShip*>* newShips)
{
    ships = newShips;
}

void AI::setShipPath(AIShip *shipToPath, Path path)
{
    shipToPath->setPath(path);
}

void AI::setPathfinder(Pathfinder* npf){
    pathfinder = npf;
}
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

vector<vector<bool>>* AI::getMapState(){
    return &storedMapState;
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
Path AI::calculatePath(AIShip* theShip)
{
     //std::cout << "Calculate Path" << std::endl;
	return pathfinder->pathfind(theShip->getPosition(), theShip->getDestination());
}

void AI::orderShip(AIShip theShip, Ship player)
{
    if(theShip.getGoal()==0)//follow player
    {
       theShip.setDestination(player.getPosition());
       //do pathfinding here? idk
    }
}
