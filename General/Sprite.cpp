
	#include "Sprite.h"

	
	//------------------------------------Constructors-----------------------------------------------
	Sprite::Sprite(): drawBox{0,0,0,0},  drawCirc{}, assetTex{nullptr} {};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{-1} {};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, int anim): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{anim} {};

	Sprite::Sprite(NSDL_Circ dCirc, SDL_Texture* aTex):drawBox{0,0,0,0}, drawCirc{dCirc}, assetTex{aTex} {};


	//------------------------------------Destructor--------------------------------------------------
	Sprite::~Sprite(){
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}

	//------------------------------Getters and Setters------------------------------------------------
	void Sprite::setX(int x){
			drawBox.x = x;
	}
	int Sprite::getX(){
			return drawBox.x;
	}
	void Sprite::setY(int y){
		drawBox.y = y;
	}
	int Sprite::getY(){
		return drawBox.y;
	}
	

	void Sprite::setR(int new_r){
		drawCirc.setR(new_r) ;
	}
	int Sprite::getR(){
		return drawCirc.getR();
	}
	void Sprite::setTexture(SDL_Texture* tex){
		assetTex = tex;
	}
	SDL_Texture* Sprite::getTexture(){
			return assetTex;
	}
	void Sprite::setAngle(double new_angle){
		angle = new_angle;
	}
	double Sprite::getAngle(){
		return angle;
	}
	int Sprite::getH(){
		return drawBox.h;
	}
	int Sprite::getW(){
		return drawBox.w;
	}
	void Sprite::setF(int anim){
		animFrame = anim;
	}
	int Sprite::getF(){
		return animFrame;
	}
	

	//--------------------------Functions Related to Drawing a Rectangle-----------------------------------------
	SDL_Rect* Sprite::getDrawBox(){
		return &drawBox;
	}

	bool Sprite::isRectEnt(){

		return drawBox.w != 0 && drawBox.h != 0;
	}
	

	//---------------------------Functions Related to Drawing a Circle-----------------------------------------
	NSDL_Circ* Sprite::getDrawCirc(){
		return &drawCirc;
	}


	
	bool Sprite::isCircEnt(){

		return drawCirc.getR() != 0;
	}












