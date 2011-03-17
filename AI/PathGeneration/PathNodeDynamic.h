#ifndef PATHNODEDYNAMIC_H
#define PATHNODEDYNAMIC_H

#include <vector>
#include <unordered_map>
#include <AI/Pathfinding/PathNode.h>
#include <Types/Vec2f.h>
class PathSegment;
class PathNode;

class PathNodeDynamic : public PathNode
{
    public:
        enum Type
        {
            eCorner, /// Can walk up to it and then stop
            eCliff, /// Can walk up to it and then stop or fall off
            eWalkable, /// Can walk past it
            eWall, /// Not a walkable surface (too upside down)
            eJumpable,
            eTypesMax
        };
        PathNodeDynamic(const Vec2f& _position);
        virtual ~PathNodeDynamic();
        void setPosition(const Vec2f& _position){position = _position;}
        void addSegment(PathSegment* segment){segments.push_back(segment);}
        bool removeSegment(PathSegment* segment); /// Returns false if this node should be deleted
        bool isConnected(PathSegment* segment);
        void setType(Type _type = eTypesMax);
        Type getType(){return type;}
        void tempRender();
        NodeReference createNode();
        void resolveLinks(std::unordered_map<PathNodeDynamic*,NodeReference>& createdNodes);
        NodeReference createNodes(std::unordered_map<PathNodeDynamic*,NodeReference>& createdNodes, std::vector<PathNode*>* nodeList);
        void path(PathfindingAlgorithm* algorithm, float distanceTravelled, NodeReference me){throw -1;}
    protected:
    private:
        std::vector<PathSegment*> segments;
        Type type;
};

#endif // PATHNODEDYNAMIC_H
