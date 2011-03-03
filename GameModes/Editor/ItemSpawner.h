#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <vector>
#include <Factory/CrateDef.h>
class FreeCamera;
class SliderBar;
class TextBox;

class ItemSpawner : public GameMode, public ClickDragEvent
{
    public:
        ItemSpawner(FreeCamera* camera, const Rect& _Rect);//, SelectionBox* _selectionBox
        virtual ~ItemSpawner();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        SliderBar* density;
        TextBox* textBox;
        bool dragging;
        Vec2f topLeft, bottomright;
};

#endif // ITEMSPAWNER_H
