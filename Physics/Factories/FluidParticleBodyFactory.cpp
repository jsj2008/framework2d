#include "FluidParticleBodyFactory.h"
#include <Physics/PhysicsManager.h>

FluidParticleBodyFactory::FluidParticleBodyFactory()
{
    //ctor
}

FluidParticleBodyFactory::~FluidParticleBodyFactory()
{
    //dtor
}

void FluidParticleBodyFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    bodyFactory = _loader->getFactory<BodyPart>("body", "SingleFixtureBodyPartFactory");
    sensorFactory = _loader->getFactory<BodyPart>("sensor", "SingleFixtureBodyPartFactory");
}

BodyPart* FluidParticleBodyFactory::useFactory(FactoryParameters* _parameters)
{
    BodyPart* body = bodyFactory->use(_parameters, nullptr);
    BodyPart* sensor = sensorFactory->use(_parameters, body);
    return body;
}
