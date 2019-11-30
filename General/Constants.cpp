#include "./Constants.h"
std::vector<SDL_Texture*> initTextures(gpRender& gr)
{
    std::vector<SDL_Texture*> allTextures;
    //allTextures.push_back(gr.loadImage("Assets/Objects/ships.png"))
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
    ///allTextures.push_back(gr.loadImage("Assets/Objects/asteroids.png"))
    allTextures.push_back(gr.loadImage("Assets/Objects/Asteroid.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/spaceStation.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/laser.png")); 
    allTextures.push_back(gr.loadImage("Assets/Objects/order_order.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/order_follow.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/order_defend.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/order_attack.png"));
    allTextures.push_back(gr.loadImage("Assets/Objects/order_auto.png")); //20
    //MORE ADDED TEXTURES HERE
    return allTextures;
}

