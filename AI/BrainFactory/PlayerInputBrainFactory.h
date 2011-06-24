#ifndef PLAYERINPUTBRAINFACTORY_H
#define PLAYERINPUTBRAINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class Brain;

class PlayerInputBrainFactory : public AbstractFactory <Brain, PlayerInputBrainFactory>
{
    public:
        PlayerInputBrainFactory(FactoryLoader* loader);
        virtual ~PlayerInputBrainFactory();
        static std::string name()
        {
            return "PlayerInputBrainFactory";
        }
        Brain* useFactory(FactoryParameters* parameters);
    protected:
    private:
};

#endif // PLAYERINPUTBRAINFACTORY_H
