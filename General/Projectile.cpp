#include "Projectile.h"
#include "Ship.h"

#define PI 3.14159265

Projectile::Projectile(): Sprite() {};

Projectile::Projectile(SDL_Rect dBox, SDL_Texture* aTex, int damage): Sprite(dBox, aTex), damage{damage * 10} {renderOrder = 1;};

Projectile::Projectile(const Projectile &spr): Sprite(spr.drawBox, spr.assetTex) {renderOrder = 1;};

void Projectile::updateMovement(std::vector<Sprite*> &osSprite, int ZONE_WIDTH, int ZONE_HEIGHT)
{
	float speedX = 10*cos((getAngle() - 90.0)*PI/180);
	float speedY = 10*sin((getAngle() - 90.0)*PI/180);
	
	setX(getTrueX() + speedX);
	/*if(getTrueX() < 0 

		|| (getX() + getW() > ZONE_WIDTH)
		|| check_all_collisions(getDrawBox(), osSprite)){
		remove = true;
	}*/
	setY(getTrueY() + speedY);
	if(getY() < 0 
		|| (getY() + getH() > ZONE_HEIGHT)
		|| check_all_collisions(getDrawBox(), osSprite)){
		
		remove = true;

		
	}
}

int Projectile::getDamage(){
	return damage;
}

bool Projectile::isProjectile(){
	return true;
}

bool Projectile::check_all_collisions(SDL_Rect* a, std::vector<Sprite*> &osSprite){
		bool isCollision = false;
		//std::cout << "osEntity.size() = " << osEntity.size() << std::endl;
		for (int i = 1; i < osSprite.size(); i++) {
			//so, one of these should result in collison if they are the same box
			if (osSprite.at(i)->isCircEnt()){
				isCollision |= check_collision(a, osSprite.at(i)->getCollisionCirc());
			}
			else{
				isCollision |= check_collision(a, osSprite.at(i)->getDrawBox());
				bool isColl2 = check_collision(a, osSprite.at(i)->getDrawBox());
				
				if (isColl2 && dynamic_cast<Ship*>(osSprite.at(i))){
					std::cout << dynamic_cast<Ship*>(osSprite.at(i))->getCurrHp() << std::endl;
					int oldHP = dynamic_cast<Ship*>(osSprite.at(i))->getCurrHp();
					int newHP = oldHP - getDamage();
					dynamic_cast<Ship*>(osSprite.at(i))->setCurrHp(newHP);
					std::cout << "Hit ship HP now " << oldHP << " - " << getDamage() << " = " << dynamic_cast<Ship*>(osSprite.at(i))->getCurrHp() << std::endl;
				}
			}
			//std::cout << "Is last command Illegal?" << std::endl;
			//std::cout << "Checked collisions: " << i << std::endl;
		}
		
		return isCollision;
}