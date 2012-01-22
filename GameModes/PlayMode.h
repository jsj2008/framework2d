#ifndef PLAYMODE_H
#define PLAYMODE_H

#include "GameMode.h"
#include <Input/Mouse/ClickDragEvent.h>
#include <Entities/Bubble.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryTypeUsageEvent.h>
#include <Events/Events/PlayerOneCreated.h>
#include <AI/Brain.h>
#include <AI/BrainFactory/PlayerInputBrainFactory.h>
class b2Body;
class PlayerInputBrain;
class GameServerInterface;

class PlayMode : public ClickDragEvent, public GameMode, public SingletonEventListener<PlayerOneCreated>
{
    public:
        PlayMode();
        virtual ~PlayMode();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        bool activate(const CEGUI::EventArgs&);
        Level* getLevel(){return activeLevel;}
        bool trigger(PlayerOneCreated* event);
    protected:
        bool v_Update();
        void setLevel(Level* _level);
        Bubble::BubbleType type;
        PlayerInputBrain* playerOneBrain;
    private:
        Level* activeLevel;
};

#endif // PLAYMODE_H
