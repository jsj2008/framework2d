#ifndef WATERVOLUME_H
#define WATERVOLUME_H

#include <Entities/Entity.h>
class WaterPhysicsSystem;

class WaterVolume : public Entity
{
    public:
        WaterVolume(WaterPhysicsSystem* _system);
        virtual ~WaterVolume();
        void update();
        void floatationAction(CollisionObject* _object);
    protected:
    private:
        WaterPhysicsSystem* system;
};

#endif // WATERVOLUME_H
