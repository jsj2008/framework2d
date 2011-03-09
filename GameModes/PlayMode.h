#ifndef PLAYMODE_H
#define PLAYMODE_H

#include "GameMode.h"
#include <Input/Mouse/ClickDragEvent.h>
#include <Factory/BubbleDef.h>
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
        BubbleDef def;
        PlayerInputBrain* playerBrain;
};

#endif // PLAYMODE_H
