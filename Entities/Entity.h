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
    eEntityTypeMax,
};
class Entity
{
    public:
        Entity();
        virtual void render();
        virtual void update()=0;
        virtual EntityType getType()=0;
        b2Body* mBody;
        Skin* mSkin;
        virtual void damage(){}
    protected:
        friend class PhysicsManager; // Just want to assert nobody else can delete these
        virtual ~Entity();
    private:
};

#endif // ENTITY_H
