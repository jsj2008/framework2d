#ifndef BODYCAMERAFACTORY_H
#define BODYCAMERAFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Events/EventListener.h>
class Camera;
class FactoryParameters;
class BodyCameraFactory : public AbstractFactory<Camera, BodyCameraFactory>, EventsListener
{
    public:
        BodyCameraFactory(FactoryLoader* _loader);
        virtual ~BodyCameraFactory();
        Camera* useFactory(FactoryParameters* params);
        bool trigger(Event* event);
        static std::string name()
        {
            return "BodyCameraFactory";
        }
    protected:
    private:
        b2Body* body;
        std::string factoryName;
};

#endif // BODYCAMERAFACTORY_H
