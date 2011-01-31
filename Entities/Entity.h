#ifndef ENTITY_H
#define ENTITY_H

class Skin;
class b2Body;
enum EntityType
{
    ePlayerEntityType,
    eCrateEntityType,
    eStaticGeometryEntityType,
    eAIEntityType,
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
    protected:
    private:
        friend class EntityFactory;
        Skin* mSkin;
        b2Body* mBody;
};

#endif // ENTITY_H
