#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"
#include "gpRender.h"

//--------------------------------Constructors--------------------------------------------------
gpRender::gpRender(){
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
		
	gWindow = SDL_CreateWindow("A DEMO!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

gpRender::gpRender(SDL_Renderer* sdlgr) : gRenderer{sdlgr}, gWindow{nullptr} {};
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
}


//Method that renders images onto the window
void gpRender::renderOnScreenEntity(std::vector<gpEntity*> osEntity){
	SDL_RenderClear(gRenderer);
	for(auto entity : osEntity){
		
		SDL_Point center;
		if (entity->isRectEnt()){
			center.x = entity->getX()/2;
			center.y = entity->getY()/2;
			SDL_RenderCopyEx(sdlgRenderer, entity->getTexture(), nullptr, entity->getDrawBox(), entity->getAngle(), &center, SDL_FLIP_NONE);
			
		}
		else if(entity->isCircEnt()){
			entity->getDrawCirc()->RenderFillCirc(gRenderer);
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


