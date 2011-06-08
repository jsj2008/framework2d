#ifndef PLAYMODE_H
#define PLAYMODE_H

#include "GameMode.h"
#include <Input/Mouse/ClickDragEvent.h>
#include <Entities/Bubble.h>
class b2Body;
class PlayerInputBrain;

class PlayMode : public ClickDragEvent, public GameMode
{
    public:
        PlayMode();
        virtual ~PlayMode();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void setBody(b2Body* body, PlayerInputBrain* _playerBrain);
        bool activate(const CEGUI::EventArgs&);
    protected:
    private:
        Bubble::BubbleType type;
        PlayerInputBrain* playerBrain;
};

#endif // PLAYMODE_H
