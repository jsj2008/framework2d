#ifndef JUMPABLENODE_H
#define JUMPABLENODE_H

#include <AI/Pathfinding/PathNode.h>
#include <AI/AIManager.h>

class JumpableNode : public PathNode
{
    public:
        JumpableNode(const Vec2f& _positiont);
        virtual ~JumpableNode();
        void path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me);
        void setNeighbours(NodeReference _target, NodeReference _previous, AIManager::Operation _jumpDirection);
    protected:
    private:
        NodeReference target;
        NodeReference previous;
        AIManager::Operation jumpDirection;
        AIManager::Operation walkDirection;
};

#endif // JUMPABLENODE_H
