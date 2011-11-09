#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <GameObject.h>
class Camera;
class InputContext;
class Level;
class GameMode : public GameObject<GameMode>
{
    public:
        GameMode();
        virtual ~GameMode();
        //virtual void renderGameMode()=0;
        virtual bool update()=0;
        static void registerActions();
    protected:
    private:
};

#endif // GAMEMODE_H
