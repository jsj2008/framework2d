#ifndef SINGLEFIXTUREBODYPORT_H
#define SINGLEFIXTUREBODYPORT_H

#include <Physics/BodyParts/BodyPart.h>
class b2Fixture;

class b2FixtureBodyPart : public BodyPart
{
    public:
        b2FixtureBodyPart(b2Fixture* _fixture);
        virtual ~b2FixtureBodyPart();
        b2Body* getBody();
        b2Fixture* getFixture();
        Entity* getEntity();

        const Vec2f& getPosition();
        float getAngle();
        void applyLinearImpulse(const Vec2f& _impulse); /// Center point
        void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        Vec2f getLinearVelocity();
        float getDensity();
        float getArea();
        float getAreaBelowLine(float _height);
    protected:
    private:
        b2Fixture* fixture;
};

#endif // SINGLEFIXTUREBODYPORT_H
