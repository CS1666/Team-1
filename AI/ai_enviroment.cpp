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

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 1280; 
constexpr int ZONE_HEIGHT = 720;

void run_ai_enviro(gpRender gr){


	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;

	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = true;

	//gpRender object that is used to render object onto screen
	
	//Ship object init
	Ship aiShip;

	//AI init

	AI ai;

	aiShip.setSprite("Assets/Objects/ship_capital_ally.png");

	SDL_Texture* tex = gr.loadImage(aiShip.getSprite());
	//SDL_Rect db = {50,325,75,75};
	SDL_Rect db = {10,10,PLAYER_WIDTH,PLAYER_HEIGHT};

	Sprite playerent(db, tex);
	osSprite.push_back(&playerent);


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {500,200,300,300};
	Sprite starent(db2, tex2);

	osSprite.push_back(&starent);

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
		gr.renderOnScreenEntity(osSprite, camera, fixed);
		
	}
}