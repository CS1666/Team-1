
	#include "Sprite.h"

	
	//------------------------------------Constructors-----------------------------------------------
	Sprite::Sprite(): drawBox{0,0,0,0},  drawCirc{}, assetTex{nullptr}, x{0}, y{0}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{-1} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, int anim): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{anim} , x{(float)dBox.x}, y{(float)dBox.y}{};



	//------------------------------------Destructor--------------------------------------------------
	Sprite::~Sprite(){
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}

	//------------------------------Getters and Setters------------------------------------------------
	//depricated 
	void Sprite::setX(int x)
	{
		Sprite::x = (float)x;
		drawBox.x = (int)Sprite::x;
	}
	void Sprite::setY(int y)
	{
		Sprite::y = (float)y;
		drawBox.y = (int)Sprite::y;
	}

	bool Sprite::isShip()
	{
		return type == 1;
	}
	bool Sprite::isCelestialBody()
	{
		return type == 2;
	}
	bool Sprite::isUI()
	{
		return type == 3;
	}
	void Sprite::setX(float x){
		Sprite::x = x;
		drawBox.x = (int)Sprite::x;
	}
	int Sprite::getX(){
			return drawBox.x;
	}
	void Sprite::setY(float y){
		Sprite::y = y;
		drawBox.y = (int)Sprite::y;
	}
	int Sprite::getY(){
		return drawBox.y;
	}
	
	float Sprite::getTrueX()
	{
		return Sprite::x;
	}
	float Sprite::getTrueY()
	{
		return Sprite::y;
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












