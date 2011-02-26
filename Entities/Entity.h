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
        virtual ~Entity();
        virtual void render();
        virtual void update()=0;
        virtual EntityType getType()=0;
        b2Body* mBody;
        Skin* mSkin;
    protected:
        friend class EntityFactory;
    private:
};

#endif // ENTITY_H
