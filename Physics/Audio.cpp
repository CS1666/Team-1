#include "Audio.h"
#include <SDL_mixer.h>

Mix_Chunk* Audio::gThrustSound = NULL;

void Audio::load_audio(){
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	gThrustSound = Mix_LoadWAV("Assets/Objects/thrustSound.wav");
}

void Audio::play_thrust_sound(){
	 Mix_PlayChannel( -1, gThrustSound, 0 );
}
