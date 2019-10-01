#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;
constexpr int BOX_OBS_HEIGHT = 70;
constexpr int BOX_OBS_WIDTH = 50;
constexpr int DOT_RADIUS = 10;
constexpr int MAX_SPEED = 5;
constexpr int FPS = 60;
constexpr int frameDelay = 1000/ FPS;

// Function declarations
bool init();
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

struct NOTSDL_Circ {
	int x;
	int y;
	int r;
};

void NOTSDL_RenderFillCirc(SDL_Renderer* rend, NOTSDL_Circ* circ) {
	for (int x = -circ->r; x < circ->r; x++) {
		for (int y = -circ->r; y < circ->r; y++) {
			if ((x*x + y*y) < (circ->r * circ->r)) {
				SDL_RenderDrawPoint(rend, circ->x + x, circ->y + y);
			}
		}
	}
}

bool init() {	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	
	gWindow = SDL_CreateWindow("Basic Motion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			
	return true;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

int main() {

	Uint32 frameStart;
	int frameTime;
	//static box
	SDL_Rect staticBox = {SCREEN_WIDTH/2 + (2 * BOX_OBS_WIDTH), SCREEN_HEIGHT/2 - BOX_OBS_HEIGHT/2, BOX_OBS_WIDTH, BOX_OBS_HEIGHT};
	//static circle
	NOTSDL_Circ staticDot = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + (4 * DOT_RADIUS), DOT_RADIUS};

	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}
	
	// Current position to render the box
	// Start off with it in the middle
	int x_pos = SCREEN_WIDTH/2 - BOX_WIDTH/2;
	int y_pos = SCREEN_HEIGHT/2 - BOX_HEIGHT/2;

	// Current velocity of the box
	// Start off at reset
	int x_vel = 0;
	int y_vel = 0;

	SDL_Event e;
	bool gameon = true;
	while(gameon) {
		frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameon = false;
			}
			else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						y_vel -= MAX_SPEED;
						break;

					case SDLK_a:
						x_vel -= MAX_SPEED;
						break;

					case SDLK_s:
						y_vel += MAX_SPEED;
						break;

					case SDLK_d:
						x_vel += MAX_SPEED;
						break;
				}
			}
			else if (e.type == SDL_KEYUP) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						y_vel += MAX_SPEED;
						break;

					case SDLK_a:
						x_vel += MAX_SPEED;
						break;

					case SDLK_s:
						y_vel -= MAX_SPEED;
						break;

					case SDLK_d:
						x_vel -= MAX_SPEED;
						break;
				}
			
			}
			
		}

		// Clear black
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		//SDL_Rect fillRect = {x_pos, y_pos, BOX_WIDTH, BOX_HEIGHT};
		//SDL_RenderFillRect(gRenderer, &fillRect);		
		SDL_RenderClear(gRenderer);
		
		// Move box
		x_pos += x_vel;
		y_pos += y_vel;

		if (x_pos >= SCREEN_WIDTH - BOX_WIDTH) {
			x_pos = SCREEN_WIDTH - BOX_WIDTH;
		}
		else if (x_pos <= 0) {
			x_pos = 0;
		}
		if (y_pos >= SCREEN_HEIGHT - BOX_HEIGHT) {
			y_pos = SCREEN_HEIGHT - BOX_HEIGHT;
		}
		else if (y_pos <= 0) {
			y_pos = 0;
		}

		// Draw box
		// Cyan box
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
		SDL_Rect fillRect = {x_pos, y_pos, BOX_WIDTH, BOX_HEIGHT};
		// Yellow box
		SDL_RenderFillRect(gRenderer, &fillRect);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &staticBox);
		//green circle
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		NOTSDL_RenderFillCirc(gRenderer, &staticDot);
		
		SDL_RenderPresent(gRenderer);


		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	// Out of game loop, clean up
	close();
}
