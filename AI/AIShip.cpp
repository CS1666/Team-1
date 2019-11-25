#define PI 3.14159265
#include "AIShip.h"

AIShip::AIShip() : Ship() {};
AIShip::AIShip(SDL_Rect dBox, SDL_Texture* aTex, bool ally): Ship(dBox, aTex, 0) {
	renderOrder = 1;
	pathset = false;
	if(ally)
	{
	    isAlly=true;
	    freeForm=false;
	}
	else
	{
	    isAlly=false;
	    freeForm=true;
	}
	isAI = true;
	setX(dBox.x);
	setY(dBox.y);
	maxVelocity=10;
	maxRotation=10;
	isUser=false;
	maxHp=50;
	currHp=50;
};

//ai follows path assigned to it by ai class
void AIShip::followPath()
    {
	    //note: change the path in Ship.h to whatever is returned.
	    if(!path->empty())
	    {
			//note: assumed whatever we're using is some (x,y)
			pair<int,int> coords=path->front();
			int x_coord=coords.first;
			int y_coord=coords.second;
			int cur_x=getX();
			int cur_y=getY();
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
			float angle=getAngle();
			//cout<<"newAngle:"<<newAngle<<endl;
			//cout<<"cur angle: "<<angle<<endl;
			bool angleChanged=rotateToAngle();
			//entity.setAngle(122);
			//cout<<"cur_x: "<<cur_x<<" cur_y : "<<cur_y<<endl;
	        ////std::cout << "x: " << x_coord << " y: " << y_coord << "points remaing: " << path->size() << endl;
			//note: since we don't have updateMovement implemented, most
			//of the stuff here can probably be removed/handled by that
			//simulate turning, acceleration of ship
			if(!angleChanged&&(cur_x != x_coord || cur_y != y_coord))
			{	
				//cout<<"Here 1 "<<cur_y<<endl;
			    if(cur_x-maxVelocity>x_coord)
			    {
			    	//cout<<"Here 2 "<<cur_y<<endl;
					if(maxVelocity>xVelocity){
						//cout<<"Here 3 "<<cur_y<<endl;
					    cur_x-=xVelocity++;
					}
					else{
						//cout<<"Here 4 "<<cur_y<<endl;
					    cur_x-=xVelocity;
					}
			    }
			    else if(cur_x>x_coord)
			    {
			    	///cout<<"Here 5 "<<cur_y<<endl;
					cur_x=x_coord; //skipped
					rotationSet=false;
			    }
			    else if(cur_x+maxVelocity<x_coord)
			    {
			    	//cout<<"Here 6 "<<cur_y<<endl;
					if(maxVelocity>xVelocity){
						//cout<<"Here 7 "<<cur_y<<endl;
					    cur_x+=xVelocity++;
					}
					else{
						//cout<<"Here 8 "<<cur_y<<endl;
					    cur_x+=xVelocity;
					}
			    }
			    else if(cur_x<x_coord)
			    {
			    	//cout<<"Here 9 "<<cur_y<<endl;
					cur_x=x_coord; //skipped
					rotationSet=false;
			    }
			    if(cur_y-maxVelocity>y_coord)
			    {
			    	//cout<<"Here 10 "<<cur_y<<endl;
					if(maxVelocity>yVelocity){
						//cout<<"Here 11 "<<cur_y<<endl;
					    cur_y-=yVelocity++;
					}
					else{
						//cout<<"Here 12 "<<cur_y<<endl;
					    cur_y-=yVelocity;
					}
			    }
			    else if(cur_y>y_coord)
			    {
			    	//cout<<"Here 13 "<<cur_y<<endl;
					cur_y=y_coord; //skipped
					rotationSet=false;
			    }
			    else if(cur_y+maxVelocity<y_coord)
			    {
			    	//cout<<"Here 13"<<cur_y<<endl;
					if(maxVelocity>yVelocity){
						//cout<<"Here 14 "<<cur_y<<endl;
					    cur_y+=yVelocity++;
					}
					else{
						//cout<<"Here 15 "<<cur_y<<endl;
					    cur_y+=yVelocity;
					}
			    }
			    else if(cur_y<y_coord)
			    {
			    	//cout<<"Here 16 "<<cur_y<<endl;
					cur_y=y_coord; //skipped
					rotationSet=false;
			    }
			    //cout<<"Here 17 "<<cur_y<<endl;
			    setX(cur_x);
			    setY(cur_y);
			}
			else if(cur_x==x_coord&&cur_y==y_coord)
			{
				//cout<<"Here 18 "<<cur_y<<endl;
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
    int cur_x=getX();
    int cur_y=getY();
    //cout<<"curx: "<<cur_x<<endl;
    //cout<<"cury: "<<cur_y<<endl;
    //cout<<"destx: "<<x_coord<<endl;
    //cout<<"desty: "<<y_coord<<endl;
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
bool AIShip::rotateToAngle()
{
    double angle= getAngle();
    if(newAngle>angle||newAngle-angle>=180)
    {
	//pretty shit acceleration stuff tbh
        if(newAngle>angle+maxRotation)
        {
            if(maxRotation>rotation)
                setAngle(angle+rotation++);
            else
                setAngle(angle+rotation);
        }
        else
             setAngle(angle+1);
        return true;
    }
    else if(newAngle<angle||newAngle-angle<-180)
    {
    	if(angle-maxRotation>newAngle)
        {
            if(maxRotation>rotation)
        	    setAngle(angle-(rotation++));
             else
               setAngle(angle-rotation);
        }
        else
	    setAngle(angle-1);
       return true;
    }
    return false;
}
bool AIShip::isFreeForm()
{
    return freeForm;
}
Uint32 AIShip::getTime()
{
    return timeActivated;
}
void AIShip::switchFreeForm()
{
    freeForm=!freeForm;
}
void AIShip::setTime(Uint32 startTime)
{
    timeActivated=startTime;
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

bool AIShip::isPathSet(){
	return pathset;
}
void AIShip::resetVariables()
{
    xVelocity=0;
    yVelocity=0;
    rotation=0;
    rotationSet=false;
}
void AIShip::setPath(queue<pair<int,int>>* thePath)
{
    resetVariables();
    path = thePath;
    pathComplete=false;
  pathset = true;
}
//note: need the texture for fireWeapon, idk why though
Projectile AIShip::attackShip(pair<int,int> otherShip,SDL_Texture* laser)
{
    //first calculate the angle to rotate to
    if(!rotationSet)
    {
	calculateNewAngle(otherShip);
	rotationSet=true;
    }
    //rotate to that angle
    bool angleChanged=rotateToAngle();
    //if not rotate then we are at angle we can fire at ship
    //also 2 seconds between shooting a laser
    if(!angleChanged&&SDL_GetTicks()-timeActivated>2000)
    {
	cout<<"fired"<<endl;
	rotationSet=false;
	timeActivated=SDL_GetTicks();
	return fireWeapon(laser);
    }
    return Projectile(); //null/empty sprite
}
