
	#include "Sprite.h"
	#include <iostream>

	
	//------------------------------------Constructors-----------------------------------------------
	Sprite::Sprite(): drawBox{0,0,0,0},  collisionCirc{}, assetTex{nullptr}, x{0}, y{0}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, collisionBox{}, collisionCirc{}, assetTex{aTex}, animFrame{0,-1} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, int anim): drawBox{dBox}, collisionBox{}, collisionCirc{}, assetTex{aTex}, animFrame{0,anim} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, SDL_Rect cBox): drawBox{dBox}, collisionBox{cBox}, collisionCirc{}, assetTex{aTex}, animFrame{0,-1} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, SDL_Rect cBox, int anim): drawBox{dBox}, collisionBox{cBox}, collisionCirc{}, assetTex{aTex}, animFrame{0,anim} , x{(float)dBox.x}, y{(float)dBox.y}{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc) : drawBox{ dBox }, collisionBox{}, collisionCirc{dCirc}, assetTex{ aTex }, animFrame{0,-1 }, x{ (float)dBox.x }, y{ (float)dBox.y }{};

	Sprite::Sprite(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc, int anim) : drawBox{ dBox }, collisionBox{}, collisionCirc{dCirc}, assetTex{ aTex }, animFrame{0,anim }, x{ (float)dBox.x }, y{ (float)dBox.y }{};

	Sprite::Sprite(const Sprite &spr): drawBox{spr.drawBox}, collisionBox{spr.collisionBox}, collisionCirc{spr.collisionCirc}, assetTex{spr.assetTex}, animFrame{spr.animFrame} , x{spr.x}, y{spr.y}{};

	//------------------------------------Destructor--------------------------------------------------
	Sprite::~Sprite(){
		//SDL_DestroyTexture(assetTex);
		//assetTex = nullptr;
	}

	//------------------------------Getters and Setters------------------------------------------------
	//depricated 
	void Sprite::setX(int x)
	{
		Sprite::x = (float)x;
		drawBox.x = (int)Sprite::x;
		collisionBox.x = (int)Sprite::x;
		collisionCirc.setX((int)(Sprite::x+drawBox.w/2.0));
	}
	void Sprite::setY(int y)
	{
		Sprite::y = (float)y;
		drawBox.y = (int)Sprite::y;
		collisionBox.y = (int)Sprite::y;
		collisionCirc.setY((int)(Sprite::y+drawBox.w/2.0));
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
	bool Sprite::isProjectile()
	{
		return type == 5;
	}
	bool Sprite::getIsAI(){
		return isAI;
	}
	bool Sprite::getIsAsteroid(){
		return isAst;
	}
	void Sprite::setX(float x){
		Sprite::x = x;
		drawBox.x = (int)Sprite::x;
		collisionBox.x = (int)Sprite::x;
		collisionCirc.setX((int)(Sprite::x+drawBox.w/2.0));
	}
	int Sprite::getX(){
			return drawBox.x;
	}
	void Sprite::setY(float y){
		Sprite::y = y;
		drawBox.y = (int)Sprite::y;
		collisionBox.y = (int)Sprite::y;
		collisionCirc.setY((int)(Sprite::y+drawBox.w/2.0));
	}
	int Sprite::getY(){
		return drawBox.y;
	}
	int Sprite::getMass(){
		return mass;
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
		if(new_angle>=360)
		{
		    double leftOver=new_angle/360;
		    angle=(int)new_angle%360+leftOver;
		}
		else if(new_angle<0)
		    angle=new_angle+360;
		else
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
	void Sprite::setF1(int anim){
		animFrame.first = anim;
	}
	void Sprite::setF2(int anim){
		animFrame.second = anim;
	}
	std::pair<int,int> Sprite::getF(){
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

	bool Sprite::check_collision(SDL_Rect* a, SDL_Rect* b) {
		// Check vertical overlap
		if (a->x==b->x && a->y==b->y && a->w==b->w && a->h==b->h)
			return false;
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

	bool Sprite::check_collision(SDL_Rect* a, NSDL_Circ* b) {
		int c_x, c_y;
		int d_x, d_y;
		int distsq;

		// Need to find closest x/y cooridinates to the Circ
		if (b->getX() < a->x)
			c_x = a->x;
		else if (b->getX() > a->x + a->w)
			c_x = a->x + a->w;
		else
			c_x = b->getX();

		if (b->getY() < a->y)
			c_y = a->y;
		else if (b->getY() > a->y + a->h)
			c_y = a->y + a->h;
		else
			c_y = b->getY();

		// Find distance from Circ to Rect
		d_x = b->getX() - c_x;
		d_y = b->getY() - c_y;

		// Compare square of distances
		distsq = d_x * d_x + d_y * d_y;
		if (distsq < (b->getR() * b->getR()))
			return true;

		// else
		return false;
	}

	bool Sprite::check_collision(NSDL_Circ* a, NSDL_Circ* b) {
		int radsum = a->getR() + b->getR();
		int d_x, d_y;
		int distsq;

		d_x = a->getX() - b->getX();
		d_y = a->getY() - b->getY();
		distsq = d_x * d_x + d_y * d_y;
		if (distsq < (radsum * radsum))
			return true;

		// else
		return false;
	}

	bool Sprite::check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite){
		bool isCollision = false;
		
		for (int i = 0; i < osSprite.size(); i++) {
			if (!osSprite.at(i)->isProjectile()){
				if (osSprite.at(i)->isCircEnt()){
					isCollision |= check_collision(a, osSprite.at(i)->getCollisionCirc());
				}
				else
					isCollision |= check_collision(a, osSprite.at(i)->getDrawBox());
			}
			
		}
		
		return isCollision;
	}
	
	bool Sprite::check_all_collisions(NSDL_Circ* a, std::vector<Sprite*> &osSprite){
		bool isCollision = false;
		//std::cout << "osEntity.size() = " << osEntity.size() << std::endl;
		for (int i = 0; i < osSprite.size(); i++) {
			//so, one of these should result in collison if they are the same box
			if (osSprite.at(i)->isCircEnt()){
				isCollision = check_collision(a, osSprite.at(i)->getCollisionCirc());
			}
		
		}
		return isCollision;
	}

	bool Sprite::check_all_collisions_ships(SDL_Rect* a, std::vector<Sprite*> &osSprite){
		bool isCollision = false;
		//std::cout << "osEntity.size() = " << osEntity.size() << std::endl;
		for (int i = 1; i < osSprite.size(); i++) {
			//so, one of these should result in collison if they are the same box
			if (osSprite.at(i)->isCircEnt()){
				isCollision |= check_collision(a, osSprite.at(i)->getCollisionCirc());
			}
			/*else
				isCollision |= check_collision(a, osSprite.at(i)->getDrawBox());*/
			//std::cout << "Is last command Illegal?" << std::endl;
			//std::cout << "Checked collisions: " << i << std::endl;
		}
		
		return isCollision;
	}

	bool Sprite::getAnimate(){
		return animate;
	}

	void Sprite::setAnimate(bool toggle){
		animate = toggle;
	}

	void Sprite::updateAnimation(){
		if (SDL_GetTicks() - getAnimLastTime() > 100) {
			int animation = getF().first;
			bool cycle = false;
			if (animation <= 1){
				cycle = true;
			}
			else if(animation == 3){
				cycle = false;
			}

			if (cycle){
				animation++;
			}
			else{
				animation--;
			}
			setAnimLastTime();
			setF1(animation);
		}
	}

	Uint32 Sprite::getAnimLastTime(){
		return animLastTime;
	}

	void Sprite::setAnimLastTime(){
		animLastTime = SDL_GetTicks();
	}

	bool Sprite::isHole()
	{
		return type == -1;
	}

	
	
	//--------------------------Functions Related to Drawing a Rectangle-----------------------------------------
	SDL_Rect* Sprite::getDrawBox(){
		return &drawBox;
	}

	bool Sprite::isRectEnt(){

		return drawBox.w != 0 && drawBox.h != 0;
	}
	

	//---------------------------Functions Related to Drawing a Circle-----------------------------------------
	NSDL_Circ* Sprite::getCollisionCirc(){
		return &collisionCirc;
	}
	
	bool Sprite::isCircEnt(){
		return collisionCirc.getR() != 0;
	}


	bool Sprite::shouldRemove()
	{
		return remove;
	}

	void Sprite::setRemove(bool rm){
		remove = rm;
	}









