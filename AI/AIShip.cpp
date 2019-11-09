
#pragma once
#define PI 3.14159265
#include "AIShip.h"

AIShip::AIShip() : Ship() {};
AIShip::AIShip(SDL_Rect dBox, SDL_Texture* aTex): Ship(dBox, aTex, 0) {renderOrder = 1;};

//ai follows path assigned to it by ai class
 void AIShip::followPath(Sprite& entity)
    {
	    //note: change the path in Ship.h to whatever is returned.
	    if(!path->empty())
	    {
			//note: assumed whatever we're using is some (x,y)
			pair<int,int> coords=path->front();
			int x_coord=coords.first;
			int y_coord=coords.second;
			int cur_x=position.first;
			int cur_y=position.second;
			double xSlope=x_coord-cur_x;
			double ySlope=y_coord-cur_y;
			//get angle of destination
			if(!rotationSet)
			{
				calculateNewAngle(coords);
				//cout<<"rotation: "<<newAngle<<endl;
				//int n;
				//cin>>n;
				rotationSet=true;
			}
			float angle=entity.getAngle();
			cout<<"newAngle:"<<newAngle<<endl;
			cout<<"cur angle: "<<angle<<endl;
			bool angleChanged=rotateToAngle(entity);
			if(newAngle>angle||newAngle-angle>=180)
			{
			    //pretty shit acceleration stuff tbh
			    if(newAngle>angle+maxRotation)
			    {
				if(maxRotation>rotation)
				    entity.setAngle(angle+rotation++);
				else
				    entity.setAngle(angle+rotation);
			    }
			    else
			        entity.setAngle(angle+1);
			    angleChanged=true;
			}
			else if(newAngle<angle||newAngle-angle<-180)
			{
			    if(angle-maxRotation>newAngle)
			    {
				if(maxRotation>rotation)
				    entity.setAngle(angle-(rotation++));
				else
				    entity.setAngle(angle-rotation);
			    }
			    else
				entity.setAngle(angle-1);
			    angleChanged=true;
			}
			//entity.setAngle(122);
		//cout<<"cur_x: "<<cur_x<<" cur_y : "<<cur_y<<endl;
	        ////std::cout << "x: " << x_coord << " y: " << y_coord << "points remaing: " << path->size() << endl;
			//note: since we don't have updateMovement implemented, most
			//of the stuff here can probably be removed/handled by that
			//simulate turning, acceleration of ship
			if(!angleChanged&&(cur_x != x_coord || cur_y != y_coord))
			{
			    if(cur_x-maxVelocity>x_coord)
			    {
				if(maxVelocity>xVelocity)
				    cur_x-=xVelocity++;
				else
				    cur_x-=xVelocity;
			    }
			    else if(cur_x>x_coord)
			    {
				cur_x=x_coord; //skipped
				rotationSet=false;
			    }
			    else if(cur_x+maxVelocity<x_coord)
			    {
				if(maxVelocity>xVelocity)
				    cur_x+=xVelocity++;
				else
				    cur_x+=xVelocity;
			    }
			    else if(cur_x<x_coord)
			    {
				cur_x=x_coord; //skipped
				rotationSet=false;
			    }
			    if(cur_y-maxVelocity>y_coord)
			    {
				if(maxVelocity>yVelocity)
				    cur_y-=yVelocity++;
				else
				    cur_y-=yVelocity;
			    }
			    else if(cur_y>y_coord)
			    {
				cur_y=y_coord; //skipped
				rotationSet=false;
			    }
			    else if(cur_y+maxVelocity<y_coord)
			    {
				if(maxVelocity>yVelocity)
				    cur_y+=yVelocity++;
				else
				    cur_y+=yVelocity;
			    }
			    else if(cur_y<y_coord)
			    {
				cur_y=y_coord; //skipped
				rotationSet=false;
			    }
			    entity.setX(cur_x);
			    entity.setY(cur_y);
			    position.first=cur_x;
			    position.second=cur_y;
			}
			else if(cur_x==x_coord&&cur_y==y_coord)
			{
			    path->pop();
			    rotationSet=false;
			}
	    }
	    else
	    {
			setSpeedY(0);
			setSpeedX(0);
	        pathComplete=true;
	    }
	}
//calculates the new angle and sets it in its own function
void AIShip::calculateNewAngle(pair<int,int> destination)
{
    //most of this initialization is currently still in follow path, but we want to use updateMovement so idk
    int x_coord=destination.first;
    int y_coord=destination.second;
    int cur_x=position.first;
    int cur_y=position.second;
    double xSlope=x_coord-cur_x;
    double ySlope=y_coord-cur_y;
    newAngle= atan2(-ySlope,xSlope);
    if(newAngle<0)
	newAngle+=2*PI;
    if(xSlope==0&&ySlope<0)
        newAngle=0;
    else if(ySlope==0&&xSlope<0)
        newAngle=270;
    else if(xSlope==0&&ySlope>0)
        newAngle=180;
    else if(ySlope==0&&xSlope>0)
        newAngle=90;
    else if(newAngle>0&&newAngle<PI/2)
        newAngle=(int)std::floor(newAngle*180/PI);
    else if(newAngle>PI/2&&newAngle<3*PI/2 && ySlope>0)
        newAngle=(int)std::floor(newAngle*180/PI);
    else if(newAngle>3*PI/2&&newAngle<2*PI)
        newAngle=(int)floor(newAngle*180/PI-180);
    else
        newAngle=(int)std::floor(newAngle*180/PI+180);
}
//rotate to the angle calculated
bool AIShip::rotateToAngle(Sprite& entity)
{
    double angle=entity.getAngle();
    if(newAngle>angle||newAngle-angle>=180)
    {
	//pretty shit acceleration stuff tbh
        if(newAngle>angle+maxRotation)
        {
            if(maxRotation>rotation)
        	entity.setAngle(angle+rotation++);
            else
                entity.setAngle(angle+rotation);
        }
        else
             entity.setAngle(angle+1);
        return true;
    }
    else if(newAngle<angle||newAngle-angle<-180)
    {
    	if(angle-maxRotation>newAngle)
        {
            if(maxRotation>rotation)
        	entity.setAngle(angle-(rotation++));
             else
                entity.setAngle(angle-rotation);
        }
        else
	    entity.setAngle(angle-1);
       return true;
    }
    return false;
}

void AIShip::setGoal(int newGoal)
{
    curGoal=newGoal;
}
int AIShip::getGoal()
{
    return curGoal;
}
bool AIShip::getPathComplete()
{
	return pathComplete;
}

void AIShip::setDestination(pair<int,int> newDestination)
{
	destination = newDestination;
}

pair<int,int> AIShip::getDestination()
{
	return destination;
}

void AIShip::setPath(queue<pair<int,int>>* thePath)
{
	//fullstops ship when setting path
	//cout<<"something"<<endl;
	xVelocity=0;
	yVelocity=0;
	rotation=0;
	maxVelocity=10;
	maxRotation=10;
	rotationSet=false;
    path = thePath;
    pathComplete=false;
}
