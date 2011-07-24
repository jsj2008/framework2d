#ifndef TILE_H
#define TILE_H

#include <Entities/Entity.h>


class Tile : public Entity
{
    public:
        Tile(Skin* _skin);
        void update();
        EntityType getType(){return eTileEntityType;}
    protected:
    private:
        friend class TileMap;
        virtual ~Tile();
};

#endif // TILE_H
