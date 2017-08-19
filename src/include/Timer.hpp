#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        Uint32 getTime();
    private:
        Uint32 startTime;
        Uint32 pausedTime;
        bool isPaused;
        bool running;
};

#endif
