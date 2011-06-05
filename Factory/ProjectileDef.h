#ifndef PROJECTILEDEF_H
#define PROJECTILEDEF_H

#include <Factory/FactoryDef.h>


class ProjectileDef : public FactoryDef
{
    public:
        ProjectileDef();
        ProjectileDef(const char* _materialName, float _radius, const Vec2f& _position, const Vec2f& _velocity);
        float radius;
        Vec2f velocity;

        short damage;
        /// Explosion parameters
        bool explosion;
        float explosionRadius;
        float explosionTime;
        /// Expiry parameters
        float expiryTime;
        float maximumImpact;
        float proximity;
    protected:
    private:
};

#endif // PROJECTILEDEF_H
