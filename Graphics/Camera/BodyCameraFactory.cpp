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
    factoryName = loader->get<std::string>("factoryName", "player");
}

BodyCameraFactory::~BodyCameraFactory()
{
    //dtor
}

Camera* BodyCameraFactory::useFactory(FactoryParameters* params)
{
    body = nullptr;
    Events::global().registerListener(this);
    AbstractFactoryBase<Entity>* entityFactory = AbstractFactories::global().getFactory<Entity>(factoryName);
    entityFactory->use(params);
    Camera* camera = new PhysicsCamera(body);
    return camera;
}

bool BodyCameraFactory::trigger(FactoryUsageEvent<b2Body>* _event)
{
    FactoryUsageEvent<b2Body>* event = static_cast<FactoryUsageEvent<b2Body>*>(_event);
    body = event->get();
    return false;
}
