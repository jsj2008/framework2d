#ifndef LEVELGEOMETRYFACTORY_H
#define LEVELGEOMETRYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class LevelGeometryFactory : public AbstractFactory
{
    public:
        LevelGeometryFactory(FactoryLoader* loader);
        virtual ~LevelGeometryFactory();
        Entity* useFactory(FactoryParameters* parameters);
    protected:
    private:
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

};

#endif // LEVELGEOMETRYFACTORY_H
