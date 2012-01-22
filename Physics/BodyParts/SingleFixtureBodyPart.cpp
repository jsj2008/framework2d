#include "SingleFixtureBodyPart.h"
#include <Box2D/Box2D.h>

SingleFixtureBodyPart::SingleFixtureBodyPart()
{
    //ctor
    body = nullptr;
}

SingleFixtureBodyPart::~SingleFixtureBodyPart()
{
    //dtor
    body->GetWorld()->DestroyBody(body);
}

void SingleFixtureBodyPart::setBody(b2Body* _body)
{
    body = _body;
    setFixture(_body->GetFixtureList());
}
