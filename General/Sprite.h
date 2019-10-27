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
		void setF(int anim);
		int getF();

		int getRenderOrder();
		void setRenderOrder(int new_order);

		
		//Methods that deal with Rectangle drawn entities
		SDL_Rect* getDrawBox();
		bool isRectEnt();  

		//Methods that deal with Circle drawn entities
		NSDL_Circ* getDrawCirc();
		bool isCircEnt(); 

	

	protected:
		SDL_Rect drawBox;
		NSDL_Circ drawCirc;
		SDL_Texture* assetTex;
		int animFrame;
		float x,y;
		int renderOrder;

		//Velocity variables
		//Probably should be moved to some physic related object
		float angle = 0.0;

};
