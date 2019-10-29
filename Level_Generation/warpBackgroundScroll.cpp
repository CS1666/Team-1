#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

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

// For the Ship
//SDL_Rect gShipRect = {0, 0, TILE_SIZE, TILE_SIZE};
// For the plane
//SDL_Rect gShipRect = {TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
// For the UFO
//SDL_Rect gShipRect = {0, TILE_SIZE, TILE_SIZE, TILE_SIZE};
// For the helicopter
SDL_Rect gShipRect = {TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE};

bool init() {	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	
	gWindow = SDL_CreateWindow("Simple BG scroll", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CAM_WIDTH, CAM_HEIGHT, SDL_WINDOW_SHOWN);
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

int backgroundWarpMovement() {
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
	
	SDL_Event e;
	bool gameon = true;
	while(gameon) {
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameon = false;
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
		scroll_offset++;
		if (scroll_offset > CAM_HEIGHT)
			scroll_offset = 0;		//might be wrong
		bgRect.y = scroll_offset;
		SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);
		bgRect.y += CAM_HEIGHT;
		SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

		// Draw the Ship
		SDL_RenderCopy(gRenderer, gShipSheet, &gShipRect, &moveBox);

		SDL_RenderPresent(gRenderer);
	}

	close();
}
