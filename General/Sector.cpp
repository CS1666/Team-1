
#include "Sector.h"

using namespace std;

Sector::Sector(){
	__SectEnts = new vector<Sprite *>();
	pf = new Pathfinder(__SectEnts, 10);
}

void Sector::init(gpRender *g, int winWidth, int winHeight)
{

	//srand(time(NULL));

	star_rect.x = winWidth / 2;
	star_rect.y = winHeight/2;
	int starChoice = rand() % 4;
	switch(starChoice)
	{
		case 0: //red giant
			star_rect.w = 315;
			star_rect.h = 332;
			star_tex = g->loadImage("Assets/Objects/red_giant.png");
			star = new Star(star_rect, star_tex, {star_rect});
			star->setPosition({star_rect.x, star_rect.y});			
			bodySprites.push_back(star);
			__SectEnts->push_back(star);
			break;

		case 1: //white dwarf
			star_rect.w = 250;
			star_rect.h = 250;
			star_tex = g->loadImage("Assets/Objects/white_dwarf.png");
			star = new Star(star_rect, star_tex, {star_rect});
			star->setPosition({star_rect.x, star_rect.y});			
			bodySprites.push_back(star);
			__SectEnts->push_back(star);
			break;

		case 2:	//yellow dwarf
			star_rect.w = 300;
			star_rect.h = 300;
			star_tex = g->loadImage("Assets/Objects/yellow_dwarf.png");
			star = new Star(star_rect, star_tex, {star_rect});
			star->setPosition({star_rect.x, star_rect.y});			
			bodySprites.push_back(star);
			__SectEnts->push_back(star);
			break;

		case 3: //blue giant
			star_rect.w = 315;
			star_rect.h = 332;
			star_tex = g->loadImage("Assets/Objects/blue_giant.png");
			star = new Star(star_rect, star_tex, {star_rect});
			star->setPosition({star_rect.x, star_rect.y});			
			bodySprites.push_back(star);
			__SectEnts->push_back(star);
			break;
	}

	
	int lastBody = star_rect.x + star_rect.h/2;
	int dist = star_rect.x + star_rect.h/2;
	int stagger;
	//SDL_Texture* evalPlanet;
	

	//std::cout << "star x: " << star_rect.x << " star y: " << star_rect.y << endl;
	

	while(dist < winWidth)
	{
		dist = (rand() % 300) + lastBody + 200;

		stagger = (rand() % 200) - 100;
		
		
		
		if((dist + 200) > winHeight)
		{
			break;
		}

	
		int planetChoice = rand() % 3;
		
		switch(planetChoice)
		{
			case 0: //far
				planet_tex.push_back(g->loadImage("Assets/Objects/planetfar.png"));
				
				break;
			
			case 1: //near
				planet_tex.push_back(g->loadImage("Assets/Objects/planetnear.png"));
				break;

			case 2: //mid
				planet_tex.push_back(g->loadImage("Assets/Objects/planetmid.png"));
				break;
		}

		planet_rect.push_back({dist, winWidth/2 + stagger, 200, 200});
		addPlanet(new Planet(planet_rect.back(), planet_tex.back(), {planet_rect.back()}, *star));
		std::cout << "Created planet" << std::endl;
		bodySprites.push_back(__planets.back());
		

		lastBody = dist + 250;

	}


}


vector<Sprite *> Sector::getBodySprites()
{
	return bodySprites;
}

Star* Sector::getStar()
{
	return star;
}

vector<Sprite *>* Sector::getSectEnts(){

	return __SectEnts;
}

void Sector::setPlanets(vector<Planet *> newPlanets)
{
	__planets = newPlanets;
}

vector<Planet *> Sector::getPlanets()
{
	return __planets;
}
void Sector::setCurEnemy(int num)
{
    curEnemy=num;
}
int Sector::getCurEnemy()
{
    return curEnemy;
}
void Sector::addPlanet(Planet* newPlanet)
{
	__planets.push_back(newPlanet);
	__SectEnts->push_back(newPlanet);
}

void Sector::setAsteroids(vector<Asteroid *> newAsteroids)
{
	__asteroids = newAsteroids;
}

vector<Asteroid *> Sector::getAsteroids()
{
	return __asteroids;
}

void Sector::addAsteroid(Asteroid* newAsteroid)
{
	__asteroids.push_back(newAsteroid);
	__SectEnts->push_back(newAsteroid);
}

void Sector::setBlackHoles(vector<BlackHole *> newBlackHoles)
{
	__blackholes = newBlackHoles;
}

vector<BlackHole *> Sector::getBlackHoles()
{
	return __blackholes;
}

void Sector::addBlackHole(BlackHole* newBlackHole)
{
	__blackholes.push_back(newBlackHole);
}


vector<Ship *> Sector::getShips()
{
	return __ships;
}

