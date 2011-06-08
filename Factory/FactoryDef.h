#ifndef FACTORYDEF_H
#define FACTORYDEF_H

#include <Types/Vec2f.h>

enum StandardFactories : unsigned short
{
    eAIEntityFactory,
    eStandardFactoriesMax
};
class FactoryDef
{
    public:
        StandardFactories type;
        Vec2f position;
        float rotation;
        char materialName[32];
        void setMaterial(const char* _materialName);
};

#endif // FACTORYDEF_H
