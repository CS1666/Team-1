 
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
using namespace std;

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 1280; 
constexpr int ZONE_HEIGHT = 720;
typedef std::vector<std::vector<bool> > Mesh;

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
	

	SDL_Texture* ptex = gr.loadImage("Assets/Objects/ship_player.png");
	
	SDL_Rect pdb = {250,250,PLAYER_WIDTH,PLAYER_HEIGHT};

	Hero playerShip(pdb, ptex);
	playerShip.setPosition(pair<int,int>(250,250));
	osSprite.push_back(&playerShip);
	
	
	//--------------------------End-----------------------------------//

	//----------------------AI Ship initilization--------------------//
	

	

	//AI Ship 1 init
	SDL_Rect db1 = {100,200,PLAYER_WIDTH,PLAYER_HEIGHT};
	SDL_Texture* tex1 = gr.loadImage("Assets/Objects/ship_capital_enemy.png");
	
	AIShip* aiShip = new AIShip(db1, tex1);
	aiShip->setPosition(pair<int,int>(100,200));
	aiShip->setDestination(playerShip.getPosition());
	osSprite.push_back(aiShip);

	
	//AI Ship 2 init
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_capital_hero.png");
	SDL_Rect db3 = {1000, 400, PLAYER_WIDTH,PLAYER_HEIGHT};

	AIShip* aiShip2 = new AIShip(db3,tex3);
	aiShip2->setPosition(pair<int,int>(1000,400)); //omega weird how some values will seg fault but not for others
	aiShip2->setDestination(playerShip.getPosition());
	
	osSprite.push_back(aiShip2);

	//std::cout << "AI controlled" << std::endl;
	vector<AIShip*>* aiControlled = new vector<AIShip*>(); //remove/replace when we can use the Ship itself
	//std::cout << "AI controlled" << std::endl;
	aiControlled->push_back(aiShip);
	//std::cout << "AI controlled" << std::endl;
	aiControlled->push_back(aiShip2);
	//std::cout << "AI controlled" << std::endl;

//	cout<<"push back ok"<<endl;

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

	//std::cout << "Creating AI" << std::endl;
	AI ai(aiControlled, sector);

	//bool render = true;
	while(gameon) {
		SDL_RenderClear(gr.getRender());
		gr.setFrameStart(SDL_GetTicks());
		TimeData::update_timestep();

		//std::cout << "Updating Player Ship" << std::endl;
		ai.updatePlayerState(&playerShip);

		//std::cout << "Handeling Players Actions" << std::endl;
		ai.handleShipsActions();
		
		//std::cout << "Rendering" << std::endl;
		while(SDL_PollEvent(&e)) {
			//////std::cout << "Key Event!!!" << std::endl;
			gameon = playerShip.handleKeyEvents(e);
			
		}
		//updatePosition(aient, osSprite, ZONE_WIDTH, ZONE_HEIGHT);
		////std::cout << "\nShip 1 postion: " << aiShip.getPosition().first <<" " << aiShip.getPosition().second << "\n" << std::endl;
		playerShip.updateMovement(osSprite, ZONE_WIDTH, ZONE_HEIGHT);
		
		TimeData::update_move_last_time();

		
		gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		
		}

	delete aiShip;
	delete aiShip2;
	//delete aiControlled;
}

