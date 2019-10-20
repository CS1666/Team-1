#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "ai_enviroment.h"
#include "AI.h"
#include "../General/Ship.h"
#include "Queue.h"
#include "../General/Sector.h"
using namespace std;

constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 1280; 
constexpr int ZONE_HEIGHT = 720;

void run_ai_enviro(gpRender gr){


	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite;
	//note: maybe merge positions and osSprite?
	vector<vector<int>> positions;
	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool fixed = true;

	//gpRender object that is used to render object onto screen

	//Ship object init
	Ship aiShip;
//testing for queue
    Queue test=Queue(5);
    std::cout << test.push(65) << endl; //A
    cout << test.push(66) << endl; //B
    cout<<test.push(67)<<endl; // C
    cout<<test.push(69)<<endl; // E
    cout<<test.push(73)<<endl; // I
    cout<<test.push(44)<<endl; //idk but wont be added
    cout <<test.getSize() <<endl; //5
    cout << test.pop() <<endl; //A
    cout<<test.getSize()<<endl; //4
    cout<<test.pop()<<endl; // B
    cout<<test.pop()<<endl; // C
    cout<<test.pop()<<endl; // E
    cout<<test.getSize()<<endl; //1
    cout<<test.pop()<<endl; //I
    cout<<test.pop()<<endl; //0/blank
    cout<<test.getSize()<<endl; //0
	//AI init

	AI ai;

	aiShip.setSprite("Assets/Objects/ship_capital_ally.png");
	aiShip.setPosition({10, 10});
	aiShip.setDestination({600, 325});

	SDL_Texture* tex = gr.loadImage(aiShip.getSprite());
	//SDL_Rect db = {50,325,75,75};
	SDL_Rect db = {10,10,PLAYER_WIDTH,PLAYER_HEIGHT};

	Sprite playerent(db, tex);
	osSprite.push_back(&playerent);

	//positions = gameState, only track the ship for now
	//destination is also a vector
	positions.push_back({10,10});

	vector<int> destination={325,325};


	//Red giant Initilzation-
	SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
	SDL_Rect db2 = {500,200,300,300};
	Sprite starent(db2, tex2);

	osSprite.push_back(&starent);

	SDL_Rect bgtile1[400];
	SDL_Rect bgtile2[100];
	std::vector<std::vector<SDL_Rect*> > bgzonelayer1( ZONE_WIDTH/20 , std::vector<SDL_Rect*> (ZONE_HEIGHT/20, 0));
	std::vector<std::vector<SDL_Rect*> > bgzonelayer2( ZONE_WIDTH/40 , std::vector<SDL_Rect*> (ZONE_HEIGHT/40, 0));


	Star star;

	star.setSize({300, 300});
	star.setPosition({500, 200});

	Sector sector;

	sector.setSize({1280, 720});
	sector.setStars({star});

	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			bgtile1[x + 20*y].x = x * 20;
			bgtile1[x + 20*y].y = y * 20;
			bgtile1[x + 20*y].w = 20;
			bgtile1[x + 20*y].h = 20;
		}
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			bgtile2[x + 40*y].x = x * 40;
			bgtile2[x + 40*y].y = y * 40;
			bgtile2[x + 40*y].w = 40;
			bgtile2[x + 40*y].h = 40;
		}
	}

	SDL_Event e;
	bool gameon = true;
	//int animation = 0;
	//bool cycle;
	//bool animate;
	//Uint32 anim_last_time = SDL_GetTicks();

	//Game Loop
	while(gameon) {
		gr.setFrameStart(SDL_GetTicks());
		if(ai.checkMapState(positions))
		{
			ai.createMapState(sector);
			//I think these were causing errors
		    //aiShip.setPath(ai.calculatePath(aiShip,destination));
		    //aiShip.followPath();
		}
		//Handles all incoming Key events
		while(SDL_PollEvent(&e)) {
			gameon = handleKeyEvents(e, playerent);	
			/*switch(e.key.keysym.sym) {
				case SDLK_w:
					if(e.type == SDL_KEYDOWN){
						animate = true;
					}
					else if (e.type == SDL_KEYUP){
						animate = false;
					}
					break;
			}*/
		}

		updatePosition(playerent, osSprite, ZONE_WIDTH, ZONE_HEIGHT);

		/*if (animate){
			if (SDL_GetTicks() - anim_last_time > 150) {
				if (animation == 0){
					cycle = true;
				}
				else if(animation == 3){
					cycle = false;
				}
				
				if (cycle){
					animation++;
				}
				else{
					animation--;
				}
				
				anim_last_time = SDL_GetTicks();
				playerent.setF(animation);
			}
		}
		else{
			animation = 0;
			playerent.setF(animation);
		}*/
		

		//Renders all renderable objects onto the screen

		gr.renderOnScreenEntity(osSprite, bgzonelayer1, bgzonelayer2, camera, fixed);
	}
}
