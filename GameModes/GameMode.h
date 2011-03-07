#ifndef GAMEMODE_H
#define GAMEMODE_H

class Camera;
class InputContext;
class GameMode
{
    public:
        GameMode();
        virtual ~GameMode();
        void set();
        virtual void renderGameMode(){}
    protected:
    private:
};

#endif // GAMEMODE_H
