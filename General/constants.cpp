#include "gpRender.h"
//A BUNCH OF CONSTANTS FOR SIZES AND A FUNCTION TO GET A VECTOR OF TEXTURES TO BE REUSED
//THESE SHOULD BE GLOBAL CONSTANTS, NEVER CHANGE
//GLOBAL VARIABLES/CONSTANTS (misc)
#define PI 3.14159265
//GLOBAL SIZE CONSTANTS
#define FIGHTER_WIDTH 50
#define FIGHTER_HEIGHT 50
#define CRUISER_WIDTH 100
#define CRUISER_HEIGHT 100
#define CAPITAL_WIDTH 150
#define CAPITAL_HEIGHT 150
//GLOBAL TEXTURE VALUES
//TO USE: CALL textures.at(TEX_FIGHT_HERO) to get the hero fighter
//0-8 ARE TEXTURES FOR SHIPS
//9-12 ARE TEXTURES FOR SUNS
//13 is asteroid
//14 is space station (one of them)
//15 is the laser projectile
//ADD MORE AS REQUIRED HERE AND IN initTextures
#define TEX_FIGHT_HERO 0
#define TEX_FIGHT_ALLY 1
#define TEX_FIGHT_ENEMY 2
#define TEX_CRUIS_HERO 3
#define TEX_CRUIS_ALLY 4
#define TEX_CRUIS_ENEMY 5
#define TEX_CAPT_HERO 6
#define TEX_CAPT_ALLY 7
#define TEX_CAPT_ENEMY 8
#define TEX_SUN_BLUE 9
#define TEX_SUN_RED 10
#define TEX_SUN_WHITE 11
#define TEX_SUN_YELLOW 12
#define TEX_ASTEROID 13
#define TEX_STATION 14
#define TEX_LASER 15


std::vector<SDL_Texture*> initTextures(gpRender gr)
{
    std::vector<SDL_Texture*> allTextures;
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_fighter_hero.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_fighter_ally.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_fighter_enemy.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_cruiser_hero.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_cruiser_ally.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_cruiser_enemy.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_capital_hero.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_capital_ally.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/ship_capital_enemy.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/blue_giant.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/red_giant.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/white_dwarf.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/yellow_dwarf.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/Asteroid.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/spaceStation.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/laser.png")); //15
    //MORE ADDED TEXTURES HERE
    return allTextures;
}
