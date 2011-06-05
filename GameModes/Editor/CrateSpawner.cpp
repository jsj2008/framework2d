#include "CrateSpawner.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactoryList.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Level/LevelManager.h>
#include <CEGUI/CEGUI.h>
#include <iostream>

CrateSpawner::CrateSpawner(FreeCamera* camera)
{
    //ctor
    camera->activate();
    mCamera = camera;
    density = NULL;
    materialName = NULL;
}

CrateSpawner::~CrateSpawner()
{
    //dtor
}

void CrateSpawner::init()
{
    density = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("CrateSpawner/Slider");
    materialName = CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("CrateSpawner/Textbox");
}
void CrateSpawner::start(unsigned char button)
{
    topLeft = startPos.ScreenToWorldSpace();
    bottomright = topLeft;
    dragging = true;
}
void CrateSpawner::mouseMove(Vec2i mouse)
{
    bottomright = mouse.ScreenToWorldSpace();
}
void CrateSpawner::buttonUp(Vec2i mouse, unsigned char button)
{
    bottomright = mouse.ScreenToWorldSpace();
    Vec2f dimensions = bottomright - startPos.ScreenToWorldSpace();
    if (dimensions.x > 1.0f && dimensions.y > 1.0f)
    {
        /*CrateDef def;
        def.set(dimensions,density->getCurrentValue(),materialName->getText().c_str());
        std::cout << "Density: " << density->getCurrentValue() << std::endl;
        def.position = topLeft + (bottomright - topLeft)*0.5;
        g_LevelManager.addBody(def);*/
        Vec2f pos(topLeft + (bottomright - topLeft)*0.5);
        FactoryParameters params({{"",pos}});
        g_LevelManager.addBody("crate", &params);
    }
    dragging = false;
}
#include <GL/gl.h>
void CrateSpawner::render()
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


































