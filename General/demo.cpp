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
#include "../Physics/BasicMovementFPSlimit.h"
#include "../Physics/TimeData.h"
#include "../Physics/Audio.h"
#include "../General/gpRender.h"
#include "../Level_Generation/Ellers_Maze.h"
#include "demo.h"

std::vector<std::pair<int, int>> randNum(){

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
constexpr int PLAYER_WIDTH = 52;
constexpr int PLAYER_HEIGHT = 60;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;

void run_demo(gpRender gr){
	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite; // vector for collision checker

	//Audio Initilization
	Audio::load_audio();

	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


	bool fixed = false;

	std::vector <std::pair<int, int>> randCoords = randNum();

	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_player.png");
	SDL_Rect db = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	//Ship playerent(db, tex, 0);
	Hero playerent(db, tex);
	//playerent.setRenderOrder(0);
	playerent.setCurrHp(100);
	playerent.setMaxHp(100);
	osSprite.push_back(&playerent);
	
	
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	//SDL_Rect db2 = {800,400,332,315};
	SDL_Rect db2 = {ZONE_WIDTH/2,ZONE_HEIGHT/2,432,415};

	Star starent(db2, tex2);

	osSprite.push_back(&starent);

	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
	SDL_Rect db3 = {randCoords[0].first,randCoords[0].second,200,200};
	Sprite planet1ent(db3, tex3);

	osSprite.push_back(&planet1ent);

	SDL_Texture* tex4 = gr.loadImage("Assets/Objects/planetmid.png");

	SDL_Rect db4 = {randCoords[1].first + rand()%100 + ZONE_WIDTH/4,randCoords[1].second+ 400,200,200};

	Sprite planet2ent(db4, tex4);

	osSprite.push_back(&planet2ent);

	SDL_Texture* tex5 = gr.loadImage("Assets/Objects/planetnear.png");
	SDL_Rect db5 = {randCoords[2].first +rand()%100 + ZONE_WIDTH/3,randCoords[2].second+ rand()%100 + ZONE_HEIGHT/3,200,200};

	Sprite planet3ent(db5, tex5);

	osSprite.push_back(&planet3ent);

	SDL_Texture* tex6 = gr.loadImage("Assets/Objects/planetnear.png");
	SDL_Rect db6 = {randCoords[3].first +rand()%200 + 2500,randCoords[3].second+rand()%100 + ZONE_HEIGHT/3,200,200};

	Sprite planet4ent(db6, tex6);

	osSprite.push_back(&planet4ent);

	SDL_Texture* tex7 = gr.loadImage("Assets/Objects/planetfar.png");
	SDL_Rect db7 = {randCoords[4].first + 2000,randCoords[4].second,200,200};
	Sprite planet5ent(db7, tex7);

	osSprite.push_back(&planet5ent);

	SDL_Texture* tex8 = gr.loadImage("Assets/Objects/planetmid.png");
	SDL_Rect db8 = {randCoords[5].first + 1800,randCoords[5].second + 500,200,200};
	Sprite planet6ent(db8, tex8);

	osSprite.push_back(&planet6ent);

	SDL_Texture* tex9 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db9 = {randCoords[6].first + 1000,randCoords[6].second + 1000,200,200};
	Sprite asteroid1ent(db9, tex9);

	osSprite.push_back(&asteroid1ent);	

	SDL_Texture* tex10 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db10 = {randCoords[7].first + 800,randCoords[7].second + 1000,200,200};
	Sprite asteroid2ent(db10, tex10);

	osSprite.push_back(&asteroid2ent);

	SDL_Texture* tex11 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db11 = {randCoords[8].first + 1100,randCoords[8].second + 1000,200,200};
	Sprite asteroid3ent(db11, tex11);

	osSprite.push_back(&asteroid3ent);

	SDL_Texture* tex12 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db12 = {randCoords[9].first + 600,randCoords[9].second + 1000,200,200};
	Sprite asteroid4ent(db12, tex12);

	osSprite.push_back(&asteroid4ent);
	
	SDL_Texture* texhp = gr.loadImage("Assets/Objects/hp_bar.png");
	SDL_Rect hp = {10,10,300,20};
	HpBar hpent(hp, texhp, playerent.getCurrHp()/playerent.getMaxHp());
	osSprite.push_back(&hpent);

	/*
	//Ship Cruiser initilization
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db3 = {400,300,225,300};
	Sprite emyent(db3, tex3);
	*/

	SDL_Texture* ltex = gr.loadImage("Assets/Objects/laser.png");

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
	bool gameon = false;
	int animation = 0;
	bool cycle;
	bool animate = false;
	int titleFrame = 0;
	// title screen
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
		// start game when enter key is pressed
		while(SDL_PollEvent(&s)){	
			switch(s.key.keysym.sym){ 
				case SDLK_RETURN:
					if(s.type == SDL_KEYDOWN){
						SDL_RenderClear(gr.getRender());
						gameon = true;
					}
			}	
			
		}
	}

	while(gameon)
	{
		SDL_RenderClear(gr.getRender());
		bool solar = true;

		//Game Loop
		while(gameon && solar)
		{
			
			gr.setFrameStart(SDL_GetTicks());
			TimeData::update_timestep();

			//Handles all incoming Key events
			while(SDL_PollEvent(&e)) {

				gameon = playerent.handleKeyEvents(e);

				switch(e.key.keysym.sym) {
					case SDLK_w:
						if(e.type == SDL_KEYDOWN){
							animate = true;
						}
						else if (e.type == SDL_KEYUP){
							animate = false;
						}
						break;

					case SDLK_m:
						if(e.type == SDL_KEYDOWN){
							solar = false;
						}
						break;
					case SDLK_SPACE:
						osSprite.push_back(new Projectile(playerent.fireWeapon(ltex)));					
						break;
				}
			}
			hpent.setPercentage((float)playerent.getCurrHp()/(float)playerent.getMaxHp());
			hpent.changeBar(playerent);

			for(auto ent : osSprite) {
				ent->updateMovement(osSprite, ZONE_WIDTH, ZONE_HEIGHT);
			}
      
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
		
		Ellers_Maze maze;
		SDL_RenderClear(gr.getRender());
		bool mazeCheck = true;

		while(mazeCheck && gameon)
		{
			SDL_RenderClear(gr.getRender());
			while(SDL_PollEvent(&e)) {
				gameon = handleKeyEvents(e, playerent);	
				switch(e.key.keysym.sym) {
					case SDLK_m:
						if(e.type == SDL_KEYDOWN){
							mazeCheck = false;
						}
						break;
						
					case SDLK_w:
						if(e.type == SDL_KEYDOWN){
							//move up
							if(col != 0 and !maze.hasBottom(row, col-1)){
								col--;
							}
						}
						break;

					case SDLK_s:
						if(e.type == SDL_KEYDOWN){
							//move down
							if(col != numCols-1 and !maze.hasBottom(row,col)){
								col++;
							}
						}
						break;

					case SDLK_a:
						if(e.type == SDL_KEYDOWN){
							//move left
							if(row != 0 and !maze.hasRight(row-1,col)){
								row--;
							}
						}
						break;

					case SDLK_d:
						if(e.type == SDL_KEYDOWN){
							//move right
							if(row != numRows-1 and !maze.hasRight(row,col)){
								row++;
							}
						}
						break;
				}
			}
			
			maze.drawMaze(gr.getWall(), gr.getRender());
			SDL_RenderPresent(gr.getRender());
		}

		SDL_RenderClear(gr.getRender());
	}
	
}
