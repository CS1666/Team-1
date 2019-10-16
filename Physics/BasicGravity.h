#include "../General/Sprite.h"
#pragma once

void gravity_pull(Sprite &playerent, Sprite &bodyent);

void updatePositionGrav(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
