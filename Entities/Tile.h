#ifndef TILE_H
#define TILE_H

#include <Entities/Entity.h>


class Tile : public Entity
{
    public:
        Tile();
        void update();
    protected:
    private:
        friend class TileMap;
        virtual ~Tile();
};

#endif // TILE_H
