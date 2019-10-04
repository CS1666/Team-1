
#include "../General/gpEntity.h"
#pragma once

bool handleKeyEvents(SDL_Event e, gpEntity &ent);
void handleKeyUpEvent(SDL_Event e, gpEntity &ent);
void handleKeyDownEvent(SDL_Event e, gpEntity &ent);
void updatePosition(gpEntity &ent);
