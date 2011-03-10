#include "PathSegment.h"
#include <AI/Pathfinding/PathNode.h>
#include <Box2D/Common/b2Math.h>

PathSegment::PathSegment(PathNode* _nodeA, PathNode* _nodeB)
{
    //ctor
    nodeA = _nodeA;
    nodeB = _nodeB;
    nodeA->addSegment(this);
    nodeB->addSegment(this);
    determineType(nodeA->getPosition(),nodeB->getPosition());
}

PathSegment::~PathSegment()
{
    //dtor
}
void PathSegment::determineType(const Vec2f& vertexA, const Vec2f& vertexB)
{
    Vec2f slope = vertexB - vertexA;
    slope.Normalize();
    float dot = b2Dot(slope,Vec2f(1,0));
    if (dot > 0.8f) // Close enough to a floor
    {
        type = eFloor;
    }
    else
    {
        type = eWall;
    }
}
bool PathSegment::isDirectlyConnected(PathSegment* neighbour)
{
    return (nodeA->isConnected(neighbour) || nodeB->isConnected(neighbour));
    return false;
    //return nodeA->getSegmentB() == neighbour || nodeB->getSegmentA() == neighbour || nodeA->getSegmentA() == neighbour || nodeB->getSegmentB() == neighbour;
}

void PathSegment::closestPoints(PathSegment* segment, float& t1, float& t2)
{
    Vec2f p1 = this->getNodeA()->getPosition();
    Vec2f p2 = this->getNodeB()->getPosition();
    Vec2f p3 = segment->getNodeA()->getPosition();
    Vec2f p4 = segment->getNodeB()->getPosition();

    t1 = (((p4.x - p3.x)*(p1.y - p3.y)) - ((p4.y - p3.y)*(p1.x - p3.x)))/
         (((p4.y - p3.y)*(p2.x - p1.x)) - ((p4.x - p3.x)*(p2.y - p1.y)));
    t2 = (((p2.x - p1.x)*(p1.y - p3.y)) - ((p2.y - p1.y)*(p1.x - p3.x)))/
         (((p4.y - p3.y)*(p2.x - p1.x)) - ((p4.x - p3.x)*(p2.y - p1.y)));
}
#include <GL/gl.h>
void PathSegment::tempRender()
{
    if (type == eFloor)
        glColor3f(0,1,0);
    else
        glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2f(nodeA->getPosition().x,nodeA->getPosition().y);
    glVertex2f(nodeB->getPosition().x,nodeB->getPosition().y);
    glEnd();
    glBegin(GL_POINTS);
    nodeA->tempRender();
    nodeB->tempRender();
    glEnd();
    glColor3f(1,1,1);
}


























