
#include "../General/Sprite.h"
#pragma once

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

bool handleKeyEvents(SDL_Event e, Sprite &ent);
void handleKeyUpEvent(SDL_Event e, Sprite &ent);
void handleKeyDownEvent(SDL_Event e, Sprite &ent);
bool check_collision(SDL_Rect* a, SDL_Rect* b);
bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite);
void updatePosition(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
