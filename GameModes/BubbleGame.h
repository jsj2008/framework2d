#ifndef BUBBLEGAME_H
#define BUBBLEGAME_H

#include <GameModes/PlayMode.h>


class BubbleGame : public PlayMode
{
    public:
        BubbleGame();
        virtual ~BubbleGame();
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
};

#endif // BUBBLEGAME_H
