#include "HpBar.h"
#include <SDL.h>

	HpBar::HpBar() {};
	HpBar::HpBar(SDL_Rect dBox, SDL_Texture* aTex, float percentage): Sprite(dBox, aTex), percentage{percentage}{};
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
	


