#ifndef FACTORYDEF_H
#define FACTORYDEF_H

#include <Types/Vec2f.h>

enum StandardFactories : unsigned short
{
    ePlayerFactory,
    eConvexPolygonFactory,
    eCrateFactory,
    eBubbleFactory,
    eParticleFactory,
    eAIEntityFactory,
    eProjectileFactory,
    eStandardFactoriesMax
};
class FactoryDef
{
    public:
        StandardFactories type;
        float xPosition, yPosition;
        float rotation;
        void setPosition(const Vec2f position);
        const Vec2f getPosition();
        char materialName[32];
        void setMaterial(const char* _materialName);
};

#endif // FACTORYDEF_H
