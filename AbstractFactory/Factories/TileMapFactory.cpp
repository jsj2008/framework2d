#include "TileMapFactory.h"
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Entities/TileMap.h>
#include <Entities/Tile.h>

TileMapFactory::TileMapFactory()
{

}
void TileMapFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    tileType = loader->get<std::string>("tileType", "TileFactory");
    tileSize = loader->get<Vec2f>("tileSize",Vec2f(1,1));
    offset = loader->get<Vec2f>("offset",Vec2f(-30,-30));
}

TileMapFactory::~TileMapFactory()
{
    //dtor
}
TileMap* g_TileMap = nullptr;
Entity* TileMapFactory::useFactory(FactoryParameters* params)
{
    Vec2i dimensions = params->get<Vec2i>("dimensions",Vec2i(100,100));
    TileMap* entity = new TileMap(dimensions,offset,tileSize);

    std::vector<Vec2i> solidTiles = params->get<std::vector<Vec2i>>("solidTiles",{Vec2i(0,0),Vec2i(2,0),Vec2i(3,0)});

    FactoryParameters parameters;

    for (unsigned int i = 0; i < solidTiles.size(); i++)
    {
        parameters.add("position",Vec2f(solidTiles[i].x*tileSize.x,solidTiles[i].y*tileSize.y));
        entity->tiles[solidTiles[i].x][solidTiles[i].y] = static_cast<Tile*>(AbstractFactories::global().useFactory<Entity>(tileType, &parameters));
    }
    g_TileMap = entity;
    return entity;
}

