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
#include "theta.h"
using namespace std;

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 1280; 
constexpr int ZONE_HEIGHT = 720;


vector<Sprite*> initilizeSprites(){

}
void run_ai_enviro(gpRender gr){


	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;
	//note: maybe merge positions and osSprite?
	vector<vector<int>> positions;
	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = true;

	//gpRender object that is used to render object onto screen

	//Ship object init


	//----------------------Player Ship initilization--------------------//
	Ship playerShip;

	playerShip.setSprite("Assets/Objects/ship_capital_ally.png");
	playerShip.setPosition(pair<int,int>(50,50));
	

	SDL_Texture* ptex = gr.loadImage(playerShip.getSprite());
	
	SDL_Rect pdb = {50,50,PLAYER_WIDTH,PLAYER_HEIGHT};

	
	Sprite playerent(pdb, ptex);
	osSprite.push_back(&playerent);
	
	//--------------------------End-----------------------------------//

	//----------------------AI Ship initilization--------------------//
	Ship aiShip;
	//AI init

	AI ai;

	aiShip.setSprite("Assets/Objects/ship_capital_enemy.png");
	aiShip.setPosition(pair<int,int>(100,200));
	aiShip.setDestination(pair<int,int>(1010, 600));

	SDL_Texture* tex1 = gr.loadImage(aiShip.getSprite());
	
	SDL_Rect db1 = {100,200,PLAYER_WIDTH,PLAYER_HEIGHT};

	Sprite aient(db1, tex1);
	osSprite.push_back(&aient);
	

	//--------------------------End-----------------------------------//

	//--------------------Red giant Initilzation-----------------------
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {500,200,300,300};
	Sprite starent(db2, tex2);

	Star star;

	star.setSize({300, 300});
	star.setPosition({500, 200});

	Sector sector;

	sector.setSize({1280, 720});
	sector.setStars({star});
	osSprite.push_back(&starent);
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
	


	ai.createMapState(sector);
	vector<vector<bool> > mesh = ai.getMapState();
	Pathfinder path(mesh, 10);
	queue<pair<int,int>>* pathq = ai.calculatePath(aiShip, path);

	if((!pathq->empty())){
		aiShip.setPath(pathq);
	
	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());
		//position needs to be in booleans?
		if(aiShip.getPosition()!=aiShip.getDestination())
		{
		    aiShip.followPath(aient);
		    if(aiShip.getPathComplete())
		    {
				pathq = ai.calculatePath(aiShip,path);
				aiShip.setPath(pathq);
		    }
		}
		else{
		    
		    aiShip.setDestination(pair<int,int>(10, 60));

		    pathq = ai.calculatePath(aiShip, path);
		
		    aiShip.setPath(pathq);
		   
		}

		//DOESN"T WORK AT THIS TIME
		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			std::cout << "Key Event!!!" << std::endl;
			gameon = handleKeyEvents(e, playerShip);	
			
		}
		updatePosition(playerShip, osSprite, ZONE_WIDTH, ZONE_HEIGHT);

		gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		}
	}

	
}
