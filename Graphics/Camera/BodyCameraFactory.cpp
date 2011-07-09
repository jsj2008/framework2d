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
    AbstractFactories::global().registerListener<b2Body>(this);
    AbstractFactoryBase<Entity>* entityFactory = AbstractFactories::global().getFactory<Entity>(factoryName);
    entityFactory->use(params);
    Camera* camera = new PhysicsCamera(body);
    static_cast<PlayMode*>(g_Game.getGameMode(ePlayGameMode))->setCamera(camera);
    return camera;
}

bool BodyCameraFactory::trigger(Event* _event)
{
    FactoryEvent<b2Body>* event = static_cast<FactoryEvent<b2Body>*>(_event);
    body = event->get();
    return false;
}
