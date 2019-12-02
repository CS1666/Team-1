#include "Credits.h"

	Credits::Credits(){};
	Credits::Credits(SDL_Rect credit_rect, SDL_Texture* credit_tex) : Sprite(credit_rect, credit_tex)
	{renderOrder = 3; type = 3;};

	Credits::~Credits()
	{
		SDL_DestroyTexture(assetTex);
		assetTex = nullptr;
	}

	void Credits::updateCredits(SDL_Texture* credits)
	{
		assetTex = credits;
	}
