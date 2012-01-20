#ifndef ENTITY_H
#define ENTITY_H

#include <GameObject.h>
#include <Events/InstanceEvents/InstanceEventHandler.h>
#include <Events/InstanceEvents/Events/DeathEvent.h>
class Skin;
class BodyPart;
class Vec2f;

class Entity : public GameObject<Entity>
{
    public:
        Entity();
        void baseInit(Skin* _skin);
        virtual ~Entity();
        virtual void render();
        virtual void update()=0;
        virtual void damage(){}
        const Vec2f& getPosition();
        /// FIXME should think of a better way to do this (its for the factories)
        void setRootBody(BodyPart* _body);
        BodyPart* getRootBody();

        static void registerActions(GameObjectType* _type);
        void floatationAction(CollisionObject* _object);

        static std::string name()
        {
            return "Entity";
        }
    protected:
        BodyPart* rootBody;
        Skin* mSkin;
    private:
};

#endif // ENTITY_H
