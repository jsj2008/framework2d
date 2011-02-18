#ifndef ENTITY_H
#define ENTITY_H

class Skin;
class b2Body;
enum EntityType
{
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
        b2Body* mBody;
    protected:
        friend class EntityFactory;
        Skin* mSkin;
    private:
};

#endif // ENTITY_H
