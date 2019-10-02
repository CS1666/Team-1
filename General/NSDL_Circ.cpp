
#include <SDL.h>
#include "NSDL_Circ.h"
	
	//-------------------------------Constructors-----------------------------------------------
	NSDL_Circ::NSDL_Circ() : x{0}, y{0}, r{0} {};
	NSDL_Circ::NSDL_Circ(int nx, int ny,  int nr): x{nx}, y{ny}, r{nr} {};

	//-------------------------------Destructors------------------------------------------------
	NSDL_Circ::~NSDL_Circ() {};



	//-----------------------------Getters and Setters-------------------------------------------
	int  NSDL_Circ::getX(){
		return x;
	}

	void NSDL_Circ::setX(int nx){
		x = nx;
	}

	int NSDL_Circ::getY(){
		return y;
	}

	void NSDL_Circ::setY(int ny){
		y = ny;
	}

	int NSDL_Circ::getR(){
		return r;
	}

	void NSDL_Circ::setR(int nr){
		r = nr;
	}

	//Renders the Circle defined by the x,y, and r
	//NOTE: THIS DOES NOT DRAW THE STORED TEXTURE AS CIRCLE
	//      STILL NEED TO FIND A WAY TO DO SO
	void NSDL_Circ::RenderFillCirc(SDL_Renderer* rend){


			for (int tmpx = -r; x < r; tmpx++) {
				for (int tmpy = -r; tmpy < r; tmpy++) {
					if ((tmpx*tmpx + tmpy*tmpy) < (r * r)) {
						SDL_RenderDrawPoint(rend, x + tmpx, y + tmpy);
					}
				}
			}
		
	}



	
