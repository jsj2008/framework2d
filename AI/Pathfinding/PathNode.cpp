#include "PathNode.h"
#include <AI/Pathfinding/PathSegment.h>

PathNode::PathNode(const Vec2f& _position)
:position(_position)
{
    type = eTypesMax;
}

PathNode::~PathNode()
{
    //dtor
}

/*void PathNode::setSegmentA(PathSegment* segment)
{
    segmentA = segment;
}
void PathNode::setSegmentB(PathSegment* segment)
{
    segmentB = segment;
}*/
#include <cassert>
bool PathNode::removeSegment(PathSegment* segment)
{
    for (auto i = segments.begin(); i != segments.end(); i++)
    {
        if (*i == segment)
        {
            segments.erase(i);
            return segments.size() != 0;
        }
    }
    assert(false);
}
bool PathNode::isConnected(PathSegment* segment)
{
    for (auto i = segments.begin(); i != segments.end(); i++)
    {
        if (*i == segment)
        {
            return true;
        }
    }
    return false;
}
#include <cassert>
void PathNode::setType()
{
    if (segments.size() == 2)
    {
        if (segments[0]->getType() == PathSegment::eFloor)
        {
            if (segments[1]->getType() == PathSegment::eFloor)
            {
                type = eWalkable;
            }
            else
            {
                assert(segments[1]->getType() == PathSegment::eWall);
                type = eCliff;
            }
        }
        else
        {
            assert(segments[0]->getType() == PathSegment::eWall);
            if (segments[1]->getType() == PathSegment::eFloor)
            {
                type = eCliff;
            }
            else
            {
                assert(segments[1]->getType() == PathSegment::eWall);
                type = eWall;
            }
        }
    }
    else assert(segments.size() == 0);
}
#include <GL/gl.h>
void PathNode::tempRender()
{
    switch (type)
    {
        case eWall:
        {
            glColor3f(1,0,0);
            break;
        }
        case eCliff:
        {
            glColor3f(0,0,1);
            break;
        }
        case eWalkable:
        {
            glColor3f(0,1,0);
            break;
        }
    }
    glVertex2f(getPosition().x,getPosition().y);
}
