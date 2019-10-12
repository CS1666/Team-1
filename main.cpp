#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "AI/ai_enviroment.h"
#include "Level_Generation/lg_enviroment.h"
#include "Physics/phy_enviroment.h"
#include "General/demo.h"
#include "General/gpRender.h"


int main(int argc, char** argv) {

	if(argc==1){
		std::cout <<  "Demo!" << std::endl;
		gpRender gr("A DEMO");

		if (!gr.isRInit()) {
			std::cout <<  "Failed to initialize!" << std::endl;
			return 1;
		}

		run_demo(gr);
		gr = nullptr;
	}
	
	//AI Enviroment: a
	if(argc==2 && strcmp(argv[1],"a")==0)
	{
		std::cout <<  "AI!" << std::endl;
		gpRender gr("AI ENVIROMENT");

		if (!gr.isRInit()) {
			std::cout <<  "Failed to initialize!" << std::endl;
			return 1;
		}
		run_ai_enviro(gr);
		gr = nullptr;
	}

	//Level Gen Enviroment: l
	else if(argc==2 && strcmp(argv[1],"l")==0)
	{
		gpRender gr("LEVEL GEN ENVIROMENT");

		if (!gr.isRInit()) {
			std::cout <<  "Failed to initialize!" << std::endl;
			return 1;
		}
		run_lg_enviro(gr);
		gr = nullptr;

	}
	//Physic Enviroment:p
	else if(argc==2 && strcmp(argv[1],"p")==0){
		gpRender gr("PHYSICS ENVIROMENT");

		if (!gr.isRInit()) {
			std::cout <<  "Failed to initialize!" << std::endl;
			return 1;
		}
		run_phy_enviro(gr);
		delete &gr;
		gr = nullptr;

	}
	//credits mode: c
	else if(argc==2 && strcmp(argv[1],"c")==0)
	{
		gpRender gr("CREDITS");

		if (!gr.isRInit()) {
			std::cout <<  "Failed to initialize!" << std::endl;
			return 1;
		}
		std::vector<SDL_Texture*> gTex;

		gTex.push_back(gr.loadImage("Assets/Credits/credits.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/ai.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/cs1666_gjc26.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_mrs185.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_evs25.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/cs1666_jcz18.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/level-generation.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_pjo13.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/cs1666_pep24.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/Keith C Stebler.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/physics.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_MCD66.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/cs1666_kel117.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_Linghai.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/CS1666_apw50.png"));
        gTex.push_back(gr.loadImage("Assets/Credits/fin.png"));
        for(auto image : gTex){
                SDL_RenderClear(gr.getRender());

                // Render the image
                SDL_RenderCopy(gr.getRender(), image, NULL, NULL);
                // Display rendering
                SDL_RenderPresent(gr.getRender());
                // Wait 5 seconds
                SDL_Delay(5000);

        }
        gr = nullptr;

	}


	
	
}




