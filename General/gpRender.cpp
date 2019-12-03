#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Sprite.h"
#include "gpRender.h"


//--------------------------------Constructors--------------------------------------------------
gpRender::gpRender() {};
gpRender::gpRender(const char* win_name){
	// Flag what subsystems to initialize
	// For now, just video
	//Render 2 randomly generated background layers and 2 randomly placed distant galaxies
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		isInit = false;
	}

	//Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        isInit = false;
    }

	// Set texture filtering to linear
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") && isInit ) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
		
	gWindow = SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	bgsheet = loadImage("Assets/Objects/backgroundss.png");
	
	maze_wall = loadImage("Assets/Objects/Maze_Wall.png");
};

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
};


//Method that renders images onto the window
void gpRender::renderOnScreenEntity(std::vector<Sprite*> osEntity, std::vector<Sprite *> bodies, std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed){
	//std::cout << "RenderONSE Start\n" << std::endl;
	SDL_RenderClear(gRenderer);

	

	if (camera.x - 200 < galaxies[0] && galaxies[0] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[1] && galaxies[1] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy1 = {400, 0, 200, 200};
		SDL_Rect campos = {(galaxies[0] - camera.x)/3, (galaxies[1] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy1, &campos);
	}

	if (camera.x - 200 < galaxies[2] && galaxies[2] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[3] && galaxies[3] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy2 = {400, 200, 200, 200};
		SDL_Rect campos = {(galaxies[2] - camera.x)/3, (galaxies[3] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy2, &campos);
	}

	for(int i = camera.x; i < camera.x + SCREEN_WIDTH*2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT*2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))/2, (j - camera.y - (j % 40))/2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background1[i/40][j/40], &campos);
		}
	}
	
	for(int i = camera.x; i < camera.x + SCREEN_WIDTH/2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT/2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))*2, (j - camera.y - (j % 40))*2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background2[i/40][j/40], &campos);
		}
	}

	//render gameplay objects
	for(auto entity : osEntity){
		//std::cout << "Render Start\n" << std::endl;
		//std::cout << "X: " << entity->getX() << "Y: " << entity->getY() << std::endl;
		//std::cout << "W: " << entity->getW() << "H: " << entity->getH() << std::endl;
		//To check if entity is player, player must be the first entity added
		//Also checks if camera should be fixed
		if ((entity->getRenderOrder() == 0 || entity == osEntity.at(0)) && !fixed){
			//std::cout << "Render 1" << std::endl;
			SDL_Point center;
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			SDL_Rect camcenter = {SCREEN_WIDTH/2 - entity->getW()/2, SCREEN_HEIGHT/2 - entity->getH()/2, entity->getW(), entity->getH()};
			SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &camcenter, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//check if entity within range of camera but ignores UI
		else if ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()) && entity->getRenderOrder() != 3){


			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};
			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 2" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 3" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				//std::cout << entity->getTexture() << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		}

		//check if entity within range of camera (objects with collision AND gravity)
		else if ((entity->getRenderOrder() == 2 || entity->getRenderOrder() == 0) && ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()))){
			
			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};

			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 4" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 5" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		
		}

		// checks if it's UI and render it
		if (entity->getRenderOrder() == 3){
			SDL_Point center;
			
			SDL_Rect campos = {entity->getX(), entity->getY(), entity->getW(), entity->getH()};
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			//std::cout << "Render 6" << std::endl;
			
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//std::cout << "Render End t\n" << std::endl;

	}
	
	//render gameplay objects
	for(auto entity : bodies){
		//std::cout << "Render Start\n" << std::endl;
		//std::cout << "X: " << entity->getX() << "Y: " << entity->getY() << std::endl;
		//std::cout << "W: " << entity->getW() << "H: " << entity->getH() << std::endl;
		//To check if entity is player, player must be the first entity added
		//Also checks if camera should be fixed
		if ((entity->getRenderOrder() == 0 || entity == bodies.at(0)) && !fixed){
			//std::cout << "Render 1" << std::endl;
			SDL_Point center;
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			SDL_Rect camcenter = {SCREEN_WIDTH/2 - entity->getW()/2, SCREEN_HEIGHT/2 - entity->getH()/2, entity->getW(), entity->getH()};
			SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &camcenter, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//check if entity within range of camera but ignores UI
		else if ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()) && entity->getRenderOrder() != 3){


			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};
			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 2" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 3" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				//std::cout << entity->getTexture() << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		}

		//check if entity within range of camera (objects with collision AND gravity)
		else if ((entity->getRenderOrder() == 2 || entity->getRenderOrder() == 0) && ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()))){
			
			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};

			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 4" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 5" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		
		}

		// checks if it's UI and render it
		if (entity->getRenderOrder() == 3){
			SDL_Point center;
			
			SDL_Rect campos = {entity->getX(), entity->getY(), entity->getW(), entity->getH()};
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			//std::cout << "Render 6" << std::endl;
			
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//std::cout << "Render End t\n" << std::endl;

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

	//std::cout << "RenderONSE End\n" << std::endl;
}





