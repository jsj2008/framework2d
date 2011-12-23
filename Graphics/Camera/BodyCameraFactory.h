#ifndef BODYCAMERAFACTORY_H
#define BODYCAMERAFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryUsageEvent.h>
class Camera;
class FactoryParameters;
class BodyCameraFactory : public AbstractFactory<Camera, BodyCameraFactory>
{
    public:
        BodyCameraFactory();
        virtual ~BodyCameraFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Camera* useFactory(FactoryParameters* params);
        static std::string name()
        {
            return "BodyCameraFactory";
        }
    protected:
    private:
};

#endif // BODYCAMERAFACTORY_H
