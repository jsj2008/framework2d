#ifndef LEVELGEOMETRYFACTORY_H
#define LEVELGEOMETRYFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;

class LevelGeometryFactory : public AbstractFactory<Entity, LevelGeometryFactory>
{
    public:
        LevelGeometryFactory();
        virtual ~LevelGeometryFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "LevelGeometryFactory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

};

#endif // LEVELGEOMETRYFACTORY_H
