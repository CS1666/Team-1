
	#include "Sprite.h"
	#include <iostream>

	
	//------------------------------------Constructors-----------------------------------------------
	Sprite::Sprite(): drawBox{0,0,0,0},  drawCirc{}, assetTex{nullptr}, x{0}, y{0}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{-1} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, int anim): drawBox{dBox}, drawCirc{}, assetTex{aTex}, animFrame{anim} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc) : drawBox{ dBox }, drawCirc{dCirc}, assetTex{ aTex }, animFrame{ anim }, x{ (float)dBox.x }, y{ (float)dBox.y }{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int anim) : drawBox{ dBox }, drawCirc{dCirc}, assetTex{ aTex }, animFrame{ -1 }, x{ (float)dBox.x }, y{ (float)dBox.y }{};

	Sprite::Sprite(const Sprite &spr): drawBox{spr.drawBox}, drawCirc{spr.drawCirc}, assetTex{spr.assetTex}, animFrame{spr.animFrame} , x{spr.x}, y{spr.y}{};

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
	void Sprite::setRenderOrder(int new_order){
		renderOrder = new_order;
	}
	int Sprite::getRenderOrder(){
		return renderOrder;
	}
	
	void Sprite::updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT){
	}

	bool check_collision(SDL_Rect* a, SDL_Rect* b) {
		// Check vertical overlap
		if (a->y + a->h <= b->y)
			return false;
		if (a->y >= b->y + b->h)
			return false;

		// Check horizontal overlap
		if (a->x >= b->x + b->w)
			return false;
		if (a->x + a->w <= b->x)
			return false;

		// Must overlap in both
		return true;
	}

	bool check_collision(SDL_Rect* a, NSDL_Circ* b) {
		int c_x, c_y;
		int d_x, d_y;
		int distsq;

		// Need to find closest x/y cooridinates to the Circ
		if (b->x < a->x)
			c_x = a->x;
		else if (b->x > a->x + a->w)
			c_x = a->x + a->w;
		else
			c_x = b->x;

		if (b->y < a->y)
			c_y = a->y;
		else if (b->y > a->y + a->h)
			c_y = a->y + a->h;
		else
			c_y = b->y;

		// Find distance from Circ to Rect
		d_x = b->x - c_x;
		d_y = b->y - c_y;

		// Compare square of distances
		distsq = d_x * d_x + d_y * d_y;
		if (distsq < (b->r * b->r))
			return true;

		// else
		return false;
	}

	bool check_collision(NSDL_Circ* a, NSDL_Circ* b) {
		int radsum = a->r + b->r;
		int d_x, d_y;
		int distsq;

		d_x = a->x - b->x;
		d_y = a->y - b->y;
		distsq = d_x * d_x + d_y * d_y;
		if (distsq < (radsum * radsum))
			return true;

		// else
		return false;
	}

	bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite){
		bool isCollision = false;
		//std::cout << "osEntity.size() = " << osEntity.size() << std::endl;
		for (int i = 1; i < osSprite.size(); i++) {
			//so, one of these should result in collison if they are the same box
			if (osSprite.at(i)->getDrawCirc())
				isCollision = check_collision(a, osSprite.at(i)->getDrawCirc());
			else
				isCollision = check_collision(a, osSprite.at(i)->getDrawBox());
			//std::cout << "Is last command Illegal?" << std::endl;
			//std::cout << "Checked collisions: " << i << std::endl;
		}
		return isCollision;
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












