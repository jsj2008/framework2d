#include "WaterVolume.h"
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/CollisionObject.h>
#include <Types/Vec2f.h>

WaterVolume::WaterVolume(WaterPhysicsSystem* _system)
{
    //ctor
    system = _system;
}

WaterVolume::~WaterVolume()
{
    //dtor
}

void WaterVolume::update()
{
}

/*void WaterPhysicsSystem::registerActions(GameObjectType* _type)
{
    type.createActionHandle("buoyancy", &WaterPhysicsSystem::floatationAction);
}*/

void WaterVolume::floatationAction(CollisionObject* _object)
{
    BodyPart* other = _object->getOther();
    other->applyLinearImpulse(other->getLinearVelocity()*-0.1f);
    other->applyLinearImpulse(Vec2f(0, other->getAreaBelowLine(18.5f) * -1.0f * other->getDensity()));
}
