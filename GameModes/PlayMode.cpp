#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <Input/InputState.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Input/Mouse/SelectionBox.h>
#include <Entities/Bubble.h>

PlayMode::PlayMode(b2Body* cameraBody)
{
    //ctor
    mInputState = new InputState;
    Rect selectionBoxRect(0,400,300,450);
    Rect fullScreen(0,0,5000,5000);
    SelectionBox* selectionBox = new SelectionBox(selectionBoxRect,Bubble::eBubbleTypesMax);
    mInputState->registerEvent(new BubbleDrawEvent(fullScreen,selectionBox));
    mInputState->registerEvent(selectionBox);
}

PlayMode::~PlayMode()
{
    //dtor
}

void PlayMode::setBody(b2Body* cameraBody)
{
    mCamera = new PhysicsCamera(cameraBody);
}
