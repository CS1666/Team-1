#include "Blackhole.h"
Blackhole::Blackhole(SDL_Rect dBox, SDL_Texture* aTex, NSDL_Circ dCirc): Sprite(dBox, aTex, dCirc) {renderOrder = 2; mass = 1000000; type = -1;};