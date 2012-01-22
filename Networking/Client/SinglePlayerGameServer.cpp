#include "SinglePlayerGameServer.h"
#include <Networking/Client/NetworkedPlayerControl.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Events/Events/PlayerOneCreated.h>
#include <Entities/AIEntity.h>
#include <Timer.h>

SinglePlayerGameServer::SinglePlayerGameServer()
{
    //ctor
    stepsTaken = 0;
    startTime = Timer::global()->getTicks();
    inited = false;
}

SinglePlayerGameServer::~SinglePlayerGameServer()
{
    //dtor
}

bool SinglePlayerGameServer::update()
{
    if (!inited)
    {
        inited = true;
    }
    unsigned int currentTime = Timer::global()->getTicks();
    unsigned int totalTimePassed = currentTime - startTime;
    if (currentTime < startTime) /// FIXME
        totalTimePassed = 0;
    unsigned int stepsToTake = totalTimePassed*60.0f/1000.0f;
    bool ret = false;
    if (stepsToTake > stepsTaken) /// FIXME needs to loop
    {
        ret = true;
        stepsTaken++;
    }
    return ret;
}

void SinglePlayerGameServer::registerPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)
{
    control = _control;
}
void SinglePlayerGameServer::unregisterPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)
{
    control = nullptr;
}

void SinglePlayerGameServer::trigger(InputActions action, bool _pressed)
{
    //control->actionFromServer(action, _pressed);
}
