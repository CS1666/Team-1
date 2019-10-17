#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "lg_enviroment.h"


//#define POISSON_PROGRESS_INDICATOR 1
//#include "PoissonGenerator.h"


constexpr int PLAYER_WIDTH = 52;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
//Ideal #s can/should be worked out later
//constexpr int NumPoints = 24;
//lay out the "zone" in which the objects will spawn, should be < w*h
//"spawn zone" = ImageSize * ImageSize
//constexpr int ImageSize  = 2160;  

/*int mPoissonGen( int argc, char** argv)
{

	PoissonGenerator::DefaultPRNG PRNG;

	const auto Points = PoissonGenerator::generatePoissonPoints( NumPoints, PRNG );

	std::vector<std::pair<float,float>> Coords;
	for(int k = 0; k < 2; k++)
    for(int i = -1; i < 2; i += 2)
        for(int j = -1; j < 2; j+= 2)
            Coords.push_back(std::make_pair(i * (k+1), j * (((k + 1) % 2) + 1)));


	return 0;
}
*/

void run_lg_enviro(gpRender gr){

	
	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;
	
	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = false;


	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_player.png");
	SDL_Rect db = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	Sprite playerent(db, tex, 0);
	osSprite.push_back(&playerent);


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	Sprite starent(db2, tex2);

	osSprite.push_back(&starent);

	
		//SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
		//SDL_Rect db3 = {};


	//Ship Cruiser initilization
	//SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	//SDL_Rect db3 = {400,300,225,300};
	//Sprite emyent(db3, tex3);

	//osSprite.push_back(&emyent);

	SDL_Rect bgtile1[400];
	SDL_Rect bgtile2[100];
	std::vector<std::vector<SDL_Rect*> > bgzonelayer1( ZONE_WIDTH/20 , std::vector<SDL_Rect*> (ZONE_HEIGHT/20, 0));
	std::vector<std::vector<SDL_Rect*> > bgzonelayer2( ZONE_WIDTH/40 , std::vector<SDL_Rect*> (ZONE_HEIGHT/40, 0));

	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			bgtile1[x + 20*y].x = x * 20;
			bgtile1[x + 20*y].y = y * 20;
			bgtile1[x + 20*y].w = 20;
			bgtile1[x + 20*y].h = 20;
		}
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			bgtile2[x + 40*y].x = x * 40;
			bgtile2[x + 40*y].y = y * 40;
			bgtile2[x + 40*y].w = 40;
			bgtile2[x + 40*y].h = 40;
		}
	}

	for (int x = 0; x < ZONE_WIDTH/20; x++) {
		for (int y = 0; y < ZONE_HEIGHT/20; y++) {
			bgzonelayer1[x][y] = &bgtile1[rand() % 400];
		}
	}

	for (int x = 0; x < ZONE_WIDTH/40; x++) {
		for (int y = 0; y < ZONE_HEIGHT/40; y++) {
			bgzonelayer2[x][y] = &bgtile2[rand() % 100];
		}
	}

	SDL_Event e;
	bool gameon = true;
	int animation = 0;
	bool cycle;
	bool animate;
	Uint32 anim_last_time = SDL_GetTicks();

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());

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


		updatePosition(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);

		if (animate){
			if (SDL_GetTicks() - anim_last_time > 150) {
				if (animation == 0){
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
				
				anim_last_time = SDL_GetTicks();
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
		gr.renderOnScreenEntity(osSprite, bgzonelayer1, bgzonelayer2, camera, fixed);
		
	}
}