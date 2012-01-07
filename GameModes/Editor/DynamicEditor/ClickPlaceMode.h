#ifndef CLICKPLACEMODE_H
#define CLICKPLACEMODE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>


class ClickPlaceMode : public DynamicEditorMode
{
    public:
        ClickPlaceMode(CEGUI::Window* _window, FactoryParameters* _params);
        virtual ~ClickPlaceMode();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
        void finish();
    private:
        Vec2f worldPosition;
};

#endif // CLICKPLACEMODE_H
