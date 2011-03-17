#include "PathNodeDynamic.h"
#include <AI/Pathfinding/PathSegment.h>

PathNodeDynamic::PathNodeDynamic(const Vec2f& _position)
:PathNode(_position)
{
    type = eTypesMax;
}

PathNodeDynamic::~PathNodeDynamic()
{
    //dtor
}

#include <cassert>
bool PathNodeDynamic::removeSegment(PathSegment* segment)
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
bool PathNodeDynamic::isConnected(PathSegment* segment)
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
void PathNodeDynamic::setType(Type _type)
{
    if (_type == eTypesMax)
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
    else
    {
        assert(_type == eJumpable);
        type = eJumpable;
    }
}
#include <AI/Paths/DeadEndNode.h>
#include <AI/Paths/JumpableNode.h>
#include <AI/Paths/WalkableNode.h>
NodeReference PathNodeDynamic::createNodes(std::unordered_map<PathNodeDynamic*,NodeReference>& createdNodes, std::vector<PathNode*>* nodeList)
{
    auto me = createdNodes.find(this);
    if (me == createdNodes.end())
    {
        switch (type)
        {
            case eWall:
            {
                return NULL;
            }
            case eCliff:
            {
                DeadEndNode* ret = new DeadEndNode(position);
                nodeList->push_back(ret);
                createdNodes[this] = nodeList->size()-1;
                assert(segments.size() == 2);
                NodeReference previous;
                if (segments[0]->getType() == PathSegment::eWall)
                {
                    previous = segments[1]->getOther(this)->createNodes(createdNodes, nodeList);
                    assert(segments[1]->getType() == PathSegment::eFloor);
                }
                else
                {
                    assert(segments[1]->getType() == PathSegment::eWall);
                    assert(segments[0]->getType() == PathSegment::eFloor);
                    previous = segments[0]->getOther(this)->createNodes(createdNodes, nodeList);
                }
                AIManager::Operation operation;
                if ((*nodeList)[previous]->getPosition().x > position.x)
                {
                    operation = AIManager::eWalkRight;
                }
                else
                {
                    operation = AIManager::eWalkLeft;
                }
                ret->setNeighbour(previous,operation);
                return nodeList->size()-1;
            }
            case eWalkable:
            {
                WalkableNode* ret = new WalkableNode(position);
                nodeList->push_back(ret);
                createdNodes[this] = nodeList->size()-1;
                assert(segments.size() == 2);
                NodeReference left = segments[0]->getOther(this)->createNodes(createdNodes, nodeList);
                NodeReference right = segments[1]->getOther(this)->createNodes(createdNodes, nodeList);
                if ((*nodeList)[left]->getPosition().x > (*nodeList)[right]->getPosition().y)
                {
                    NodeReference notLeft = left;
                    left = right;
                    right = notLeft;
                }
                ret->setNeighbours(left,right);
                return nodeList->size()-1;
            }
            case eJumpable:
            {
                JumpableNode* ret = new JumpableNode(position);
                nodeList->push_back(ret);
                createdNodes[this] = nodeList->size()-1;
                assert(segments.size() == 3);
                NodeReference target, previous;
                for (unsigned int i = 0; i < 3; i++)
                {
                    if (segments[i]->getType() == PathSegment::eTwoWayJump)
                    {
                        PathNodeDynamic* other = segments[i]->getOther(this);
                        target = other->createNodes(createdNodes, nodeList);
                    }
                    else if (segments[i]->getType() == PathSegment::eFloor)
                    {
                        PathNodeDynamic* other = segments[i]->getOther(this);
                        previous = other->createNodes(createdNodes, nodeList);
                    }
                }
                AIManager::Operation jumpDirection;
                if ((*nodeList)[target]->getPosition().x > position.x)
                {
                    jumpDirection = AIManager::eJumpRight;
                }
                else jumpDirection = AIManager::eJumpLeft;
                ret->setNeighbours(target,previous,jumpDirection);
                return nodeList->size()-1;
            }
            default:
            {
                throw -1;
            }
        }
    }
    else return me->second;
}

#include <GL/gl.h>
void PathNodeDynamic::tempRender()
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
        case eJumpable:
        {
            glColor3f(1,1,1);
            break;
        }
    }
    glVertex2f(getPosition().x,getPosition().y);
}






























