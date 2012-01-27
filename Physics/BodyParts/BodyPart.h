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
        Entity* getEntity();
        void setFixture(b2Fixture* _fixture);
        b2Body* getBody();

        static std::string name()
        {
            return "BodyPart";
        }

        virtual void applyLinearImpulse(const Vec2f& _impulse); /// Center point
        virtual void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        Vec2f getLinearVelocity();
        virtual float getDensity();
        virtual float getArea();
        virtual float getAreaBelowLine(float _height);
    protected:
        b2Fixture* fixture;
    private:
};

#endif // BODYPART_H
