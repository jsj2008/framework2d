#ifndef WATERPARTICLEBODYFACTORY_H
#define WATERPARTICLEBODYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
<<<<<<< HEAD
#include <Physics/BodyParts/BodyPart.h>
=======
#include <Physics/BodyPart.h>
>>>>>>> FETCH_HEAD

class FluidParticleBodyFactory : public AbstractFactory<BodyPart, FluidParticleBodyFactory>
{
    public:
        FluidParticleBodyFactory();
        virtual ~FluidParticleBodyFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "FluidParticleBodyFactory";
        }
    protected:
    private:
        AbstractFactoryBase<BodyPart>* bodyFactory;
        AbstractFactoryBase<BodyPart>* sensorFactory;
};

#endif // WATERPARTICLEBODYFACTORY_H
