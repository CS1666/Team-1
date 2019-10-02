
#include <SDL.h>
#include "gpEntity.h"



	gpEntity::gpEntity(): drawBox{0,0,0,0}, assetTex{NULL} {};

	gpEntity::gpEntity(SDL_Rect dBox, SDL_Texture* aTex): drawBox{dBox}, assetTex{aTex} {};

	gpEntity::~gpEntity(){};

	void gpEntity::setX(int x){
			drawBox.x = x;
		}
		int gpEntity::getX(){
			return drawBox.x;
		}
		void gpEntity::setY(int y){

			drawBox.y = y;
		}
		int gpEntity::getY(){
			return drawBox.y;
		}
		void gpEntity::setVX(int new_vx){
			vx = new_vx;
		}
		int gpEntity::getVX(){
			return vx;
		}
		void gpEntity::setVY(int new_vy){
			vy = new_vy;
		}
		int gpEntity::getVY(){
			return vy;
		}
		SDL_Rect* gpEntity::getDrawBox(){
			return &drawBox;
		}
		void gpEntity::updateDrawBox(){
			drawBox.x += vx;
			drawBox.y += vy;

		}
		void gpEntity::setTexture(SDL_Texture* tex){
			assetTex = tex;
		}
		SDL_Texture* gpEntity::getTexture(){
			return assetTex;
		}
		void gpEntity::handelEntityPos(int sw, int sh){
			updateDrawBox();

			if (drawBox.x >= sw - drawBox.w) {
				drawBox.x = sw - drawBox.w;
				
			}
			else if (drawBox.x <= 0) {
				drawBox.x = 0;
			
			}
			if (drawBox.y >= sh -  drawBox.h) {
				drawBox.y = sh - drawBox.h;
				
			}
			else if (drawBox.y <= 0) {
				drawBox.y = 0;
				
			}

		}









