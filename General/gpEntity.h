#include <SDL.h>
#include "NSDL_Circ.h"

#pragma once



class gpEntity{

	public:

		//Constructors
		gpEntity();
		gpEntity(SDL_Rect dBox, SDL_Texture* aTex);
		gpEntity(NSDL_Circ dCirc, SDL_Texture* aTex);
		~gpEntity();


		//Getters and Setters
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		void setVX(int new_vx);
		int getVX();
		void setVY(int new_vy);
		int getVY();

		

		SDL_Rect* getDrawBox();
		void updateDrawBox();
		bool isRectEnt();  

		NSDL_Circ* getDrawCirc();
		void updateDrawCirc();
		bool isCircEnt(); 

		void setR(int new_r);
		int getR();
		
		void setTexture(SDL_Texture* tex);
		SDL_Texture* getTexture();
		void handelEntityPos(int sw, int sh);

	private:

		SDL_Rect drawBox;
		NSDL_Circ drawCirc;
		SDL_Texture* assetTex;
		int vx =0;
		int vy = 0; 
	

};
