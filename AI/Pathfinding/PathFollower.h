#ifndef PATHFOLLOWER_H
#define PATHFOLLOWER_H

#include <stack>
#include <Types/Vec2f.h>
#include <AI/Pathfinding/Node.h>
#include <AI/AIManager.h>
class b2Body;
class PathNode;

class PathFollower
{
    public:
        PathFollower();
        virtual ~PathFollower();
        AIManager::Operation update(b2Body* body, Node newTarget);
        Node getCurrentSegment(){return instructions.top().node;}
    protected:
    private:
        std::stack<AIManager::PathInstruction> instructions;
        Node closest;
        Node target;
        void calculateNewPath();
};

#endif // PATHFOLLOWER_H
