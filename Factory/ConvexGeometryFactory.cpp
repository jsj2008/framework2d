#include "ConvexGeometryFactory.h"
#include <Factory/ConvexGeometryDef.h>
#include <Graphics/GraphicsManager.h>
#include <Entities/StaticGeometry.h>
#include <Graphics/Skins/ConvexPolygonSkin.h>
using namespace std;

ConvexGeometryFactory::ConvexGeometryFactory()
{
    //ctor
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::StaticGeometryCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::StaticGeometryCategory);
}

ConvexGeometryFactory::~ConvexGeometryFactory()
{
    //dtor
}
Entity* ConvexGeometryFactory::createEntity(FactoryDef* data)
{
    ConvexGeometryDef* def = (ConvexGeometryDef*)data;
    StaticGeometry* entity = new StaticGeometry;

    assert(def->numVertices <= b2_maxPolygonVertices);

    shapeDef.Set(&def->getVertex(0),def->numVertices);

    bodyDef.position = def->getPosition();
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new ConvexPolygonSkin(&def->getVertex(0),def->numVertices);
    MaterialContext* material = g_GraphicsManager.getMaterial(def->materialName);
    setMaterial(entity->mSkin,material);

    return entity;
}
