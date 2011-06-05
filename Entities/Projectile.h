#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entities/Entity.h>
#include <string>

class Projectile : public Entity
{
    public:
        Projectile(const std::string& _explosion, Skin* _skin);
        virtual ~Projectile();
        void update();
        EntityType getType(){return eProjectileEntityType;}
        void hitWall(); /// Or something. It doesn't damage whatever it hit
        void hitAndDamage(Entity* target);
    protected:
    private:
        bool alive;
        std::string explosion;
};

#endif // PROJECTILE_H
