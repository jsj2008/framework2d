#ifndef PARALLAXEDITOR_H
#define PARALLAXEDITOR_H

#include <Input/Mouse/ClickDragEvent.h>
#include <Input/Mouse/TriggerListener.h>
#include <GameModes/GameMode.h>
class SelectionBox;
class TextBox;
class SliderBar;
class FreeCamera;

class ParallaxEditor : public GameMode, public ClickDragEvent, public TriggerListener
{
    public:
        ParallaxEditor(FreeCamera* camera, const Rect& _Rect);
        virtual ~ParallaxEditor();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void trigger(TriggerButton* button, unsigned char mouseButton);
    protected:
    private:
        SelectionBox* layers;
        TextBox* textBox;
        SliderBar* depth;
};

#endif // PARALLAXEDITOR_H
