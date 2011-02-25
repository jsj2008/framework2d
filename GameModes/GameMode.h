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
        InputState* getInputState(){return mInputState;} /// For callback event construction
    protected:
        InputState* mInputState;
        Camera* mCamera;
    private:
};

#endif // GAMEMODE_H
