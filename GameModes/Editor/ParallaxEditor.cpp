#include "ParallaxEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <sstream>

ParallaxEditor::ParallaxEditor(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
    camera->activate();
}

ParallaxEditor::~ParallaxEditor()
{
    //dtor
}

void ParallaxEditor::start(unsigned char button)
{

}
void ParallaxEditor::mouseMove(Vec2i mouse)
{

}
void ParallaxEditor::buttonUp(Vec2i mouse, unsigned char button)
{

}
