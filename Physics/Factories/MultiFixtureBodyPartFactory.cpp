#include "MultiFixtureBodyPartFactory.h"

MultiFixtureBodyPartFactory::MultiFixtureBodyPartFactory()
{
    //ctor
}

MultiFixtureBodyPartFactory::~MultiFixtureBodyPartFactory()
{
    //dtor
}
void MultiFixtureBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    bodyFactory = _loader->getFactory<BodyPart>("body", "b2BodyBodyPartFactory");

    fixtureFactories = _loader->getFactoryArray<BodyPart>("fixtures", {"b2FixtureBodyPartFactory"});
}

BodyPart* MultiFixtureBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    BodyPart* body = bodyFactory->use(_parameters, nullptr);
    _parameters->add<BodyPart*>("body", body);
    for (unsigned int i = 0; i != fixtureFactories.size(); i++)
    {
        fixtureFactories[i]->use(_parameters, body);
    }
    return body;
}
