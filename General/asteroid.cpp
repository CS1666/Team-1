#include "../General/asteroid.h"
using namespace std;


Asteroid::Asteroid(): Sprite() {};
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 2; isAst = true; mass = 1;};
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex, float speedX, float speedY): Sprite(dBox, aTex) {veloX = speedX; veloY = speedY; renderOrder = 2; isAst = true; mass = 1;};
Asteroid::~Asteroid()
{
	SDL_DestroyTexture(assetTex);
	assetTex = nullptr;
}

int Asteroid::getRadius()
{
	return radius;
}

int Asteroid::getVelocity()
{
	
	return velocity;
}

float Asteroid::getDirection()
{
	
	return direction;
}

long Asteroid::getMass()
{
	return mass;	
}

pair<int, int> Asteroid::getPosition()
{
	return position;
}

string Asteroid::getSprite()
{
	return sprite;
}

void Asteroid::setRadius(int r)
{
	radius = r;
}

void Asteroid::setVelocity(int v)
{
	velocity = v;
}

void Asteroid::setDirection(float d)
{
	direction = d;
}

void Asteroid::setPosition(pair<int, int> newPos)
{
	position = newPos;
}

void Asteroid::setSprite(string s)
{
	sprite = s;
}

void Asteroid::setMass(long m)
{
	mass = m;	
}

float Asteroid::getVeloX(){
	return veloX;
}

float Asteroid::getVeloY(){
	return veloY;
}

void Asteroid::setVeloX(float vX){
	veloX = vX;
}

void Asteroid::setVeloY(float vY){
	veloY = vY;
}

void Asteroid::updateAsteroids(std::vector<Sprite*> &osSprite, std::vector<Asteroid*> &osAst, int i)
{	
	
	// asteroids die if it crashes into a star or sun
	for(int k = 0; k != osSprite.size(); k++){
		if(!osSprite.at(k)->getIsAsteroid() && !osSprite.at(k)->isUI()){
			if(check_collision(getDrawBox(), osSprite.at(k)->getDrawBox())){	
				if(osSprite.at(k)->isCelestialBody()){
					for(int n = 0; n != osSprite.size(); n++){
						if((Sprite*)this == osSprite.at(n)){
							osAst.erase(osAst.begin() + i);
							osSprite.erase(osSprite.begin() + n);
						}
					}
				}
			}
		}
	}

	// asteroids checking collision against each other
	for(int j = i + 1; j != osAst.size(); j++){
		if(check_collision(getDrawBox(), osAst.at(j)->getDrawBox())){
			collision_ast(*this, *osAst.at(j));
		}
	}
	setAngle(getAngle()+rotation);
	setVeloX(veloX);
	setVeloY(veloY);
	setX(getTrueX() + veloX);
	setY(getTrueY() + veloY);

}

void Asteroid::collision_ast(Asteroid &ast1, Asteroid &ast2){		
			
	float distance = sqrtf((ast1.getTrueX() - ast2.getTrueX())*(ast1.getTrueX() - ast2.getTrueX()) + (ast1.getTrueY() - ast2.getTrueY())*(ast1.getTrueY() - ast2.getTrueY()));
	float nx = (ast2.getTrueX() - ast1.getTrueX()) / distance;
	float ny = (ast2.getTrueY() - ast1.getTrueY()) / distance;

	float tx = -ny;
	float ty = nx;

	float dpTan1 = ast1.getVeloX() * tx + ast1.getVeloY() * ty;
	float dpTan2 = ast2.getVeloX() * tx + ast2.getVeloY() * ty;

	float dpNorm1 = ast1.getVeloX() * nx + ast1.getVeloY() * ny;
	float dpNorm2 = ast2.getVeloX() * nx + ast2.getVeloY() * ny;

	float m1 = (dpNorm1 * (ast1.getMass() - ast2.getMass()) + 2.0f * ast2.getMass() * dpNorm2)/(ast1.getMass() + ast2.getMass());
	float m2 = (dpNorm2 * (ast2.getMass() - ast1.getMass()) + 2.0f * ast1.getMass() * dpNorm1)/(ast1.getMass() + ast2.getMass());

	ast1.setVeloX(tx * dpTan1 + nx * m1);
	ast1.setVeloY(ty * dpTan1 + ny * m1);
	ast2.setVeloX(tx * dpTan2 + nx * m2);
	ast2.setVeloY(ty * dpTan2 + ny * m2);
	
						
}



