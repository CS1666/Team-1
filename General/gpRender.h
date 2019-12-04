#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Sprite.h"
#include "../General/Ship.h"



class gpRender{

	public:

		//Constructors
		gpRender();
		gpRender(const char* win_name);

		//Destructor
		~gpRender();

		//Needs Mover and Copier

		//Renders passend in entities on screen

		void renderOnScreenEntity(std::vector<Sprite*> osSprite, std::vector<Sprite*> bodies, std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed);
		
		void renderOnScreenEntity(std::vector<Sprite*> osSprite, std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed);
		void renderOnScreenEntity(std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed);

		//Renders background on screen (camera?)
		//void renderBackground(std::);

		//Loads Images into a Texture
		SDL_Texture* loadImage(std::string fname);
		SDL_Texture* loadText(std::string text);

		void setFrameStart(Uint32 tick);
		Uint32 getFrameStart();

		void setFrameTime(int nft);
		int getFrameTime();

		bool isRInit();

		int getSW();
		int getSH();
		int getFD();
		
		SDL_Renderer* getRender();
		SDL_Texture *getWall();
		int getImageWidth();
		int getImageHeight();
		
		void pushSprite(Sprite* ent);
		void checkForDeath();

		std::vector<Sprite*> get_osSprite();
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
		SDL_Texture* bgsheet;
		int image_width;
		int image_height;
		SDL_Texture *maze_wall;
		std::vector<Sprite*> osEntity;

};
