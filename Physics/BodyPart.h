#ifndef BODYPART_H
#define BODYPART_H

#include <GameObject.h>
class b2Fixture;
class Entity;
class Vec2f;

class BodyPart : public GameObject<BodyPart>
{
    public:
        BodyPart();
        virtual ~BodyPart();
        static void registerActions();
        const Vec2f& getPosition();
        float getAngle();
        void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        Entity* getEntity();
        void setFixture(b2Fixture* _fixture);
    protected:
    private:
        b2Fixture* fixture;
};

#endif // BODYPART_H
