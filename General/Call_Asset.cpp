#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../General/Sprite.h"
#include "../Physics/BasicMovementFPSlimit.h"
#include "../General/gpRender.h"
#include "Call_Asset.h"
#include "../Level_Generation/lg_enviroment.h"

using namespace std;
constexpr int PLAYER_WIDTH = 52;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;

	void Call_Asset::testOutput(gpRender gr, vector<Sprite*> osSprite, vector <pair<int, int>> randCoords){


		SDL_Texture* tex2 = gr.loadImage("Assets/Objects/red_giant.png");
		SDL_Rect db2 = {800,400,332,315};
		Sprite starent(db2, tex2);

		osSprite.push_back(&starent);

		SDL_Texture* tex3 = gr.loadImage("Assets/Objects/planetfar.png");
		SDL_Rect db3 = {randCoords[0].first,randCoords[0].second,200,200};
		Sprite planet1ent(db3, tex3);

		osSprite.push_back(&planet1ent);

		SDL_Texture* tex4 = gr.loadImage("Assets/Objects/planetmid.png");
		SDL_Rect db4 = {randCoords[1].first,randCoords[1].second+ 400,200,200};
		Sprite planet2ent(db4, tex4);

		osSprite.push_back(&planet2ent);

		SDL_Texture* tex5 = gr.loadImage("Assets/Objects/planetnear.png");
		SDL_Rect db5 = {randCoords[2].first +400,randCoords[2].second+ 700,200,200};
		Sprite planet3ent(db5, tex5);

		osSprite.push_back(&planet3ent);

		SDL_Texture* tex6 = gr.loadImage("Assets/Objects/planetnear.png");
		SDL_Rect db6 = {randCoords[3].first +1200,randCoords[3].second+ 600,200,200};
		Sprite planet4ent(db6, tex6);

		osSprite.push_back(&planet4ent);

		SDL_Texture* tex7 = gr.loadImage("Assets/Objects/planetfar.png");
		SDL_Rect db7 = {randCoords[4].first + 2000,randCoords[4].second,200,200};
		Sprite planet5ent(db7, tex7);

		osSprite.push_back(&planet5ent);

		SDL_Texture* tex8 = gr.loadImage("Assets/Objects/planetmid.png");
		SDL_Rect db8 = {randCoords[5].first + 1800,randCoords[5].second + 500,200,200};
		Sprite planet6ent(db8, tex8);

		osSprite.push_back(&planet6ent);

		SDL_Texture* tex9 = gr.loadImage("Assets/Objects/Asteroid.png");
		SDL_Rect db9 = {randCoords[6].first + 1000,randCoords[6].second + 1000,200,200};
		Sprite asteroid1ent(db9, tex9);

		osSprite.push_back(&asteroid1ent);	

		SDL_Texture* tex10 = gr.loadImage("Assets/Objects/Asteroid.png");
		SDL_Rect db10 = {randCoords[7].first + 800,randCoords[7].second + 1000,200,200};
		Sprite asteroid2ent(db10, tex10);

		osSprite.push_back(&asteroid2ent);

		SDL_Texture* tex11 = gr.loadImage("Assets/Objects/Asteroid.png");
		SDL_Rect db11 = {randCoords[8].first + 1100,randCoords[8].second + 1000,200,200};
		Sprite asteroid3ent(db11, tex11);

		osSprite.push_back(&asteroid3ent);

		SDL_Texture* tex12 = gr.loadImage("Assets/Objects/Asteroid.png");
		SDL_Rect db12 = {randCoords[9].first + 600,randCoords[9].second + 1000,200,200};
		Sprite asteroid4ent(db12, tex12);

		osSprite.push_back(&asteroid4ent);
	}
	void Call_Asset::sayHi(){
		cout<< "hi";
	}

	Call_Asset::Call_Asset(){
		sayHi();
	}