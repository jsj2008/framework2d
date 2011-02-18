#ifndef GAME_H
#define GAME_H

class GraphicsManager;
class PhysicsManager;
class InputManager;
class Entity;
class GameMode;
#include <Types/FastVector.h>
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
    protected:
    private:
        PhysicsManager* mPhysicsManager;
        GameMode* mGameModes[eGameModesMax];
}g_Game;

#endif // GAME_H
