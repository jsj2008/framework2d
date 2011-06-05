#include "Timer.h"
#include <SDL/SDL_timer.h>
Timer g_Timer;
void Timer::init()
{
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
