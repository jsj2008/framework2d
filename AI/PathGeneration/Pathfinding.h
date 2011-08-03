#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <AI/PathGeneration/PathGraph.h>
class Vec2f;

class Pathfinding
{
    public:
        Pathfinding(PhysicsManager* _physicsManager);
        virtual ~Pathfinding();
        void addStaticGeometry(Vec2f* vertices, int numVertices);
        Paths* finalise();
        void tempRender(){pathGraph.tempRender();}
        PathSegment* findClosestPath(const Vec2f& position){return pathGraph.findClosestPath(position);}
    protected:
    private:
        PathGraph pathGraph;
};

#endif // PATHFINDING_H
