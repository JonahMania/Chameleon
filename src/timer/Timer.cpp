#include "../include/Timer.hpp"

Timer::Timer()
{
    startTime = 0;
    pausedTime = 0;
    isPaused = false;
    running = false;
}

void Timer::start()
{
    isPaused = false;
    running = true;
    startTime = SDL_GetTicks();
    pausedTime = 0;
}

void Timer::stop()
{
    startTime = 0;
    pausedTime = 0;
    isPaused = false;
    running = false;
}

void Timer::pause()
{
    if(!running || isPaused)
    {
        return;
    }
    isPaused = true;
    pausedTime = SDL_GetTicks() - startTime;
    startTime = 0;
}

void Timer::unpause()
{
    if(!running || !isPaused)
    {
        return;
    }
    isPaused = false;
    startTime = SDL_GetTicks() - pausedTime;
    pausedTime = 0;
}

Uint32 Timer::getTime()
{
    if(!running)
    {
        return 0;
    }
    if(isPaused)
    {
        return pausedTime;
    }else{
        return SDL_GetTicks() - startTime;
    }
}
