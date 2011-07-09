#ifndef STATICSKINFACTORY_H
#define STATICSKINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class StaticSkinFactory : public AbstractFactory<Skin, StaticSkinFactory>
{
    public:
        StaticSkinFactory();
        virtual ~StaticSkinFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "StaticSkinFactory";
        }
        Skin* useFactory(FactoryParameters* parameters);
    protected:
    private:
        std::string materialName;
};

#endif // STATICSKINFACTORY_H
