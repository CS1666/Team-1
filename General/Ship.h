#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../AI/Queue.h"
//#include "Physics/BasicMovementFPSlimit.h"
using namespace std;

class Ship
{
    private:
        int hull;
        string sprite;
        vector<int> position;
        int velocity;
        float rotation;
        int weaponType;
        bool damageTaken;
        int maxVelocity;
        string currKey;
        long mass;

        //ai
        Queue path;
        vector<int> destination;
        bool isUser;
        bool isAlly;
        bool pathComplete;

    public:
        void setSprite(string newSprite);
        string getSprite();
        void checkPhysics();
        //integrate BasicMovementFPSlimit.cpp
        void updateMovement();
        void checkAction(/*stream*/);
        void updateHull(int newHull);
        void setPosition(vector<int> newPosition);
        vector<int> getPosition();
        void setPath(Queue thePath);
        //ai follows path assigned to it by ai class
        void followPath();
        bool getPathComplete();
        vector<int> getDestination();
        int getMaxVelocity();
        void setDestination(vector<int> newDestination);
        long getMass();
};

class Hero:Ship{};

class Fighter:Ship{};

class Cruiser:Ship{};

class Capital:Ship{};
