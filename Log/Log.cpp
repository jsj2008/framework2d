#include "Log.h"
#include <Log/GameConsole.h>
#include <Log/UninitialisedLogger.h>
#include <SDL/SDL_timer.h>
Log g_Log;

Log::Log()
{
    //ctor
    logger = new UninitialisedLogger;
}

Log::~Log()
{
    //dtor
}

void Log::init()
{
    logger = logger->newLogger(new GameConsole());
}
void Log::warning(const std::string& _message)
{
    logger->outputText("Warning: " + _message, SDL_GetTicks(), 0xFFFFFF00);
}
void Log::error(const std::string& _message)
{
    logger->outputText("Error: " + _message, SDL_GetTicks(), 0xFFFF0000);
    throw -1;
}
void Log::message(const std::string& _message)
{
    logger->outputText("Message: " + _message, SDL_GetTicks(), 0xFFFFFFFF);
}

std::string Log::getTimeString(unsigned int _timeStamp)
{
    unsigned int milliseconds = _timeStamp % 1000;
    unsigned int seconds = _timeStamp / 1000;
    unsigned int minutes = seconds / 60;
    seconds = seconds % 60;
    unsigned int hours = minutes / 60;
    minutes = minutes % 60;
    char buffer[16];
    sprintf(buffer, "%d:%d:%d", hours, minutes, seconds);
    //sprintf(buffer, "%d:%d:%d:%d", hours, minutes, seconds, milliseconds);
    return buffer;
}
