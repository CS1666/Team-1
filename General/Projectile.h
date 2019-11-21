#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include <queue>

using namespace std;

class Projectile : public Sprite
{
    private:
        string sprite;
        pair<int,int> position;
        int xVelocity;
	    int yVelocity;
	    float rotation;
        string currKey;
        int damage;

    public:
        Projectile();
        Projectile(SDL_Rect dBox, SDL_Texture* aTex, int damage);
        Projectile(const Projectile &spr);
        void updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
        int getDamage();
        bool check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite);
        bool isProjectile();
};