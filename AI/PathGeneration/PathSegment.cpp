#include "PathSegment.h"
#include <AI/PathGeneration/PathNodeDynamic.h>
#include <Box2D/Common/b2Math.h>

PathSegment::PathSegment(PathNodeDynamic* _nodeA, PathNodeDynamic* _nodeB)
{
    //ctor
    nodeA = _nodeA;
    nodeB = _nodeB;
    nodeA->addSegment(this);
    nodeB->addSegment(this);
    determineType(nodeA->getPosition(),nodeB->getPosition());
}

PathSegment::PathSegment(PathNodeDynamic* _nodeA, PathNodeDynamic* _nodeB, Type jumpType)
{
    //ctor
    nodeA = _nodeA;
    nodeB = _nodeB;
    nodeA->addSegment(this);
    nodeB->addSegment(this);
    type = jumpType;
}

PathSegment::~PathSegment()
{
    //dtor
}
PathNodeDynamic* PathSegment::getOther(PathNodeDynamic* first)
{
    if (first == nodeA)
    {
        return nodeB;
    }
    else
    {
        assert(first == nodeB);
        return nodeA;
    }
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
Vec2f GetClosetPoint(Vec2f A, Vec2f B, Vec2f P, bool segmentClamp)
{
    Vec2f AP = P - A;
    Vec2f AB = B - A;
    float ab2 = AB.x*AB.x + AB.y*AB.y;
    float ap_ab = AP.x*AB.x + AP.y*AB.y;
    float t = ap_ab / ab2;
    if (segmentClamp)
    {
        if (t < 0.0f) t = 0.0f;
        else if (t > 1.0f) t = 1.0f;
    }
    Vec2f Closest = A + AB * t;
    return Closest;
}
float PathSegment::closestPoint(const Vec2f& P)
{
    Vec2f A = nodeA->getPosition();
    Vec2f B = nodeB->getPosition();
    Vec2f AP = P - A;
    Vec2f AB = B - A;
    float ab2 = AB.x*AB.x + AB.y*AB.y;
    float ap_ab = AP.x*AB.x + AP.y*AB.y;
    float t = ap_ab / ab2;
    const bool segmentClamp = true;
    if (segmentClamp)
    {
        if (t < 0.0f) t = 0.0f;
        else if (t > 1.0f) t = 1.0f;
    }
    Vec2f Closest = A + AB * t;
    Vec2f connection = Closest - P;
    return connection.Length();
}
void PathSegment::closestPoints(const Vec2f& p3, const Vec2f& p4, float& t1, float& t2)
{
    Vec2f p1 = this->getNodeA()->getPosition();
    Vec2f p2 = this->getNodeB()->getPosition();

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
    else if (type == eWall)
        glColor3f(1,0,0);
    else
        glColor3f(1,1,1);
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


























