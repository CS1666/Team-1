#pragma once
#include "../General/Sprite.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"


//std::vector<float> calculateGravityPull(Sprite &playerent, Sprite &bodyent); //depricated
std::vector<float> calculateGravityPull(Sprite &playerent,  std::vector<Sprite*> &osSprite);
void updatePositionGrav(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
