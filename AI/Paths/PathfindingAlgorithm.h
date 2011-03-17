#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include <queue>
#include <vector>
#include <stack>
#include <AI/AIManager.h>
class PathNode;
typedef unsigned int NodeReference;

class PathfindingAlgorithm
{
    public:
        PathfindingAlgorithm(std::vector<PathNode*>& _nodes, NodeReference _start, NodeReference _target, unsigned int _set);
        virtual ~PathfindingAlgorithm();
        void path(std::stack<AIManager::PathInstruction>& instructions);
        void add(NodeReference node, float distanceTravelled, NodeReference previous, const AIManager::Operation& instruction);
    protected:
    private:
        std::vector<PathNode*>& nodes;
        NodeReference start;
        NodeReference target;
        unsigned int set;
        class WorkingSetNode
        {
            public:
                WorkingSetNode(NodeReference _node, float _distanceTravelled){node = _node; distanceTravelled = _distanceTravelled;}
                bool operator <(const WorkingSetNode& rhs)
                {
                    return distanceTravelled > rhs.distanceTravelled; /// Priority queue puts the highest at the top, and I want the lowest
                }
                NodeReference getNode()const{return node;}
                float getDistanceTravelled()const{return distanceTravelled;}
            private:
                NodeReference node;
                float distanceTravelled;
        };
        std::priority_queue<WorkingSetNode,std::vector<WorkingSetNode>> workingSet;
        struct DoublesValue
        {
            DoublesValue(){isChecked = false;}
            bool isChecked;
            float distanceTravelled;
            NodeReference previous;
            AIManager::Operation operation;
        };
        DoublesValue* doublesValues;
};

#endif // PATHFINDINGALGORITHM_H
