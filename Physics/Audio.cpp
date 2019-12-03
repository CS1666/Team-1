#include "Audio.h"
#include <SDL_mixer.h>

Mix_Chunk* Audio::gThrustSound = NULL;
Mix_Chunk* Audio::laserSound = NULL;
Mix_Music* Audio::ambientBGM = NULL;
bool Audio::isSolar;
void Audio::load_chunk0(string filename){
	gThrustSound = Mix_LoadWAV(filename.c_str());
}
void Audio::load_chunk1(string filename){
	laserSound = Mix_LoadWAV(filename.c_str());
}
void Audio::load_music(string filename){
	ambientBGM = Mix_LoadMUS(filename.c_str());
}
void Audio::play_laser_sound(){
	if(isSolar)
	{
		Mix_PlayChannel( -1, laserSound, 0 );
	}
}
void Audio::play_thrust_sound(){
	if(isSolar)
	{
		Mix_PlayChannel( -1, gThrustSound, 0 );
	}
}
void Audio::play_music(){
	if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( ambientBGM, -1 );
   	}
}
void Audio::close(){
	if( Mix_PlayingMusic() == 1 )
    {
        Mix_HaltMusic();
   	}
	Mix_FreeChunk(laserSound);
	Mix_FreeChunk(gThrustSound);
	Mix_FreeMusic(ambientBGM);
	gThrustSound = NULL;
	ambientBGM = NULL;
	Mix_Quit();
}

void Audio::set_solar(bool iss)
{
	isSolar = iss;
}