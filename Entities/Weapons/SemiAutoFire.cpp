#include "SemiAutoFire.h"

SemiAutoFire::SemiAutoFire(const SemiAutoFire::ImmutableData& _data, FactoryParameters* _parameters)
:immutableData(_data)
{
    //ctor
    AutoSelfFactory<FiringMechanism, SemiAutoFire>::staticInstantiate();
}

SemiAutoFire::~SemiAutoFire()
{
    //dtor
}

void SemiAutoFire::ImmutableData::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    reloadFrames = _loader->get<int>("reloadFrames", 20);
}

bool SemiAutoFire::fireEnd(const Vec2f& source, const Vec2f& position)
{
    return true;
}
