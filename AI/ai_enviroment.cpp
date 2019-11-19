#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "ai_enviroment.h"
#include "AI.h"
#include "../General/Ship.h"
#include "../General/Sector.h"
#include "AIShip.h"
#include "theta.h"
#include "../Physics/TimeData.h"
#include "../General/Constants.h"
using namespace std;

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;



vector<Sprite*> initilizeSprites(){

}
void run_ai_enviro(gpRender gr){


	//Vector used to store all on screen entities
	vector<SDL_Texture*> allTextures=initTextures(gr);
	std::vector<Sprite*> osSprite;
	//note: maybe merge positions and osSprite?
	vector<vector<int>> positions;
	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = false;
	//gpRender object that is used to render object onto screen

	//Ship object init


	//----------------------Player Ship initilization--------------------//
	

	SDL_Texture* ptex = allTextures.at(TEX_FIGHT_HERO);
	SDL_Rect pdb = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};


	Hero playerShip(pdb, ptex);
	playerShip.setPosition(pair<int,int>(250,250));
	playerShip.setRenderOrder(0);
	//cout<<"playership sprite: "<<playerShip.getTexture()<<endl;
	osSprite.push_back(&playerShip);
	
	
	//--------------------------End-----------------------------------//

	//----------------------AI Ship initilization--------------------//
	

	

	//AI Ship 1 init
	SDL_Rect db1 = {100,200,PLAYER_WIDTH,PLAYER_HEIGHT};
	SDL_Texture* tex1 = gr.loadImage("Assets/Objects/ship_capital_enemy.png");
	
	AIShip aiShip(db1, tex1,true);
	aiShip.setPosition(pair<int,int>(100,200));
	aiShip.setDestination(playerShip.getPosition());
	aiShip.setRenderOrder(0);
	aiShip.setF(-1);
	aiShip.setGoal(0);
	//cout<<"aiShip texture: "<<aiShip.getTexture()<<endl;
	osSprite.push_back(&aiShip);

	
	//AI Ship 2 init
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_capital_hero.png");
	SDL_Rect db3 = {1000, 400, PLAYER_WIDTH,PLAYER_HEIGHT};

	AIShip aiShip2(db3,tex3,false);
	aiShip2.setPosition(pair<int,int>(1000,400)); //omega weird how some values will seg fault but not for others
	aiShip2.setDestination(playerShip.getPosition());
	aiShip2.setRenderOrder(0);
	aiShip2.setF(-1);
	aiShip2.setGoal(-1);
	//cout<<"aiShip2 texture: "<<aiShip2.getTexture()<<endl;
	osSprite.push_back(&aiShip2);
	//Ship testship(db3,tex3);
	//load a laser to be reused
	SDL_Texture* laser=gr.loadImage("Assets/Objects/laser.png");
	//osSprite.push_back(&testship);
	vector<AIShip*> aiControlled;
	
	aiControlled.push_back(&aiShip);
	aiControlled.push_back(&aiShip2);
	
//	cout<<"push back ok"<<endl;

	//--------------------------End-----------------------------------//

	//--------------------Red giant Initilzation-----------------------
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {ZONE_WIDTH/2,ZONE_HEIGHT/2,300,300};
	Sprite starent(db2, tex2);

	Star star;

	star.setSize({300, 300});
	star.setPosition({500, 200});

	Sector sector;

	sector.setSize({ZONE_WIDTH, ZONE_HEIGHT});
	sector.setStars({star});
	osSprite.push_back(&starent);

	sector.setShips({&playerShip, &aiShip, &aiShip2});
	//----------------------------------------------------------------------



