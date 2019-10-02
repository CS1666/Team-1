#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"


constexpr int MAX_SPEED = 10;


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





