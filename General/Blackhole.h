#pragma once
#include <iostream>
#include "Sprite.h"
#include <SDL.h>
#include "gpRender.h"

class Blackhole : public Sprite
{
	public:
		Blackhole(SDL_Rect dBox, SDL_Texture* aTex,NSDL_Circ dCirc);//just make the texture fixed
};