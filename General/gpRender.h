

#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"

#pragma once

class gpRender{

	public:
		gpRender();
		gpRender(SDL_Renderer* sdlgr);
		~gpRender();


		void renderOnScreenEntity(std::vector<gpEntity*> osEntity);
		SDL_Texture* loadImage(std::string fname);



	private:
		SDL_Renderer* sdlgRenderer;

};