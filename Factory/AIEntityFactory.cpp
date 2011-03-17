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

    wheelJoint.collideConnected = false;
    wheelJoint.maxMotorTorque = 50.0f;
    wheelJoint.enableMotor = true;

    jumpBody.type = b2_dynamicBody;
    jumpBody.userData = NULL;
    jumpFixture.shape = &jumpShape;
    jumpFixture.density = 0.1f;
    jumpFixture.friction = 50.0f;
    jumpFixture.filter.categoryBits = PhysicsManager::PlayerCategory;
    jumpFixture.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::PlayerCategory);
    jumpShape.SetAsBox(0.2f,0.2f);

    jumpJoint.collideConnected = false;
    jumpJoint.maxMotorForce = 500.0f;
    jumpJoint.motorSpeed = -1.0f;
    jumpJoint.enableMotor = true;
    jumpJoint.lowerTranslation = 0.0f;
    jumpJoint.upperTranslation = 1.0f;
    jumpJoint.enableLimit = true;
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
    anchorPoint += def->getPosition(); //entity->mBody->GetPosition();


    AIEntity* entity = new AIEntity(brain);
    int collisionGroup = g_PhysicsManager.getNextNegativeCollisionGroup();
    fixtureDef.filter.groupIndex = collisionGroup;
    wheelFixture.filter.groupIndex = collisionGroup;
    jumpFixture.filter.groupIndex = collisionGroup;

    bodyDef.position = def->getPosition();
    bodyDef.position.x += def->width*0.1f;
    shapeDef.SetAsBox(def->width*0.4f,def->height*0.33f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    wheelBody.position = def->getPosition();
    wheelBody.position += Vec2f(def->width*0.1f,def->height*0.33f);
    b2Body* wheel = g_PhysicsManager.createBody(&wheelBody);
    wheel->CreateFixture(&wheelFixture);

    wheelJoint.Initialize(entity->mBody,wheel,anchorPoint);
    entity->setWheel((b2RevoluteJoint*)g_PhysicsManager.createJoint(&wheelJoint));

    jumpBody.position = def->getPosition();
    jumpBody.position += Vec2f(def->width*0.1f,def->height*0.33f);
    b2Body* jump = g_PhysicsManager.createBody(&jumpBody);
    jump->CreateFixture(&jumpFixture);

    jumpJoint.Initialize(entity->mBody,jump,anchorPoint,Vec2f(0.0f,1.0f));
    entity->setJump((b2PrismaticJoint*)g_PhysicsManager.createJoint(&jumpJoint));
    //entity->setWheel((b2RevoluteJoint*)g_PhysicsManager.createJoint(&wheelJoint));

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(data->materialName));

    if (def->aiType == ePlayerInputBrainType)
    {
        ((PlayMode*)g_Game.getGameMode(ePlayGameMode))->setBody(entity->mBody,(PlayerInputBrain*)brain);
    }
    return entity;
}



























