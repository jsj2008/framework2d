#ifndef PLAYMODE_H
#define PLAYMODE_H

#include "GameMode.h"
#include <Input/Mouse/ClickDragEvent.h>
#include <Entities/Bubble.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryTypeEvent.h>
#include <AI/Brain.h>
#include <AI/BrainFactory/PlayerInputBrainFactory.h>
class b2Body;
class PlayerInputBrain;

class PlayMode : public ClickDragEvent, public GameMode, public EventsListener<FactoryTypeEvent<Brain, PlayerInputBrainFactory>>
{
    public:
        PlayMode();
        virtual ~PlayMode();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void setCamera(Camera* _camera);
        bool activate(const CEGUI::EventArgs&);
        bool update();
        Level* getLevel(){return activeLevel;}
    protected:
        Bubble::BubbleType type;
        PlayerInputBrain* playerBrain;
        Level* activeLevel;
    private:
};

#endif // PLAYMODE_H
