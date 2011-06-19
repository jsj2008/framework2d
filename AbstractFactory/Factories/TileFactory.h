#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class TileFactory : public AbstractFactory<Entity, TileFactory>
{
    public:
        TileFactory(FactoryLoader* loader);
        virtual ~TileFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "TileFactory";
        }
    protected:
    private:
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

        Vec2f size;
        std::string materialName;
};

#endif // TILEFACTORY_H
