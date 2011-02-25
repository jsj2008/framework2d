#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class ConvexGeometryDef;
#include <vector>
#include <unordered_map>
#include <Entities/StaticGeometry.h>

extern class LevelManager
{
    public:
        LevelManager();
        virtual ~LevelManager();
        void addPlatform(ConvexGeometryDef* def);
        void removeBody(b2Body* body);
        void loadLevel(const char* name);
        void saveLevel(const char* name);
    protected:
    private:
        void constructBodies();
        std::vector<ConvexGeometryDef> defs;
        std::unordered_map<b2Body*, unsigned int> bodyToDefTable; /// Maps a body to a defs index
}g_LevelManager;

#endif // LEVELMANAGER_H
