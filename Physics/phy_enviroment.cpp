#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "phy_enviroment.h"

constexpr int PLAYER_WIDTH = 150;
constexpr int PLAYER_HEIGHT = 150;

void run_phy_enviro(gpRender gr){
	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;

	//Camera Initilization
	//SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	//gpRender object that is used to render object onto screen
	
	//Camera Initilization
	//SDL_Texture* tex = gr.loadImage("Assets/Objects/backgroundss.png");
	SDL_Rect camera = {ZONE_WIDTH/2 - SCREEN_WIDTH/2, ZONE_HEIGHT/2 - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_capital_ally.png");
	SDL_Rect db = {100,100,150,150};
	Sprite playerent(db, tex);
	osSprite.push_back(&playerent);


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	Sprite starent(db2, tex2);

	osSprite.push_back(&starent);


	//Ship Cruiser initilization
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db3 = {400,300,225,300};
	Sprite emyent(db3, tex3);

	osSprite.push_back(&emyent);

	SDL_Event e;
	bool gameon = true;

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());

		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
		}
		updatePosition(playerent, osSprite);

		camera.x = playerent.getX() + SCREEN_WIDTH/2 - PLAYER_WIDTH/2;
		camera.y = playerent.getY() + SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2;

		//Renders all renderable objects onto the screen
		gr.renderOnScreenEntity(osSprite, camera);
		
	}
}