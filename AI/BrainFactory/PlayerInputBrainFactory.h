#ifndef PLAYERINPUTBRAINFACTORY_H
#define PLAYERINPUTBRAINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;
class Brain;

class PlayerInputBrainFactory : public AbstractFactory <Brain, PlayerInputBrainFactory>
{
    public:
        PlayerInputBrainFactory();
        virtual ~PlayerInputBrainFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "PlayerInputBrainFactory";
        }
        Brain* useFactory(FactoryParameters* parameters);
    protected:
    private:
};

#endif // PLAYERINPUTBRAINFACTORY_H
