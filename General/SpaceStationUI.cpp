#include "SpaceStationUI.h"
#include <SDL.h>

	SpaceStationUI::SpaceStationUI() {};
	SpaceStationUI::SpaceStationUI(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex), select{-1}, spriteIndex{-1}{renderOrder = 3;};
	SpaceStationUI::~SpaceStationUI()
	{
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}
	
	int SpaceStationUI::get_select() {
		return select;
	}

	int SpaceStationUI::get_spriteIndex() {
		return spriteIndex;
	}

	void SpaceStationUI::set_select(int newSelect) {
		select = newSelect;
	}

	void SpaceStationUI::set_spriteIndex(int newSpriteIndex) {
		spriteIndex = newSpriteIndex;
	}
	


