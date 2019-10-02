#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"
#include "gpRender.h"

gpRender::gpRender(): sdlgRenderer{nullptr} {};
gpRender::gpRender(SDL_Renderer* sdlgr) : sdlgRenderer{sdlgr} {};
gpRender::~gpRender(){

	SDL_DestroyRenderer(sdlgRenderer);
	sdlgRenderer = nullptr;
}


void gpRender::renderOnScreenEntity(std::vector<gpEntity*> osEntity){
	SDL_RenderClear(sdlgRenderer);
	for(auto entity : osEntity){
		
	
		if (entity->isRectEnt()){
			SDL_RenderCopy(sdlgRenderer, entity->getTexture(), NULL, entity->getDrawBox());
			
		}
		else if(entity->isCircEnt()){
			entity->getDrawCirc()->RenderFillCirc(sdlgRenderer);
		}
		
		SDL_RenderPresent(sdlgRenderer);

	}

	

}
SDL_Texture* gpRender::loadImage(std::string fname) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(sdlgRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

