#include "AIEntityFactory.h"
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
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/FactoryLoader.h>

AIEntityFactory::AIEntityFactory(FactoryLoader* loader)
{
    //ctor
    aiType = loader->get<int>("aiType",ePlayerInputBrainType);
    dimensions = loader->get<Vec2f>("dimensions",Vec2f(2,2));
    weapon = loader->get<std::string>("weapon","pistol");
    materialName = loader->get<std::string>("materialName","player");

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

Entity* AIEntityFactory::useFactory(FactoryParameters* parameters)
{
    Brain* brain;
    switch (aiType)
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
    Vec2f position = parameters->get<Vec2f>("position",Vec2f(0,0));
    Vec2f anchorPoint(dimensions.x*0.1f,dimensions.y*0.33f);
    anchorPoint += position;

    AIEntity* entity = new AIEntity(brain, new Weapon(g_ContentManager.getContent<WeaponContent>(weapon)));
    int collisionGroup = g_PhysicsManager.getNextNegativeCollisionGroup();
    fixtureDef.filter.groupIndex = collisionGroup;
    wheelFixture.filter.groupIndex = collisionGroup;

    bodyDef.position = position;
    bodyDef.position.x += dimensions.x*0.1f;
    shapeDef.SetAsBox(dimensions.x*0.4f,dimensions.y*0.33f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    wheelBody.position = position;
    wheelBody.position += Vec2f(dimensions.x*0.1f,dimensions.y*0.33f);
    b2Body* wheel = g_PhysicsManager.createBody(&wheelBody);
    wheel->CreateFixture(&wheelFixture);

    wheelJoint.Initialize(entity->mBody,wheel,anchorPoint);
    entity->setWheel((b2RevoluteJoint*)g_PhysicsManager.createJoint(&wheelJoint));

    entity->mSkin = new StaticSkin(dimensions.x,dimensions.y);
    setMaterial(entity->mSkin,materialName);

    if (aiType == ePlayerInputBrainType)
    {
        ((PlayMode*)g_Game.getGameMode(ePlayGameMode))->setBody(entity->mBody,(PlayerInputBrain*)brain);
    }
    return entity;
}
