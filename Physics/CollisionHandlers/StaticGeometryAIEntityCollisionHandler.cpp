#include "StaticGeometryAIEntityCollisionHandler.h"
#include <Entities/StaticGeometry.h>
#include <Entities/AIEntity.h>
#include <cassert>

StaticGeometryAIEntityCollisionHandler::StaticGeometryAIEntityCollisionHandler()
{
    //ctor
}

StaticGeometryAIEntityCollisionHandler::~StaticGeometryAIEntityCollisionHandler()
{
    //dtor
}

void StaticGeometryAIEntityCollisionHandler::handle(Entity* a, Entity* b, float totalImpulse)
{
    StaticGeometry* staticGeometry = (StaticGeometry*)a;
    AIEntity* aiEntity = (AIEntity*)b;

    if (totalImpulse > 50)
    {
        aiEntity->damage();
    }
}
