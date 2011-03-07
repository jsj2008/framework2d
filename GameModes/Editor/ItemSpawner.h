#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <vector>
#include <Factory/CrateDef.h>
class FreeCamera;
namespace CEGUI
{
    class Window;
    class Slider;
}

class ItemSpawner : public GameMode, public ClickDragEvent
{
    public:
        ItemSpawner(FreeCamera* camera);
        virtual ~ItemSpawner();
        void init();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void render();
    protected:
    private:
        CEGUI::Window* materialName;
        CEGUI::Slider* density;
        bool dragging;
        Vec2f topLeft, bottomright;
};

#endif // ITEMSPAWNER_H
