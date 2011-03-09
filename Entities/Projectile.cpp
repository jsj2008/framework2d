#include "Projectile.h"
#include <Physics/PhysicsManager.h>

Projectile::Projectile()
{
    //ctor
    alive = true;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::update()
{
    if (!alive)
    {
        g_PhysicsManager.destroyBody(mBody);
    }

}

void Projectile::hitWall()
{
    alive = false;
}

void Projectile::hitAndDamage(Entity* target)
{
    target->damage();
    alive = false;
}