void gpRender::renderOnScreenEntity(std::vector<Sprite*> osEntity, std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed){
	//std::cout << "RenderONSE Start\n" << std::endl;
	SDL_RenderClear(gRenderer);

	

	if (camera.x - 200 < galaxies[0] && galaxies[0] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[1] && galaxies[1] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy1 = {400, 0, 200, 200};
		SDL_Rect campos = {(galaxies[0] - camera.x)/3, (galaxies[1] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy1, &campos);
	}

	if (camera.x - 200 < galaxies[2] && galaxies[2] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[3] && galaxies[3] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy2 = {400, 200, 200, 200};
		SDL_Rect campos = {(galaxies[2] - camera.x)/3, (galaxies[3] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy2, &campos);
	}

	for(int i = camera.x; i < camera.x + SCREEN_WIDTH*2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT*2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))/2, (j - camera.y - (j % 40))/2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background1[i/40][j/40], &campos);
		}
	}
	
	for(int i = camera.x; i < camera.x + SCREEN_WIDTH/2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT/2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))*2, (j - camera.y - (j % 40))*2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background2[i/40][j/40], &campos);
		}
	}

	//render gameplay objects
	for(auto entity : osEntity){
		//std::cout << "Render Start\n" << std::endl;
		//std::cout << "X: " << entity->getX() << "Y: " << entity->getY() << std::endl;
		//std::cout << "W: " << entity->getW() << "H: " << entity->getH() << std::endl;
		//To check if entity is player, player must be the first entity added
		//Also checks if camera should be fixed
		if ((entity->getRenderOrder() == 0 || entity == osEntity.at(0)) && !fixed){
			//std::cout << "Render 1" << std::endl;
			SDL_Point center;
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			SDL_Rect camcenter = {SCREEN_WIDTH/2 - entity->getW()/2, SCREEN_HEIGHT/2 - entity->getH()/2, entity->getW(), entity->getH()};
			SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &camcenter, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//check if entity within range of camera but ignores UI
		else if ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()) && entity->getRenderOrder() != 3){


			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};
			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 2" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 3" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				//std::cout << entity->getTexture() << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		}

		//check if entity within range of camera (objects with collision AND gravity)
		else if ((entity->getRenderOrder() == 2 || entity->getRenderOrder() == 0) && ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()))){
			
			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};

			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 4" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 5" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		
		}

		// checks if it's UI and render it
		if (entity->getRenderOrder() == 3){
			SDL_Point center;
			
			SDL_Rect campos = {entity->getX(), entity->getY(), entity->getW(), entity->getH()};
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			//std::cout << "Render 6" << std::endl;
			
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//std::cout << "Render End t\n" << std::endl;

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

	//std::cout << "RenderONSE End\n" << std::endl;
}

