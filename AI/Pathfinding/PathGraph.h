#ifndef PATHGRAPH_H
#define PATHGRAPH_H

#include <vector>
class PathNode;
class PathSegment;
class Vec2f;

class PathGraph
{
    public:
        PathGraph();
        virtual ~PathGraph();
        void tempRender();
        PathSegment* addSegment(const Vec2f& vertexA, const Vec2f& vertexB, PathSegment** trueFirst);
        PathSegment* appendSegment(PathSegment* currentSegement, const Vec2f& vertexB);
        PathSegment* connectSegments(PathSegment* segmentA, PathSegment* segmentB);
        void finalise();
    protected:
    private:
        void deleteNode(PathNode* node);
        PathSegment* addSegment(PathSegment* segment);
        PathSegment* separate(PathSegment* segment, float point, PathNode* newNode);
        std::vector<PathSegment*> segments;
        std::vector<PathNode*> nodes;

};

#endif // PATHGRAPH_H
