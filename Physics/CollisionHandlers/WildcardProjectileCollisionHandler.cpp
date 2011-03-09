#include "WildcardProjectileCollisionHandler.h"
#include <Entities/Projectile.h>

WildcardProjectileCollisionHandler::WildcardProjectileCollisionHandler()
{
    //ctor
}

WildcardProjectileCollisionHandler::~WildcardProjectileCollisionHandler()
{
    //dtor
}

void WildcardProjectileCollisionHandler::handle(Entity* a, Entity* b, float totalImpulse)
{
    Projectile* projectile = (Projectile*)b;
    projectile->hitWall();
}
