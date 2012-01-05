#ifndef BUBBLESKINFACTORY_H
#define BUBBLESKINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class Skin;

class BubbleSkinFactory : public AbstractFactory<Skin, BubbleSkinFactory>
{
    public:
        BubbleSkinFactory();
        virtual ~BubbleSkinFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "BubbleSkinFactory";
        }
        Skin* useFactory(FactoryParameters* _parameters);
    protected:
    private:
        std::string materialName;
        float radius;
};

#endif // BUBBLESKINFACTORY_H
