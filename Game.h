#ifndef GAME_H
#define GAME_H

class GraphicsManager;
class PhysicsManager;
class InputManager;
class Entity;
#include <Types/FastVector.h>
class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
    protected:
    private:
        GraphicsManager* mGraphicsManager;
        PhysicsManager* mPhysicsManager;
        FastVector<Entity*> entities;
};

#endif // GAME_H
