#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../General/HpBar.h"
#include "../General/Ship.h"
#include "../General/Star.h"
#include "../General/SpaceStation.h"
#include "../General/SpaceStationUI.h"
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
	//Vector used to store all on screen entities
	std::vector<Ship*> osShip;
	
	//load audio for sound
	Audio::load_chunk("Assets/Objects/thrustSoundSmall.wav");
	Audio::load_music("Assets/Sound/spacegamemainsound.wav");
	Audio::set_solar(true);
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
	osShip.push_back(&playerent);
	
	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	NSDL_Circ dc2 = {db2};
	Star starent(db2, tex2, dc2);
	starent.initMass();
	osSprite.push_back(&starent);
	//std::vector <std::pair<int, int>> randCoords = randNumP();

	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
	SDL_Rect db3 = {1600,400,200,200};
	NSDL_Circ dc3 = {db3};
	Planet planet1ent(db3, tex3, dc3,15, starent, 100);
	osSprite.push_back(&planet1ent);
	std::cout<< "mass " << starent.getMass() << std::endl;
	//Space Station Initialization-
	SDL_Texture* tex_ss = gr.loadImage("Assets/Objects/Asteroid.png"); //placeholder img
	SDL_Rect db4 = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2 - 200,PLAYER_WIDTH,PLAYER_HEIGHT};
	SpaceStation ss_ent(db4, tex_ss);
	//osSprite.push_back(&ss_ent);
	osSprite.push_back(&ss_ent);
	
	/*//Ship Cruiser initilization
	SDL_Texture* tex_em = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db5 = {500,300,50,50};
	Ship ement(db5, tex_em);
	ement.setCurrHp(100);
	ement.setMaxHp(100);
	osSprite.push_back(&ement);
	osShip.push_back(&ement);

	SDL_Rect db6 = {400,500,50,50};
	Ship ement2(db6, tex_em);
	ement2.setCurrHp(100);
	ement2.setMaxHp(100);
	osSprite.push_back(&ement2);
	osShip.push_back(&ement2);*/

	SDL_Texture* texhp = gr.loadImage("Assets/Objects/hp_bar.png");
	SDL_Rect hp = {10,10,300,20};
	HpBar hpent(hp, texhp, playerent.getCurrHp()/playerent.getMaxHp());
	osSprite.push_back(&hpent);

	SDL_Texture* e_tex = gr.loadImage("Assets/Objects/E.png");
	SDL_Rect e_rect = {50, 50, 100, 100};
	SpaceStationUI e_UI(e_rect, e_tex);
	/* //code for making E render on screen
	e_UI.set_spriteIndex(osSprite.size());
	osSprite.push_back(&e_UI);
	*/
	SDL_Texture* ss_UI_tex = gr.loadImage("Assets/Objects/spaceStation.png");
	SDL_Rect ss_UI_rect = { 200, 200, 200, 200};
	SpaceStationUI ss_UI(ss_UI_rect, ss_UI_tex);
	/* //code for making the space station menu render on screen
	ss_UI.set_spriteIndex(osSprite.size());
	osSprite.push_back(&ss_UI);
	*/
	bool in_space_station_menu = false;
	bool is_space_station_in_range = false;

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
	Audio::play_music();

	gameon = false;

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

		for(std::size_t i = 0; i != osShip.size(); i++){
			if(osShip.at(i)->getCurrHp() <= 0){
				for(std::size_t j = 0; j != osSprite.size(); j++){
					if((Sprite*)osShip.at(i) == osSprite.at(j)){
						osShip.erase(osShip.begin() + (i--));
						osSprite.erase(osSprite.begin() + j);
					}
				}
			}
		}

		//Handle spacestation proximity code
		//Prox code = just increase the size of the ship collision box and do a collision check
		//physics function
		if(!is_space_station_in_range){
			if(check_proximity(playerent, ss_ent, 3)){
				//then we set the is_space_station_in_range flag to true
				is_space_station_in_range = true;
				//SDL_RenderCopy(gr.getRender(), e_tex, nullptr, &e_rect);
			}
		} else {
			//we display the E png to show that space station can be accessed
				
				//SDL_RenderPresent(gr.getRender());
			//we need to check if our ship has left the range of the space station
			if(!check_proximity(playerent, ss_ent, 3)){
				
				if(in_space_station_menu) {
					osSprite.erase(osSprite.begin() + ss_UI.get_spriteIndex());
				}
				osSprite.erase(osSprite.begin() + e_UI.get_spriteIndex());
				//then we set the is_space_station_in_range flag to false
				is_space_station_in_range = false;
				in_space_station_menu = false;
				//SDL_RenderCopy(gr.getRender(), e_tex, nullptr, &e_rect);
				
			}
		}
		
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
				
				case SDLK_e:
					if(e.type == SDL_KEYDOWN){
						//SDL_RenderClear(gr.getRender());
						//gameon = false;
						if(!in_space_station_menu && is_space_station_in_range){
							in_space_station_menu = true;
							ss_UI.set_spriteIndex(osSprite.size());
							osSprite.push_back(&ss_UI);
						} else if(in_space_station_menu && is_space_station_in_range) {
							//in_space_station_menu = false;
							in_space_station_menu = false;
							osSprite.erase(osSprite.begin() + ss_UI.get_spriteIndex());
						}
					}
					break;

				case SDLK_r:
					if(e.type == SDL_KEYDOWN){
						//SDL_RenderClear(gr.getRender());
						//gameon = false;
						if(in_space_station_menu && is_space_station_in_range){
							in_space_station_menu = false;
							osSprite.erase(osSprite.begin() + ss_UI.get_spriteIndex());
						} else {
							//in_space_station_menu = false;
						}
					}
					break;

				/*case SDLK_p:
					if(e.type == SDL_KEYDOWN){
						ement.setCurrHp(0);
					}
					break;

				case SDLK_o:
					if(e.type == SDL_KEYDOWN){
						ement2.setCurrHp(0);
					}
					break;*/
			}
		}
		hpent.setPercentage((float)playerent.getCurrHp()/(float)playerent.getMaxHp());
		hpent.changeBar(playerent);
		std::cout << hpent.getW() << endl;
		planet1ent.updatePosition(playerent);
		updatePosition3(playerent, osSprite, osShip, ZONE_WIDTH, ZONE_HEIGHT);
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
		
		/*
		if(is_space_station_in_range){
		//we display the E png to show that space station can be accessed
			SDL_RenderCopy(gr.getRender(), e_tex, nullptr, &e_rect);
			SDL_RenderPresent(gr.getRender());
			if(in_space_station_menu){
				SDL_RenderCopy(gr.getRender(), ss_UI_tex, nullptr, &ss_UI_rect);
				SDL_RenderPresent(gr.getRender());
			}
				
		}
		*/
		gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		if(playerent.getCurrHp() <=0 )
		{
			gameon = false;
		}
		
	}
	Audio::close();
}
