#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "General/gpEntity.h"
#include "Physics/BasicMovementFPSlimit.h"
#include "General/gpRender.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int FPS = 60;
constexpr int frameDelay = 1000/ FPS;

// Function declarations
bool init();

void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
std::vector<SDL_Texture*> gTex;

bool init() {	
	// Flag what subsystems to initialize
	// For now, just video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Set texture filtering to linear
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
		
	gWindow = SDL_CreateWindow("A DEMO!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	/* Create a renderer for our window
	 * Use hardware acceleration (last arg)
	 * Choose first driver that can provide hardware acceleration
	 *   (second arg, -1)
	 */
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr) {	
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			
	// Initialize PNG loading via SDL_image extension library
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);
	if(retFlags != imgFlags) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	
	return true;
}

void close() {
	for (auto i : gTex) {
		SDL_DestroyTexture(i);
		i = nullptr;
	}

	
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main() {

	//Frame timiers
	Uint32 frameStart;
	int frameTime;

	//Vector used to store all on screen entities

	std::vector<gpEntity*> osEntity;
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}

	//gpRender object that is used to render object onto screen
	gpRender gr(gRenderer);


	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_capital_ally.png");
	SDL_Rect db = {100,100,150,150};
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
		frameStart = SDL_GetTicks();

		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
		}
		updatePosition(playerent);

		//---------------COLLISION SHOULD BE HANDLED HERE------------------------
		//Adjusts the players entities pos based on interal values
		playerent.handelEntityOB(SCREEN_WIDTH, SCREEN_HEIGHT);
		//---------------COLLISION SHOULD BE HANDLED HERE------------------------

		//Renders all renderable objects onto the screen
		gr.renderOnScreenEntity(osEntity);
	
		//Calculates when the next frame should be drawn
		//Likely reason for image studdering
		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	close();
}



//I moved credit sequence down here til we can integrate into the gamre 

/**
	gTex.push_back(loadImage("Assets/Credits/credits.png"));
	gTex.push_back(loadImage("Assets/Credits/ai.png"));
	gTex.push_back(loadImage("Assets/Credits/cs1666_gjc26.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_mrs185.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_evs25.png"));
	gTex.push_back(loadImage("Assets/Credits/cs1666_jcz18.png"));
	gTex.push_back(loadImage("Assets/Credits/level-generation.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_pjo13.png"));
	gTex.push_back(loadImage("Assets/Credits/cs1666_pep24.png"));
	gTex.push_back(loadImage("Assets/Credits/Keith C Stebler.png"));
	gTex.push_back(loadImage("Assets/Credits/physics.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_MCD66.png"));
	gTex.push_back(loadImage("Assets/Credits/cs1666_kel117.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_Linghai.png"));
	gTex.push_back(loadImage("Assets/Credits/CS1666_apw50.png"));
	gTex.push_back(loadImage("Assets/Credits/fin.png"));
	

	for(auto image : gTex){
		SDL_RenderClear(gRenderer);

		// Render the image
		SDL_RenderCopy(gRenderer, image, NULL, NULL);
		// Display rendering
		SDL_RenderPresent(gRenderer);
		// Wait 5 seconds
		SDL_Delay(5000);

	}

**/
