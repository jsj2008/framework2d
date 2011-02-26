#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <unordered_map>
#include <Factory/ConvexGeometryDef.h>
#include <Entities/StaticGeometry.h>
#include <Factory/CrateDef.h>

class Level
{
    public:
        Level();
        Level(const char* _name);
        virtual ~Level();
        void addPlatform(ConvexGeometryDef* def);
        void addCrate(CrateDef* def);
        void removeBody(b2Body* body);
    protected:
    private:
        const char* name;
        void loadLevel();
        void saveLevel();
        std::vector<ConvexGeometryDef> geometryDefs;
        std::vector<CrateDef> crateDefs;
        std::unordered_map<b2Body*, unsigned int> bodyToGeometryDefTable; /// Maps a body to a defs index
        std::unordered_map<b2Body*, unsigned int> bodyToCrateDefTable;
};

#endif // LEVEL_H
