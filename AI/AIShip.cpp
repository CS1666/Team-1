
#define PI 3.14159265
#include "AIShip.h"

AIShip::AIShip() : Ship() {};
AIShip::AIShip(SDL_Rect dBox, SDL_Texture* aTex): Ship(dBox, aTex, 0) {renderOrder = 1;};

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
		int cur_x=position.first;
		int cur_y=position.second;
		double xSlope=x_coord-cur_x;
		double ySlope=y_coord-cur_y;
		//get angle of destination
		if(!rotationSet)
		{
			//if(y_coord>cur_y)
			curRotation= atan2(-ySlope,xSlope);
			if(curRotation<0)
			    curRotation+=2*PI;
			//cout<<"radian cur: "<<curRotation<<endl;
			char n;
			if(xSlope==0&&ySlope<0)
			    curRotation=0;
			else if(ySlope==0&&xSlope<0)
			    curRotation=270;
			else if(xSlope==0&&ySlope>0)
			    curRotation=180;
			else if(ySlope==0&&xSlope>0)
			    curRotation=90;
			else if(curRotation>0&&curRotation<PI/2)
			{
			    curRotation=(int)std::floor(curRotation*180/PI);
			//	cout<<"first quad"<<endl;
			//	cin>>n;
			}
			else if(curRotation>PI/2&&curRotation<3*PI/2 && ySlope>0)
			{
			    curRotation=(int)std::floor(curRotation*180/PI);
			//	cout<<"second quad"<<endl;
			//	cin>>n;
			}
			else if(curRotation>3*PI/2&&curRotation<2*PI)
			{
			    curRotation=(int)floor(curRotation*180/PI-180);
				//cout<<"third quad"<<endl;
				//cin>>n;
			}
			else
			{
			    curRotation=(int)std::floor(curRotation*180/PI+180);
			    //cout<<"fourth quad"<<endl;
			   //cin>>n;
			}
			//cout<<"rotation: "<<curRotation<<endl;
			//int n;
			//cin>>n;
			rotationSet=true;
		}
		double angle= getAngle();
		cout<<"currotation:"<<curRotation<<endl;
		cout<<"cur angle: "<<angle<<endl;
		bool angleChanged=false;
		if(curRotation>angle||curRotation-angle>=180)
		{
		    //pretty shit acceleration stuff tbh
		    if(curRotation>angle+maxRotation)
		    {
			if(maxRotation>rotation)
			    setAngle(angle+rotation++);
			else
			    setAngle(angle+rotation);
		    }
		    else
		        setAngle(angle+1);
		    angleChanged=true;
		}
		else if(curRotation<angle||curRotation-angle<-180)
		{
		    if(angle-maxRotation>curRotation)
		    {
			if(maxRotation>rotation)
			    setAngle(angle-(rotation++));
			else
			    setAngle(angle-rotation);
		    }
		    else
			 	setAngle(angle-1);
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
		    setX(cur_x);
		    setY(cur_y);
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
