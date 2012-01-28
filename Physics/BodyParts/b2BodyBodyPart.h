#ifndef B2BODYBODYPART_H
#define B2BODYBODYPART_H

#include <Physics/BodyParts/BodyPart.h>
class b2Body;

class b2BodyBodyPart : public BodyPart
{
    public:
        b2BodyBodyPart(b2Body* _body);
        virtual ~b2BodyBodyPart();
        Entity* getEntity();
        b2Body* getBody();

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
        b2Body* body;
};

#endif // B2BODYBODYPART_H
