#include <SDL.h>
#include <string>
#include <vector>

#include "NSDL_Circ.h"


#pragma once


class Sprite{

	public:

		//Constructors
		Sprite();
		Sprite(SDL_Rect dBox, SDL_Texture* aTex);
		Sprite(SDL_Rect dBox, SDL_Texture* aTex, int anim);
		Sprite(SDL_Rect dBox, SDL_Texture* aTex, SDL_Rect cBox);
		Sprite(SDL_Rect dBox, SDL_Texture* aTex, SDL_Rect cBox, int anim);
		Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc);
		Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int anim);
		Sprite(const Sprite &spr);

		//Destructors
		~Sprite();

		//Needs Mover and Copier


		//Getters and Setters
		void setX(int x);
		void setY(int y);
		void setX(float x);
		int getX();
		void setY(float y);
		int getY();

		float getTrueX();
		float getTrueY();

		void setTexture(SDL_Texture* tex);
		SDL_Texture* getTexture();
		void setAngle(double new_angle);
		double getAngle();
		int getH();
		int getW();
		void setF1(int anim);
		void setF2(int anim);
		std::pair<int,int> getF();

		void updateAnimation();
		bool getAnimate();
		void setAnimate(bool toggle);
		Uint32 getAnimLastTime();
		void setAnimLastTime();

		int getRenderOrder();
		void setRenderOrder(int new_order);
		virtual void updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
		bool check_collision(SDL_Rect* a, SDL_Rect* b);
		bool check_collision(SDL_Rect* a, NSDL_Circ* b);
		bool check_collision(NSDL_Circ* a, NSDL_Circ* b);
		bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite);
		bool check_all_collisions(NSDL_Circ* a, std::vector<Sprite*> &osSprite);
		bool check_all_collisions_ships(SDL_Rect* a, std::vector<Sprite*> &osSprite);
		int getMass();
		bool getIsAI();
		bool getIsAsteroid();

		//Methods that deal with Rectangle drawn entities
		SDL_Rect* getDrawBox();
		SDL_Rect* getCollisionBox();
		bool isRectEnt();  

		//Methods that deal with Circle drawn entities
		NSDL_Circ* getCollisionCirc();
		bool isCircEnt(); 
		bool isShip();
		bool isCelestialBody();
		bool isUI();
		bool isProjectile();
		bool isHole();
		
		bool shouldRemove();
		void setRemove(bool rm);
	protected:
		SDL_Rect drawBox;
		SDL_Rect collisionBox;
		NSDL_Circ collisionCirc;
		SDL_Texture* assetTex;
		std::pair<int,int> animFrame;
		bool animate = false;
		Uint32 animLastTime = SDL_GetTicks();
		int type = 0;
		float x,y;
		bool remove = false;
		bool isAI = false;
		bool isAst = false;
		// set renderOrder for all objects
		// 0 = player ship
		// 1 = objects with collision but no gravity (all other ships + space station)
		// 2 = objects with gravity (stars, planets, astroids, etc.)
		// 3 = UI
		// 4 = black hole
		int renderOrder;
		int mass = 0;
		//Velocity variables
		//Probably should be moved to some physic related object
		float angle = 0.0;

};
