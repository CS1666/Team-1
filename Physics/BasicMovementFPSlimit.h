
#include "../General/gpEntity.h"
#pragma once

bool handleKeyEvents(SDL_Event e, gpEntity &ent);
void handleKeyUpEvent(SDL_Event e, gpEntity &ent);
void handleKeyDownEvent(SDL_Event e, gpEntity &ent);
bool check_collision(SDL_Rect* a, SDL_Rect* b);
bool check_all_collisions(SDL_Rect* a, std::vector<gpEntity*> &osEntity);
void updatePosition(gpEntity &ent, std::vector<gpEntity*> &osEntity);
