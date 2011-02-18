#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class PlatformDef;
#include <vector>
#include <Entities/StaticGeometry.h>

extern class LevelManager
{
    public:
        LevelManager();
        virtual ~LevelManager();
        void addPlatform(PlatformDef* def);
        void loadLevel(const char* name);
        void saveLevel(const char* name);
    protected:
    private:
        std::vector<PlatformDef> defs;
}g_LevelManager;

#endif // LEVELMANAGER_H
