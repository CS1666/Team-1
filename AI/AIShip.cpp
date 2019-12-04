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
	maxVelocity=20;
	maxRotation=10;
	isUser=false;
	maxHp=50;
	currHp=50;
};

AIShip::AIShip(SDL_Rect dBox, SDL_Texture* aTex, int anim, bool ally): Ship(dBox, aTex, anim + ally) {
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
bool AIShip::followPath(vector<Sprite *>* osSprite)
    {
    	bool reCalPath = false;
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
				rotationSet=true;
			}
			float angle=getAngle();
			bool angleChanged=rotateToAngle();

			

			//note: since we don't have updateMovement implemented, most
			//of the stuff here can probably be removed/handled by that
			//simulate turning, acceleration of ship
			if(!angleChanged&&(cur_x != x_coord || cur_y != y_coord))
			{	
				setAnimate(true);
				Audio::play_thrust_sound();
				
			   	int xmov = 0;
			   	int ymov = 0;

			   	bool xai = false;
			   	bool yai = false; 

			  	cur_x = deterXAxisMovement(cur_x, x_coord, &xmov, &xai);
			  	cur_y = deterYAxisMovement(cur_y, y_coord, &ymov, &yai);


			  	reCalPath = colRes(osSprite, cur_x, cur_y, xmov, ymov, xai, yai);
			
			    
			    
			}
			else if(cur_x==x_coord&&cur_y==y_coord)
			{
			    path->pop();
			    rotationSet=false;
				setAnimate(false);
				setF1(0);
			}
	    }
	    else
	    {
			setSpeedY(0);
			setSpeedX(0);
	        pathComplete=true;
	    }

	    return reCalPath;
	}


int AIShip::deterXAxisMovement(int cur_x, int x_coord, int* xmov, bool* xai){

	int px = cur_x;
	cur_x= moveRight(cur_x, x_coord, xai);

	if(px != cur_x){
		*xmov = 1;
		return cur_x;
	}

	cur_x= moveLeft(cur_x, x_coord, xai);

	if(px != cur_x){
		*xmov = -1;
		return cur_x;
	}
	
	*xmov = 0;	
	return cur_x;
	
}


int AIShip::moveRight(int cur_x, int x_coord, bool* xai){

	if(cur_x+maxVelocity<x_coord)
	{
	    
		if(maxVelocity>xVelocity){
			*xai = true;
		    cur_x+=xVelocity++;
		}
		else{
			
		    cur_x+=xVelocity;
		}
	}
	else if(cur_x<x_coord)
	{
	    	
		cur_x=x_coord; //skipped
		rotationSet=false;
	}

	return cur_x;
}

int AIShip::moveLeft(int cur_x, int x_coord, bool* xai){

    if(cur_x-maxVelocity>x_coord)
    {
    	
		if(maxVelocity>xVelocity){
			
			*xai = true;
		    cur_x-=xVelocity++;
		}
		else{
	
		    cur_x-=xVelocity;
		}
    }
    else if(cur_x>x_coord)
    {
    	
		cur_x=x_coord; //skipped
		rotationSet=false;
    }

  	return cur_x;

}

int AIShip::deterYAxisMovement(int cur_y, int y_coord, int * ymov, bool* yai){

	int py = cur_y;
	
	cur_y= moveDown(cur_y, y_coord, yai);

	if(py != cur_y){
		*ymov = 1;
		return cur_y;
	}

	cur_y= moveUp(cur_y, y_coord, yai);

	if(py != cur_y){
		*ymov = -1;
		return cur_y;
	}

	
	
	*ymov = 0;	
	return cur_y;

}

int AIShip::moveUp(int cur_y, int y_coord, bool* yai){

    if(cur_y-maxVelocity>y_coord)
    {
    	
		if(maxVelocity>yVelocity){
			*yai = true;
		    cur_y-=yVelocity++;
		}
		else{
			
		    cur_y-=yVelocity;
		}
    }
    else if(cur_y>y_coord)
    {
    	
		cur_y=y_coord; //skipped
		rotationSet=false;
    }

    return cur_y;
}

int AIShip::moveDown(int cur_y, int y_coord, bool* yai){


	if(cur_y+maxVelocity<y_coord)
    {
    	
		if(maxVelocity>yVelocity){
			*yai = true;
		    cur_y+=yVelocity++;
		}
		else{
			
		    cur_y+=yVelocity;
		}
    }
    else if(cur_y<y_coord)
    {
    	
		cur_y=y_coord; //skipped
		rotationSet=false;
    }
			    

	return cur_y;
}	

bool AIShip::colRes(vector<Sprite *>* osSprite, int cur_x, int cur_y,int xmov, int ymov, bool xai, bool yai){
	bool reCalc = false;
	setX(cur_x);
    if(check_all_collisions(getDrawBox(), *osSprite)){
    	
    	if(xai){
    		xVelocity--;
    	}

    	if(xmov == 1){
    		setX(cur_x - xVelocity);
    		reCalc = true;
    	}
    	else if(xmov == -1){
    		setX(cur_x + xVelocity);
    		reCalc = true;
    	}

    		
	}
	
	
	setY(cur_y);
	if(check_all_collisions(getDrawBox(), *osSprite)){
		if(yai){
    		yVelocity--;
    	}
		
		if(ymov == 1){
    		setY(cur_y - yVelocity);
    		reCalc = true;
    	}
    	else if(ymov == -1){
    		setY(cur_y + yVelocity);
    		reCalc = true;
    	}	

	}

	return reCalc;
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

void AIShip::attackShip(pair<int,int> otherShip)
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
	//cout<<"fired"<<endl;
	rotationSet=false;
	timeActivated=SDL_GetTicks();
	fireWeapon();
    }
    //return Projectile(); //null/empty sprite
}

void AIShip::setHasTarget(bool nht){
	hasTarget = nht;
}
bool AIShip::getHasTarget(){
	return hasTarget;
}

void AIShip::setTargetShip(Ship* ts){
	targetShip = ts;
}
Ship* AIShip::getTargetShip(){
	return targetShip;
}
pair<int, int> AIShip::getTargetShipPos(){
	return targetShip->getPosition();
}

Fighter::Fighter(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 2, ally) {weaponType = 1;} ;

Cruiser::Cruiser(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 4, ally) {weaponType = 3;} ;

Capital::Capital(SDL_Rect dBox, SDL_Texture* aTex, bool ally): AIShip(dBox, aTex, 6, ally) {weaponType = 4;} ;
