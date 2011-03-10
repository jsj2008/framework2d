#include "ProjectileFactory.h"
#include <Factory/ProjectileDef.h>
#include <Entities/Projectile.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/GraphicsManager.h>
#include <Graphics/Skins/StaticSkin.h>

ProjectileFactory::ProjectileFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    fixtureDef.density = 10.0f;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::ProjectileCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::ProjectileCategory);
    shapeDef.m_radius = 2.0f;
}

ProjectileFactory::~ProjectileFactory()
{
    //dtor
}

Entity* ProjectileFactory::createEntity(FactoryDef* data)
{
    ProjectileDef* def = (ProjectileDef*)data;
    Projectile* projectile = new Projectile;

    bodyDef.position = data->getPosition() + Vec2f(def->radius*0.5,def->radius*0.5);
    bodyDef.linearVelocity = def->getVelocity();
    bodyDef.userData = (void*)projectile;
    shapeDef.m_radius = def->radius;

    projectile->mBody = g_PhysicsManager.createBody(&bodyDef);
    projectile->mBody->CreateFixture(&fixtureDef);
    projectile->mSkin = new StaticSkin(def->radius,def->radius);
    MaterialContext* material = g_GraphicsManager.getMaterial(data->materialName);
    setMaterial(projectile->mSkin,material);
    return projectile;
}
