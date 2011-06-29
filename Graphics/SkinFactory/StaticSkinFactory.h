#ifndef STATICSKINFACTORY_H
#define STATICSKINFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class StaticSkinFactory : public AbstractFactory<Skin, StaticSkinFactory>
{
    public:
        StaticSkinFactory(FactoryLoader* _loader);
        virtual ~StaticSkinFactory();
        static std::string name()
        {
            return "StaticSkinFactory";
        }
        Skin* useFactory(FactoryParameters* parameters);
    protected:
    private:
        std::string materialName;
        Vec2f dimensions;
};

#endif // STATICSKINFACTORY_H
