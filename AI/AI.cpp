#include "AI.h"


void AI::executeAIActions(){

    for(AIShip* ship : *ships){

        switch(ship->getGoal()){
            case(0)://Action 1: Follow Player
                ship->setTargetShip(getPlayerShip());
                followPlayer(ship);
                break;
            case(1)://Action 2: Defend position
                cout<<"Defending Positon"<<endl;
                if(!ship->getHasTarget()){
                    findShip(ship, 1);
                }
                else{
                    defendPosition(ship);
                }
                break;

            case(2)://Action 3: Attack Enemy
                cout<<"Attack Enemy"<<endl;
                if(!ship->getHasTarget()){
                    findShip(ship, 2);
                }
                else{
                    pursueShip(ship);
                }
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
void AI::followShip(AIShip* ship){
    if(!ship->isPathSet()){
        ship->setPath(calculatePath(*ship));
    }
    
    ship->setDestination(ship->getTargetShipPos());
    bool recalc = ship->followPath(osSprite);

    if(recalc){
        cout<<"Re Calc"<<endl;
        ship->setPath(calculatePath(*ship));
    }
    else if(ship->getPathComplete())
    {
        
        cout<<"Path Complete"<<endl;
        ship->setDestination(ship->getTargetShip()->getPosition());
        ship->setPath(calculatePath(*ship));
    }
}

void AI::followPlayer(AIShip* ship){

    int distance = calculateDistance(ship->getPosition(), ship->getTargetShipPos());
    //cout<<distance<<endl;
    if(distance > 150){
        followShip(ship);
    }
     
}

void AI::followEnemy(AIShip* ship){
    int distance = calculateDistance(ship->getPosition(), ship->getTargetShipPos());
    if(distance > DISTANCE_PURSUE){
        followShip(ship);
    }
    else if(ship->isFreeForm()){
        ship->setGoal(1);
    }

}

void AI::defendPosition(AIShip* ship)
{   
    
    if(SDL_GetTicks() - ship->getFireLastTime() > 200){
        ship->attackShip(ship->getTargetShipPos());
    }
    
    
    if(ship->isFreeForm())
    {
        	int distance=calculateDistance(ship->getPosition(),ship->getTargetShipPos());
        	//pursue/attack
        	if(distance>150&&distance<450)
        	{
        	    ship->setGoal(2);
        	}
            else if(distance>150) {
                ship->setHasTarget(false);
            }
        	//too low HP
            if(ship->getCurrHp()<ship->getMaxHp()/5){
                ship->setHasTarget(false);
                ship->setGoal(3);
            }
                
    }
}

//pathfind until close enough then rotate to attack
void AI::pursueShip(AIShip* ship)
{   
    
    followEnemy(ship);
    if(SDL_GetTicks() - ship->getFireLastTime() > 200){
        ship->attackShip(ship->getTargetShipPos());
    }
    
    if(ship->isFreeForm())
    {
    	//too low HP
    	if(ship->getCurrHp()<ship->getMaxHp()/5){
            ship->setHasTarget(false);
            ship->setGoal(3);
        }
            
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
	ship->followPath(osSprite);
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

int AI::calculateDistance(pair<int,int> start, pair<int,int> stop)
{
    int x = stop.first - start.first;
    int y = stop.second - start.second;

    int z = sqrt(x*x + y*y);

    return z;
}


//calculate the path for a ship and destination
queue<pair<int,int>>* AI::calculatePath(AIShip& theShip)
{
    pair<int,int> curPos=theShip.getPosition();
    pair<int,int> curDest=theShip.getDestination();

    queue<pair<int,int>>* pth = pathfinder->pathfind(curPos,curDest, &theShip);
  
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


void AI::findShip(AIShip* ship, int routine){
    radar(*ship);

   if(ship->getHasTarget()){
        if(routine == 1)
            defendPosition(ship);

        if(routine == 2)
            pursueShip(ship);
   }

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

			pair<int, int> shipSize = ship->getSize();

            std::cout << "Check ship location "<< ship->getIsAlly() << ", " << aiShip.getIsAlly() << std::endl;

			if (shipCheck != radarPosition && ship->getIsAlly() != aiShip.getIsAlly())
			{

				shipCheck.first = shipCheck.first + shipSize.first/2;

				shipCheck.second = shipCheck.second + shipSize.second/2;



				double z = sqrt(pow(radarPosition.first - shipCheck.first, 2.0) + pow(radarPosition.second - shipCheck.second, 2.0));


				if (z < radarSize && closestEnemyPosition.first != -1 &&  closestEnemyPosition.second != -1 && closestEnemyDistance > z)
				{   
                    aiShip.setTargetShip(ship);
                    aiShip.setHasTarget(true);
					closestEnemyPosition = shipCheck;
					closestEnemyDistance = z;
				}
				else if (z < radarSize && closestEnemyPosition.first == -1 &&  closestEnemyPosition.second == -1)
				{   
                    aiShip.setTargetShip(ship);
                    aiShip.setHasTarget(true);
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

void AI::createShip(bool isAlly,int goal){

    //Create New Ally Ship
    if(isAlly){
        if(sector->getNumAlly() < SHIP_SECTOR_LIMIT){
            sector->setNumAlly(sector->getNumAlly() + 1);
            pair<int,int> asp = ChooseAllySpawn();

            if(asp.first != -1 && asp.second != -1){
                SDL_Rect db = {asp.first,asp.second,FIGHTER_WIDTH,FIGHTER_HEIGHT};
                SDL_Texture* tex  = allTextures->at(TEX_SHIPS);
                AIShip* newShip = new AIShip(db, tex,true);
                newShip->setPosition(asp);
                newShip->setDestination(playerShip->getPosition());
                newShip->setRenderOrder(0);
                newShip->setF2(2);
                newShip->setGoal(goal);
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
                SDL_Texture* tex  = allTextures->at(TEX_SHIPS);
    
                AIShip* newShip = new  AIShip(db, tex,false);
                newShip->setPosition(esp);
                newShip->setDestination(playerShip->getPosition());
                newShip->setRenderOrder(0);
                newShip->setF2(1);
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


