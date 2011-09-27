#ifndef BODYCAMERAFACTORY_H
#define BODYCAMERAFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Events/EventListener.h>
#include <Events/Events/FactoryUsageEvent.h>
class Camera;
class FactoryParameters;
class BodyCameraFactory : public AbstractFactory<Camera, BodyCameraFactory>, EventsListener<FactoryUsageEvent<b2Body>>
{
    public:
        BodyCameraFactory();
        virtual ~BodyCameraFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Camera* useFactory(FactoryParameters* params);
        bool trigger(FactoryUsageEvent<b2Body>* event);
        static std::string name()
        {
            return "BodyCameraFactory";
        }
    protected:
    private:
        b2Body* body;
        AbstractFactoryBase<Entity>* entityFactory;
};

#endif // BODYCAMERAFACTORY_H
