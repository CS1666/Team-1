#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


#include "ai_enviroment.h"
#include "AI.h"
#include "AIShip.h"
#include "theta.h"
#include "../General/gpRender.h"
#include "../General/Sprite.h"
#include "../Physics/TimeData.h"
#include "../General/Ship.h"
#include "../General/Sector.h"
#include "../General/Constants.h"
#include "../General/gpRender.h"
#include "../Physics/BasicMovementFPSlimit.h"
void run_ai_enviro(gpRender gr);
