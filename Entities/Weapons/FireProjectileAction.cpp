#include "FireProjectileAction.h"
#include <Entities/Entity.h>

FireProjectileAction::FireProjectileAction(const FireProjectileAction::ImmutableData& _immutableData, FactoryParameters* _parameters)
:immutableData(_immutableData)
{
    //ctor
    AutoSelfFactory<WeaponAction, FireProjectileAction>::staticInstantiate();
}

FireProjectileAction::~FireProjectileAction()
{
    //dtor
}

void FireProjectileAction::ImmutableData::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    projectileFactory = _loader->getFactory<Entity>("projectile", "ProjectileFactory");
}

void FireProjectileAction::fire(const Vec2f& _source, const Vec2f& _position)
{
    Vec2f direction = _position - _source;
    direction.Normalize();
    Vec2f position = _source;
    position += direction*3;
    FactoryParameters parameters;
    parameters.add<Vec2f>("position", position);
    parameters.add<Vec2f>("velocity", direction*100);
    immutableData.projectileFactory->use(&parameters);
}

