#ifndef SINGLEFIXTUREBODYPORT_H
#define SINGLEFIXTUREBODYPORT_H

#include <Physics/BodyPart.h>
class b2Body;
class b2Fixture;

class SingleFixtureBodyPart : public BodyPart
{
    public:
        SingleFixtureBodyPart();
        virtual ~SingleFixtureBodyPart();
        void setBody(b2Body* _body);
        b2Body* getBody();
        b2Fixture* getFixture();
    protected:
    private:
        b2Body* body;
};

#endif // SINGLEFIXTUREBODYPORT_H
