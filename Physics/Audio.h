#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

using namespace std;

class Audio{
    private:
		//static Mix_Music *gMusic;
		static Mix_Chunk *gThrustSound;
	
	public:
		static void load_audio();
		//static void play_music();
		//static void stop_music();
		static void play_thrust_sound();
};
