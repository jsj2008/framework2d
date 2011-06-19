#ifndef TILE_H
#define TILE_H

#include <Entities/Entity.h>


class Tile : public Entity
{
    public:
        Tile();
        void update();
        EntityType getType(){return eTileEntityType;}
    protected:
    private:
        virtual ~Tile();
};

#endif // TILE_H
