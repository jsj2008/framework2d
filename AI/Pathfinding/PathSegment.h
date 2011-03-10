#ifndef PATHSEGMENT_H
#define PATHSEGMENT_H

class PathNode;
class Vec2f;

class PathSegment
{
    public:
        enum Type
        {
            eFloor,
            eWall,
            eTypesMax
        };
        PathSegment(PathNode* _nodeA, PathNode* _nodeB);
        PathSegment(const Vec2f& vertexA, const Vec2f& vertexB);
        PathSegment(PathSegment* segmentA, const Vec2f& vertexB);
        PathSegment(PathSegment* segmentA, PathSegment* segmentB);
        virtual ~PathSegment();
        void tempRender();
        PathNode* getNodeA(){return nodeA;}
        PathNode* getNodeB(){return nodeB;}
        void setNodeB(PathNode* _nodeB){nodeB = _nodeB;}
        bool isDirectlyConnected(PathSegment* neighbour);
        void closestPoints(PathSegment* segment, float& t1, float& t2);
        void setNodeTypes();
        Type getType(){return type;}
    protected:
    private:
        Type type;
        void determineType(const Vec2f& vertexA, const Vec2f& vertexB);
        PathNode* nodeA,* nodeB;
};

#endif // PATHSEGMENT_H
