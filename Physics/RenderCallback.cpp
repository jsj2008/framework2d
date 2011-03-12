#include "RenderCallback.h"
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>

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
    Entity* entity = (Entity*)body->GetUserData();
    if (entity != NULL)
    {
        entity->render();
    }
    return true;
}
