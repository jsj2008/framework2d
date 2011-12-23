#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entities/Entity.h>
#include <string>
template <typename Product>
class AbstractFactoryBase;

class Projectile : public Entity
{
    public:
        Projectile(AbstractFactoryBase<Entity>* _explosion);
        virtual ~Projectile();
        void update();
        void hitWall(); /// Or something. It doesn't damage whatever it hit
        void hitAndDamage(Entity* target);
    protected:
    private:
        bool alive;
        AbstractFactoryBase<Entity>* explosion;
};

#endif // PROJECTILE_H
