#ifndef GAME_H
#define GAME_H

class InputContext;
class Level;
#include <stack>
enum GameModes
{
    eEditorGameMode,
    ePlayGameMode,
    eGameModesMax
};
extern class Game
{
    public:
        Game();
        void init();
        virtual ~Game();
        void run();
    protected:
    private:
        InputContext* editor;
        Level* level;
}g_Game;

#endif // GAME_H
