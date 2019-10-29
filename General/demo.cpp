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
#include "../Physics/BasicMovementFPSlimit.h"
#include "../Physics/TimeData.h"
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
	std::vector<Sprite*> osSprite2; // 2nd vector for rendering (will contain objects that ignore collision)

	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


	bool fixed = false;

	std::vector <std::pair<int, int>> randCoords = randNum();

	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_player.png");
	SDL_Rect db = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	Ship playerent(db, tex, 0);
	playerent.setRenderOrder(0);
	playerent.setCurrHp(100);
	playerent.setMaxHp(100);
	osSprite.push_back(&playerent);
	
	
	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	Star starent(db2, tex2);

	osSprite.push_back(&starent);

	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
	SDL_Rect db3 = {randCoords[0].first,randCoords[0].second,200,200};
	Sprite planet1ent(db3, tex3);

	osSprite.push_back(&planet1ent);

	SDL_Texture* tex4 = gr.loadImage("Assets/Objects/planetmid.png");
	SDL_Rect db4 = {randCoords[1].first,randCoords[1].second+ 400,200,200};
	Sprite planet2ent(db4, tex4);

	osSprite.push_back(&planet2ent);

	SDL_Texture* tex5 = gr.loadImage("Assets/Objects/planetnear.png");
	SDL_Rect db5 = {randCoords[2].first +400,randCoords[2].second+ 700,200,200};
	Sprite planet3ent(db5, tex5);

	osSprite.push_back(&planet3ent);

	SDL_Texture* tex6 = gr.loadImage("Assets/Objects/planetnear.png");
	SDL_Rect db6 = {randCoords[3].first +1200,randCoords[3].second+ 600,200,200};
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


	for(auto sprite : osSprite){
		osSprite2.push_back(sprite);
	}

	SDL_Texture* texhp = gr.loadImage("Assets/Objects/hp_bar.png");
	SDL_Rect hp = {10,10,300,20};
	HpBar hpent(hp, texhp, playerent.getCurrHp()/playerent.getMaxHp());
	osSprite2.push_back(&hpent);
	/*
	//Ship Cruiser initilization
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db3 = {400,300,225,300};
	Sprite emyent(db3, tex3);
	*/

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

					case SDLK_m:
						if(e.type == SDL_KEYDOWN){
							solar = false;
						}
						break;
				}
			}
			hpent.setPercentage((float)playerent.getCurrHp()/(float)playerent.getMaxHp());
			hpent.changeBar(playerent);
			updatePosition(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);
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

			gr.renderOnScreenEntity(osSprite2, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
		}
		
		Ellers_Maze maze;
		SDL_RenderClear(gr.getRender());
		bool mazeCheck = true;

		
		constexpr int CAM_WIDTH = 1280;
constexpr int CAM_HEIGHT = 720;
constexpr int TILE_SIZE = 100;

// Function declarations
bool init();
SDL_Texture* loadImage(std::string fname);
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gBackground;
SDL_Texture* gShipSheet;

SDL_Rect gShipRect = {0, 0, TILE_SIZE, TILE_SIZE};

bool init() {	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	
	gWindow = SDL_CreateWindow("Warping", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CAM_WIDTH, CAM_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	// Adding VSync to avoid absurd framerates
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {	
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);
	if(retFlags != imgFlags) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			
	return true;
}

SDL_Texture* loadImage(std::string fname) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}


void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	SDL_DestroyTexture(gBackground);
	gBackground = nullptr;

	SDL_DestroyTexture(gShipSheet);
	gShipSheet = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

int warpMovement() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}
	
	gBackground = loadImage("Assets/Objects/warpEffect.png");

	int scroll_offset = 0;
	
	gShipSheet = loadImage("Assets/Objects/warpShip.png");

	// Moving box
	SDL_Rect moveBox = {CAM_WIDTH/2 - TILE_SIZE/2, CAM_HEIGHT/2 - TILE_SIZE/2, TILE_SIZE, TILE_SIZE};	
	int x_vel = 0;
	int y_vel = 0;
	int x_deltav = 0;
	int y_deltav = 0;

	SDL_Rect bgRect = {0, 0, CAM_WIDTH, CAM_HEIGHT};
		
		
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
				}
			}
			
		x_deltav = 0;
		y_deltav = 0;
		const Uint8* keystate = SDL_GetKeyboardState(nullptr);
		if (keystate[SDL_SCANCODE_W])
			y_deltav -= 1;
		if (keystate[SDL_SCANCODE_A])
			x_deltav -= 1;
		if (keystate[SDL_SCANCODE_S])
			y_deltav += 1;
		if (keystate[SDL_SCANCODE_D])
			x_deltav += 1;

		if (x_deltav == 0) {
			if (x_vel > 0)
				x_deltav = -1;
			else if (x_vel < 0)
				x_deltav = 1;
		}
		if (y_deltav == 0) {
			if (y_vel > 0)
				y_deltav = -1;
			else if (y_vel < 0)
				y_deltav = 1;
		}
		
		x_vel += x_deltav;
		y_vel += y_deltav;

		if (x_vel < -5)
			x_vel = -5;
		else if (x_vel > 5)
			x_vel = 5;

		if (y_vel < -5)
			y_vel = -5;
		else if (y_vel > 5)
			y_vel = 5;

		// Move Ship vertically
		moveBox.y += y_vel;
		// Vertical movement constrained by camera height and tiles at bottom
		if (moveBox.y < 0 || (moveBox.y + TILE_SIZE > CAM_HEIGHT))
			moveBox.y -= y_vel;

		// Move Ship horizontally
		moveBox.x += x_vel;
		// Horizontal movement constrained by length of level
		if (moveBox.x < 0 || (moveBox.x + TILE_SIZE > CAM_WIDTH))
			moveBox.x -= x_vel;

		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		// Always scroll the background
		scroll_offset += 4;
		if (scroll_offset > CAM_HEIGHT)
			scroll_offset = -1;		
		bgRect.y = scroll_offset;
		SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);
		bgRect.y -= CAM_HEIGHT;
		SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

		// Draw the Ship
		SDL_RenderCopy(gRenderer, gShipSheet, &gShipRect, &moveBox);

		SDL_RenderPresent(gRenderer);
			
			maze.drawMaze(gr.getWall(), gr.getRender());
			SDL_RenderPresent(gr.getRender());
		}

		SDL_RenderClear(gr.getRender());
	}
	
}
