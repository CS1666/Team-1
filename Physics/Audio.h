#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

using namespace std;

class Audio{
    private:
		//static Mix_Music *gMusic;
		static Mix_Chunk *gThrustSound;
		static Mix_Chunk *laserSound;
		static Mix_Music *ambientBGM;
		static bool isSolar;
	public:
		static void load_chunk0(string filename);
		static void load_chunk1(string filename);
		static void load_music(string filename);
		//static void play_music();
		//static void stop_music();
		static void play_laser_sound();
		static void play_thrust_sound();
		static void pause_thrust_sound();
		static void set_solar(bool iss);
		static void play_music();
		static void close();
};
