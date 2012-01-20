#ifndef BODYPART_H
#define BODYPART_H

#include <GameObject.h>
class b2Fixture;
class b2Body;
class Entity;
class Vec2f;

class BodyPart : public GameObject<BodyPart>
{
    public:
        BodyPart();
        virtual ~BodyPart();
        static void registerActions(GameObjectType* _type);
        const Vec2f& getPosition();
        float getAngle();
        void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        Entity* getEntity();
        void setFixture(b2Fixture* _fixture);
        b2Body* getBody();

        static std::string name()
        {
            return "BodyPart";
        }
    protected:
    private:
        b2Fixture* fixture;
};

#endif // BODYPART_H
