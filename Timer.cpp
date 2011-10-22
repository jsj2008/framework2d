#include "Timer.h"
#include <SDL/SDL.h>
#include <cassert>
Timer g_Timer;
void Timer::init()
{
    int result = SDL_Init(SDL_INIT_TIMER);
        assert(result == 0);
    startTime = SDL_GetTicks();
    currentlyPaused = false;
    frame = 0;
}
void Timer::pause()
{
    pauseTime = SDL_GetTicks();
}
void Timer::unPause()
{
    unsigned int totalPauseTime = SDL_GetTicks() - pauseTime;
    startTime += totalPauseTime;
}
unsigned int Timer::getTicks()
{
    if (currentlyPaused)
    {
        return pauseTime - startTime;
    }
    else
    {
        unsigned int ticks = SDL_GetTicks();
        return ticks - startTime;
    }
}
unsigned int Timer::getFrame()
{
    return frame;
}
void Timer::tick()
{
    frame++;
}
