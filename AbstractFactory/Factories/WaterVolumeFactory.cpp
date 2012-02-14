#include "WaterVolumeFactory.h"
#include <Entities/WaterVolume.h>
#include <Physics/PhysicsManager.h>
#include <Physics/WaterPhysicsSystem.h>

WaterVolumeFactory::WaterVolumeFactory()
{
    //ctor
    system = nullptr;
}

WaterVolumeFactory::~WaterVolumeFactory()
{
    //dtor
}

void WaterVolumeFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin", "ConvexPolygonSkinFactory");
    bodyFactory = loader->getFactory<BodyPart>("body", "b2BodyBodyPartFactory");
    system = factories->getWorld()->getChildOfType<WaterPhysicsSystem>();
}

Entity* WaterVolumeFactory::useFactory(FactoryParameters* _parameters)
{
    //g_AIManager.addStaticGeometry(&points[0],points.size());
    WaterVolume* entity = new WaterVolume(system);
    Vec2f waterPoint = _parameters->get<Vec2f>("point", {0.0f,0.0f});
    waterPoint.y = 2;
    std::vector<Vec2f> points = system->getContainer(waterPoint);
    _parameters->addArray<Vec2f>("points", points);
    entity->baseInit(skinFactory->use(_parameters, entity));
    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);

    return entity;
}
