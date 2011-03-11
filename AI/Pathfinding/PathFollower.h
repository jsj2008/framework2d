#ifndef PATHFOLLOWER_H
#define PATHFOLLOWER_H

#include <Types/Vec2f.h>
#include <queue>
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
        Operation update(const Vec2f& position);
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
        void calculateNewPath();
};

#endif // PATHFOLLOWER_H
