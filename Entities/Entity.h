#ifndef ENTITY_H
#define ENTITY_H

class Skin;
class b2Body;
enum EntityType
{
    eCrateEntityType,
    eStaticGeometryEntityType,
    eAIEntityType,
    eBubbleEntityType,
    ePhysicsParticleEntityType,
    eProjectileEntityType,
    eExplosionEntityType,
    eEntityTypeMax,
};
class Entity
{
    public:
        Entity();
        virtual void render();
        virtual void update()=0;
        virtual EntityType getType()=0;
        virtual void damage(){}
        b2Body* mBody;
        Skin* mSkin;
    protected:
        friend class PhysicsManager; // Just want to assert nobody else can delete these
        virtual ~Entity();
    private:
};

#endif // ENTITY_H
