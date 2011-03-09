#ifndef PROJECTILEDEF_H
#define PROJECTILEDEF_H

#include <Factory/FactoryDef.h>


class ProjectileDef : public FactoryDef
{
    public:
        void set(const char* _materialName, float _radius, const Vec2f position, const Vec2f velocity);
        void setVelocity(const Vec2f velocity);
        const Vec2f getVelocity();
        float radius;
        float xVelocity, yVelocity;
    protected:
    private:
};

#endif // PROJECTILEDEF_H
