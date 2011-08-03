#include "Pathfinding.h"
#include <Types/Vec2f.h>
class PathSegment;

Pathfinding::Pathfinding(PhysicsManager* _physicsManager)
:pathGraph(_physicsManager)
{
    //ctor
}

Pathfinding::~Pathfinding()
{
    //dtor
}
Paths* Pathfinding::finalise()
{
    return pathGraph.finalise();
}
void Pathfinding::addStaticGeometry(Vec2f* vertices, int numVertices)
{
    PathSegment* trueFirstSegment = nullptr;
    PathSegment* firstSegment = pathGraph.addSegment(vertices[0],vertices[1], &trueFirstSegment);
    PathSegment* currentSegment = firstSegment;
    for (int i = 2; i < numVertices; i++)
    {
        currentSegment = pathGraph.appendSegment(currentSegment, vertices[i]);
    }
    pathGraph.connectSegments(currentSegment, trueFirstSegment);
}
