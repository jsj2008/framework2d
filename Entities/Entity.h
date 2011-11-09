#ifndef ENTITY_H
#define ENTITY_H

#include <GameObject.h>
#include <Events/InstanceEvents/InstanceEventHandler.h>
#include <Events/InstanceEvents/Events/DeathEvent.h>
class Skin;
class Body;
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

class Entity : public GameObject<Entity>
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
        void setBody(Body* _body);
        Body* getBody(){return body;}

        static void registerActions();
    protected:
        Body* body;
        Skin* mSkin;
    private:
};

#endif // ENTITY_H
