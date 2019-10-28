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
	Ship aiShip;
	//AI init

	AI ai;

	aiShip.setSprite("Assets/Objects/ship_capital_ally.png");
	aiShip.setPosition(pair<int,int>(10,10));
	aiShip.setDestination(pair<int,int>(1010, 600));

	SDL_Texture* tex = gr.loadImage(aiShip.getSprite());
	//SDL_Rect db = {50,325,75,75};
	SDL_Rect db = {10,10,PLAYER_WIDTH,PLAYER_HEIGHT};

	Ship playerent(db, tex);
	Sprite hpent(db, tex);
	osSprite.push_back(&playerent);

	//positions = gameState, only track the ship for now
	//destination is also a vector
	positions.push_back({10,10});

	


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {500,200,300,300};
	Sprite starent(db2, tex2);

	osSprite.push_back(&starent);
	osSprite.push_back(&hpent);

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


	Star star;

	star.setSize({300, 300});
	star.setPosition({500, 200});

	Sector sector;

	sector.setSize({1280, 720});
	sector.setStars({star});

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
			ai.createMapState(sector);
		   
		    
		    //make a testing queue of a path
		   
		    
		    aiShip.followPath(playerent);

		}
		else{
			;
		    
		    aiShip.setDestination(pair<int,int>(10, 60));

		    pathq = ai.calculatePath(aiShip, path);
		
		    aiShip.setPath(pathq);
		   
		}
		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
			
		}

		updatePosition(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);

		gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		}
	}

	
}
