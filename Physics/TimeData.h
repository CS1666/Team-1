#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

class TimeData{
    private:
        //not sure if all of these will get used
        //fps for tracking frames
        Uint32 fps_cur_time;
        Uint32 fps_last_time;
        //Uint32 frame_count;
        //move tracks movement time (like update position)
	    Uint32 move_last_time;
        //anim only needed if ship has animation
	    Uint32 anim_last_time;
	    double timestep;

    public:

        //constructors
        TimeData();
        

        //destructor
        ~TimeData();

        //Other Methods
        double getFPS();
        double getTimeSinceMove();
        double getTimeSinceAnim();

        //additional getter/setter for code check
        Uint32 get_fps_cur_time();
        Uint32 get_fps_last_time();
        //Uint32 get_frame_count();
        Uint32 get_move_last_time();
        Uint32 get_anim_last_time();
        double get_timestep();

        void set_fps_cur_time(Uint32 newTime);
        void set_fps_last_time(Uint32 newTime);
        //void set_frame_count(Uint32 newCount);
        void set_move_last_time(Uint32 newTime);
        void set_anim_last_time(Uint32 newTime);
        void set_timestep(double newTimestep);
        
};