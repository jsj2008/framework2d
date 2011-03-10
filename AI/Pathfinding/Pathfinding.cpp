#include "Pathfinding.h"
#include <Types/Vec2f.h>
class PathSegment;

Pathfinding::Pathfinding()
{
    //ctor
}

Pathfinding::~Pathfinding()
{
    //dtor
}
void Pathfinding::finalise()
{
    pathGraph.finalise();
}
void Pathfinding::addStaticGeometry(Vec2f* vertices, int numVertices)
{
    PathSegment* trueFirstSegment = NULL;
    PathSegment* firstSegment = pathGraph.addSegment(vertices[0],vertices[1], &trueFirstSegment);
    PathSegment* currentSegment = firstSegment;
    for (int i = 2; i < numVertices; i++)
    {
        currentSegment = pathGraph.appendSegment(currentSegment, vertices[i]);
    }
    pathGraph.connectSegments(currentSegment, trueFirstSegment);
}
