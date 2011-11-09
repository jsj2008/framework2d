#ifndef BODY_H
#define BODY_H

#include <GameObject.h>
class b2Body;
class b2FixtureDef;
class b2Shape;
class Vec2f;

class Body : public GameObject<Body>
{
    public:
        Body(b2Body* _body);
        virtual ~Body();
        const Vec2f& getPosition();
        void applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point);
        void createFixture(const b2FixtureDef* _def);
        void createFixture(const b2Shape* _def, float _density);
        float getAngle();
        static void registerActions();
        b2Body* getBody(){return body;} /// For joint creation only, remeove it later
    protected:
    private:
        b2Body* body;
};

#endif // BODY_H
