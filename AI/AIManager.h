#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <stack>
#include <AI/PathGeneration/Pathfinding.h>
#include <AI/Pathfinding/Node.h>
#include <Types/Vec2f.h>
class Paths;
class PathNode;
class b2Body;
class PhysicsManager;

extern class AIManager
{
    public:
        enum Operation
        {
            eStandStill,
            eWalkLeft,
            eWalkRight,
            eJumpLeft,
            eJumpRight,
            eOperationsMax
        };
        struct PathInstruction
        {
            Node node;
            Operation operation;
            Vec2f target;
        };
        virtual ~AIManager();
        void init(PhysicsManager* _physicsManager);
        void addStaticGeometry(Vec2f* vertices, int numVertices){pathfinding->addStaticGeometry(vertices, numVertices);}
        void finalisePathfinding(){paths = pathfinding->finalise();}
        void tempRender(){pathfinding->tempRender();}
        Node findClosestNode(const Vec2f& position);
        Node getPlayerNode(){return playerNode;}
        void setPlayerNode(const Vec2f& _playerPosition);
        void path(Node start, Node end, std::stack<PathInstruction>& instructions);
        AIManager(); /// This is just here as a reminder to call init(), and then migrate it to here
    protected:
    private:
        Paths* paths;
        Pathfinding* pathfinding;
        Node playerNode;
}g_AIManager;

#endif // AIMANAGER_H
