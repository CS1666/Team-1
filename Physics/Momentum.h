#pragma once
#include "../General/Sprite.h"
#include "../General/Ship.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "BasicMovementFPSlimit.h"

std::vector<float> calculateMomentumConserv(Ship &playerent, std::vector<Ship*> &osShip);
void shipCollisionHandler(Ship &ship1, Ship &ship2);


