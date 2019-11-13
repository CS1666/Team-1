#include "AI.h"



void AI::executeAIActions(){

    for(AIShip* ship : *ships){

        switch(ship->getGoal()){

            case(0)://Action 1: Follow Player
                followPlayer(ship);
                break;
            case(1)://Action 2: Defend position
                Defend(ship);
                break;

            case(2)://Action 3: Attack Enemy
                Attack(ship);
                break;

            
            case(3)://Action 4: Run away from enemy
                Flee(ship);
                break;

            default://If not assigned goal follow player
                followPlayer(ship);
                break;

        }
        
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


void AI::Defend(AIShip* ship){

}

void AI::Attack(AIShip* ship){

}

void AI::Flee(AIShip* ship){

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
