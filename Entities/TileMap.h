#ifndef TILEMAP_H
#define TILEMAP_H

#include <Entities/Entity.h>
#include <Types/Vec2i.h>
#include <vector>
class Tile;

class TileMap : public Entity
{
    public:
        TileMap(const Vec2i& _dimensions, const Vec2f& _offset, const Vec2f& _tileSize);
        void update();
        EntityType getType(){return eTileMapEntityType;}
        void destroy(Vec2f position, Vec2f direction);
    protected:
    private:
        virtual ~TileMap();
        friend class TileMapFactory;

        Vec2i dimensions;
        Vec2f offset, tileSize;
        std::vector<std::vector<Tile*>> tiles;
        bool destroy(Vec2i tile);
};

#endif // TILEMAP_H
