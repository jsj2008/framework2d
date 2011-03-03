#include "ParallaxEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Input/InputState.h>
#include <Input/Mouse/SelectionBox.h>
#include <Input/Mouse/TextBox.h>
#include <Input/Mouse/TriggerButton.h>
#include <Input/Mouse/SliderBar.h>
#include <sstream>

ParallaxEditor::ParallaxEditor(FreeCamera* camera, const Rect& _Rect)
:ClickDragEvent(_Rect)
{
    //ctor
    mCamera = camera;
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    layers = new SelectionBox(Rect(0,100,300,200),{""});
    mInputState->registerEvent(layers);
    mInputState->registerEvent(new TriggerButton(Rect(50,200,100,250),this));
    textBox = new TextBox(Vec2i(0,200),"Material");
    mInputState->registerEvent(textBox);
    depth = new SliderBar(Vec2i(0,250),100,"Depth of new layer");
    mInputState->registerEvent(depth);
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
void ParallaxEditor::trigger(TriggerButton* button, unsigned char mouseButton)
{
    std::stringstream depthString;
    depthString << depth->getPosition();
    layers->push(depthString.str().c_str());
}
