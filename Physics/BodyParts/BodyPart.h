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
        virtual const Vec2f& getPosition()=0;
        virtual float getAngle()=0;
        virtual Entity* getEntity()=0;
        void setFixture(b2Fixture* _fixture);
        b2Body* getBody();

        static std::string name()
        {
            return "BodyPart";
        }

        virtual void applyLinearImpulse(const Vec2f& _impulse)=0; /// Center point
        virtual void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)=0;
        virtual Vec2f getLinearVelocity()=0;
        virtual float getDensity()=0;
        virtual float getArea()=0;
        virtual float getAreaBelowLine(float _height)=0;
    protected:
    private:
};

#endif // BODYPART_H
