#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <Entities/Entity.h>
#include <initializer_list>

class Explosion : public Entity
{
    public:
        Explosion(float _radius, float _damage, float _force, unsigned short _frames, Skin* _skin);
        virtual ~Explosion();
        void update();
        EntityType getType(){return eExplosionEntityType;};
    protected:
    private:
        float radius;
        float damage;
        float force;
        unsigned short expiryFrame;
};

#endif // EXPLOSION_H
