#include "ItemSpawner.h"
#include <Input/Mouse/SelectionBox.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Level/LevelManager.h>
#include <Input/InputState.h>
#include <Input/Mouse/SliderBar.h>
#include <Input/Mouse/TextBox.h>

ItemSpawner::ItemSpawner(FreeCamera* camera, const Rect& _Rect)
:ClickDragEvent(_Rect)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect rect(0,100,200,200);
    density = new SliderBar(Vec2i(0,100),100,"Density 0-30",1.0f);
    textBox = new TextBox(Vec2i(0,150),"Material");
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(this);

    mInputState->registerEvent(density);
    mInputState->registerEvent(textBox);
}

ItemSpawner::~ItemSpawner()
{
    //dtor
}

void ItemSpawner::start(unsigned char button)
{
    topLeft = startPos.ScreenToWorldSpace();
    bottomright = topLeft;
    dragging = true;
}
void ItemSpawner::mouseMove(Vec2i mouse)
{
    bottomright = mouse.ScreenToWorldSpace();
}
void ItemSpawner::buttonUp(Vec2i mouse, unsigned char button)
{
    bottomright = mouse.ScreenToWorldSpace();
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    if (dimensions.x > 1.0f && dimensions.y > 1.0f)
    {
        CrateDef def;
        def.set(dimensions,density->getPosition()*30.0f,textBox->getString());
        def.setPosition(topLeft + (bottomright - topLeft)*0.5);
        g_LevelManager.addBody(def);
    }
    dragging = false;
}
#include <GL/gl.h>
void ItemSpawner::render()
{
    if (dragging)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2f(topLeft.x,topLeft.y);
        glVertex2f(topLeft.x,bottomright.y);
        glVertex2f(bottomright.x,bottomright.y);
        glVertex2f(bottomright.x,topLeft.y);
        glEnd();
    }
}


































