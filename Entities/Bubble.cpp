#include "Bubble.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

Bubble::Bubble()
{
    //ctor
}

Bubble::~Bubble()
{
    //dtor
}

void Bubble::update()
{
    b2Fixture* myFixture = mBody->GetFixtureList();
    Vec2f myPosition = mBody->GetWorldCenter();
    for (b2ContactEdge* ce = mBody->GetContactList(); ce != nullptr; ce = ce->next)
    {
        b2Contact* c = ce->contact;
        b2Fixture* fixture = c->GetFixtureA();
        if (fixture == myFixture)
        {
            fixture = c->GetFixtureB();
        }
        b2Body* body = fixture->GetBody();
        Vec2f point;
        point = body->GetWorldCenter();
        affectBody(body,myPosition-point);
    }
}
