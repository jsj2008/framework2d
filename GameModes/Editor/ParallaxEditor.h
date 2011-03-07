#ifndef PARALLAXEDITOR_H
#define PARALLAXEDITOR_H

#include <Input/Mouse/ClickDragEvent.h>
#include <GameModes/GameMode.h>
class FreeCamera;

class ParallaxEditor : public GameMode, public ClickDragEvent
{
    public:
        ParallaxEditor(FreeCamera* camera);
        virtual ~ParallaxEditor();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
};

#endif // PARALLAXEDITOR_H
