#include "HpBar.h"
#include <SDL.h>

	HpBar::HpBar() {};
	HpBar::HpBar(SDL_Rect dBox, SDL_Texture* aTex, float percentage): Sprite(dBox, aTex), percentage{percentage}{renderOrder = 3;};
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
	
	void HpBar::changeBar(Ship player){
		w = player.getCurrHp()/player.getMaxHp() * ogW; 	
	}
	


