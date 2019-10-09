#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/gpEntity.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "ai_enviroment.h"
#include "AI.h"
#include "../General/Ship.h"


void run_ai_enviro(gpRender gr){


	//Vector used to store all on screen entities

	std::vector<gpEntity*> osEntity;

	

	//gpRender object that is used to render object onto screen
	
	//Ship object init
	Ship aiShip;

	//AI init

	AI ai;

	aiShip.setSprite("Assets/Objects/ship_capital_ally.png");

	SDL_Texture* tex = gr.loadImage(aiShip.getSprite());
	SDL_Rect db = {50,50,75,75};

	gpEntity playerent(db, tex);
	osEntity.push_back(&playerent);


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {800,400,332,315};
	gpEntity starent(db2, tex2);

	osEntity.push_back(&starent);


	//Ship Cruiser initilization
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db3 = {400,300,225,300};
	gpEntity emyent(db3, tex3);

	osEntity.push_back(&emyent);

	SDL_Event e;
	bool gameon = true;

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());

		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
		}
		updatePosition(playerent, osEntity);

		//---------------COLLISION SHOULD BE HANDLED HERE------------------------
		//Adjusts the players entities pos based on interal values
		playerent.handelEntityOB(gr.getSW(), gr.getSH());
		//---------------COLLISION SHOULD BE HANDLED HERE------------------------

		//Renders all renderable objects onto the screen
		gr.renderOnScreenEntity(osEntity);
		
	}
}