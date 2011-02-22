#ifndef GAME_H
#define GAME_H

class GraphicsManager;
class PhysicsManager;
class InputManager;
class Entity;
class GameMode;
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
        void init();
        virtual ~Game();
        void run();
        GameMode* getGameMode(GameModes mode);
        void set(GameMode* root, GameMode* mode); /// This'll pop until it finds root, then push mode. NULL for the root will pop everything from the stack. NULL for mode won't push it
    protected:
    private:
        std::stack<GameMode*> gameModeStack;
        GameMode* mGameModes[eGameModesMax];
}g_Game;

#endif // GAME_H
