#ifndef LEVELGEOMETRYFACTORY_H
#define LEVELGEOMETRYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class LevelGeometryFactory : public AbstractFactory<Entity, LevelGeometryFactory>
{
    public:
        LevelGeometryFactory(FactoryLoader* loader);
        virtual ~LevelGeometryFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "LevelGeometryFactory";
        }
    protected:
    private:
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

};

#endif // LEVELGEOMETRYFACTORY_H
