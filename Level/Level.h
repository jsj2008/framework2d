#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <Factory/ConvexGeometryDef.h>
#include <Entities/StaticGeometry.h>
#include <Factory/CrateDef.h>
class b2Joint;
class b2JointDef;

class Level
{
    public:
        Level();
        Level(const char* _name);
        virtual ~Level();
        void addPlatform(ConvexGeometryDef* def);
        void addCrate(CrateDef* def);
        void addJoint(b2JointDef* def);
        void tempRender();
        void removeBody(b2Body* body);
        void removeJoint(b2Joint* joint);
    protected:
    private:
        const char* name;
        void loadLevel();
        void saveLevel();
        std::unordered_map<b2Body*, ConvexGeometryDef> bodyToGeometryDefTable; /// Maps a body to a defs index
        std::unordered_map<b2Body*, CrateDef> bodyToCrateDefTable;
        std::unordered_map<b2Joint*, b2JointDef*> jointToDefTable;
};

#endif // LEVEL_H
