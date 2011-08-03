#include "TileMap.h"
#include <Physics/PhysicsManager.h>
#include <Entities/Tile.h>

TileMap::TileMap(const Vec2i& _dimensions, const Vec2f& _offset, const Vec2f& _tileSize)
:Entity(nullptr)
{
    //ctor
    dimensions = _dimensions;
    offset = _offset;
    tileSize = _tileSize;
    tiles.resize(dimensions.x);
    for (int i = 0; i < dimensions.x; i++)
    {
        tiles[i].resize(dimensions.y);
    }
}

TileMap::~TileMap()
{
    //dtor
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        for (unsigned int ii = 0; ii < tiles[i].size(); ii++)
        {
            delete tiles[i][ii];
        }
    }
}

void TileMap::update()
{

}

void TileMap::destroy(Vec2f position, Vec2f direction)
{
    //position += direction*0.5;
    position -= offset;
    position /= tileSize;
    Vec2i tile(position.x,position.y);
    if (!destroy(tile))
    {
        if (position.x*position.x > position.y*position.y)
        {
            if (position.x > 0)
            {
                tile.x++;
                destroy(tile);
            }
            else
            {
                tile.x--;
                destroy(tile);
            }
        }
        else
        {
            if (position.y > 0)
            {
                tile.y++;
                destroy(tile);
            }
            else
            {
                tile.y--;
                destroy(tile);
            }
        }
    }
}

bool TileMap::destroy(Vec2i tile)
{
    if (tile.x < dimensions.x && tile.y < dimensions.y && tile.x >= 0 && tile.y >= 0)
    if (tiles[tile.x][tile.y] != nullptr)
    {
        mBody->GetWorld()->DestroyBody(tiles[tile.x][tile.y]->mBody);
        tiles[tile.x][tile.y] = nullptr;
        return true;
    }
    return false;
}
