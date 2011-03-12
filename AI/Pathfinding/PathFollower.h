#ifndef PATHFOLLOWER_H
#define PATHFOLLOWER_H

#include <Types/Vec2f.h>
#include <queue>
class b2Body;
class PathSegment;

class PathFollower
{
    public:
        enum Operation
        {
            eWalkLeft,
            eWalkRight,
            eOperationsMax
        };
        PathFollower();
        virtual ~PathFollower();
        Operation update(b2Body* body, PathSegment* newTarget);
        PathSegment* getCurrentSegment(){return instructions.back().segment;}
    protected:
    private:
        struct PathInstruction
        {
            PathSegment* segment;
            Operation operation;
            Vec2f target;
        };
        bool loop;
        std::queue<PathInstruction> instructions;
        PathSegment* closest;
        PathSegment* target;
        void calculateNewPath();
};

#endif // PATHFOLLOWER_H
