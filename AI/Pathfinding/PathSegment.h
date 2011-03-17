#ifndef PATHSEGMENT_H
#define PATHSEGMENT_H

class PathNodeDynamic;
class Vec2f;

class PathSegment
{
    public:
        enum Type
        {
            eFloor,
            eWall,
            eTwoWayJump,
            eTypesMax
        };
        PathSegment(PathNodeDynamic* _nodeA, PathNodeDynamic* _nodeB);
        PathSegment(PathNodeDynamic* _nodeA, PathNodeDynamic* _nodeB, Type jumpType);
        virtual ~PathSegment();
        void tempRender();
        PathNodeDynamic* getNodeA(){return nodeA;}
        PathNodeDynamic* getNodeB(){return nodeB;}
        void setNodeB(PathNodeDynamic* _nodeB){nodeB = _nodeB;}
        bool isDirectlyConnected(PathSegment* neighbour);
        float closestPoint(const Vec2f& point);
        void closestPoints(const Vec2f& p3, const Vec2f& p4, float& t1, float& t2);
        void setNodeTypes();
        Type getType(){return type;}
        PathNodeDynamic* getOther(PathNodeDynamic* first);
    protected:
    private:
        Type type;
        void determineType(const Vec2f& vertexA, const Vec2f& vertexB);
        PathNodeDynamic* nodeA,* nodeB;
};

#endif // PATHSEGMENT_H
