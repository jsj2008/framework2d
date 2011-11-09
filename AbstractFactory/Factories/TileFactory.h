#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class PhysicsManager;
class Skin;

class TileFactory : public AbstractFactory<Entity, TileFactory>
{
    public:
        TileFactory();
        virtual ~TileFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
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
        PhysicsManager* physicsManager;

        AbstractFactoryBase<Skin>* skinFactory;
};

#endif // TILEFACTORY_H
