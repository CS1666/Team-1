#include "Projectile.h"

#define PI 3.14159265

Projectile::Projectile(): Sprite() {};

Projectile::Projectile(SDL_Rect dBox, SDL_Texture* aTex): Sprite(dBox, aTex) {renderOrder = 1;};

Projectile::Projectile(const Projectile &spr): Sprite(spr.drawBox, spr.assetTex) {renderOrder = 1;};

void Projectile::updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT)
{
	float speedX = 10*cos((getAngle() - 90.0)*PI/180);
	float speedY = 10*sin((getAngle() - 90.0)*PI/180);
	
	setX(getTrueX() + speedX);
	/*if(getTrueX() < 0 

		|| (getX() + getW() > ZONE_WIDTH)
		|| check_all_collisions(getDrawBox(), osSprite)){

		setX(getTrueX() - speedX);
	}*/
	setY(getTrueY() + speedY);
	/*if(getY() < 0 
		|| (getY() + getH() > ZONE_HEIGHT)
		|| check_all_collisions(getDrawBox(), osSprite)){

		setY(getTrueY() - speedY);
	}*/
}