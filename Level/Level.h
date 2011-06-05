#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <string>
#include <Factory/FactoryList.h>
class b2Joint;
class b2JointDef;
class TextureContext;
class ParallaxLayer;
class FactoryParameters;

class Level
{
    public:
        Level(const char* _name);
        virtual ~Level();
        void addBody(const std::string& factory, FactoryParameters* parameters);
        void addBody(StandardFactoryDef def);
        void addJoint(b2JointDef* def);
        void tempRender();
        void renderBackLayers();
        void removeBody(b2Body* body);
        void removeJoint(b2Joint* joint);
    protected:
    private:
        const char* name;
        void loadLevel();
        void saveLevel();
        std::unordered_map<b2Body*, StandardFactoryDef> bodyToDefTable; /// Maps a body to a defs index
        std::unordered_map<b2Joint*, b2JointDef*> jointToDefTable;
        Vec2f backgroundScale;
        Vec2f backgroundTransform;
        std::vector<ParallaxLayer*> parallaxLayers;
};

#endif // LEVEL_H
