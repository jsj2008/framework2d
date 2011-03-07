#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Entities/Bubble.h>
#include <Graphics/Primitives/Icon.h>
#include <Factory/FactoryList.h>

PlayMode::PlayMode()
{
    //ctor
    def.setMaterial("defaultBubble");
    mCamera = NULL;
}

PlayMode::~PlayMode()
{
    //dtor
}

void PlayMode::start(unsigned char button)
{

}
void PlayMode::mouseMove(Vec2i mouse)
{

}
void PlayMode::buttonUp(Vec2i mouse, unsigned char button)
{
    def.setPosition(startPos.ScreenToWorldSpace());
    def.radius = (def.getPosition()-mouse.ScreenToWorldSpace()).Length();
    def.type = (Bubble::BubbleType)1;
    if (def.radius != 0.0f)
    {
        g_FactoryList.useFactory(def, eBubbleFactory);
    }
}
void PlayMode::setBody(b2Body* body)
{
    mCamera = new PhysicsCamera(body);
}
