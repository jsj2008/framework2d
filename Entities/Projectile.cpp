#include "Projectile.h"
#include <Physics/Body.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Box2D/Box2D.h>

Projectile::Projectile(AbstractFactoryBase<Entity>* _explosion, Skin* _skin)
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
        FactoryParameters parameters;
        parameters.add<Vec2f>("position", body->getPosition());
        explosion->use(&parameters);
        delete this;
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
