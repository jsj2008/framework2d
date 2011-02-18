#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <Input/InputState.h>

PlayMode::PlayMode(b2Body* cameraBody)
{
    //ctor
    mInputState = new InputState;
}

PlayMode::~PlayMode()
{
    //dtor
}

void PlayMode::setBody(b2Body* cameraBody)
{
    mCamera = new PhysicsCamera(cameraBody);
}
