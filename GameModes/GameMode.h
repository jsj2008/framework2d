#ifndef GAMEMODE_H
#define GAMEMODE_H

class Camera;
class InputState;
class ClickEvent;
class GameMode
{
    public:
        GameMode();
        virtual ~GameMode();
        void registerEvent(ClickEvent* event);
        void set();
        InputState* mInputState; /// FIXME player input brain constructor needs this
    protected:
        Camera* mCamera;
    private:
};

#endif // GAMEMODE_H
