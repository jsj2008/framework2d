#ifndef GAME_H
#define GAME_H

class InputContext;
class Level;
class GameMode;

extern class Game
{
    public:
        Game();
        void init();
        virtual ~Game();
        void run();
    protected:
    private:
        GameMode* gameMode;
}g_Game;

#endif // GAME_H
