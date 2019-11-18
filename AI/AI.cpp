#include "AI.h"


void AI::executeAIActions(){

    for(AIShip* ship : *ships){

    	//pair<int, int> radarOut = radar(*ship);
      
        //std::cout << radarOut.first << ", " << radarOut.second << std::endl;

        switch(ship->getGoal()){
            case(0)://Action 1: Follow Player
                followPlayer(ship);
                break;
            case(1)://Action 2: Defend position
                defendPosition(ship);
                break;

            case(2)://Action 3: Attack Enemy
                Attack(ship);
                break;
            case(3)://Action 4: Run away from enemy
                Flee(ship);
                break;
            default://If not assigned goal do nothing
                doNothing(ship);
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
    if(ship->isFreeForm())
    {
	//idk if ships should be able to autonomously leave/enter follow
    }
}


void AI::defendPosition(AIShip* ship){
    pair<int,int> shipDetected=radar(*ship);
   	cout<<shipDetected.first<<endl;
    cout<<shipDetected.second<<endl;
    if(shipDetected.first!=-1)
    {
	Projectile proj=ship->attackShip(shipDetected, allTextures.at(TEX_LASER));
	if(proj.getTexture()!=nullptr)
	    osSprite.push_back(&proj);
    }
   //todo: have different radar range?
    if(ship->isFreeForm())
    {
	//stuff to switch states
    }
}

void AI::Attack(AIShip* ship){

}

void AI::Flee(AIShip* ship){

}

//if something on radar switch goal, else do nothing
void AI::doNothing(AIShip* ship)
{
    if(radar(*ship).first!=-1)
    {
	if(ship->getTime()==0)
	    ship->setTime(SDL_GetTicks());
	//1 second between spotting and activation
	//note that if player ship leaves radius it'll 
	//swap goals upon coming back in range
	else if(SDL_GetTicks()-ship->getTime()>1000)
	    ship->setGoal(1);
    }
}
void AI::setSprites(vector<Sprite*>& sprites)
{
    osSprite=sprites;
}
void AI::setTextures(vector<SDL_Texture*>& textures)
{
    allTextures=textures;
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

bool AI::createShipState(Sector currentSector)
{
    // Buffer in pixels
    const int buffer = 50;

    // Gets sector size and sets mesh size to be the size of the sector
    vector<int> sectorSize = currentSector.getSize();

    // Gets the positions and sizes of everything within the sector
    vector<vector<int> > currentState = currentSector.getShipState();

      // Creates a new map state with everything equal to zero
    vector<vector<bool> > newStoredShipState (sectorSize[0], std::vector<bool>(sectorSize[1], 0));

    // Puts 1's at the edges of objecys within the sector + the size of the buffer
    for (vector<int> object : currentState)
    {

        for (int x = object[0] - buffer; x < object[0] + object[2] + buffer; x++)
        {
            for (int y = object[1] - buffer; y < object[1] + object[3] + buffer; y++)
            {
                if (x >= 0 && x < newStoredShipState.size() && y >=0 && y < newStoredShipState[0].size())
                {
                    newStoredShipState[x][y] = 1;
                }

            }
        }
    }
    
    if(checkMapState(newStoredShipState))
    {
        storedShipState=newStoredShipState;
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


void AI::setCurrentSector(Sector newSector)
{
	sector = newSector;
}

pair<int, int> AI::radar(AIShip aiShip)
{
	int radarSize = 200;

	pair<int, int> closestEnemyPosition = make_pair(-1, -1);

	double closestEnemyDistance = -1;

	vector<Ship*> ships = sector.getShips();

	pair<int, int> radarPosition = aiShip.getPosition();


		//std::cout << "Radar ship location "<< radarPosition.first << ", " << radarPosition.second << std::endl;

		//int i = 0;

		for (Ship* ship : ships)
		{

			//i++;

			//std::cout << "Ship "<< i << std::endl;

			pair<int, int> shipCheck = ship->getPosition();

			if (shipCheck != radarPosition)
			{

				//std::cout << "Check ship location "<< shipCheck.first << ", " << shipCheck.second << std::endl;

				double z = sqrt(pow(radarPosition.first - shipCheck.first, 2.0) + pow(radarPosition.second - shipCheck.second, 2.0));

				///std::cout << "Distance "<< z << std::endl;

				if (z < radarSize && closestEnemyPosition.first != -1 &&  closestEnemyPosition.second != -1 && closestEnemyDistance > z)
				{
					closestEnemyPosition = shipCheck;
					closestEnemyDistance = z;
				}
				else if (z < radarSize && closestEnemyPosition.first == -1 &&  closestEnemyPosition.second == -1)
				{
					closestEnemyPosition = shipCheck;
					closestEnemyDistance = z;
				}

			}	

		}

		return closestEnemyPosition;

	}


bool AI::checkBounds(int x, int y)
{
	if (x >= 0 && x < storedMapState.size() && y >= 0 && y < storedMapState[0].size())
	{
		return true;
	}

	return false;
}