void Sector::setShips(vector<Ship *> newShips)
{
	__ships = newShips;
}

void Sector::addShips(Ship* newShip){
	__ships.push_back(newShip);
	__SectEnts->push_back(newShip);
}

void Sector::setSize(vector<int> newSize)
{
	__size = newSize;
}

vector<int> Sector::getSize()
{
	return __size;
}


vector<vector<int> > Sector::getState()
{
	std::cout << "11" << std::endl;
	std::vector<std::vector<int> > currentState;
	if (!__stars.empty())
	{
		for (Star* star : __stars)
		{
			
			vector<int> size = star->getSize();
			vector<int> position = star->getPosition();
			currentState.push_back({position[0], position[1], size[0], size[1]});
		}
	}
	
	if (!__ships.empty())
	{
		for (Ship *ship : __ships)
		{
			pair<int, int> size = ship->getSize();
			pair<int, int> position = ship->getPosition();
			currentState.push_back({position.first, position.second, size.first, size.second});

		}
	}


	if (!__planets.empty())
	{
		for (Planet *planet : __planets)
		{
			pair<int, int> size = pair<int,int>(planet->getW(), planet->getH());
			pair<int, int> position = pair<int,int>(planet->getX(), planet->getY());
			currentState.push_back({position.first, position.second, size.first, size.second});

		}
	}

	if (!__asteroids.empty())
	{
		for (Asteroid *asteroid : __asteroids)
		{
			pair<int, int> size = pair<int,int>(asteroid->getW(), asteroid->getH());
			pair<int, int> position = pair<int,int>(asteroid->getX(), asteroid->getY());
			currentState.push_back({position.first, position.second, size.first, size.second});

		}
	}

	//caused seg fault at this point
	currentState.push_back({ss->getX(), ss->getY(), ss->getW(), ss->getH()});
	return currentState;
}

int  Sector::getNumAlly(){
	return num_ally;
}
int  Sector::getNumEnemy(){
	return num_enemy;
}
void Sector::setNumAlly(int numa){
	num_ally = numa;
}
void Sector::setNumEnemy(int nume){
	num_enemy = nume;
}

void Sector::setSpaceStation(SpaceStation* nss){
	ss = nss;
	__SectEnts->push_back(ss);
}

SpaceStation* Sector::getSpaceStation(){
	return ss;
}

vector<pair<int,int>> Sector::getEnemySpawn(int spawnloc){

	switch(spawnloc){

		//top
		case 0:

			return {pair<int,int>((3840/2) - 25 , 50), pair<int,int>((3840/2) + 50 , 50), pair<int,int>((3840/2) - 100 , 50)};

		//left
		case 1:

			return {pair<int,int>(3840 - 50 , (2160/2) - 25), pair<int,int>(3840 - 50 , (2160/2) + 50), pair<int,int>(3840 - 50 , (2160/2) - 100)};

		//bottom
		case 2:

			return {pair<int,int>((3840/2) - 25 , 2160 - 50), pair<int,int>((3840/2) + 50 , 2160 - 50), pair<int,int>((3840/2) - 100, 2160 - 50)};

		//right
		case 3:

			return {pair<int,int>(50 , (2160/2) - 25), pair<int,int>(50 , (2160/2)+ 50), pair<int,int>(50, (2160/2) - 100)};

	}




}


vector<pair<int,int>> Sector::getAllySpawn(){
	//std::cout << "1" << std::endl;
	vector<int> sspos = ss->getPosition();
	//std::cout << "2" <<  std::endl;
	std::cout << sspos[0] <<  std::endl;
	std::cout << sspos[1] <<  std::endl;

	//                            left                               top                                     right										bottom
	return {pair<int,int>(sspos[0] - 100, sspos[1]), pair<int,int>(sspos[0], sspos[1] - 100),  pair<int,int>(sspos[0] + 100, sspos[1]), pair<int,int>(sspos[0],  sspos[1] + 100) };
}

Pathfinder* Sector::getPathfinder(){
	return pf;
}

void Sector::clearDeadEnts(){
	for(int i = 0; i < __SectEnts->size();){
		//std::cout << "Clearing Dead ent" << std::endl;
		if(__SectEnts->at(i)->getIsAI()){
			if(((dynamic_cast<AIShip*>(__SectEnts->at(i)))->getCurrHp()) <= 0){
                
                __SectEnts->erase(__SectEnts->begin() + i);
       		}
        	else{
           		i++;
    		}
		}
		else{
			i++;
		}
        
	}

	for(int i = 0; i < __ships.size();){

		if(__ships.at(i)->getIsAI()){
			if((dynamic_cast<AIShip*>(__ships.at(i)))->getCurrHp() <= 0){
                
                __ships.erase(__ships.begin() + i);
       		}
        	else{
           		i++;
    		}
		}
		else{
           		i++;
    	}
        
	}
}