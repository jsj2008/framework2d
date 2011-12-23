#ifdef BODY_H
#define BODY_H

#include <GameObject.h>
class b2Body;
class b2FixtureDef;
class b2Shape;
class Vec2f;
class BodyPart;

class Body : public GameObject<Body>
{
    public:
        Body(BodyPart* _root);
        virtual ~Body();
        const Vec2f& getPosition();
        void createFixture(const b2FixtureDef* _def);
        void createFixture(const b2Shape* _def, float _density);
        float getAngle();
        static void registerActions();
        b2Body* getBody(){return body;} /// For joint creation only, remeove it later
        void setRoot(BodyPart* _root);
    protected:
    private:
        b2Body* body;
        BodyPart* root;
};

#endif // BODY_H
