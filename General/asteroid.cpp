#include "../General/asteroid.h"
using namespace std;


Asteroid::Asteroid(): Sprite() {};
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 2; isAst = true; };
Asteroid::Asteroid(SDL_Rect dBox, SDL_Texture* aTex, float speedX, float speedY): Sprite(dBox, aTex) {veloX = speedX; veloY = speedY; renderOrder = 2; isAst = true;};
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

float Asteroid::getMass()
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

void Asteroid::setMass(float m)
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

void Asteroid::setHP(float new_hp){
	hp = new_hp;
}

float Asteroid::getHP(){
	return hp;	
}

void Asteroid::updateAsteroids(std::vector<Sprite*> &osSprite, std::vector<Asteroid*> &osAst, Ship& playerent, int i)
{	
	
	// asteroids checking collision against each other
	for(int j = i + 1; j < osAst.size(); j++){
		if(check_collision(getDrawBox(), osAst.at(j)->getDrawBox())){
			collision_ast(*this, *osAst.at(j));
		}
	}
	
	if(check_collision(getDrawBox(), playerent.getDrawBox())){
			collision_hero(*this, playerent);
	}


	setAngle(getAngle()+rotation);
	setVeloX(veloX);
	setVeloY(veloY);
	setX(getTrueX() + veloX);
	setY(getTrueY() + veloY);

	// asteroids hp become zero if it hits a star or planet
	for(int k = 0; k != osSprite.size(); k++){
		if(!osSprite.at(k)->getIsAsteroid() && !osSprite.at(k)->isUI()){
			if(check_collision(getDrawBox(), osSprite.at(k)->getDrawBox())){	
				if(osSprite.at(k)->isCelestialBody()){
					setHP(0);	
				}
			}
		}
	}

	// flag for removal if hp = 0
	if(getHP() == 0){
		osAst.erase(osAst.begin() + i);
		remove = true;
	}

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
	
	ast1.setHP(ast1.getHP() - abs(m2 * 10));
	ast2.setHP(ast2.getHP() - abs(m1 * 10));
	
	ast1.setVeloX(tx * dpTan1 + nx * m1);
	ast1.setVeloY(ty * dpTan1 + ny * m1);
	ast2.setVeloX(tx * dpTan2 + nx * m2);
	ast2.setVeloY(ty * dpTan2 + ny * m2);
	
						
}

void Asteroid::collision_hero(Asteroid &ast, Ship &player){		
			
	float distance = sqrtf((ast.getTrueX() - player.getTrueX())*(ast.getTrueX() - player.getTrueX()) + (ast.getTrueY() - player.getTrueY())*(ast.getTrueY() - player.getTrueY()));
	float nx = (player.getTrueX() - ast.getTrueX()) / distance;
	float ny = (player.getTrueY() - ast.getTrueY()) / distance;

	float tx = -ny;
	float ty = nx;

	float dpTan1 = ast.getVeloX() * tx + ast.getVeloY() * ty;
	float dpTan2 = player.getSpeedX() * tx + player.getSpeedY() * ty;

	float dpNorm1 = ast.getVeloX() * nx + ast.getVeloY() * ny;
	float dpNorm2 = player.getSpeedX() * nx + player.getSpeedY() * ny;

	float m1 = (dpNorm1 * (ast.getMass() - player.getMass()) + 2.0f * player.getMass() * dpNorm2)/(ast.getMass() + player.getMass());
	float m2 = (dpNorm2 * (player.getMass() - ast.getMass()) + 2.0f * ast.getMass() * dpNorm1)/(ast.getMass() + player.getMass());
	
	// player gets knocked around and lose hp if they get hit by asteroids with 4 or higher mass
	// player takes no damage and causes asteroid to stop if it is sub 4 mass
	if(getMass() > 4){
		ast.setHP(ast.getHP() - abs(m2 * 10));
		player.setCurrHp(player.getCurrHp() - abs(m1 * 5));

		player.setX(player.getTrueX() + (tx * dpTan2 + nx * m2)*4);
		player.setY(player.getTrueY() + (ty * dpTan2 + ny * m2)*4);
	}else if (getMass() <= 4){
		ast.setHP(ast.getHP() - abs(m1 * 10));
		ast.setX(ast.getTrueX() - ast.getVeloX());
		ast.setY(ast.getTrueY() - ast.getVeloY());
	}
							
}



