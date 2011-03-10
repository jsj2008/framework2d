#ifndef PATHNODE_H
#define PATHNODE_H

#include <vector>
#include <Types/Vec2f.h>
class PathSegment;

class PathNode
{
    public:
        enum Type
        {
            eCorner, /// Can walk up to it and then stop
            eCliff, /// Can walk up to it and then stop or fall off
            eWalkable, /// Can walk past it
            eWall, /// Not a walkable surface (too upside down)
            eTypesMax
        };
        PathNode(const Vec2f& _position);
        virtual ~PathNode();
        const Vec2f& getPosition(){return position;}
        void setPosition(const Vec2f& _position){position = _position;}
        /*void setSegmentA(PathSegment* segment);
        void setSegmentB(PathSegment* segment);
        PathSegment* getSegmentA(){return segmentA;}
        PathSegment* getSegmentB(){return segmentB;}*/
        void addSegment(PathSegment* segment){segments.push_back(segment);}
        bool removeSegment(PathSegment* segment); /// Returns false if this node should be deleted
        bool isConnected(PathSegment* segment);
        void setType();
        void tempRender();
    protected:
    private:
        std::vector<PathSegment*> segments;
        Vec2f position;
        Type type;
};

#endif // PATHNODE_H
