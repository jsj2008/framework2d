#include "FluidParticle.h"
#include <AbstractFactory/AutoSelfFactory.h>
#include <Graphics/Skins/Skin.h>
#include <Physics/BodyPart.h>

FluidParticle::FluidParticle(const ImmutableData& _data, FactoryParameters* _parameters)
:data(_data)
{
    //ctor
    rootBody = data.bodyFactory->use(_parameters, this);
    baseInit(_data.skinFactory->use(_parameters, this));
    AutoSelfFactory<Entity, FluidParticle>::staticInstantiate();
}

void FluidParticle::ImmutableData::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    skinFactory = _loader->getFactory<Skin>("skin", "StaticSkinFactory");
    bodyFactory = _loader->getFactory<BodyPart>("body", "FluidParticleBodyFactory");
}

FluidParticle::~FluidParticle()
{
    //dtor
}

void FluidParticle::update()
{
}
