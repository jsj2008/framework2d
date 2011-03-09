#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entities/Entity.h>


class Projectile : public Entity
{
    public:
        Projectile();
        virtual ~Projectile();
        void update();
        EntityType getType(){return eProjectileEntityType;}
        void hitWall(); /// Or something. It doesn't damage whatever it hit
        void hitAndDamage(Entity* target);
    protected:
    private:
        bool alive;
};

#endif // PROJECTILE_H
