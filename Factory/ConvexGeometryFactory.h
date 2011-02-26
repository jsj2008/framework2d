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
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;

};

#endif // CONVEXGEOMETRYFACTORY_H
/*struct PhysicsFactoryDef
{
    PhysicsFactoryDef();
    b2BodyDef bodyDef;
    b2PolygonShape shape;
#ifdef JUMPING_SENSOR
    b2FixtureDef additionalFixture;
    bool useAdditionalFixture;
#endif
    float density;
};*/