void gpRender::renderOnScreenEntity(std::vector<int> galaxies, std::vector<std::vector<SDL_Rect*> > background1, std::vector<std::vector<SDL_Rect*> > background2, SDL_Rect camera, bool fixed){
	//std::cout << "RenderONSE Start\n" << std::endl;
	SDL_RenderClear(gRenderer);

	

	if (camera.x - 200 < galaxies[0] && galaxies[0] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[1] && galaxies[1] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy1 = {400, 0, 200, 200};
		SDL_Rect campos = {(galaxies[0] - camera.x)/3, (galaxies[1] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy1, &campos);
	}

	if (camera.x - 200 < galaxies[2] && galaxies[2] < camera.x + SCREEN_WIDTH*3 &&
		camera.y - 200 < galaxies[3] && galaxies[3] < camera.x + SCREEN_WIDTH*3){
		SDL_Rect galaxy2 = {400, 200, 200, 200};
		SDL_Rect campos = {(galaxies[2] - camera.x)/3, (galaxies[3] - camera.y)/3, 50, 50};
		SDL_RenderCopy(gRenderer, bgsheet, &galaxy2, &campos);
	}

	for(int i = camera.x; i < camera.x + SCREEN_WIDTH*2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT*2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))/2, (j - camera.y - (j % 40))/2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background1[i/40][j/40], &campos);
		}
	}
	
	for(int i = camera.x; i < camera.x + SCREEN_WIDTH/2; i+=40){
		for (int j = camera.y; j < camera.y + SCREEN_HEIGHT/2; j+=40){
			SDL_Rect campos = {(i - camera.x - (i % 40))*2, (j - camera.y - (j % 40))*2, 40, 40};
			SDL_RenderCopy(gRenderer, bgsheet, background2[i/40][j/40], &campos);
		}
	}

	//render gameplay objects
	for(auto entity : osEntity){
		//std::cout << "Render Start\n" << std::endl;
		//std::cout << "X: " << entity->getX() << "Y: " << entity->getY() << std::endl;
		//std::cout << "W: " << entity->getW() << "H: " << entity->getH() << std::endl;
		//To check if entity is player, player must be the first entity added
		//Also checks if camera should be fixed
		if ((entity->getRenderOrder() == 0 || entity == osEntity.at(0)) && !fixed){
			//std::cout << "Render 1" << std::endl;
			SDL_Point center;
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			SDL_Rect camcenter = {SCREEN_WIDTH/2 - entity->getW()/2, SCREEN_HEIGHT/2 - entity->getH()/2, entity->getW(), entity->getH()};
			SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &camcenter, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//check if entity within range of camera but ignores UI
		else if ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()) && entity->getRenderOrder() != 3){


			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};
			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 2" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 3" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				//std::cout << entity->getTexture() << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		}

		//check if entity within range of camera (objects with collision AND gravity)
		else if ((entity->getRenderOrder() == 2 || entity->getRenderOrder() == 0) && ((camera.x - entity->getW() < entity->getX()) && (entity->getX() < camera.x + SCREEN_WIDTH + entity->getW()) && 
			(camera.y - entity->getH() < entity->getY()) && (entity->getY() < camera.y + SCREEN_HEIGHT + entity->getH()))){
			
			SDL_Rect campos = {entity->getX() - camera.x, entity->getY() - camera.y, entity->getW(), entity->getH()};

			SDL_Point center;
		
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			if(entity->getF().second < 0){
				//std::cout << "Render 4" << std::endl;
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
			}
			else{
				//std::cout << "Render 5" << std::endl;
				SDL_Rect animBox = {entity->getF().first * entity->getW(), entity->getF().second * entity->getH(), entity->getW(), entity->getH()};
				SDL_RenderCopyEx(gRenderer, entity->getTexture(), &animBox, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);		
			}
		
		}

		// checks if it's UI and render it
		if (entity->getRenderOrder() == 3){
			SDL_Point center;
			
			SDL_Rect campos = {entity->getX(), entity->getY(), entity->getW(), entity->getH()};
			center.x = entity->getW()/2;
			center.y = entity->getH()/2;
			//std::cout << "Render 6" << std::endl;
			
			SDL_RenderCopyEx(gRenderer, entity->getTexture(), nullptr, &campos, entity->getAngle(), &center, SDL_FLIP_NONE);
		}

		//std::cout << "Render End t\n" << std::endl;

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

	//std::cout << "RenderONSE End\n" << std::endl;
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

	image_width = startSurf->w;
	image_height = startSurf->h;
	
	SDL_FreeSurface(startSurf);

	return newText;
}

SDL_Texture* gpRender::loadText(std::string text)
{
	TTF_Init();
	SDL_Texture* newText = nullptr;
	SDL_Color color = {255, 255, 255};
	TTF_Font *font = TTF_OpenFont("Assets/OpenSans-Bold.ttf", 20);
	if(font == nullptr)
	{
		std::cout << "Failed to load font." << std::endl 
			<< "SDL_ttf Error: " << TTF_GetError() << std::endl;
		return nullptr;
	}


	SDL_Surface* startSurf = TTF_RenderText_Solid(font, text.c_str(), color);
	if (startSurf == nullptr) {
		std::cout << "Unable to render text surface." << endl
		<< "SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from text."
		<<  "SDL Error: " << SDL_GetError() << std::endl;
	}

	image_width = startSurf->w;
	image_height = startSurf->h;

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

SDL_Renderer* gpRender::getRender(){
	return gRenderer;
}

int gpRender::getImageWidth()
{
	return image_width;
}

int gpRender::getImageHeight()
{
	return image_height;
}

SDL_Texture* gpRender::getWall()
{
	return maze_wall;
}

void gpRender::pushSprite(Sprite * ent)
{
	osEntity.push_back(ent);
}

void gpRender::checkForDeath()
{
	for(std::size_t j = 0; j != osEntity.size(); j++){
		Sprite* ent = osEntity.at(j);
		if(ent->getRenderOrder() == 1) //check only if it is a ship
		{
			if(dynamic_cast<Ship*>(ent)->getCurrHp() <=0)
			{
				osEntity.erase(osEntity.begin()+j);
			}
		}
	}
}
std::vector<Sprite*> gpRender::get_osSprite()
{
	return osEntity;
}
