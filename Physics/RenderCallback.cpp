#include "RenderCallback.h"
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>
#include <Physics/BodyPart.h>

RenderCallback::RenderCallback()
{
    //ctor
}

RenderCallback::~RenderCallback()
{
    //dtor
}
bool RenderCallback::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    Entity* entity = body->getBodyPart()->getEntity();
    if (entity != nullptr)
    {
        entity->render();
    }
    return true;
}
