#include "Bubble.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

Bubble::Bubble(Skin* _skin)
:Entity(_skin)
{
    //ctor
}

Bubble::~Bubble()
{
    //dtor
}

void Bubble::update()
{
    /*b2Fixture* myFixture = body->GetFixtureList();
    Vec2f myPosition = body->GetWorldCenter();
    for (b2ContactEdge* ce = body->GetContactList(); ce != nullptr; ce = ce->next)
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
    }*/
}
