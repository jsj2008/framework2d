#ifndef GAMEMODE_H
#define GAMEMODE_H

class Camera;
class InputContext;
class Level;
class GameMode
{
    public:
        GameMode();
        virtual ~GameMode();
        //virtual void renderGameMode()=0;
        virtual bool update()=0;
    protected:
    private:
};

#endif // GAMEMODE_H
