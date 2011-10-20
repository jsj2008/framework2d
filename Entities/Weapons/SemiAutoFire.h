#ifndef SEMIAUTOFIRE_H
#define SEMIAUTOFIRE_H

#include <Entities/Weapons/FiringMechanism.h>
#include <AbstractFactory/AutoSelfFactory.h>


class SemiAutoFire : public FiringMechanism
{
    public:
        struct ImmutableData
        {
            void init(FactoryLoader* _loader, AbstractFactories* _factories);
            unsigned short reloadFrames;
        };
        SemiAutoFire(const SemiAutoFire::ImmutableData& _data, FactoryParameters* _parameters);
        virtual ~SemiAutoFire();
        static std::string factoryName()
        {
            return "SemiAutoFireFactory";
        }
        bool fireEnd(const Vec2f& source, const Vec2f& position);
    protected:
    private:
        const SemiAutoFire::ImmutableData& immutableData;
};

#endif // SEMIAUTOFIRE_H
