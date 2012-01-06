#include "Projectile.h"
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Box2D/Box2D.h>

Projectile::Projectile(AbstractFactoryBase<Entity>* _explosion)
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
        FactoryParameters _parameters;
        _parameters.add<Vec2f>("position", rootBody->getPosition());
        explosion->use(&_parameters, nullptr);
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
