#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
    //ctor
}

ShapeFactory::~ShapeFactory()
{
    //dtor
}

void ShapeFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    type = static_cast<ShapeType>(_loader->get<int>("bodyType", e_Circle)); /// FIXME loader needs to accept enums
    assert(type != e_ShapeTypeMax);
}

b2Shape* ShapeFactory::useFactory(FactoryParameters* _parameters)
{
    b2Shape* _shape = nullptr;
    switch (type)
    {
        case e_Circle:
        {
            b2CircleShape* shape = new b2CircleShape;
            shape->m_radius = _parameters->get<float>("radius", 1.0f);
            return shape;
            break;
        }
        case e_Polygon:
        {
            b2PolygonShape* shape = new b2PolygonShape;
            std::vector<Vec2f> points = _parameters->getArray<Vec2f>("points", {{0,0}, {0, 1}, {1, 0}});
            shape->Set(&points[0], points.size());
            return shape;
            break;
        }
        case e_Rect:
        {
            b2PolygonShape* shape = new b2PolygonShape;
            Vec2f dimensions = _parameters->get<Vec2f>("dimensions", {1,1});
            shape->SetAsBox(dimensions.x*0.5f, dimensions.y*0.5f);
            return shape;
            break;
        }
        case e_ShapeTypeMax:
        default:
        {
            throw -1;
        }
    }
    return _shape;
}
