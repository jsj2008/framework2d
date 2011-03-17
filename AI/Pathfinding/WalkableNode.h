#ifndef WALKABLENODE_H
#define WALKABLENODE_H

#include <AI/Pathfinding/PathNode.h>


class WalkableNode : public PathNode
{
    public:
        WalkableNode(const Vec2f& _position);
        virtual ~WalkableNode();
        void path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me);
        void setNeighbours(NodeReference _left, NodeReference _right);
    protected:
    private:
        NodeReference left;
        NodeReference right;
};

#endif // WALKABLENODE_H
