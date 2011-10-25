#include "BodyCameraFactory.h"
#include <Box2D/Box2D.h>
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/PlayMode.h>
#include <Game.h>

BodyCameraFactory::BodyCameraFactory()
{
    //ctor
}
void BodyCameraFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
}

BodyCameraFactory::~BodyCameraFactory()
{
    //dtor
}

Camera* BodyCameraFactory::useFactory(FactoryParameters* params)
{
    b2Body* body = params->get<b2Body*>("body", nullptr);
    Camera* camera = new PhysicsCamera(body);
    return camera;
}

