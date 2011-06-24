#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
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
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

        Vec2f size;
        std::string materialName;
};

#endif // TILEFACTORY_H
