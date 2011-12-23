#ifndef WATERPARTICLE_H
#define WATERPARTICLE_H

#include <Entities/Entity.h>
#include <AbstractFactory/AbstractFactory.h>
class FactoryParameters;
class AbstractFactories;
class FactoryLoader;

class FluidParticle : public Entity
{
    public:
        struct ImmutableData
        {
            void init(FactoryLoader* _loader, AbstractFactories* _factories);
            AbstractFactoryBase<BodyPart>* bodyFactory;
            AbstractFactoryBase<Skin>* skinFactory;
        };
        FluidParticle(const ImmutableData& _data, FactoryParameters* _parameters);
        virtual ~FluidParticle();
        void update();
        static std::string factoryName()
        {
            return "FluidParticleFactory";
        }
    protected:
    private:
        const ImmutableData& data;
};

#endif // WATERPARTICLE_H
