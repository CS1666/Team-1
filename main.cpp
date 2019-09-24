#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

// Function declarations
bool init();
SDL_Texture* loadImage(std::string fname);
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
		
	gWindow = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	for (auto i : gTex) {
		SDL_DestroyTexture(i);
		i = nullptr;
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}

	// Load media
	gTex.push_back(loadImage("Assets/credits.png"));
	gTex.push_back(loadImage("Assets/ai.png"));
	gTex.push_back(loadImage("Assets/cs1666_gjc26.png"));
	gTex.push_back(loadImage("Assets/CS1666_mrs185.png"));
	gTex.push_back(loadImage("Assets/CS1666_evs25.png"));
	gTex.push_back(loadImage("Assets/cs1666_jcz18.png"));
	gTex.push_back(loadImage("Assets/level-generation.png"));
	gTex.push_back(loadImage("Assets/CS1666_pjo13.png"));
	gTex.push_back(loadImage("Assets/cs1666_pep24.png"));
	gTex.push_back(loadImage("Assets/Keith C Stebler.png"));
	gTex.push_back(loadImage("Assets/physics.png"));
	gTex.push_back(loadImage("Assets/CS1666_MCD66.png"));
	gTex.push_back(loadImage("Assets/cs1666_kel177.png"));
	gTex.push_back(loadImage("Assets/CS1666_Linghai.png"));
	gTex.push_back(loadImage("Assets/CS1666_apw50.png"));
	gTex.push_back(loadImage("Assets/fin.png"));
	

	for(auto image : gTex){
		SDL_RenderClear(gRenderer);

		// Render the image
		SDL_RenderCopy(gRenderer, image, NULL, NULL);
		// Display rendering
		SDL_RenderPresent(gRenderer);
		// Wait 5 seconds
		SDL_Delay(5000);
	}

	close();
}
