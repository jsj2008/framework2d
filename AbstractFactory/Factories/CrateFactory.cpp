#include "CrateFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Crate.h>
#include <Graphics/Skins/StaticSkin.h>

CrateFactory::CrateFactory(const std::string& _materialName, float density)
:AbstractFactory()
{
    //ctor
    materialName = _materialName;
    dimensions = Vec2f(2,2);
    bodyDef.type = b2_dynamicBody;
    fixtureDef.density = density;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::CrateCategory);
    shapeDef.SetAsBox(dimensions.x*0.5f,dimensions.y*0.5f);
}

CrateFactory::~CrateFactory()
{
    //dtor
}
Entity* CrateFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Vec2f position(parameters->getVec2f(""));
    Entity* entity = new Crate;

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new StaticSkin(dimensions.x,dimensions.y);
    setMaterial(entity->mSkin,materialName);
    return entity;
}
