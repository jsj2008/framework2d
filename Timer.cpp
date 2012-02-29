#include "Timer.h"
#include <Filesystem/Filesystem.h>
#include <Filesystem/Folder.h>
#include <SDL/SDL.h>
#include <cassert>

Timer::Timer()
  :GameObject<Timer>("timer")
{
}
void Timer::init()
{
    int result = SDL_Init(SDL_INIT_TIMER);
    assert(result == 0);
    startTime = SDL_GetTicks();
    currentlyPaused = false;
    frame = 0;
    Filesystem::global()->makeFolders("/dev")->attachChild(this);
}
void Timer::pause()
{
    pauseTime = SDL_GetTicks();
    currentlyPaused = true;
}
void Timer::unpause()
{
    unsigned int totalPauseTime = SDL_GetTicks() - pauseTime;
    startTime += totalPauseTime;
    currentlyPaused = false;
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

void Timer::registerActions(GameObjectType* _type)
{
    _type->createActionHandle("pause", &Timer::pause);
    _type->createActionHandle("unpause", &Timer::unpause);
}
Timer* Timer::global()
{
    static Timer* timer = new Timer;
    return timer;
}







