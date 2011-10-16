#include "ClickPlaceMode.h"
#include <Types/TypeTable.h>

ClickPlaceMode::ClickPlaceMode(CEGUI::Window* _window, FactoryParameters* _params)
:DynamicEditorMode(_window, _params)
{
    //ctor
}

ClickPlaceMode::~ClickPlaceMode()
{
    //dtor
}

void ClickPlaceMode::buttonDown(Vec2i mouse, unsigned char button)
{
}
void ClickPlaceMode::mouseMove(Vec2i mouse)
{
}
void ClickPlaceMode::buttonUp(Vec2i mouse, unsigned char button)
{
    worldPosition = mouse.ScreenToWorldSpace();
    create();
}
void ClickPlaceMode::finish()
{
    typeTable->addValue("position",worldPosition);
}

