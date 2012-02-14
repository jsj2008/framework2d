#include "WaterPhysicsSystem.h"
#include <Physics/BodyParts/b2FixtureBodyPart.h>
#include <Box2D/Box2D.h>
#include <Types/Vec2f.h>

WaterPhysicsSystem::WaterPhysicsSystem()
{
    //ctor
    addEdge({-10,0}, {-5,5}, nullptr);
    addEdge({5,5}, {10,0}, nullptr);
    addEdge({-6,5}, {6,5}, nullptr);
}

WaterPhysicsSystem::~WaterPhysicsSystem()
{
    //dtor
}

void WaterPhysicsSystem::registerActions(GameObjectType* _type)
{

}

void WaterPhysicsSystem::addFixture(b2FixtureBodyPart* _bodyPart)
{
    b2Fixture* fixture = _bodyPart->getFixture();
    b2Shape* shape = fixture->GetShape();
    assert(dynamic_cast<b2PolygonShape*>(shape)); /// Can't support circles at this time
    b2PolygonShape* polygon = static_cast<b2PolygonShape*>(shape);
    for (int i = 0; i != polygon->GetVertexCount(); i++)
    {
        Vec2f a = polygon->GetVertex(i);
        Vec2f b = polygon->GetVertex((i+1)%polygon->GetVertexCount());
        addEdge(a, b, _bodyPart);
    }
}

void WaterPhysicsSystem::addEdge(const Vec2f& _a, const Vec2f& _b, b2FixtureBodyPart* _destructionListener)
{
    Edge* edge = new Edge;
    Edge* intersections[2] = {-1, -1};
    unsigned int numIntersections = 0;
    for (unsigned int i = 0; i != edges.size(); i++)
    {
        try
        {
            Vec2f position = intersectionPosition(edges[i]->aPosition(), edges[i]->bPosition(), _a, _b);
            assert(numIntersections < 2);
            intersections[numIntersections] = edges[i];
            numIntersections++;
        }
        catch (int i)
        {
        }
    }
    switch (numIntersections)
    {
        case 0:
        {
            edge->a = new Vertex(_a);
            edge->a->b = edge;
            edge->b = new Vertex(_b);
            edge->b->a = edge;
            edges.push_back(edge);
            break;
        }
        case 1:
        {
            float scalar = intersectionValue(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
            if (scalar < 0.01f)
            {
                Vec2f position = intersectionPosition(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
                createVertex(position, intersections[0], edge);
            }
            else if (scalar > 0.99f)
            {
                Vec2f position = intersectionPosition(_a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
                createVertex(position, edge, intersections[0]);
            }
            else assert(false);
            edges.push_back(edge);
            break;
        }
        case 2:
        {
            float scalar0 = intersectionValue( _a, _b, intersections[0]->aPosition(), intersections[0]->bPosition());
            float scalar1 = intersectionValue( _a, _b, intersections[1]->aPosition(), intersections[1]->bPosition());
            if (scalar0 > scalar1)
            {
                /*Edge* temp = intersections[0];
                intersections[0] = intersections[1];
                intersections[1] = temp;*/
                float temp = scalar0;
                scalar0 = scalar1;
                scalar1 = temp;
            }
            Vec2f position0 = positionFromScalarValue(_a, _b, scalar0); /// FIXME might be the wrong line
            createVertex(position0, intersections[0], edge);

            Vec2f position1 = positionFromScalarValue(_a, _b, scalar1);
            createVertex(position1, edge, intersections[1]);
            edges.push_back(edge);
            break;
        }
        default:
        {
            assert(false);
        }
    }
    //edges.push_back({_a, _b});
}

void WaterPhysicsSystem::createVertex(const Vec2f& _position, Edge* _a, Edge* _b)
{
    Vertex* vertex = nullptr;
    Vertex* oldA = _a->b;
    Vertex* oldB = _b->a;
    if (oldA == nullptr)
    {
        if (oldB == nullptr)
        {
            vertex = new Vertex(_position);
            vertex->a = _b;
            vertex->b = _a;
        }
        else
        {
            vertex = oldB;
            vertex->position = _position;
            vertex->a = _b;
            vertex->b = _a;
        }
    }
    else
    {
        vertex = oldA;
        vertex->position = _position;
        vertex->a = _b;
        vertex->b = _a;
    }
    assert(vertex);
    _a->b = vertex;
    _b->a = vertex;
}

Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd, bool _aNeedsIntersect, bool _bNeedsIntersect);

std::vector<Vec2f> WaterPhysicsSystem::getContainer(const Vec2f& _position)
{
    Vec2f a = _position;
    Vec2f b = a;
    a.x -= 100;
    b.x += 100;

    Edge* left = nullptr;
    float leftX;
    Edge* right = nullptr;
    float rightX;
    unsigned int edgesSize = edges.size();
    for (unsigned int i = 0; i != edgesSize; i++)
    {
        Edge* edge = edges[i];
        try
        {
            Vec2f position = intersectionPosition(edge->aPosition(), edge->bPosition(), a, b, false, true);
            if (position.x < _position.x)
            {
                if (left)
                {
                    if (leftX < position.x)
                    {
                        left = edge;
                        leftX = position.x;
                    }
                }
                else
                {
                    left = edge;
                    leftX = position.x;
                }
            }
            else
            {
                if (right)
                {
                    if (rightX < position.x)
                    {
                        right = edge;
                        rightX = position.x;
                    }
                }
                else
                {
                    right = edge;
                    rightX = position.x;
                }
            }
        }
        catch (int i)
        {
        }
    }
    if (left == nullptr || right == nullptr)
    {
        assert(false);
    }
    std::vector<Vec2f> shape;
    shape.push_back({rightX, _position.y});
    while (true)
    {
        if (right == left)
        {
            shape.push_back({leftX, _position.y});
            return shape;
        }
        if (right->a->getVertexShape() == Vertex::eLeft) /// FIXME change this to left
        {
            shape.push_back(right->aPosition());
            right = right->a->b;
        }
        else assert(false);
    }
}

WaterPhysicsSystem::Vertex::VertexShape WaterPhysicsSystem::Vertex::getVertexShape()
{
    Vec2f dirA = a->aPosition() - position;
    Vec2f dirB = b->bPosition() - position;
    dirA /= dirA.Length();
    dirB /= dirB.Length();
    float angleA = atan2(dirA.x, dirA.y);
    float angleB = atan2(dirB.x, dirB.y);
    float angleDiff = angleB - angleA;
    return eLeft;
}



































