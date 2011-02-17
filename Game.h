#ifndef GAME_H
#define GAME_H

class GraphicsManager;
class PhysicsManager;
class InputManager;
class Entity;
class GameMode;
#include <Types/FastVector.h>
class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
    protected:
    private:
        PhysicsManager* mPhysicsManager;
        FastVector<Entity*> entities;
        GameMode* editorMode;
};

#endif // GAME_H
