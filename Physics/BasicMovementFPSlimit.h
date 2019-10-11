
#include "../General/gpEntity.h"
#pragma once

constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;

bool handleKeyEvents(SDL_Event e, gpEntity &ent);
void handleKeyUpEvent(SDL_Event e, gpEntity &ent);
void handleKeyDownEvent(SDL_Event e, gpEntity &ent);
bool check_collision(SDL_Rect* a, SDL_Rect* b);
bool check_all_collisions(SDL_Rect* a, std::vector<gpEntity*> &osEntity);
void updatePosition(gpEntity &ent, std::vector<gpEntity*> &osEntity);
