#ifndef PATHGRAPH_H
#define PATHGRAPH_H

#include <vector>
class Paths;
class PathNodeDynamic;
class PathSegment;
class Vec2f;
class PhysicsManager;

class PathGraph
{
    public:
        PathGraph(PhysicsManager* _physicsManager);
        virtual ~PathGraph();
        void tempRender();
        PathSegment* addSegment(const Vec2f& vertexA, const Vec2f& vertexB, PathSegment** trueFirst);
        PathSegment* appendSegment(PathSegment* currentSegement, const Vec2f& vertexB);
        PathSegment* connectSegments(PathSegment* segmentA, PathSegment* segmentB);
        Paths* finalise();
        PathSegment* findClosestPath(const Vec2f& position);
    protected:
    private:
        void deleteNode(PathNodeDynamic* node);
        PathSegment* addSegment(PathSegment* segment);
        PathSegment* separate(PathSegment* segment, float point, PathNodeDynamic* newNode);
        std::vector<PathSegment*> segments;
        std::vector<PathNodeDynamic*> nodes;
        PhysicsManager* physicsManager;
};

#endif // PATHGRAPH_H
