#ifndef ENTITY_H
#define ENTITY_H

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
    protected:
        b2Body* mBody;
        Skin* mSkin;
    private:
};

#endif // ENTITY_H
