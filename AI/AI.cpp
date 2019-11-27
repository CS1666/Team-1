#include "AI.h"


void AI::executeAIActions(){

    for(AIShip* ship : *ships){

    	//pair<int, int> radarOut = radar(*ship);
      
        //std::cout << radarOut.first << ", " << radarOut.second << std::endl;

        switch(ship->getGoal()){
            case(0)://Action 1: Follow Player
                cout<<"Following Player"<<endl;
                followPlayer(ship);
                break;
            case(1)://Action 2: Defend position
                cout<<"Defending Positon"<<endl;
                defendPosition(ship);
                break;

            case(2)://Action 3: Attack Enemy
                cout<<"Attack Enemy"<<endl;
                pursueShip(ship);
                break;
            case(3)://Action 4: Run away from enemy
                cout<<"Flee"<<endl;
                fleeToCorner(ship);
                break;
	    case(4): //Action 5: roam around for enemies
		cout<<"Roaming"<<endl;
		roamAround(ship);
		break;
            default://If not assigned goal do nothing
                cout<<"Do nothing"<<endl;
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


void AI::defendPosition(AIShip* ship)
{
    pair<int,int> shipDetected=radar(*ship);
    //cout<<shipDetected.first<<endl;
    //cout<<shipDetected.second<<endl;
    if(shipDetected.first!=-1)
    {
	if(SDL_GetTicks() - ship->getFireLastTime() > 200){
        Projectile* proj= new Projectile(ship->attackShip(shipDetected, allTextures->at(TEX_LASER)));
        //cout<<"Texture "<<proj.getTexture()<<endl;
        if(proj->getTexture()!=nullptr)
            osSprite->push_back(proj);
        }
    }
   //todo: have different radar range?
    if(ship->isFreeForm())
    {
	int distance=calculateDistance(ship->getPosition(),shipDetected);
	//pursue/attack
	if(distance>150&&distance<450)
	{
	    //cout<<"begin pursuit"<<endl;
	    ship->setGoal(2);
	}
	//too low HP
        if(ship->getCurrHp()<ship->getMaxHp()/5)
            ship->setGoal(3);
    }
}
//pathfind until close enough then rotate to attack
void AI::pursueShip(AIShip* ship)
{
    pair<int,int> shipDetected=radar(*ship);
    if(shipDetected.first!=-1)
    {
	if(!ship->isPathSet())
	{
	    ship->setPath(calculatePath(*ship));
	}
	//calculate a destination where it will be close enough
	//kinda simplistic calculations, can probably be in its own function
	ship->setDestination(generateCoordinate(ship->getPosition(),shipDetected,0));
	cout<<ship->getDestination().first<<endl;
	cout<<ship->getDestination().second<<endl;
	ship->followPath();
   	if(ship->getPathComplete())
    	{
	    int distance=calculateDistance(ship->getPosition(),shipDetected);
	    //still too far, continue pursuit
	    if(distance>DISTANCE_PURSUE)
	    {
		ship->setPath(calculatePath(*ship));
		ship->setDestination(generateCoordinate(ship->getPosition(),shipDetected,0));
	    }
	    //rotate and fire
	    else
	    {
            ship->setGoal(1);
	//	Projectile proj=ship->attackShip(shipDetected, allTextures->at(TEX_LASER));
        //	if(proj.getTexture()!=nullptr)
          //  	    osSprite->push_back(&proj);
	    }
    	}
    }
    if(ship->isFreeForm())
    {
	//ship went out of radar
	if(shipDetected.first==-1)
	    ship->setGoal(4);
	//too low HP
	if(ship->getCurrHp()<ship->getMaxHp()/5)
	    ship->setGoal(3);
    }
}
//run to a corner when low on HP
void AI::fleeToCorner(AIShip* ship)
{
    //note: ally ships will also pick where to go based on player ship
    if(!ship->isPathSet()){
        ship->setPath(calculatePath(*ship));
    }
    ship->setDestination(generateCoordinate(ship->getPosition(),getPlayerShip()->getPosition(),1));
    ship->followPath();
    if(ship->getPathComplete())
    {
        ship->setPath(calculatePath(*ship));
        ship->setDestination(generateCoordinate(ship->getPosition(),getPlayerShip()->getPosition(),1));
    }
    //note: don't really want to have a transition out of here...
    //and we currently can't since no way for aiships to regen hp for now
    if(ship->isFreeForm())
    {
	if(ship->getCurrHp()>ship->getMaxHp()/3)
            ship->setGoal(4);
    }
}
//roam around and switch state if find another ship
void AI::roamAround(AIShip* ship)
{
    if(!ship->isPathSet()){
        ship->setPath(calculatePath(*ship));
    }
    ship->setDestination(generateCoordinate(ship->getPosition(),ship->getPosition(),2));
    //wait 2 seconds before go to a new place
    if(SDL_GetTicks()-ship->getTime()>2000)
	ship->followPath();
    if(ship->getPathComplete())
    {
	ship->setTime(SDL_GetTicks());
        ship->setPath(calculatePath(*ship));
        ship->setDestination(generateCoordinate(ship->getPosition(),ship->getPosition(),2));
    }
    if(ship->isFreeForm())
    {   //if detect ship go to attack
	if(radar(*ship).first!=-1)
	    ship->setGoal(2);
    }
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
	{
	    cout<<"alert: ship activated"<<endl;
	    ship->setGoal(1);
	}
    }
}
vector<AIShip*>* AI::getShips()
{
    return ships;
}
void AI::setSprites(vector<Sprite*>* sprites)
{
    osSprite=sprites;
}
void AI::setTextures(vector<SDL_Texture*>* textures)
{
    allTextures=textures;
}

void AI::setShips(vector<AIShip*>* newShips)
{
    ships = newShips;
}
pair<int,int> AI::generateCoordinate(pair<int,int> start, pair<int,int> stop, int typeGen)
{
    pair<int, int> val;
    if(typeGen==0)
    {
	int xDiff=stop.first-start.first;
	int yDiff=stop.second-start.second;
	if(xDiff>0)
	    val.first=stop.first+50;
	else
	    val.first=stop.first-50;
	if(yDiff>0)
            val.second=stop.second+50;
	else
	    val.second=stop.second-50;
    }
    else if(typeGen==1)
    {
	//get the corners
	pair<int,int> topRight;
	topRight.first=0;
	topRight.second=0;
	pair<int,int> topLeft;
	topLeft.first=sectorSize.first;
	topLeft.second=0;
	pair<int,int> botRight;
	botRight.first=0;
	botRight.second=sectorSize.second;
	pair<int,int> botLeft;
	botLeft.first=sectorSize.first;
	botRight.second=sectorSize.second;
	//calc distance of pairs with ship
	int trShip=calculateDistance(start,topRight);
	int tlShip=calculateDistance(start,topLeft);
	int brShip=calculateDistance(start,botRight);
	int blShip=calculateDistance(start,botLeft);
	//calc distance of pairs with hero/player
	int trHero=calculateDistance(stop,topRight);
	int tlHero=calculateDistance(stop,topLeft);
	int brHero=calculateDistance(stop,botRight);
	int blHero=calculateDistance(stop,botLeft);
	//find differences between, get biggest difference
	int trDiff=trHero-trShip;
	int tlDiff=tlHero-tlShip;
	int brDiff=brHero-brShip;
	int blDiff=blHero-blShip;
	//set coordinate to be biggest one
	if(trDiff>=tlDiff && trDiff>=brDiff && trDiff>=blDiff)
	    val=topRight;
	else if(tlDiff>=trDiff && tlDiff>=brDiff && tlDiff>=blDiff)
	    val=topLeft;
	else if(brDiff>=trDiff && brDiff>=tlDiff && brDiff>=blDiff)
	    val=botRight;
	else
	    val=botLeft;
    }
    else if(typeGen==2)
    {
	//determine the max/min ranges for x/y
	int xMax=min(DISTANCE_ROAM_X,sectorSize.first-stop.first);
	int xMin=max(-1*DISTANCE_ROAM_X,0-stop.first);
	int yMax=min(DISTANCE_ROAM_Y,sectorSize.second-stop.second);
	int yMin=max(-1*DISTANCE_ROAM_Y,0-stop.second);
	//rng if add or subtract, set coord to be rand between 0, bound
	if(rand()%2==0)
	    val.first=stop.first+rand()%xMax;
	else
	    val.first=stop.first-rand()%xMin;
	if(rand()%2==0)
	    val.second=stop.second+rand()%yMax;
	else
	    val.second=stop.second-rand()%yMin;
    }
    return val;
}
void AI::setSectorSize(pair<int,int> sector)
{
    sectorSize=sector;
}
pair<int,int> AI::getSectorSize()
{
    return sectorSize;
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

bool AI::createMapState(Sector* currentSector)
{
    // Buffer in pixels
    const int buffer = 50;
    // Gets sector size and sets mesh size to be the size of the sector
    vector<int> sectorSize = currentSector->getSize();
    // Gets the positions and sizes of everything within the sector
    vector<vector<int> > currentState = currentSector->getState();
    std::cout << "8" << std::endl;
      // Creates a new map state with everything equal to zero
    vector<vector<bool> > newStoredMapState (sectorSize[0], std::vector<bool>(sectorSize[1], 0));
    // Puts 1's at the edges of objecys within the sector + the size of the buffer
    std::cout << "9" << std::endl;
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
    std::cout << "10" << std::endl;
    
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


void AI::setCurrentSector(Sector* newSector)
{
	sector = newSector;
}

pair<int, int> AI::radar(AIShip& aiShip)
{
	int radarSize = 450;

	pair<int, int> closestEnemyPosition = make_pair(-1, -1);

	double closestEnemyDistance = -1;

	vector<Ship*> ships = sector->getShips();

	pair<int, int> radarPosition = aiShip.getPosition();


//		std::cout << "Radar ship location "<< radarPosition.first << ", " << radarPosition.second << std::endl;

		//int i = 0;

		for (Ship* ship : ships)
		{

			//i++;

			//std::cout << "Ship "<< i << std::endl;

			pair<int, int> shipCheck = ship->getPosition();

            std::cout << "Check ship location "<< ship->getIsAlly() << ", " << aiShip.getIsAlly() << std::endl;

			if (shipCheck != radarPosition && ship->getIsAlly() != aiShip.getIsAlly())

			{

//				std::cout << "Check ship location "<< shipCheck.first << ", " << shipCheck.second << std::endl;

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

void AI::createShip(bool isAlly){

    //Create New Ally Ship
    if(isAlly){
        if(sector->getNumAlly() < SHIP_SECTOR_LIMIT){
            sector->setNumAlly(sector->getNumAlly() + 1);
            pair<int,int> asp = ChooseAllySpawn();

            if(asp.first != -1 && asp.second != -1){
                SDL_Rect db = {asp.first,asp.second,FIGHTER_WIDTH,FIGHTER_HEIGHT};
                SDL_Texture* tex  = allTextures->at(TEX_FIGHT_ALLY);
                AIShip* newShip = new AIShip(db, tex,true);
                newShip->setPosition(asp);
                newShip->setDestination(playerShip->getPosition());
                newShip->setRenderOrder(0);
                newShip->setF(-1);
                newShip->setGoal(0);
                newShip->setCurrHp(100);
                newShip->setMaxHp(100);
                osSprite->push_back(newShip);
                ships->push_back(newShip);
                sector->addShips(newShip);


            }
            else{
                std::cout << "Cannot spawn Ally" << std::endl;
            }
            
        }
    }
    else{//Create New Enemy Ship

        if(sector->getNumEnemy() < SHIP_SECTOR_LIMIT){
            sector->setNumEnemy(sector->getNumEnemy() + 1);
            pair<int,int> esp = ChooseEnemySpawn();
            if(esp.first != -1 && esp.second != -1){
                
                SDL_Rect db = {esp.first,esp.second,FIGHTER_WIDTH,FIGHTER_HEIGHT};
                SDL_Texture* tex  = allTextures->at(TEX_FIGHT_ENEMY);
    
                AIShip* newShip = new  AIShip(db, tex,false);
                newShip->setPosition(esp);
                newShip->setDestination(playerShip->getPosition());
                newShip->setRenderOrder(0);
                newShip->setF(-1);
                newShip->setGoal(2);
                newShip->setCurrHp(100);
                newShip->setMaxHp(100);
    
                osSprite->push_back(newShip);
                ships->push_back(newShip);
                std::cout << "Spawned Enemy" << std::endl;

            }

            else{
                std::cout << "Cannot spawn Enemy" << std::endl;
            }
            
        }

    }


}



pair<int,int> AI::ChooseEnemySpawn(){
    int decidedspawn = 3; //note: function will determine which spawn to choose

    vector<pair<int,int>> es = sector->getEnemySpawn(decidedspawn);

    for(pair<int,int> spawn : es){

        if(!occupied(spawn)){
            return spawn;
        }
    }



    return pair<int,int>(-1,-1);

}

pair<int,int> AI::ChooseAllySpawn(){
    //std::cout << "1" << std::endl;
    vector<pair<int,int>> as = sector->getAllySpawn();
    //std::cout << "2" << std::endl;
    for(pair<int,int> spawn : as){
        //std::cout << "3" << std::endl;
        if(!occupied(spawn)){
            return spawn;
        }
    }
    //std::cout << "4" << std::endl;
    return pair<int,int>(-1,-1);
}


bool AI::occupied(pair<int,int> spawn){

    for(Sprite* s: *osSprite){
        int spx = s->getX();
        int spy = s->getY();
        int spw = s->getW();
        int sph = s->getH();
        bool lbc = (spx >= spawn.first && spx <=  spawn.first + 50);
        bool rbc = ((spx + spw)  >= spawn.first && (spx + spw)  <=  spawn.first + 50);
        bool tbc = (spy >= spawn.second && spy <=  spawn.second + 50);
        bool bbc = ((spy + sph)  >= spawn.second && (spy + sph)  <=  spawn.second + 50);

        if((lbc || rbc) && (tbc || bbc)){
            return true;
        }
    }


    return false;
}


