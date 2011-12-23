#ifndef PATHNODE_H
#define PATHNODE_H

#include <Types/Vec2f.h>
class PathfindingAlgorithm;
typedef unsigned int NodeReference;

class PathNode
{
    public:
        PathNode(const Vec2f& _position);
        virtual ~PathNode();
        const Vec2f& getPosition(){return position;}
        virtual void path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me)=0;
    protected:
        Vec2f position;
    private:
};

#endif // PATHNODE_H
