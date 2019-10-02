#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"


constexpr int MAX_SPEED = 5;
/**struct NOTSDL_Circ {
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
}**/


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





