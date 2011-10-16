#ifndef ENTITY_H
#define ENTITY_H

#include <Events/InstanceEvents/InstanceEventHandler.h>
#include <Events/InstanceEvents/Events/DeathEvent.h>
class Skin;
class b2Body;
class Vec2f;
enum EntityType
{
    eCrateEntityType,
    eStaticGeometryEntityType,
    eAIEntityType,
    eBubbleEntityType,
    ePhysicsParticleEntityType,
    eProjectileEntityType,
    eExplosionEntityType,
    eTileMapEntityType,
    eTileEntityType,
    eEntityTypeMax,
};
class Entity
{
    public:
        Entity(Skin* _skin);
        virtual ~Entity();
        virtual void render();
        virtual void update()=0;
        virtual EntityType getType()=0;
        virtual void damage(){}
        const Vec2f& getPosition();
        /// FIXME should think of a better way to do this (its for the factories)
        void setBody(b2Body* _body);
        void registerDeathListener(InstanceEventListener<EntityDeathEvent>* _listener);
        b2Body* getBody(){return mBody;}
    protected:
        b2Body* mBody;
        Skin* mSkin;
    private:
        InstanceEventHandler<EntityDeathEvent> deathHandler;
};

#endif // ENTITY_H
