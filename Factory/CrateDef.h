#ifndef CRATEDEF_H
#define CRATEDEF_H

#include <Factory/FactoryDef.h>


class CrateDef : public FactoryDef
{
    public:
        void set(const Vec2f dimensions, float _density, const char* _materialName);
        float width, height;
        float density;
};

class PlayerDef : public FactoryDef /// FIXME
{
    public:
        void set(float _width, float _height, const char* _materialName);
        float width, height;
};

#endif // CRATEDEF_H
