#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"
#include "gpRender.h"

//--------------------------------Constructors--------------------------------------------------
gpRender::gpRender() {};
gpRender::gpRender(const char* win_name){
	// Flag what subsystems to initialize
	// For now, just video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		isInit = false;
	}

	// Set texture filtering to linear
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") && isInit ) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
		
	gWindow = SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr && isInit) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		isInit = false;
	}

	/* Create a renderer for our window
	 * Use hardware acceleration (last arg)
	 * Choose first driver that can provide hardware acceleration
	 *   (second arg, -1)
	 */
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr && isInit) {	
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		isInit =  false;
	}

	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			
	// Initialize PNG loading via SDL_image extension library
	int imgFlags = IMG_INIT_PNG;
	int retFlags = IMG_Init(imgFlags);

	if(retFlags != imgFlags && isInit) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		isInit =  false;
	}
};

//--------------------------------Destructors---------------------------------------------------
gpRender::~gpRender(){

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	if(gWindow != nullptr){
		SDL_DestroyWindow(gWindow);
		gWindow = nullptr;
	}
	
	
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
};


//Method that renders images onto the window
void gpRender::renderOnScreenEntity(std::vector<gpEntity*> osEntity, SDL_Rect camera){
	
	int d;
	int c;
	SDL_Rect cur_out;
	SDL_Rect bgtile[16];
	//SDL_Rect bgzonelayer1[ZONE_WIDTH/100 * ZONE_HEIGHT/100];
	
	SDL_Texture* bgsheet = loadImage("Assets/Objects/backgroundss.png");

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			bgtile[x + 4*y].x = x * 100;
			bgtile[x + 4*y].y = y * 100;
			bgtile[x + 4*y].w = 100;
			bgtile[x + 4*y].h = 100;
		}
	}
	SDL_RenderClear(gRenderer);

	d = 0;
	while (d * 100 < SCREEN_HEIGHT) {
		c = 0;
		while (c * 100 < SCREEN_WIDTH) {
			cur_out = {camera.x + (c * 100), camera.y + (d * 100), 100, 100};
			SDL_RenderCopy(gRenderer, bgsheet, &bgtile[c % 16], &cur_out);
			c += 1;
		}
		d+= 1;
	}
	
	for(auto entity : osEntity){

		//To check if entity is player, player must be the first entity added
		if (entity == osEntity.at(0)){
			SDL_Point center;
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			SDL_Rect camcenter = {SCREEN_WIDTH/2 - entity->getW()/2, SCREEN_HEIGHT/2 - entity->getH()/2, entity->getW(), entity->getH()};
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &camcenter, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//check if entity within range of camera
		else if ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH())){
			
			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};

			SDL_Point center;
			if (entity->isRectEnt()){
				center.x = entity->getW()/2;
				center.y = entity->getH()/2;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
				
			}
			else if(entity->isCircEnt()){
				entity->getDrawCirc()->RenderFillCirc(gRenderer);
			}
		}
	}
	SDL_RenderPresent(gRenderer);

	//If you are using new functionality
	if(gWindow != nullptr){
		setFrameTime(SDL_GetTicks() - frameStart);

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}


///Provided method that loads Images
SDL_Texture* gpRender::loadImage(std::string fname) {
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



void gpRender::setFrameStart(Uint32 tick){

	frameStart = tick;
};
Uint32 gpRender::getFrameStart(){
	return frameStart;
}

void gpRender::setFrameTime(int nft){
	frameTime = nft;
}
int gpRender::getFrameTime(){
	return frameTime;
}

bool gpRender::isRInit(){
	return isInit;
}


int gpRender::getSW(){
	return SCREEN_WIDTH;
}
int gpRender::getSH(){
	return SCREEN_HEIGHT;
}
int gpRender::getFD(){
	return frameDelay;
}

SDL_Renderer* gpRender::getRender(){
	return gRenderer;
}
