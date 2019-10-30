#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../General/Ship.h"
#include "../General/Star.h"
#include "../General/SpaceStation.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../Physics/TimeData.h"
#include "../Physics/Audio.h"
#include "../General/gpRender.h"
#include "../Level_Generation/Ellers_Maze.h"
#include "../General/planet.h"
#include "phy_enviroment.h"

constexpr int PLAYER_WIDTH = 52;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;

std::vector<std::pair<int, int>> randNumP(){

	std::vector<int> coorX;
	std::vector<int> coorY;
	std::vector<std::pair<int, int>> coords;

	srand(time(0));
	
	for(int i = 0; i<10; i++){
		coorX.push_back((rand()%100));
	}
	
	for(int i = 0; i<10; i++){
		coorY.push_back((rand()%200));
	}

	coords.reserve(10);
	std::transform(coorX.begin(), coorX.end(), coorY.begin(), std::back_inserter(coords), 
		[](int a, int b){return std::make_pair(a, b);});

	for(int k = 0; k<10; k++){
	 	std::cout << coords[k].first << ", " << coords[k].second << endl;
	}

	 return coords;
}
void run_phy_enviro(gpRender gr){
	//Vector used to store all on screen entities
	std::vector<Sprite*> osSprite;
	
	//load audio for sound
	Audio::load_audio();

	bool gameon = false;
	int titleFrame = 0;

	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = false;
	
	//gpRender object that is used to render object onto screen
	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_player.png");
	SDL_Rect db = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	Ship playerent(db, tex, 0);
	playerent.setCurrHp(100);
	playerent.setMaxHp(100);
	playerent.setRenderOrder(0);
	osSprite.push_back(&playerent);
	

	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	Star starent(db2, tex2);

	osSprite.push_back(&starent);

	std::vector <std::pair<int, int>> randCoords = randNumP();


	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
	SDL_Rect db3 = {1600,400,200,200};
	Planet planet1ent(db3, tex3,1, starent, 100);
	osSprite.push_back(&planet1ent);

	//Space Station Initialization-
	SDL_Texture* tex_ss = gr.loadImage("Assets/Objects/Asteroid.png"); //placeholder img
	SDL_Rect db4 = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2 - 200,PLAYER_WIDTH,PLAYER_HEIGHT};
	SpaceStation ss_ent(db4, tex_ss);
	//osSprite.push_back(&ss_ent);
	osSprite.push_back(&ss_ent);
	
	//planet1ent.initVelocity(starent);

	
	//Ship Cruiser initilization
	//SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	//SDL_Rect db3 = {400,300,225,300};
	//Sprite emyent(db3, tex3);

	//osSprite.push_back(&emyent);
	
	SDL_Texture* texhp = gr.loadImage("Assets/Objects/hp_bar.png");
	SDL_Rect hp = {10,10,300,20};
	HpBar hpent(hp, texhp, playerent.getCurrHp()/playerent.getMaxHp());
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


	SDL_Event e;
	
	int animation = 0;
	bool cycle;
	bool animate = false;
	Uint32 anim_last_time = SDL_GetTicks();

	SDL_Texture* titletex = gr.loadImage("Assets/Objects/title1.png");
	SDL_Texture* titletex2 = gr.loadImage("Assets/Objects/title2.png");
	SDL_Rect title = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Event s;
	while(!gameon){
		if(titleFrame == 0){
			SDL_RenderCopy(gr.getRender(), titletex, nullptr, &title);
			titleFrame++;
		}else{
			SDL_RenderCopy(gr.getRender(), titletex2, nullptr, &title);
			titleFrame--;
		}
		SDL_RenderPresent(gr.getRender());
		SDL_Delay(300);
		while(SDL_PollEvent(&s)){	
			switch(s.key.keysym.sym) {
				case SDLK_RETURN:
					if(s.type == SDL_KEYDOWN){
						SDL_RenderClear(gr.getRender());
						gameon = true;
					}
			}	
			
		}
	}

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());
		TimeData::update_timestep();
		
		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
			
			switch(e.key.keysym.sym) {
				case SDLK_w:
					if(e.type == SDL_KEYDOWN){
						animate = true;
					}
					else if (e.type == SDL_KEYUP){
						animate = false;
					}
					break;
			}
		}
		hpent.setPercentage((float)playerent.getCurrHp()/(float)playerent.getMaxHp());
		hpent.changeBar(playerent);
		std::cout << hpent.getW() << endl;
		planet1ent.updatePosition();
		updatePosition2(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);
		TimeData::update_move_last_time();

		if (animate){
			if (TimeData::getTimeSinceAnim() > 100) {
				if (animation <= 1){
					cycle = true;
				}
				else if(animation == 3){
					cycle = false;
				}
				
				if (cycle){
					animation++;
				}
				else{
					animation--;
				}
				
				TimeData::update_anim_last_time();
				playerent.setF(animation);
			}
		}
		else{
			animation = 0;
			playerent.setF(animation);
		}
		//Renders all renderable objects onto the screen
		
		camera.x = playerent.getX() - SCREEN_WIDTH/2 + PLAYER_WIDTH/2;
		camera.y = playerent.getY() - SCREEN_HEIGHT/2 + PLAYER_HEIGHT/2;
		
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
