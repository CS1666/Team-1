#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Projectile.h"
#include <queue>
#include "gpRender.h"
#include "../Physics/Audio.h"

//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship : public Sprite
{
    protected:

        string currKey;

        int hull;
        int weaponType;

        int maxVelocity;
        int xVelocity;
        int yVelocity;
        int currHp;
        int maxHp;
        int mass;
       

        float curRotation;
        float rotation;
        float maxRotation;
        float speedX;
        float speedY;
        float newAngle;

        bool damageTaken;
        bool rotationSet;
        bool isUser;
        bool isAlly;

        string sprite;
        pair<int, int> size;
        pair<int,int> position;
       

    public:
        float speed = 0;
        float deltaV = 0;
        float rotationRate = 0;
        float rotationSpeed = 0;
        float direction;

        Ship();
        Ship(const Ship& ship);
        Ship(SDL_Rect dBox, SDL_Texture* aTex);
        Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim);
        Ship(SDL_Rect dBox, SDL_Texture* aTex, int anim, int mass);
        ~Ship();
        
        void setSprite(string newSprite);
        string getSprite();
        void checkPhysics();
        //integrate BasicMovementFPSlimit.cpp

        void setSpeedX(float speed);
        void setSpeedY(float speed);
        float getSpeedX();
        float getSpeedY();
        void updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
        void updateHull(int newHull);
        void setPosition(pair<int,int> newPosition);
        pair<int,int> getPosition();

        void setSize(pair<int,int> newSize);
        pair<int,int> getSize();

	    void setGoal(int newGoal);
	    int getGoal();
        void setPath(queue<pair<int, int>>* thePath);
        //ai follows path assigned to it by ai class
        void followPath(Sprite& entity);
        bool getPathComplete();
        pair<int,int> getDestination();
        int getMaxVelocity();
        void setDestination(pair<int,int> newDestination);
        int getMass();
        void setCurrHp(int newCurrHp);
        int getCurrHp();
        void setMaxHp(int newMaxHp);
        int getMaxHp();
        Projectile fireWeapon(SDL_Texture* texture); 

        //allied status
        void setIsAlly(bool alliedStatus);
        bool getIsAlly();
};

class Hero: public Ship{        
        public:
                Hero(SDL_Rect dBox, SDL_Texture* aTex);
                
                bool handleKeyEvents(SDL_Event e);
                void handleKeyUpEvent(SDL_Event e);
                void handleKeyDownEvent(SDL_Event e);
};

class Fighter: public Ship{};

class Cruiser: public Ship{};

class Capital: public Ship{};