//------------------------------------Rendering Background--------------------------------------//
	srand(time(0));
	SDL_Rect bgtile[100];
	std::vector<std::vector<SDL_Rect*> > bgzonelayer1( ZONE_WIDTH/20 , std::vector<SDL_Rect*> (ZONE_HEIGHT/20, 0));
	std::vector<std::vector<SDL_Rect*> > bgzonelayer2( ZONE_WIDTH/40 , std::vector<SDL_Rect*> (ZONE_HEIGHT/40, 0));
	std::vector<int> bggalaxies(4);

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			bgtile[x + 10*y].x = x * 40;
			bgtile[x + 10*y].y = y * 40;
			bgtile[x + 10*y].w = 40;
			bgtile[x + 10*y].h = 40;
		}
	}
	
	for (int x = 0; x < ZONE_WIDTH/20; x++) {
		for (int y = 0; y < ZONE_HEIGHT/20; y++) {
			bgzonelayer1[x][y] = &bgtile[rand() % 100];
			if ((x < ZONE_WIDTH/40) && (y < ZONE_HEIGHT/40)) {
				bgzonelayer2[x][y] = &bgtile[rand() % 100];
			}
		}
	}

	//random background galaxies
	bggalaxies[0] = rand() % (ZONE_WIDTH - 200);
	bggalaxies[1] = rand() % (ZONE_HEIGHT - 200);
	
	bggalaxies[2] = rand() % (ZONE_WIDTH - 200);
	bggalaxies[3] = rand() % (ZONE_HEIGHT - 200);

	//------------------------------------Rendering Background--------------------------------------//

	SDL_Event e;
	bool gameon = true;
	

	AI ai;

	ai.createMapState(sector);
	ai.setCurrentSector(sector);
	//ai.createShipState(sector);
	vector<vector<bool> > mesh = ai.getMapState();
	pair<int,int> sectorSize;
	sectorSize.first=ZONE_WIDTH;
	sectorSize.second=ZONE_HEIGHT;
	ai.setSectorSize(sectorSize);
	Pathfinder path(mesh, 10);

	ai.setPathfinder(&path);
	ai.setPlayerShip(&playerShip);
	ai.setShips(&aiControlled);
	ai.setSprites(osSprite);
	ai.setTextures(allTextures);

	//cout<<"pathfinded?"<<endl;
	//Game Loop
	bool render = true;
	while(gameon) {
		//ai.createShipState(sector);
		SDL_RenderClear(gr.getRender());
		gr.setFrameStart(SDL_GetTicks());
		TimeData::update_timestep();
		//position needs to be in booleans?
		ai.executeAIActions();

		//DOESN"T WORK AT THIS TIME
		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			
			gameon = playerShip.handleKeyEvents(e);
			
		}
		//updatePosition(aient, osSprite, ZONE_WIDTH, ZONE_HEIGHT);
		//std::cout << "\nShip 1 postion: " << aiShip.getPosition().first <<" " << aiShip.getPosition().second << "\n" << std::endl;
		playerShip.updateMovement(osSprite, ZONE_WIDTH, ZONE_HEIGHT);
		
		

		camera.x = playerShip.getX() - SCREEN_WIDTH/2 + PLAYER_WIDTH/2;
		camera.y = playerShip.getY() - SCREEN_HEIGHT/2 + PLAYER_HEIGHT/2;
			
		if (camera.x < 0){
			camera.x = 0;
			fixed = true;
		}
		else if (camera.x + SCREEN_WIDTH > ZONE_WIDTH){
			camera.x = ZONE_WIDTH - SCREEN_WIDTH;
			fixed = true;
		}
		if (camera.y < 0){
			camera.y = 0;

			fixed = true;
		}
		else if (camera.y + SCREEN_HEIGHT > ZONE_HEIGHT){
			camera.y = ZONE_HEIGHT - SCREEN_HEIGHT;
			fixed = true;
		}

			
		
		gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		
		}


}


	/**for(auto &ship : aiControlled)
		{
		   
			if(!ship->isPathSet()){
			
	
				ship->setPath(ai.calculatePath(*ship, path));
			}
			
			ship->setDestination(playerShip.getPosition());
			ship->followPath();
			if(ship->getPathComplete())
			{
	
			    ship->setPath(ai.calculatePath(*ship, path));
			}
		}**/
