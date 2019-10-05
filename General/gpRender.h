

#include <SDL.h>
#include <SDL_image.h>
#include "gpEntity.h"

#pragma once

constexpr int gSCREEN_WIDTH = 1280;
constexpr int gSCREEN_HEIGHT = 720;
constexpr int gFPS = 60;
constexpr int gframeDelay = 1000/ gFPS;
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




	private:
		SDL_Renderer* gRenderer;
		SDL_Window* gWindow;
		bool isInit = true;
		Uint32 frameStart;
		int frameTime;
		
};