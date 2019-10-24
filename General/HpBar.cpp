#include "HpBar.h"
#include <SDL.h>

	HpBar::HpBar() {};
	HpBar::HpBar(SDL_Rect dBox, SDL_Texture* aTex, float new_percentage):drawbox{dBox}, assetTex{aTex},  percentage{new_percentage}, x{(float)dBox.x}, y{(float)dBox.y}{};
	HpBar::~HpBar()
	{
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}
       
	void HpBar::setPercentage(float newPercentage){
		percentage = newPercentage;
	}
	
	float HpBar::getPercentage(){
		return percentage;
	}

	void HpBar::setX(int x)
	{
		HpBar::x = (float)x;
		drawbox.x = (int)HpBar::x;
	}

	void HpBar::setY(int y)
	{
		HpBar::y = (float)y;
		drawbox.y = (int)HpBar::y;
	}


	void HpBar::setX(float x){
		HpBar::x = x;
		drawbox.x = (int)HpBar::x;
	}

	int HpBar::getX(){
			return drawbox.x;
	}

	void HpBar::setY(float y){
		HpBar::y = y;
		drawbox.y = (int)HpBar::y;
	}
	int HpBar::getY(){
		return drawbox.y;
	}
	
	float HpBar::getTrueX()
	{
		return HpBar::x;
	}

	float HpBar::getTrueY()
	{
		return HpBar::y;
	}

	int HpBar::getW(){
		return drawbox.w;
	}

	int HpBar::getH(){
		return drawbox.h;
	}
	void HpBar::setW(int new_w){
		drawbox.w = new_w;
	}
	void HpBar::setH(int new_h){
		drawbox.h = new_h;
	}

	void HpBar::setTexture(SDL_Texture* tex){
		assetTex = tex;
	}

	SDL_Texture* HpBar::getTexture(){
			return assetTex;
	}

	SDL_Rect* HpBar::getDrawBox(){
		return &drawbox;
	}


