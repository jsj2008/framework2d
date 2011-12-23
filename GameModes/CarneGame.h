#ifndef CARNEGAME_H
#define CARNEGAME_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <Entities/Bubble.h>
class PlayerInputBrain;

class CarneGame : public ClickDragEvent, public GameMode
{
    public:
        CarneGame();
        virtual ~CarneGame();
        void start(unsigned char button){}
        void mouseMove(Vec2i mouse){}
        void buttonUp(Vec2i mouse, unsigned char button);
        bool activate(const CEGUI::EventArgs&);
    protected:
    private:
        Bubble::BubbleType type;
        PlayerInputBrain* playerBrain;
};

#endif // CARNEGAME_H
