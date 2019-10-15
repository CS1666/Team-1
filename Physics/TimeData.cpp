#include "TimeData.h"

TimeData::TimeData(){
    fps_cur_time = 0;
    fps_last_time = SDL_GetTicks();
    //frame_count = 0;
    move_last_time = SDL_GetTicks();
    anim_last_time = SDL_GetTicks();
    timestep = 0;
}

TimeData::~TimeData(){
    //idk if this actually necessary
}

double TimeData::getFPS(){
    fps_cur_time = SDL_GetTicks();
    return (1/ ((fps_cur_time-fps_last_time))/1000.0);
}

double TimeData::getTimeSinceMove(){
    return (double)(SDL_GetTicks() - move_last_time);
}

double TimeData::getTimeSinceAnim(){
    return (double)(SDL_GetTicks() - anim_last_time);
}

Uint32 TimeData::get_fps_cur_time(){
    return fps_cur_time;
}

Uint32 TimeData::get_fps_last_time(){
    return fps_last_time;
}

Uint32 TimeData::get_move_last_time(){
    return move_last_time;
}

Uint32 TimeData::get_anim_last_time(){
    return anim_last_time;
}

double TimeData::get_timestep(){
    return timestep;
}

void TimeData::set_fps_cur_time(Uint32 newTime){
    fps_cur_time = newTime;
}

void TimeData::set_fps_last_time(Uint32 newTime){
    fps_last_time = newTime;
}

void TimeData::set_move_last_time(Uint32 newTime){
    move_last_time = newTime;
}

void TimeData::set_anim_last_time(Uint32 newTime){
    anim_last_time = newTime;
}

void TimeData::set_timestep(double newTimestep){
    timestep = newTimestep;
}