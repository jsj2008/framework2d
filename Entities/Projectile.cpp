#include "Projectile.h"
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Box2D/Box2D.h>

Projectile::Projectile(const std::string& _explosion, Skin* _skin)
:Entity(_skin)
{
    //ctor
    alive = true;
    explosion = _explosion;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::update()
{
    if (!alive)
    {
        FactoryParameters parameters({{"position",mBody->GetPosition()}});
        AbstractFactories::global().useFactory<Entity>(explosion,&parameters);
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
