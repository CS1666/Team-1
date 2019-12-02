#pragma once   
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Ship.h"

using namespace std;

class SpaceStationUI : public Sprite 
{
    private:
        int select;
		int spriteIndex;

    public:
        SpaceStationUI();
        SpaceStationUI(SDL_Rect dBox, SDL_Texture* aTex);
        ~SpaceStationUI();
        
        int get_select();
		int get_spriteIndex();
		void set_select(int newSelect);
		void set_spriteIndex(int newSpriteIndex);

};

