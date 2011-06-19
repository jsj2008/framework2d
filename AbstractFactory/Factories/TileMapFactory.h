#ifndef TILEMAPFACTORY_H
#define TILEMAPFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class TileMapFactory : public AbstractFactory<Entity, TileMapFactory>
{
    public:
        TileMapFactory(FactoryLoader* loader);
        virtual ~TileMapFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "TileMapFactory";
        }
    protected:
    private:
        Vec2f tileSize, offset;
        std::string tileType;
};

#endif // TILEMAPFACTORY_H
