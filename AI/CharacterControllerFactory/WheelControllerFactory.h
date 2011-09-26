#ifndef WHEELCONTROLLERFACTORY_H
#define WHEELCONTROLLERFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <AI/CharacterControllers/WheelCharacterController.h>

class WheelControllerFactory : public AbstractFactory <CharacterController, WheelControllerFactory>
{
    public:
        WheelControllerFactory();
        virtual ~WheelControllerFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "WheelControllerFactory";
        }
        CharacterController* useFactory(FactoryParameters* parameters);
    protected:
    private:
        WheelCharacterController::Properties properties;
};

#endif // WHEELCONTROLLERFACTORY_H
