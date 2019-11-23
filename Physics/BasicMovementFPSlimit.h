#pragma once
#include "../General/Sprite.h"
#include "../General/Ship.h"
#include "BasicGravity.h"
#include "Momentum.h"



constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

bool handleKeyEvents(SDL_Event e, Ship &ent);
void handleKeyUpEvent(SDL_Event e, Ship &ent);
void handleKeyDownEvent(SDL_Event e, Ship &ent);
bool check_collision(SDL_Rect* a, SDL_Rect* b);
bool check_proximity(Sprite &aSprite, Sprite &bSprite, int sz);
bool check_all_collisions2(SDL_Rect* a, std::vector<Sprite*> &osSprite);
void updatePosition(Ship &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);

void updatePosition3(Ship &ent, std::vector<Sprite*> &osSprite, std::vector<Ship*> &osShip, int ZONE_WIDTH, int ZONE_HEIGHT);



