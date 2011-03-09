#include "AIEntityProjectileCollisionHandler.h"
#include <Entities/AIEntity.h>
#include <Entities/Projectile.h>

AIEntityProjectileCollisionHandler::AIEntityProjectileCollisionHandler()
{
    //ctor
}

AIEntityProjectileCollisionHandler::~AIEntityProjectileCollisionHandler()
{
    //dtor
}

void AIEntityProjectileCollisionHandler::handle(Entity* a, Entity* b, float totalImpulse)
{
    AIEntity* aiEntity = (AIEntity*)a;
    Projectile* projectile = (Projectile*)b;
    projectile->hitAndDamage(aiEntity);
}
