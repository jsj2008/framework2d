#include "b2FixtureBodyPartFactory.h"
#include <Physics/PhysicsManager.h>
#include <Physics/BodyParts/b2FixtureBodyPart.h>
#include <Entities/CollisionResponse.h>
#include <Physics/BodyParts/b2BodyBodyPart.h>

b2FixtureBodyPartFactory::b2FixtureBodyPartFactory()
{
    //ctor
}

b2FixtureBodyPartFactory::~b2FixtureBodyPartFactory()
{
    //dtor
}

void b2FixtureBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    physicsManager = _factories->getWorld();

    responseFactory = _loader->getFactory<CollisionResponse>("collisionResponse", "CollisionResponseFactory");
    fixtureDef.density = _loader->get<float>("density", 1.0f);
    fixtureDef.restitution = _loader->get<float>("restitution", 0.0f);

    type = static_cast<ShapeType>(_loader->get<int>("shapeType", e_Circle)); /// FIXME loader needs to accept enums
    switch (type)
    {
        case e_Circle:
        {
            b2CircleShape* shape = new b2CircleShape;
            shape->m_radius = _loader->get<float>("radius", 1.0f);
            fixtureDef.shape = shape;
            break;
        }
        case e_Rect:
        {
            b2PolygonShape* shape = new b2PolygonShape;
            Vec2f dimensions = _loader->get<Vec2f>("dimensions", {1,1});
            shape->SetAsBox(dimensions.x*0.5f, dimensions.y*0.5f);
            fixtureDef.shape = shape;
            break;
        }
        case e_Polygon:
        {
            break;
        }
        case e_ShapeTypeMax:
        default:
        {
            throw -1;
        }
    }
}

BodyPart* b2FixtureBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    if (type == e_Polygon)
    {
        b2PolygonShape* shape = new b2PolygonShape;
        std::vector<Vec2f> points = _parameters->getArray<Vec2f>("points", {});
        assert(points.size() > 2);
        assert(points.size() < b2_maxPolygonVertices);
        shape->Set(&points[0], points.size());
        fixtureDef.shape = shape;
    }
    BodyPart* body = _parameters->get<BodyPart*>("body", nullptr);
    assert(dynamic_cast<b2BodyBodyPart*>(body));

    b2Fixture* fixture = static_cast<b2BodyBodyPart*>(body)->getBody()->CreateFixture(&fixtureDef);
    b2FixtureBodyPart* bodyPart = new b2FixtureBodyPart(fixture);

    fixture->SetFilterData({responseFactory->use(_parameters, bodyPart)});

    if (type == e_Polygon)
    {
        delete fixtureDef.shape;
    }
    return bodyPart;
}
