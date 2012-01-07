#ifndef SHOOTERGAME_H
#define SHOOTERGAME_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <GameModes/PlayMode.h>
#include <Entities/Bubble.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryTypeUsageEvent.h>
#include <AI/Brain.h>
#include <AI/BrainFactory/PlayerInputBrainFactory.h>
class b2Body;
class PlayerInputBrain;
class Level;
class AbstractFactories;

class ShooterGame : public PlayMode
{
    public:
        ShooterGame();
        virtual ~ShooterGame();
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
};

#endif // SHOOTERGAME_H
