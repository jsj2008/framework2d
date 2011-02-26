#ifndef FACTORYDEF_H
#define FACTORYDEF_H

#include <Types/Vec2f.h>

class FactoryDef
{
    public:
        FactoryDef();
        Vec2f position;
        char materialName[32];
        void setMaterial(const char* _materialName);
};

#endif // FACTORYDEF_H
