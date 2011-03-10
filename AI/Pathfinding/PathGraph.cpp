#include "PathGraph.h"
#include <AI/Pathfinding/PathSegment.h>
#include <AI/Pathfinding/PathNode.h>

PathGraph::PathGraph()
{
    //ctor
}

PathGraph::~PathGraph()
{
    //dtor
}

PathSegment* PathGraph::addSegment(const Vec2f& vertexA, const Vec2f& vertexB, PathSegment** trueFirst)
{
    PathNode* nodeA = new PathNode(vertexA);
    PathNode* nodeB = new PathNode(vertexB);
    PathSegment* segment = new PathSegment(nodeA, nodeB);

    nodes.push_back(nodeA);
    nodes.push_back(nodeB);
    PathSegment* ret = addSegment(segment);
    *trueFirst = segment;
    return ret;
}

PathSegment* PathGraph::appendSegment(PathSegment* currentSegment, const Vec2f& vertexB)
{
    PathNode* nodeA = currentSegment->getNodeB();
    PathNode* nodeB = new PathNode(vertexB);
    PathSegment* segment = new PathSegment(nodeA, nodeB);

    nodes.push_back(nodeB);
    PathSegment* ret = addSegment(segment);
    return ret;
}

PathSegment* PathGraph::connectSegments(PathSegment* segmentA, PathSegment* segmentB)
{
    PathNode* nodeA = segmentA->getNodeB();
    PathNode* nodeB = segmentB->getNodeA();
    PathSegment* segment = new PathSegment(nodeA, nodeB);

    PathSegment* ret = addSegment(segment);
    return ret;
}

void PathGraph::tempRender()
{
    for (auto i = segments.begin(); i != segments.end(); i++)
    {
        (*i)->tempRender();
    }
}
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>
class PathNodeGeometryCallback : public b2QueryCallback
{
    public:
        PathNodeGeometryCallback(Vec2f _point)
        :point(_point)
        {
            numBodies = 0;
        }
        ~PathNodeGeometryCallback()
        {

        }
        bool ReportFixture(b2Fixture* fixture)
        {
            if (fixture->GetBody()->GetType() == b2_staticBody)
            {
                if (fixture->TestPoint(point)
                    || fixture->TestPoint(Vec2f(point.x-0.001,point.y+0.001))
                    || fixture->TestPoint(Vec2f(point.x+0.001,point.y+0.001))
                    || fixture->TestPoint(Vec2f(point.x+0.001,point.y-0.001))
                    || fixture->TestPoint(Vec2f(point.x-0.001,point.y-0.001)))
                numBodies++;
            }
            return true;
        }
        bool contained()
        {
            return numBodies > 1;
        }
    private:
        int numBodies;
        Vec2f point;
};
#include <iostream>
using namespace std;
void PathGraph::finalise()
{
    unsigned int size = 0;
    while (segments.size() != size)
    {
        unsigned int oldSize = size;
        size = segments.size();
        for (unsigned int i = 0; i < size; i++)
        {
            unsigned int offset = (i < oldSize)? oldSize:i;
            for (unsigned int ii = offset; ii < size; ii++)
            {
                auto a = segments[i];
                auto b = segments[ii];
                if ((b)->isDirectlyConnected(a) || a == b)
                {
                    continue;
                }
                float t1,t2;
                a->closestPoints(b,t1,t2);
                if (t1 > 0.0f && t1 < 1.0f && t2 > 0.0f && t2 < 1.0f)
                {
                    Vec2f start = b->getNodeA()->getPosition();
                    Vec2f end = b->getNodeB()->getPosition();
                    Vec2f direction = end-start;
                    Vec2f middle = ((direction)*t2) + start;
                    PathNode* newNode = new PathNode(middle);
                    nodes.push_back(newNode);
                    separate(b,t2, newNode);
                    separate(a,t1, newNode);
                }
            }
        }
    }
    for (unsigned int i = 0; i < segments.size(); i++)
    {
        PathSegment* segment = segments[i];
        Vec2f point = ((segment->getNodeB()->getPosition() - segment->getNodeA()->getPosition())*0.5f)+segment->getNodeA()->getPosition();
        PathNodeGeometryCallback callback(point);
        g_PhysicsManager.AABBQuery(&callback,point);
        if (callback.contained())
        {
            PathNode* node = segments[i]->getNodeA();
            if (!node->removeSegment(segments[i]))
            {
                deleteNode(node);
            }
            node = segments[i]->getNodeB();
            if (!node->removeSegment(segments[i]))
            {
                deleteNode(node);
            }
            segments.erase(segments.begin() + i);
            i--;
        }
    }
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->setType();
    }

}
void PathGraph::deleteNode(PathNode* node)
{
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        if (*i == node)
        {
            nodes.erase(i);
            return;
        }
    }
}
PathSegment* PathGraph::addSegment(PathSegment* segment)
{
    segments.push_back(segment);
    return segment;
}
PathSegment* PathGraph::separate(PathSegment* segment, float point, PathNode* newNode)
{
    PathNode* nodeB = segment->getNodeB();
    nodeB->removeSegment(segment);
    segment->setNodeB(newNode);
    newNode->addSegment(segment);

    PathSegment* segmentB = new PathSegment(newNode,nodeB);

    addSegment(segmentB);
    return segmentB;
}




















































