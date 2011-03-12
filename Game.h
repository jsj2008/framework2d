#ifndef GAME_H
#define GAME_H

class InputContext;
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
        InputContext* getGameMode(GameModes mode);
    protected:
    private:
        InputContext* mGameModes[eGameModesMax];
}g_Game;

#endif // GAME_H
