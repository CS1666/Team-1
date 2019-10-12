#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "demo.h"

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;

void run_demo(gpRender gr){
	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;

	//Camera Initilization
	//SDL_Texture* tex = gr.loadImage("Assets/Objects/backgroundss.png");
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = false;

	//Player Entity Initilizaiton
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/ship_capital_ally.png");
	SDL_Rect db2 = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	Sprite playerent(db2, tex2);
	osSprite.push_back(&playerent);

	
	//Red giant Initilzation-
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db3 = {800,400,332,315};
	Sprite starent(db3, tex3);

	osSprite.push_back(&starent);

	/*
	//Ship Cruiser initilization
	SDL_Texture* tex4 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db4 = {400,300,225,300};
	Sprite emyent(db4, tex4);

	osEntity.push_back(&emyent);
	*/
	//Background initilization
	/*SDL_Texture* bgsheet = gr.loadImage("Assets/Objects/backgroundss.png");
	SDL_Rect bgtile[16];

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			bgtile[x + 4*y].x = x * 100;
			bgtile[x + 4*y].y = y * 100;
			bgtile[x + 4*y].w = 100;
			bgtile[x + 4*y].h = 100;
		}
	}*/

	SDL_Event e;
	bool gameon = true;

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());

		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
		}
		updatePosition(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);

	

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
		gr.renderOnScreenEntity(osSprite, camera, fixed);
		
	}
}