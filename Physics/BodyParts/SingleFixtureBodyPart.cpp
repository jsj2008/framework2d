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

float SingleFixtureBodyPart::getArea()
{
    return fixture->GetShape()->getArea();
}
float SingleFixtureBodyPart::getAreaBelowLine(float _height)
{
    return fixture->GetShape()->getAreaBelowLine(fixture, _height);
}
