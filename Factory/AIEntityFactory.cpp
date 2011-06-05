#include "AIEntityFactory.h"
#include <Factory/AIEntityDef.h>
#include <Entities/AIEntity.h>
#include <AI/ZombieBrain.h>
#include <AI/PlayerInputBrain.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <SharedContent/ContentManager.h>
#include <Entities/Weapons/Weapon.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <iostream>

AIEntityFactory::AIEntityFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    fixtureDef.shape = &shapeDef;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = PhysicsManager::EnemyCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::EnemyCategory);

    wheelBody.type = b2_dynamicBody;
    wheelBody.userData = NULL;
    wheelFixture.shape = &wheelShape;
    wheelFixture.density = 1.0f;
    wheelFixture.friction = 50.0f;
    wheelFixture.filter.categoryBits = PhysicsManager::PlayerCategory;
    wheelFixture.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::PlayerCategory);
    wheelShape.m_radius = 0.5f;

    wheelJoint.collideConnected = false;
    wheelJoint.maxMotorTorque = 50.0f;
    wheelJoint.enableMotor = true;
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}

Entity* AIEntityFactory::createEntity(FactoryDef* data)
{
    AIEntityDef* def = (AIEntityDef*)data;
    Brain* brain;
    switch (def->aiType)
    {
        case ePlayerInputBrainType:
        {
            brain = new PlayerInputBrain;
            break;
        }
        case eZombieBrainType:
        {
            brain = new ZombieBrain;
            break;
        }
        case eBrainTypesMax:
        default:
        {
            std::cout << "Invalid ai entity type" << std::endl;
            throw -1;
        }
    }
    Vec2f anchorPoint(def->width*0.1f,def->height*0.33f);
    anchorPoint += def->position; //entity->mBody->GetPosition();


    AIEntity* entity = new AIEntity(brain, new Weapon(g_ContentManager.getContent<WeaponContent>(def->weapon)));
    int collisionGroup = g_PhysicsManager.getNextNegativeCollisionGroup();
    fixtureDef.filter.groupIndex = collisionGroup;
    wheelFixture.filter.groupIndex = collisionGroup;

    bodyDef.position = def->position;
    bodyDef.position.x += def->width*0.1f;
    shapeDef.SetAsBox(def->width*0.4f,def->height*0.33f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    wheelBody.position = def->position;
    wheelBody.position += Vec2f(def->width*0.1f,def->height*0.33f);
    b2Body* wheel = g_PhysicsManager.createBody(&wheelBody);
    wheel->CreateFixture(&wheelFixture);

    wheelJoint.Initialize(entity->mBody,wheel,anchorPoint);
    entity->setWheel((b2RevoluteJoint*)g_PhysicsManager.createJoint(&wheelJoint));

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(data->materialName));

    if (def->aiType == ePlayerInputBrainType)
    {
        ((PlayMode*)g_Game.getGameMode(ePlayGameMode))->setBody(entity->mBody,(PlayerInputBrain*)brain);
    }
    return entity;
}



























