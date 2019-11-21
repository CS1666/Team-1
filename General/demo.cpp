#include "demo.h"

std::vector<std::pair<int, int>> randNum(){

	std::vector<int> coorX;
	std::vector<int> coorY;
	std::vector<std::pair<int, int>> coords;

	srand(time(0));
	
	for(int i = 0; i<10; i++){
		coorX.push_back((rand()%100));
	}
	
	for(int i = 0; i<10; i++){
		coorY.push_back((rand()%200));
	}

	coords.reserve(10);
	std::transform(coorX.begin(), coorX.end(), coorY.begin(), std::back_inserter(coords), 
		[](int a, int b){return std::make_pair(a, b);});

	for(int k = 0; k<10; k++){
	 	std::cout << coords[k].first << ", " << coords[k].second << endl;
	}

	 return coords;
}
std::tuple<int, int, std::string, std::string, std::string, std::string> callAsset(){
	int assetNumSun = rand()%3 + 1;
	switch(assetNumSun){
		case 1:
		{
			std::tuple<int, int, std::string, std::string, std::string,std::string> sunAsset(332, 315, "Assets/Objects/red_giant.png", "Assets/Objects/planetfar.png", "Assets/Objects/planetmid.png","Assets/Objects/planetmid.png");
			return sunAsset;
		}
			break;
		case 2:
		{
			std::tuple<int, int, std::string, std::string, std::string, std::string> sunAsset(250, 250,  "Assets/Objects/white_dwarf.png","Assets/Objects/Asteroid.png", "Assets/Objects/planetmid.png","Assets/Objects/planetnear.png");
			return sunAsset;
		}
			break;
		case 3:
		{
			std::tuple<int, int, std::string, std::string, std::string, std::string> sunAsset(300, 300,  "Assets/Objects/yellow_dwarf.png", "Assets/Objects/planetmid.png", "Assets/Objects/planetmid.png","Assets/Objects/planetnear.png");
			return sunAsset;
		}
			break;
		default:
		{
			std::tuple<int, int, std::string, std::string, std::string, std::string> sunAsset(332, 315, "Assets/Objects/red_giant.png", "Assets/Objects/planetfar.png", "Assets/Objects/planetmid.png","Assets/Objects/planetmid.png");
			return sunAsset;
		}
			break;
	}
}
constexpr int PLAYER_WIDTH = 52;
constexpr int PLAYER_HEIGHT = 60;
constexpr int ZONE_WIDTH = 3840; 
constexpr int ZONE_HEIGHT = 2160;

