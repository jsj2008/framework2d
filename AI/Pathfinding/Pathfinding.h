#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <AI/Pathfinding/PathGraph.h>
class Vec2f;

class Pathfinding
{
    public:
        Pathfinding();
        virtual ~Pathfinding();
        void addStaticGeometry(Vec2f* vertices, int numVertices);
        void finalise();
        void tempRender(){pathGraph.tempRender();}
        PathSegment* findClosestPath(const Vec2f& position){return pathGraph.findClosestPath(position);}
    protected:
    private:
        PathGraph pathGraph;
};

#endif // PATHFINDING_H
