#include <SDL.h>
#include "NSDL_Circ.h"

#pragma once



class gpEntity{

	public:

		//Constructors
		gpEntity();
		gpEntity(SDL_Rect dBox, SDL_Texture* aTex);
		gpEntity(NSDL_Circ dCirc, SDL_Texture* aTex);

		//Destructors
		~gpEntity();

		//Needs Mover and Copier


		//Getters and Setters
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		void setR(int new_r);
		int getR();
		void setTexture(SDL_Texture* tex);
		SDL_Texture* getTexture();

		//Velocity Setters and getters
		//Probably should be moved to some physic related object
		void setVX(int new_vx);
		int getVX();
		void setVY(int new_vy);
		int getVY();

		
		//Methods that deal with Rectangle drawn entities
		SDL_Rect* getDrawBox();
		void updateDrawBox();
		bool isRectEnt();  

		//Methods that deal with Circle drawn entities
		NSDL_Circ* getDrawCirc();
		void updateDrawCirc();
		bool isCircEnt(); 

		//Should be collision functionss
		void handelEntityOB(int sw, int sh);

	private:

		SDL_Rect drawBox;
		NSDL_Circ drawCirc;
		SDL_Texture* assetTex;

		//Velocity variables
		//Probably should be moved to some physic related object
		int vx =0;
		int vy = 0; 
	

};
