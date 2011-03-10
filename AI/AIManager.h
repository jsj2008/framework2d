#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <AI/Pathfinding/Pathfinding.h>

extern class AIManager
{
    public:
        AIManager();
        virtual ~AIManager();
        void addStaticGeometry(Vec2f* vertices, int numVertices){pathfinding.addStaticGeometry(vertices, numVertices);}
        void finalisePathfinding(){pathfinding.finalise();}
        void tempRender(){pathfinding.tempRender();}
    protected:
    private:
        Pathfinding pathfinding;
}g_AIManager;

#endif // AIMANAGER_H
