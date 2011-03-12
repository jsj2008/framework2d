#include "AIEntityFactory.h"
#include <Factory/AIEntityDef.h>
#include <Entities/AIEntity.h>
#include <AI/ZombieBrain.h>
#include <AI/PlayerInputBrain.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
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

    jointDef.collideConnected = false;
    jointDef.maxMotorTorque = 50.0f;
    jointDef.enableMotor = true;
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
    Vec2f anchorPoint(0,def->height*0.33f);
    anchorPoint += def->getPosition(); //entity->mBody->GetPosition();

    wheelBody.position = def->getPosition();
    wheelBody.position += Vec2f(0,def->height*0.33f);
    b2Body* wheel = g_PhysicsManager.createBody(&wheelBody);
    wheel->CreateFixture(&wheelFixture);

    AIEntity* entity = new AIEntity(brain);

    bodyDef.position = def->getPosition();
    bodyDef.position.x += def->width*0.1f;
    shapeDef.SetAsBox(def->width*0.4f,def->height*0.33f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    jointDef.Initialize(entity->mBody,wheel,anchorPoint);
    entity->setWheel((b2RevoluteJoint*)g_PhysicsManager.createJoint(&jointDef));

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(data->materialName));

    if (def->aiType == ePlayerInputBrainType)
    {
        ((PlayMode*)g_Game.getGameMode(ePlayGameMode))->setBody(entity->mBody,(PlayerInputBrain*)brain);
    }
    return entity;
}



























