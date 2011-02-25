#include "ConvexGeometryFactory.h"
#include <Factory/ConvexGeometryDef.h>
#include <Graphics/GraphicsManager.h>
#include <Entities/StaticGeometry.h>
#include <Graphics/Skins/ConvexPolygonSkin.h>
using namespace std;

ConvexGeometryFactory::ConvexGeometryFactory()
{
    //ctor
}

ConvexGeometryFactory::~ConvexGeometryFactory()
{
    //dtor
}
Entity* ConvexGeometryFactory::createEntity(FactoryDef* data)
{
    ConvexGeometryDef* def = (ConvexGeometryDef*)data;
    StaticGeometry* entity = new StaticGeometry;

    assert(def->numVertices < b2_maxPolygonVertices);

    physicsDef.shape.Set(def->vertices,def->numVertices);

    physicsDef.bodyDef.position = def->position;
    physicsDef.bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&physicsDef.bodyDef);
    entity->mBody->CreateFixture(&physicsDef.shape, physicsDef.density);

    entity->mSkin = new ConvexPolygonSkin(def->vertices,def->numVertices);
    MaterialContext* material = g_GraphicsManager.getMaterial(def->materialName);
    setMaterial(entity->mSkin,material);

    return entity;
}
