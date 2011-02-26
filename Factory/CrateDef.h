#ifndef CRATEDEF_H
#define CRATEDEF_H

#include <Factory/FactoryDef.h>


class CrateDef : public FactoryDef
{
    public:
        CrateDef();
        CrateDef(float _width, float _height, const char* _materialName);
        float width, height;
};

#endif // CRATEDEF_H
