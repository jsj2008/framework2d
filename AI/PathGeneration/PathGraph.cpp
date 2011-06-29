#include "PathGraph.h"
#include <AI/PathGeneration/PathSegment.h>
#include <AI/PathGeneration/PathNodeDynamic.h>
#include <AI/Pathfinding/Paths.h>

PathGraph::PathGraph()
{
    //ctor
}

PathGraph::~PathGraph()
{
    //dtor
    while (!segments.empty())
    {
        delete segments.back();
        segments.pop_back();
    }
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        delete *i;
    }
}

PathSegment* PathGraph::addSegment(const Vec2f& vertexA, const Vec2f& vertexB, PathSegment** trueFirst)
{
    PathNodeDynamic* nodeA = new PathNodeDynamic(vertexA);
    PathNodeDynamic* nodeB = new PathNodeDynamic(vertexB);
    PathSegment* segment = new PathSegment(nodeA, nodeB);

    nodes.push_back(nodeA);
    nodes.push_back(nodeB);
    PathSegment* ret = addSegment(segment);
    *trueFirst = segment;
    return ret;
}

PathSegment* PathGraph::appendSegment(PathSegment* currentSegment, const Vec2f& vertexB)
{
    PathNodeDynamic* nodeA = currentSegment->getNodeB();
    PathNodeDynamic* nodeB = new PathNodeDynamic(vertexB);
    PathSegment* segment = new PathSegment(nodeA, nodeB);

    nodes.push_back(nodeB);
    PathSegment* ret = addSegment(segment);
    return ret;
}

PathSegment* PathGraph::connectSegments(PathSegment* segmentA, PathSegment* segmentB)
{
    PathNodeDynamic* nodeA = segmentA->getNodeB();
    PathNodeDynamic* nodeB = segmentB->getNodeA();
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
class PathNodeDynamicGeometryCallback : public b2QueryCallback
{
    public:
        PathNodeDynamicGeometryCallback(Vec2f _point)
        :point(_point)
        {
            numBodies = 0;
        }
        ~PathNodeDynamicGeometryCallback()
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
#include <unordered_map>
#include <iostream>
using namespace std;
Paths* PathGraph::finalise()
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
                a->closestPoints(b->getNodeA()->getPosition(),b->getNodeB()->getPosition(),t1,t2);
                if (t1 > 0.0f && t1 < 1.0f && t2 > 0.0f && t2 < 1.0f)
                {
                    Vec2f start = b->getNodeA()->getPosition();
                    Vec2f end = b->getNodeB()->getPosition();
                    Vec2f direction = end-start;
                    Vec2f middle = ((direction)*t2) + start;
                    PathNodeDynamic* newNode = new PathNodeDynamic(middle);
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
        PathNodeDynamicGeometryCallback callback(point);
        g_PhysicsManager.AABBQuery(&callback,point);
        if (callback.contained())
        {
            PathNodeDynamic* node = segments[i]->getNodeA();
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
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        (*i)->setType();
    }
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        if ((*i)->getType() == PathNodeDynamic::eCliff)
        {
            for (auto ii = i+1; ii != nodes.end(); ii++)
            {
                if ((*ii)->getType() == PathNodeDynamic::eCliff)
                {
                    Vec2f connection = (*ii)->getPosition() - (*i)->getPosition();
                    float length = connection.Length();
                    if (length < 1.0f)
                    {
                        PathSegment* jumpSegment = new PathSegment(*i,*ii,PathSegment::eTwoWayJump);
                        (*i)->setType(PathNodeDynamic::eJumpable);
                        (*ii)->setType(PathNodeDynamic::eJumpable);
                        segments.push_back(jumpSegment);
                        break;
                    }
                }
            }
        }
    }
    std::unordered_map<PathNodeDynamic*,NodeReference> createdNodes;
    /*for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        PathNode* node = (*i)->createNode();
        createdNodes[*i] = node;
        paths.addNode(node);
    }
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        (*i)->resolveLinks(createdNodes);
    }*/
    std::vector<std::vector<PathNode*>*> nodeLists;
    nodeLists.push_back(new std::vector<PathNode*>);
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        (*i)->createNodes(createdNodes,nodeLists.back());
        if (nodeLists.back()->size() != 0)
        {
            nodeLists.push_back(new std::vector<PathNode*>);
        }
    }
    delete nodeLists.back();
    nodeLists.pop_back();
    std::cout << nodeLists.size() << endl;
    return new Paths(nodeLists);
}
void PathGraph::deleteNode(PathNodeDynamic* node)
{
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        if (*i == node)
        {
            delete *i;
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
PathSegment* PathGraph::separate(PathSegment* segment, float point, PathNodeDynamic* newNode)
{
    PathNodeDynamic* nodeB = segment->getNodeB();
    nodeB->removeSegment(segment);
    segment->setNodeB(newNode);
    newNode->addSegment(segment);

    PathSegment* segmentB = new PathSegment(newNode,nodeB);

    addSegment(segmentB);
    return segmentB;
}
PathSegment* PathGraph::findClosestPath(const Vec2f& position)
{
    float smallestT = 1000.0f;
    PathSegment* closestPath = nullptr;
    for (auto i = segments.begin(); i != segments.end(); i++)
    {
        if ((*i)->getType() == PathSegment::eFloor)
        {
            float t = (*i)->closestPoint(position);
            if (t < smallestT)
            {
                smallestT = t;
                closestPath = *i;
            }
        }
    }
    assert(closestPath);
    return closestPath;
}



















































