#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
//#include "Projectile.h"
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

        float max_deltaV = 1;

        bool fired = false;
        Uint32 fireLastTime = SDL_GetTicks();
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

        void setMaxDelta(float new_accel);
        void setSpeedX(float speed);
        void setSpeedY(float speed);
        float getSpeedX();
        float getSpeedY();
        void updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT);
        void updateMovement(std::vector<Sprite*> &osSprite, std::vector<Sprite*> otherSprites, int ZONE_WIDTH, int ZONE_HEIGHT);
        void updateMovementShips(std::vector<Sprite*> &osSprite, std::vector<Ship*> &osShip, int ZONE_WIDTH, int ZONE_HEIGHT);
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
        void fireWeapon(); 
        void getFired(std::vector<Sprite*> &osSprite, SDL_Texture* texture);
        //Projectile fireWeaponatme(SDL_Texture* texture); 
        Uint32 getFireLastTime();
		void setFireLastTime();

        //allied status
        void setIsAlly(bool alliedStatus);
        bool getIsAlly();
};

class Hero: public Ship{
	private:
	    int shipType;
        public:
            Hero(SDL_Rect dBox, SDL_Texture* aTex);
            bool handleKeyEvents(SDL_Event e);
            void handleKeyUpEvent(SDL_Event e);
            void handleKeyDownEvent(SDL_Event e);
	    int getType();
	    void upgradeType();
};

/*class Fighter: public Ship{
    public:
        Fighter(SDL_Rect dBox, SDL_Texture* aTex, bool ally);
};

class Cruiser: public Ship{
    public:
        Cruiser(SDL_Rect dBox, SDL_Texture* aTex, bool ally);
};

class Capital: public Ship{
    public:
        Capital(SDL_Rect dBox, SDL_Texture* aTex, bool ally);
};*/
