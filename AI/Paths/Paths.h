#ifndef PATHS_H
#define PATHS_H

#include <vector>
#include <AI/Paths/Node.h>
#include <AI/AIManager.h>
class PathNode;
class Vec2f;

class Paths
{
    public:
        Paths(std::vector<std::vector<PathNode*>*>& _nodes);
        virtual ~Paths();
        Node findClosestNode(const Vec2f& position);
        void path(Node start, Node end, std::stack<AIManager::PathInstruction>& instructions);
    protected:
    private:
        std::vector<std::vector<PathNode*>*> nodes;
};

#endif // PATHS_H
