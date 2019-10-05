

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

		void setFrameStart(Uint32 tick);
		Uint32 getFrameStart();

		void setFrameTime(int nft);
		int getFrameTime();

		bool isRInit();

		int getSW();
		int getSH();
		int getFD();



	private:
		SDL_Renderer* gRenderer;
		SDL_Window* gWindow;
		bool isInit = true;
		Uint32 frameStart;
		int frameTime;
		int SCREEN_WIDTH = 1280;
		int SCREEN_HEIGHT = 720;
		int FPS = 60;
		int frameDelay = 1000/ FPS;
		
};