#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"

using namespace std;

class Credits : public Sprite 
{
    public:
        Credits();
        Credits(SDL_Rect credit_rect, SDL_Texture* credit_tex);
        ~Credits();
        
	void updateCredits(SDL_Texture* credits);
        

};
