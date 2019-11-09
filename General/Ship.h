#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Projectile.h"
#include <queue>
#include "gpRender.h"

//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship : public Sprite
{
    private:
        int hull;
        string sprite;
        pair<int,int> position;
        int xVelocity;
	int yVelocity;
        float maxRotation;
        int weaponType;
        bool damageTaken;
	bool rotationSet;
	float newAngle;
	float rotation;
        int maxVelocity;
        string currKey;

        int mass;
        pair<int, int> size;

        float speedX;
        float speedY;
        int currHp;
        int maxHp;

        //ai
        std::queue<pair<int,int>>* path;
        pair<int,int> destination;
        bool isUser;
        bool isAlly;
        bool pathComplete;
	int curGoal; //'modes' of ai: follow, defend, attack, flee = {0,1,2,3} for now
	void calculateNewAngle(pair<int,int> destination);
    public:
        float speed = 0;
        float deltaV = 0;
        float rotationRate = 0;
        float rotationSpeed = 0;
        float direction;

        Ship();
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
