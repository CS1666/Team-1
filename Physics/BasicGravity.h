#include "../General/Sprite.h"
#pragma once

void gravity_pull(Sprite &body1, Sprite &body2);
void updatePositionGrav(Sprite &ent, std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
