#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

class TimeData{
    private:
        //not sure if all of these will get used
        //fps for tracking frames
        //static Uint32 fps_cur_time;
        //static Uint32 fps_last_time;
        //Uint32 frame_count;
        //move tracks movement time (like update position)
	    static Uint32 move_last_time;
        //anim only needed if ship has animation
	    static Uint32 anim_last_time;
	    static double timestep;

    public:

        //constructors
        TimeData();
        

        //destructor
        ~TimeData();

        //Other Methods
        //static double getFPS();
        static Uint32 getTimeSinceMove();
        static Uint32 getTimeSinceAnim();

        //additional getter/setter for code check
        //static Uint32 get_fps_cur_time();
        //static Uint32 get_fps_last_time();
        //Uint32 get_frame_count();
        static Uint32 get_move_last_time();
        static Uint32 get_anim_last_time();
        static double get_timestep();

        //static void set_fps_cur_time(Uint32 newTime);
        //static void set_fps_last_time(Uint32 newTime);
        //void set_frame_count(Uint32 newCount);
        static void update_move_last_time();
        static void update_anim_last_time();
        static void update_timestep();
        
};