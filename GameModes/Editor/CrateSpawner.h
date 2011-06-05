#ifndef CRATESPAWNER_H
#define CRATESPAWNER_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickDragEvent.h>
#include <vector>
class FreeCamera;
namespace CEGUI
{
    class Window;
    class Slider;
}

class CrateSpawner : public GameMode, public ClickDragEvent
{
    public:
        CrateSpawner(FreeCamera* camera);
        virtual ~CrateSpawner();
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

#endif // CRATESPAWNER_H
