#include "SingleFixtureBodyPartFactory.h"
#include <Physics/PhysicsManager.h>
#include <Physics/BodyParts/SingleFixtureBodyPart.h>
#include <Entities/CollisionResponse.h>

SingleFixtureBodyPartFactory::SingleFixtureBodyPartFactory()
{
    //ctor
}

SingleFixtureBodyPartFactory::~SingleFixtureBodyPartFactory()
{
    //dtor
}

void SingleFixtureBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    physicsManager = _factories->getWorld();

    bodyDef.bullet = _loader->get<bool>("bullet", false);
    bodyDef.fixedRotation = _loader->get<bool>("fixedRotation", false);
    bodyDef.type = _loader->get<int>("bodyType", b2_dynamicBody); /// FIXME loader needs to accept enums

    responseFactory = _loader->getFactory<CollisionResponse>("collisionResponse", "CollisionResponseFactory");
    fixtureDef.density = _loader->get<float>("density", 1.0f);
    fixtureDef.restitution = _loader->get<float>("restitution", 1.0f);
    //shapeFactory = _loader->getFactory<b2Shape>("shape", "ShapeFactory");
    type = static_cast<ShapeType>(_loader->get<int>("shapeType", e_Circle)); /// FIXME loader needs to accept enums
}

BodyPart* SingleFixtureBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    bodyDef.position = _parameters->get<Vec2f>("position", {0,0});
    bodyDef.linearVelocity = _parameters->get<Vec2f>("velocity",{0,0});
    SingleFixtureBodyPart* bodyPart = new SingleFixtureBodyPart;
    bodyDef.bodyPart = bodyPart;
    b2Body* body = physicsManager->createBody(&bodyDef);

    fixtureDef.filter.response = responseFactory->use(_parameters, bodyPart);
    switch (type)
    {
        case e_Circle:
        {
            b2CircleShape* shape = new b2CircleShape;
            shape->m_radius = _parameters->get<float>("radius", 1.0f);
            fixtureDef.shape = shape;
            break;
        }
        case e_Polygon:
        {
            b2PolygonShape* shape = new b2PolygonShape;
            std::vector<Vec2f> points = _parameters->getArray<Vec2f>("points", {{0,0}, {0, 1}, {1, 0}});
            shape->Set(&points[0], points.size());
            fixtureDef.shape = shape;
            break;
        }
        case e_Rect:
        {
            b2PolygonShape* shape = new b2PolygonShape;
            Vec2f dimensions = _parameters->get<Vec2f>("dimensions", {1,1});
            shape->SetAsBox(dimensions.x*0.5f, dimensions.y*0.5f);
            fixtureDef.shape = shape;
            break;
        }
        case e_ShapeTypeMax:
        default:
        {
            throw -1;
        }
    }

    bodyPart->setBody(body);
    fixtureDef.bodyPart = bodyPart;
    bodyPart->setFixture(body->CreateFixture(&fixtureDef));

    delete fixtureDef.shape; /// FIXME override the box2d factory for efficiency

    return bodyPart;
}
