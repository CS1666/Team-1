
	#include "gpEntity.h"

	
	//------------------------------------Constructors-----------------------------------------------
	gpEntity::gpEntity(): drawBox{0,0,0,0},  drawCirc{}, assetTex{nullptr} {};

	gpEntity::gpEntity(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, drawCirc{}, assetTex{aTex} {};

	gpEntity::gpEntity(NSDL_Circ dCirc, SDL_Texture* aTex):drawBox{0,0,0,0}, drawCirc{dCirc}, assetTex{aTex} {};


	//------------------------------------Destructor--------------------------------------------------
	gpEntity::~gpEntity(){
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}

	//------------------------------Getters and Setters------------------------------------------------
	void gpEntity::setX(int x){
			drawBox.x = x;
	}
	int gpEntity::getX(){
			return drawBox.x;
	}
	void gpEntity::setY(int y){
		drawBox.y = y;
	}
	int gpEntity::getY(){
		return drawBox.y;
	}
	void gpEntity::setVX(int new_vx){
		vx = new_vx;
	}
	int gpEntity::getVX(){
		return vx;
	}
	void gpEntity::setVY(int new_vy){
		vy = new_vy;
	}
	int gpEntity::getVY(){
		return vy;
	}

	void gpEntity::setR(int new_r){
		drawCirc.setR(new_r) ;
	}
	int gpEntity::getR(){
		return drawCirc.getR();
	}
	void gpEntity::setTexture(SDL_Texture* tex){
		assetTex = tex;
	}
	SDL_Texture* gpEntity::getTexture(){
			return assetTex;
	}
	void gpEntity::setAngle(double new_angle){
		angle = new_angle;
	}
	double gpEntity::getAngle(){
		return angle;
	}
	int gpEntity::getH(){
			return drawBox.h;
	}
	int gpEntity::getW(){
			return drawBox.w;
	}
	

	//--------------------------Functions Related to Drawing a Rectangle-----------------------------------------
	SDL_Rect* gpEntity::getDrawBox(){
		return &drawBox;
	}
	void gpEntity::updateDrawBox(){
		drawBox.x += vx;
		drawBox.y += vy;

	}
	bool gpEntity::isRectEnt(){

		return drawBox.w != 0 && drawBox.h != 0;
	}
	

	//---------------------------Functions Related to Drawing a Circle-----------------------------------------
	NSDL_Circ* gpEntity::getDrawCirc(){
		return &drawCirc;
	}

	void gpEntity::updateDrawCirc(){
		drawCirc.setX(drawCirc.getX() + vx);
		drawCirc.setY(drawCirc.getY() + vy);

	}
	
	bool gpEntity::isCircEnt(){

		return drawCirc.getR() != 0;
	}


	//Function that handles cases where entity box is out of bounds. 
	//Probably should be Renamed and moved into collison
	void gpEntity::handelEntityOB(int sw, int sh){
		updateDrawBox();

		if (drawBox.x >= sw - drawBox.w) {
			drawBox.x = sw - drawBox.w;
			
		}
		else if (drawBox.x <= 0) {
			drawBox.x = 0;
			
		}
		if (drawBox.y >= sh -  drawBox.h) {
			drawBox.y = sh - drawBox.h;
				
		}
		else if (drawBox.y <= 0) {
			drawBox.y = 0;
				
		}

	}









