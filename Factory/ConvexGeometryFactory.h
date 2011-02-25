#ifndef CONVEXGEOMETRYFACTORY_H
#define CONVEXGEOMETRYFACTORY_H

#include <Factory/Factory.h>
#include <Physics/PhysicsManager.h>
/**
Contents of stream:

unsigned char numPolygons
Vec2f vertices[numPolygons]
Vec2f position
unsigned short material
*/
class ConvexGeometryFactory : public Factory
{
    public:
        ConvexGeometryFactory();
        virtual ~ConvexGeometryFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
        PhysicsFactoryDef physicsDef;
};

#endif // CONVEXGEOMETRYFACTORY_H
