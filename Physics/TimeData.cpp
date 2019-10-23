#include "TimeData.h"

Uint32 TimeData::move_last_time = SDL_GetTicks();
Uint32 TimeData::anim_last_time = SDL_GetTicks();
double TimeData::timestep = 0;

TimeData::TimeData(){
    //fps_cur_time = 0;
    //fps_last_time = SDL_GetTicks();
    //frame_count = 0;
    
}

TimeData::~TimeData(){
    //idk if this actually necessary
}

//double TimeData::getFPS(){
//    fps_cur_time = SDL_GetTicks();
//    return (1/ ((fps_cur_time-fps_last_time))/1000.0);
//}

Uint32 TimeData::getTimeSinceMove(){
    return (SDL_GetTicks() - move_last_time);
}

Uint32 TimeData::getTimeSinceAnim(){
    return (SDL_GetTicks() - anim_last_time);
}

//Uint32 TimeData::get_fps_cur_time(){
//    return fps_cur_time;
//}

//Uint32 TimeData::get_fps_last_time(){
//    return fps_last_time;
//}

Uint32 TimeData::get_move_last_time(){
    return move_last_time;
}

Uint32 TimeData::get_anim_last_time(){
    return anim_last_time;
}

double TimeData::get_timestep(){
    return timestep;
}

//void TimeData::update_fps_cur_time(Uint32 newTime){
//    fps_cur_time = newTime;
//}

//void TimeData::update_fps_last_time(Uint32 newTime){
//    fps_last_time = newTime;
//}

void TimeData::update_move_last_time(){
    move_last_time = SDL_GetTicks();
}

void TimeData::update_anim_last_time(){
    anim_last_time = SDL_GetTicks();
}

void TimeData::update_timestep(){
    timestep = (SDL_GetTicks() - move_last_time) / 1000.0;;
}