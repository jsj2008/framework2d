#include "WheelControllerFactory.h"
#include <AI/CharacterControllers/WheelCharacterController.h>
#include <Physics/BodyParts/JointBodyPart.h>

WheelControllerFactory::WheelControllerFactory()
{
    //ctor
    /// Defaults
    properties.walkSpeed = 20.0f;
    properties.jumpHeight = 50.0f;
    properties.extraGravity = 0.5f;
    properties.jumpRecharge = 5;
    properties.fallTolerance = 3;
}

WheelControllerFactory::~WheelControllerFactory()
{
    //dtor
}

void WheelControllerFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    properties.walkSpeed = loader->get<float>("walkSpeed", properties.walkSpeed);
    properties.jumpHeight = loader->get<float>("jumpHeight", properties.jumpHeight);
    properties.extraGravity = loader->get<float>("extraGravity", properties.extraGravity);
    properties.jumpRecharge = loader->get<int>("jumpRecharge", properties.jumpRecharge);
    properties.fallTolerance = loader->get<int>("fallTolerance", properties.fallTolerance);
}
CharacterController* WheelControllerFactory::useFactory(FactoryParameters* _parameters)
{
    /*void* userData = _parameters->get<void*>("userData", nullptr);
    assert(userData);*/
    BodyPart* joint = _parameters->get<BodyPart*>("joint", nullptr);
    assert(joint);
    assert(dynamic_cast<JointBodyPart*>(joint));
    JointBodyPart* castJoint = static_cast<JointBodyPart*>(joint);
    WheelCharacterController* controller = new WheelCharacterController(castJoint, &properties);
    return controller;
}
