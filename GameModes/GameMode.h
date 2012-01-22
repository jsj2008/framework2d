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
        bool update();
        static void registerActions(GameObjectType* _type);
        static std::string name()
        {
            return "GameMode";
        }
    protected:
        virtual bool v_Update()=0;
    private:
};

#endif // GAMEMODE_H
