#ifndef PHYSICSPARTICLE_H
#define PHYSICSPARTICLE_H

#include <Entities/Entity.h>


class PhysicsParticle : public Entity
{
    public:
        PhysicsParticle(int _timer);
        virtual ~PhysicsParticle();
        void update();
    protected:
    private:
        int timer;
};

#endif // PHYSICSPARTICLE_H
