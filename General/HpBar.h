
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HpBar 
{
    private:
        
	SDL_Rect drawbox;
	SDL_Texture* assetTex;
	float percentage;
	float x, y;

    public:
        HpBar();
        HpBar(SDL_Rect dBox, SDL_Texture* aTex, float percentage);
        ~HpBar();
        
        void setPercentage(float newPercentage);
        float getPercentage();

	void setX(int new_x);
	void setY(int new_y);
	int getX();
	int getY();
	void setX(float new_x);
	void setY(float new_y);
	float getTrueX();
	float getTrueY();
	int getW();
	int getH();
	void setW(int new_w);
	void setH(int new_h);
	void setTexture(SDL_Texture* tex);
	SDL_Texture* getTexture();
	SDL_Rect* getDrawBox();
};