void run_demo(gpRender gr){
	Sector sector;
	sector.setSize({ZONE_WIDTH, ZONE_HEIGHT});

	Ellers_Maze seed;
	int sunSeed = seed.getSeed();
	int seed2 = sunSeed + 100;
	srand(seed.getSeed());
	//std::cout << seed << "," << seed2 << endl;
	//Vector used to store all on screen entities

	std::vector<Sprite*> osSprite; // vector for collision checker and rendering

	std::vector<Ship*> osShip; // vector for tracking ships
	//tuple to control the sun and subsequent spawns
	std::tuple<int, int, std::string, std::string, std::string, std::string> sunAsset = callAsset();
	vector<SDL_Texture*> allTextures=initTextures(gr);

	//Audio Initilization
	Audio::load_chunk("Assets/Objects/thrustSoundSmall.wav");

	Audio::load_music("Assets/Sound/spacegamemainsound.wav");
	Audio::set_solar(true);
	//Camera Initilization
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


	bool fixed = false;
	bool something = true;
	//call tuple stuff
	int sunHeight = std::get<0>(sunAsset);
	int sunWidth = std::get<1>(sunAsset); 
	std::string z = std::get<2>(sunAsset);
	std::string q = std::get<3>(sunAsset);
	std::string u = std::get<4>(sunAsset);
	std::string o = std::get<5>(sunAsset);

	std::vector <std::pair<int, int>> randCoords = randNum();

	//Player Entity Initilizaiton
	SDL_Texture* tex = gr.loadImage("Assets/Objects/ship_player.png");
	SDL_Rect db = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2,PLAYER_WIDTH,PLAYER_HEIGHT};
	//Ship playerent(db, tex, 0);
	Hero playerent(db, tex);
	//playerent.setRenderOrder(0);
	playerent.setCurrHp(100);
	playerent.setMaxHp(100);
	osSprite.push_back(&playerent);
	sector.addShips(&playerent);
	
	//SDL_Texture* tex2 = gr.loadImage(z);
	//if(something == true){
	SDL_Texture* tex2 = gr.loadImage(z);
	SDL_Rect db2 = {ZONE_WIDTH/2,ZONE_HEIGHT/2,sunHeight,sunWidth};
	NSDL_Circ dc2 = {db2};
	Star starent(db2, tex2, dc2);
	starent.setSize({sunHeight,sunWidth});
	starent.setPosition({ZONE_WIDTH/2,ZONE_HEIGHT/2});
	osSprite.push_back(&starent);
	//}
	sector.addStars(&starent);

	SDL_Texture* tex3 = gr.loadImage(q);
	SDL_Rect db3 = {randCoords[0].first,randCoords[0].second,200,200};
	NSDL_Circ dc3 = {db3};
	Planet planet1ent(db3, tex3, dc3,starent);
	osSprite.push_back(&planet1ent);
	sector.addPlanet(&planet1ent);

	SDL_Texture* tex4 = gr.loadImage(u);
	SDL_Rect db4 = {randCoords[1].first + rand()%100 + ZONE_WIDTH/4,randCoords[1].second+ 400,200,200};
	NSDL_Circ dc4 = {db4};
	Planet planet2ent(db4, tex4, dc4,starent);
	osSprite.push_back(&planet2ent);
	sector.addPlanet(&planet2ent);


	SDL_Texture* tex5 = gr.loadImage(o);
	SDL_Rect db5 = {randCoords[2].first +rand()%100 + ZONE_WIDTH/3,randCoords[2].second+ rand()%100 + ZONE_HEIGHT/3,200,200};
	NSDL_Circ dc5 = {db5};

	Planet planet3ent(db5, tex5, dc5,starent);

	osSprite.push_back(&planet3ent);
	sector.addPlanet(&planet3ent);


	SDL_Texture* tex6 = gr.loadImage(o);
	SDL_Rect db6 = {randCoords[3].first +rand()%200 + 2300	,randCoords[3].second+rand()%100 + ZONE_HEIGHT/3,200,200};
	NSDL_Circ dc6 = {db6};
	Planet planet4ent(db6, tex6, dc6,starent);
	osSprite.push_back(&planet4ent);
	sector.addPlanet(&planet4ent);


	SDL_Texture* tex7 = gr.loadImage(q);
	SDL_Rect db7 = {randCoords[4].first + 2000,randCoords[4].second,200,200};
	NSDL_Circ dc7 = {db7};
	
	Planet planet5ent(db7, tex7, dc7,starent);

	osSprite.push_back(&planet5ent);
	sector.addPlanet(&planet5ent);

	SDL_Texture* tex8 = gr.loadImage(u);
	SDL_Rect db8 = {randCoords[5].first + 1800,randCoords[5].second + 500,200,200};
	NSDL_Circ dc8 = {db8};
	
	Planet planet6ent(db8, tex8, dc8,starent);

	osSprite.push_back(&planet6ent);
	sector.addPlanet(&planet6ent);

	SDL_Texture* tex9 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db9 = {randCoords[6].first + 1000,randCoords[6].second + 1000,35,35};
	Asteroid asteroid1ent(db9, tex9);

	osSprite.push_back(&asteroid1ent);
	sector.addAsteroid(&asteroid1ent);	

	SDL_Texture* tex10 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db10 = {randCoords[7].first + 800,randCoords[7].second + 1000,35,35};
	Asteroid asteroid2ent(db10, tex10);
	sector.addAsteroid(&asteroid2ent);

	osSprite.push_back(&asteroid2ent);

	SDL_Texture* tex11 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db11 = {randCoords[8].first + 1100,randCoords[8].second + 1000,35,35};
	Asteroid asteroid3ent(db11, tex11);
	sector.addAsteroid(&asteroid3ent);

	osSprite.push_back(&asteroid3ent);

	SDL_Texture* tex12 = gr.loadImage("Assets/Objects/Asteroid.png");
	SDL_Rect db12 = {randCoords[9].first + 600,randCoords[9].second + 1000,35,35};
	Asteroid asteroid4ent(db12, tex12);
	sector.addAsteroid(&asteroid4ent);

	osSprite.push_back(&asteroid4ent);
	
	SDL_Texture* texhp = gr.loadImage("Assets/Objects/hp_bar.png");
	SDL_Rect hp = {10,10,300,20};
	HpBar hpent(hp, texhp, playerent.getCurrHp()/playerent.getMaxHp());
	osSprite.push_back(&hpent);
	
	SDL_Texture* mapTex = gr.loadImage("Assets/Objects/map.png");
	SDL_Rect mapRect = {1170,10,100,100};
	HpBar mapent(mapRect, mapTex, 0);
	osSprite.push_back(&mapent);

	SDL_Texture* tex_ss = gr.loadImage("Assets/Objects/spacestation.png");
	SDL_Rect rect_ss = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2 - 200,PLAYER_WIDTH,PLAYER_HEIGHT};
	SpaceStation ss_ent(rect_ss, tex_ss);
	ss_ent.setPosition(std::vector<int>{SCREEN_WIDTH/2 - PLAYER_WIDTH/2,SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2 - 200 });
	osSprite.push_back(&ss_ent);

	SDL_Texture* e_tex = gr.loadImage("Assets/Objects/E.png");
	SDL_Rect e_rect = {50, 50, 100, 100};
	SpaceStationUI e_UI(e_rect, e_tex);

	SDL_Texture* r_tex = gr.loadImage("Assets/Objects/R.png");
	SDL_Rect r_rect = {50, 200, 100, 100};
	SpaceStationUI r_UI(r_rect, r_tex);

	SDL_Texture* ss_UI_tex = gr.loadImage("Assets/Objects/spaceStation.png");
	SDL_Rect ss_UI_rect = { 300, 100, 200, 200};
	SpaceStationUI ss_UI(ss_UI_rect, ss_UI_tex);

	bool in_space_station_menu = false;
	bool is_space_station_in_range = false;
	
	//Sector 1
	SDL_Texture* sector1Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector1Rect = {1184,25,15,15};
	HpBar sector1ent(sector1Rect, sector1Tex, 0);
	osSprite.push_back(&sector1ent);
	//Sector 2
	SDL_Texture* sector2Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector2Rect = {1213,25,15,15};
	HpBar sector2ent(sector2Rect, sector2Tex, 0);
	osSprite.push_back(&sector2ent);
	//Sector 3
	SDL_Texture* sector3Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector3Rect = {1242,25,15,15};
	HpBar sector3ent(sector3Rect, sector3Tex, 0);
	osSprite.push_back(&sector3ent);
	//Sector 4
	SDL_Texture* sector4Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector4Rect = {1184,52,15,15};
	HpBar sector4ent(sector4Rect, sector4Tex, 0);
	osSprite.push_back(&sector4ent);
	//Sector 5
	SDL_Texture* sector5Tex = gr.loadImage("Assets/Objects/contestedControl.png");
	SDL_Rect sector5Rect = {1213,52,15,15};
	HpBar sector5ent(sector5Rect, sector5Tex, 0);
	osSprite.push_back(&sector5ent);
	//Sector 6
	SDL_Texture* sector6Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector6Rect = {1242,52,15,15};
	HpBar sector6ent(sector6Rect, sector6Tex, 0);
	osSprite.push_back(&sector6ent);
	//Sector 7
	SDL_Texture* sector7Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector7Rect = {1184,79,15,15};
	HpBar sector7ent(sector7Rect, sector7Tex, 0);
	osSprite.push_back(&sector7ent);
	//Sector 8
	SDL_Texture* sector8Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector8Rect = {1213,79,15,15};
	HpBar sector8ent(sector8Rect, sector8Tex, 0);
	osSprite.push_back(&sector8ent);
	//Sector 9
	SDL_Texture* sector9Tex = gr.loadImage("Assets/Objects/enemySector.png");
	SDL_Rect sector9Rect = {1242,79,15,15};
	HpBar sector9ent(sector9Rect, sector9Tex, 0);
	osSprite.push_back(&sector9ent);
	//current sector
	int curSector = 5;
	
	SDL_Texture* mapSectors[] = {sector1Tex, sector2Tex, sector3Tex, sector4Tex, sector5Tex, sector6Tex, sector7Tex, sector8Tex, sector9Tex};
	

	/*
	//Ship Cruiser initilization
	SDL_Texture* tex3 = gr.loadImage("Assets/Objects/ship_cruiser_enemy.png");
	SDL_Rect db3 = {400,300,225,300};
	Sprite emyent(db3, tex3);
	*/

	SDL_Texture* ltex = gr.loadImage("Assets/Objects/laser.png");


	SDL_Rect bgtile[100];
	std::vector<std::vector<SDL_Rect*> > bgzonelayer1( ZONE_WIDTH/20 , std::vector<SDL_Rect*> (ZONE_HEIGHT/20, 0));
	std::vector<std::vector<SDL_Rect*> > bgzonelayer2( ZONE_WIDTH/40 , std::vector<SDL_Rect*> (ZONE_HEIGHT/40, 0));
	std::vector<int> bggalaxies(4);

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			bgtile[x + 10*y].x = x * 40;
			bgtile[x + 10*y].y = y * 40;
			bgtile[x + 10*y].w = 40;
			bgtile[x + 10*y].h = 40;
		}
	}
	
	for (int x = 0; x < ZONE_WIDTH/20; x++) {
		for (int y = 0; y < ZONE_HEIGHT/20; y++) {
			bgzonelayer1[x][y] = &bgtile[rand() % 100];
			if ((x < ZONE_WIDTH/40) && (y < ZONE_HEIGHT/40)) {
				bgzonelayer2[x][y] = &bgtile[rand() % 100];
			}
		}
	}

	//random background galaxies
	bggalaxies[0] = rand() % (ZONE_WIDTH - 200);
	bggalaxies[1] = rand() % (ZONE_HEIGHT - 200);
	
	bggalaxies[2] = rand() % (ZONE_WIDTH - 200);
	bggalaxies[3] = rand() % (ZONE_HEIGHT - 200);

	SDL_Event e;
	bool gameon = false;
	int animation = 0;
	bool cycle;
	bool animate = false;
	int titleFrame = 0;
	// title screen
	SDL_Texture* titletex = gr.loadImage("Assets/Objects/title1.png");
	SDL_Texture* titletex2 = gr.loadImage("Assets/Objects/title2.png");
	SDL_Rect title = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Event s;
	
	vector<AIShip*> aiControlled;

	AI ai;

	


	

	sector.setShips({&playerent});
	sector.setSpaceStation(&ss_ent);

	


	ai.createMapState(&sector);
	
	ai.setCurrentSector(&sector);


	vector<vector<bool> > mesh = ai.getMapState();

	pair<int,int> sectorSize;

	sectorSize.first=ZONE_WIDTH;
	
	sectorSize.second=ZONE_HEIGHT;
	ai.setSectorSize(sectorSize);
	Pathfinder path(mesh, 10);

	ai.setPathfinder(&path);
	ai.setPlayerShip(&playerent);
	ai.setShips(&aiControlled);
	ai.setSprites(&osSprite);
	ai.setTextures(&allTextures);

	Audio::play_music();
	
	while(!gameon){
		if(titleFrame == 0){
			SDL_RenderCopy(gr.getRender(), titletex, nullptr, &title);
			titleFrame++;
		}else{
			SDL_RenderCopy(gr.getRender(), titletex2, nullptr, &title);
			titleFrame--;
		}
		SDL_RenderPresent(gr.getRender());
		SDL_Delay(300);
		// start game when enter key is pressed
		while(SDL_PollEvent(&s)){	
			switch(s.key.keysym.sym){ 
				case SDLK_RETURN:
					if(s.type == SDL_KEYDOWN){
						SDL_RenderClear(gr.getRender());
						gameon = true;
					}
			}	
			
		}
	}

	int startPlayerX = playerent.getX();
	int startPlayerY = playerent.getY();
	
	std::vector<int> toErase;

	while(gameon)
	{
		playerent.setX(startPlayerX);
		playerent.setY(startPlayerY);
		playerent.speed = 0;
		playerent.deltaV = 0;
		int side = 0;
		
		SDL_RenderClear(gr.getRender());
		bool solar = true;
		int frames = 0;

		//Game Loop
		while(gameon && solar)
		{	
			gr.setFrameStart(SDL_GetTicks());
			TimeData::update_timestep();
			ai.createShip(false);
			ai.executeAIActions();
			// Checking for if the Space Station is in range of the player ship.
			if(!is_space_station_in_range){
				if(check_proximity(playerent, ss_ent, 3)){
					//then we set the is_space_station_in_range flag to true
					is_space_station_in_range = true;
					//we display the E png to show that space station can be accessed
					e_UI.set_spriteIndex(osSprite.size());
					osSprite.push_back(&e_UI);
				}
			} else {
				//we need to check if our ship has left the range of the space station
				if(!check_proximity(playerent, ss_ent, 3)){
					if(in_space_station_menu) {
						osSprite.erase(osSprite.begin() + ss_UI.get_spriteIndex());
					}
					osSprite.erase(osSprite.begin() + e_UI.get_spriteIndex());

					is_space_station_in_range = false;
					in_space_station_menu = false;
				}
			}

			// Deletes 0 hp ships
			for(std::size_t i = 0; i != osShip.size(); i++){
				if(osShip.at(i)->getCurrHp() <= 0){
					for(std::size_t j = 0; j != osSprite.size(); j++){
						if((Sprite*)osShip.at(i) == osSprite.at(j)){
							osShip.erase(osShip.begin() + (i--));
							osSprite.erase(osSprite.begin() + j);
						}
					}
				}
			}

			//Handles all incoming Key events
			while(SDL_PollEvent(&e)) {

				gameon = playerent.handleKeyEvents(e);

				switch(e.key.keysym.sym) {
					case SDLK_w:
						if(e.type == SDL_KEYDOWN){
							animate = true;
						}
						else if (e.type == SDL_KEYUP){
							animate = false;
						}
						break;

					case SDLK_m:
						if(e.type == SDL_KEYDOWN){
							solar = false;
						}
						break;
					case SDLK_SPACE:
						if (SDL_GetTicks() - playerent.getFireLastTime() > 200) {
							osSprite.push_back(new Projectile(playerent.fireWeapon(ltex)));					
						}
						break;
					
					case SDLK_e:
						if(e.type == SDL_KEYDOWN){
							if(!in_space_station_menu && is_space_station_in_range){
								in_space_station_menu = true;
								ss_UI.set_spriteIndex(osSprite.size());
								osSprite.push_back(&ss_UI);
								r_UI.set_spriteIndex(osSprite.size());
								osSprite.push_back(&r_UI);
							}
						}
						break;
				}
			}

			// --- START OF SPACE STATION UI SUB-LOOP ----
			while(in_space_station_menu && gameon) {
				while(SDL_PollEvent(&e)) {
				gameon = handleKeyEvents(e, playerent);	
				
					switch(e.key.keysym.sym) {
						
						case SDLK_e:
							if(e.type == SDL_KEYDOWN){
								if(in_space_station_menu && is_space_station_in_range) {
									in_space_station_menu = false;
									osSprite.erase(osSprite.begin() + r_UI.get_spriteIndex());
									osSprite.erase(osSprite.begin() + ss_UI.get_spriteIndex());
								}
							}
							break;
		
						case SDLK_r:
							if(e.type == SDL_KEYDOWN){
								ai.createShip(true);
								
							}
							break;
					}
				}
				gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2, camera, fixed);
			}
			//--- END OF SPACE STATION UI SUB LOOP ---

			hpent.setPercentage((float)playerent.getCurrHp()/(float)playerent.getMaxHp());
			hpent.changeBar(playerent);


			for(auto ent : osSprite) {
				if(!ent->getIsAI())
					ent->updateMovement(osSprite, ZONE_WIDTH, ZONE_HEIGHT);
				if(ent->getRenderOrder() == 0 && ent->getAnimate())
					ent->updateAnimation();
			}
			if(sector.getPlanets().size() > 0)
			{
				for( auto ent : sector.getPlanets())
				{
					ent->updatePosition(playerent);
				}
			}
			else
			{
				planet1ent.updatePosition(playerent);	
				planet2ent.updatePosition(playerent);	
				planet4ent.updatePosition(playerent);	
			}
			if(playerent.getTrueX() < 0 || (playerent.getX() + playerent.getW() > ZONE_WIDTH) || playerent.getY() < 0 || (playerent.getY() + playerent.getH() > ZONE_HEIGHT))
			{
				
				solar = false;
				if(playerent.getTrueX() < 0)
				{
					if(curSector != 1 && curSector != 4 && curSector != 7)
					{
						side = 2;
						curSector--;
					}
					else
					{
						//set x = 0
						playerent.setX(0);
						solar = true;
					}
				}
				else if(playerent.getX() + playerent.getW() > ZONE_WIDTH)
				{
					if(curSector != 3 && curSector != 6 && curSector != 9)
					{
						side = 0;
						curSector++;
					}
					else
					{
						//set x = ZONE_WIDTH	
						playerent.setX(ZONE_WIDTH - PLAYER_WIDTH);
						solar = true;
					}
				}
				else if(playerent.getY() < 0)
				{
					if(curSector != 1 && curSector != 2 && curSector != 3)
					{
						side = 1;
						curSector -= 3;
					}
					else
					{
						//set y = 0
						playerent.setY(0);
						solar = true;
					}
				}
				else if(playerent.getY() + playerent.getH() > ZONE_HEIGHT)
				{
					if(curSector != 7 && curSector != 8 && curSector != 9)
					{
						side = 3;
						curSector += 3;
					}
					else
					{
						//set y = ZONE_HEIGHT
						playerent.setY(ZONE_HEIGHT - PLAYER_WIDTH);
						solar = true;
					}
				}	
				else
				{
					solar = true;
				}
				
			}
      
			
			frames++;
			if(frames > 120){
				frames = 0;
				if(curSector == 1){
					sector1Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 2){
					sector2Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 3){
					sector3Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 4){
					sector4Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 5){
					sector5Tex = gr.loadImage("Assets/Objects/currentSector.png");
					HpBar sector5ent2(sector5Rect, sector5Tex, 1);
					osSprite.push_back(&sector5ent2);
				}
				else if(curSector == 6){
					sector6Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 7){
					sector7Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 8){
					sector8Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
				else if(curSector == 9){
					sector9Tex = gr.loadImage("Assets/Objects/currentSector.png");
				}
			}
			else if(frames > 60){
				if(curSector == 1){
					sector1Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 2){
					sector2Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 3){
					sector3Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 4){
					sector4Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 5){
					sector5Tex = gr.loadImage("Assets/Objects/enemySector.png");
					HpBar sector5ent2(sector5Rect, sector5Tex, 1);
					osSprite.push_back(&sector5ent2);
				}
				else if(curSector == 6){
					sector6Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 7){
					sector7Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 8){
					sector8Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
				else if(curSector == 9){
					sector9Tex = gr.loadImage("Assets/Objects/enemySector.png");
				}
			}
			
			
			TimeData::update_move_last_time();

			/*if (animate){
				if (TimeData::getTimeSinceAnim() > 100) {
					if (animation <= 1){
						cycle = true;
					}
					else if(animation == 3){
						cycle = false;
					}
					
					if (cycle){
						animation++;
					}
					else{
						animation--;
					}
					
					TimeData::update_anim_last_time();
					playerent.setF(animation);
				}
			}
			else{
				animation = 0;
				playerent.setF(animation);
			}*/

			//Renders all renderable objects onto the screen

			camera.x = playerent.getX() - SCREEN_WIDTH/2 + PLAYER_WIDTH/2;
			camera.y = playerent.getY() - SCREEN_HEIGHT/2 + PLAYER_HEIGHT/2;
			
			if (camera.x < 0){
				camera.x = 0;
				fixed = true;
			}
			else if (camera.x + SCREEN_WIDTH > ZONE_WIDTH){
				camera.x = ZONE_WIDTH - SCREEN_WIDTH;
				fixed = true;
			}
			if (camera.y < 0){
				camera.y = 0;

				fixed = true;
			}
			else if (camera.y + SCREEN_HEIGHT > ZONE_HEIGHT){
				camera.y = ZONE_HEIGHT - SCREEN_HEIGHT;
				fixed = true;bgzonelayer1;
			}
			
			
			
			for(std::size_t i = 0; i != osSprite.size(); i++){
				if(osSprite.at(i)->shouldRemove())
				{
					toErase.push_back(i);
				}
			}
			for(auto i : toErase)
			{
				osSprite.erase(osSprite.begin()+i);
			}
			toErase.clear();
			gr.renderOnScreenEntity(osSprite, bggalaxies, bgzonelayer1, bgzonelayer2,  camera, fixed);
			Audio::set_solar(solar);
		}
		
		Ellers_Maze maze(side);
		SDL_RenderClear(gr.getRender());
		bool mazeCheck = true;
		int col = maze.getStartRow();
		int row = maze.getStartCol();
		int numCols = maze.getRowSize();
		int numRows = maze.getColSize();
		int indexSize = 36;
		SDL_Texture* warpTex = gr.loadImage("Assets/Objects/warpShip.png");
		int spawnCol = 7 + col * indexSize;
		int spawnRow = 10 + row * indexSize;
		int spotCol = -1273 + col * indexSize;;
		int spotRow = -710 + row * indexSize;
			
		SDL_Rect warpRect = {spawnCol, spawnRow, 25, 25};
		SDL_Texture* spotlightTex = gr.loadImage("Assets/Objects/spotlight.png");

		SDL_Rect spotlightRect = {spotCol, spotRow, 2560, 1440};
		bool spotlight = true;

		while(mazeCheck && gameon)
		{	

			SDL_RenderClear(gr.getRender());
			
			maze.drawMaze(gr.getWall(), gr.getRender());
			SDL_RenderCopy(gr.getRender(), warpTex, nullptr, &warpRect);
			if(spotlight)
			{
				SDL_RenderCopy(gr.getRender(), spotlightTex, nullptr, &spotlightRect);
			}
			SDL_RenderPresent(gr.getRender());
			
			while(SDL_PollEvent(&e)) {
				gameon = handleKeyEvents(e, playerent);	
				switch(e.key.keysym.sym) {
					case SDLK_m:
						if(e.type == SDL_KEYDOWN){
							mazeCheck = false;
							seed.setSeed();
						}
						break;
						
					case SDLK_d:
						if(e.type == SDL_KEYDOWN){
							//move right
							if(col != numCols-1 and !maze.hasBottom(col, row)){
								col++;
								warpRect.x += indexSize;
								spotlightRect.x += indexSize;
							}
						}
						break;

					case SDLK_a:
						if(e.type == SDL_KEYDOWN){
							//move left
							if(col != 0 and !maze.hasBottom(col-1,row)){
								col--;
								warpRect.x -= indexSize;
								spotlightRect.x -= indexSize;
							}
						}
						break;

					case SDLK_w:
						if(e.type == SDL_KEYDOWN){
							//move up
							if(row != 0 and !maze.hasRight(col,row-1)){
								row--;
								warpRect.y -= indexSize;
								spotlightRect.y -= indexSize;
							}
						}
						break;

					case SDLK_s:
						if(e.type == SDL_KEYDOWN){
							//move down
							if(row != numRows-1 and !maze.hasRight(col, row)){
								row++;
								warpRect.y += indexSize;
								spotlightRect.y += indexSize;
							}
						}
						break;
					case SDLK_c:
						if(e.type == SDL_KEYDOWN)
						{
							if(spotlight)
							{
								spotlight = false;
							}	
							else
							{
								spotlight = true;
							}
						}
				}
				
			}

			if(maze.isEnd(col, row))
			{
				mazeCheck = false;
			}
			
			
		}

		SDL_RenderClear(gr.getRender());
	}
	
}
