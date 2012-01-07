#include "Weapon.h"
#include <Timer.h>
#include <Entities/Weapons/FiringMechanism.h>
#include <Entities/Weapons/WeaponAction.h>
#include <AbstractFactory/AutoSelfFactory.h>

Weapon::Weapon(const Weapon::ImmutableData& _data, FactoryParameters* _parameters)
:data(_data)
{
    //ctor
    AutoSelfFactory<Weapon, Weapon>::staticInstantiate();

    mechanism = data.mechanismFactory->use(_parameters, this);
    action = data.actionFactory->use(_parameters, this);
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::ImmutableData::init(FactoryLoader* _loader, AbstractFactories * _factories)
{
    mechanismFactory = _loader->getFactory<FiringMechanism>("firingMechanism", "SemiAutoFireFactory");
    actionFactory = _loader->getFactory<WeaponAction>("actionFactory", "FireProjectileActionFactory");
}

void Weapon::fireEnd(const Vec2f& source, const Vec2f& position)
{
    if (mechanism->fireEnd(source, position))
    {
        action->fire(source, position); /// FIXME could insert a control mechanism thing here
    }
}

void Weapon::registerActions()
{

}
