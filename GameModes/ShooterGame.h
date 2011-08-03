#ifndef SHOOTERGAME_H
#define SHOOTERGAME_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <Entities/Bubble.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryTypeEvent.h>
#include <AI/Brain.h>
#include <AI/BrainFactory/PlayerInputBrainFactory.h>
class b2Body;
class PlayerInputBrain;

class ShooterGame : public ClickDragEvent, public GameMode, public EventsListener<FactoryTypeEvent<Brain, PlayerInputBrainFactory>>
{
    public:
        ShooterGame();
        virtual ~ShooterGame();
        void start(unsigned char button){}
        void mouseMove(Vec2i mouse){}
        void buttonUp(Vec2i mouse, unsigned char button);
        void setBody(b2Body* body, PlayerInputBrain* _playerBrain);
        bool activate(const CEGUI::EventArgs&);
        bool trigger(FactoryTypeEvent<Brain, PlayerInputBrainFactory>* event);
        void setCamera(Camera* _camera);
    protected:
    private:
        Bubble::BubbleType type;
        PlayerInputBrain* playerBrain;
};

#endif // SHOOTERGAME_H
