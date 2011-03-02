#ifndef CONVEXGEOMETRYFACTORY_H
#define CONVEXGEOMETRYFACTORY_H

#include <Factory/Factory.h>
#include <Physics/PhysicsManager.h>

class ConvexGeometryFactory : public Factory
{
    public:
        ConvexGeometryFactory();
        virtual ~ConvexGeometryFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

};

#endif // CONVEXGEOMETRYFACTORY_H
