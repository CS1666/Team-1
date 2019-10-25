
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"

using namespace std;

class HpBar : public Sprite 
{
    private:
        
	float percentage;

    public:
        HpBar();
        HpBar(SDL_Rect dBox, SDL_Texture* aTex, float percentage);
        ~HpBar();
        
        void setPercentage(float Percentage);
        float getPercentage();

};

