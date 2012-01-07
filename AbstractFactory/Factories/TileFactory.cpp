#include "TileFactory.h"
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Tile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Types/Vec2i.h>

TileFactory::TileFactory()
{


}
TileFactory::~TileFactory()
{
    //dtor
}
void TileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin", "StaticSkinFactory");
}


Entity* TileFactory::useFactory(FactoryParameters* _parameters)
{
    Entity* entity = new Tile;
    entity->baseInit(skinFactory->use(_parameters, entity));

    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);


    return entity;
}

