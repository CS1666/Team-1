

#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"

#pragma once

class gpRender{

	public:

		//Constructors
		gpRender();
		gpRender(SDL_Renderer* sdlgr);

		//Destructor
		~gpRender();

		//Needs Mover and Copier

		//Renders passend in entities on screen
		void renderOnScreenEntity(std::vector<gpEntity*> osEntity);

		//Loads Images into a Texture
		SDL_Texture* loadImage(std::string fname);



	private:
		SDL_Renderer* sdlgRenderer;

};