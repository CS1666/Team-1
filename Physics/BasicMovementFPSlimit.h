#pragma once
#include "../General/Sprite.h"
#include "../General/Ship.h"
#include "BasicGravity.h"



constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

bool handleKeyEvents(SDL_Event e, Ship &ent);
void handleKeyUpEvent(SDL_Event e, Ship &ent);
void handleKeyDownEvent(SDL_Event e, Ship &ent);
bool check_collision(SDL_Rect* a, SDL_Rect* b);
bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite);
void updatePosition(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);

bool updatePosition(Ship &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);

void updatePosition2(Ship &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
