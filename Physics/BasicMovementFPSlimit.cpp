#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"
constexpr int MAX_SPEED = 10;

//NOTE: File should probably be renamed and moved to general. This deals more with handling key inputs than
//      actual movements


//General wrapper function to handle Key evenets
bool handleKeyEvents(SDL_Event e, gpEntity &ent){
	if (e.type == SDL_QUIT) {
		return  false;
	}
	else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		handleKeyDownEvent(e, ent);
	}
	else if(e.type == SDL_KEYUP){
		handleKeyUpEvent(e, ent);
	}

	return true;
	
}

//Handles Up Key Events
void handleKeyUpEvent(SDL_Event e, gpEntity &ent){
	if(e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
			case SDLK_w:
				//std::cout <<  (ent.getVY() - MAX_SPEED) << std::endl;
				//if(ent.getVY() != 0){
					ent.setVY(ent.getVY() + MAX_SPEED);
				//}
				
				break;

			case SDLK_a:
				//if(ent.getVX() != 0){
					ent.setVX(ent.getVX() + MAX_SPEED);
				//}
				break;

			case SDLK_s:
				//if(ent.getVY() != 0){
					ent.setVY(ent.getVY() - MAX_SPEED);
				//}
				break;

			case SDLK_d:
				//if(ent.getVX() != 0){
					ent.setVX(ent.getVX() - MAX_SPEED);
				//}
				break;
		}
	}
}

//Handles down Key Events
void handleKeyDownEvent(SDL_Event e, gpEntity &ent){
	
		switch(e.key.keysym.sym) {
			case SDLK_w:
				
				ent.setVY(ent.getVY() - MAX_SPEED);
			
				
				break;

			case SDLK_a:

				ent.setVX(ent.getVX() - MAX_SPEED);
				
				break;

			case SDLK_s:
			
				ent.setVY(ent.getVY() + MAX_SPEED);
			
				break;

			case SDLK_d:
				
				ent.setVX(ent.getVX() + MAX_SPEED);
				
				break;
		
	}
}





