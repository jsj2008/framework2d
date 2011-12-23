#ifndef CHARACTERBODYFACTORY_H
#define CHARACTERBODYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class BodyPart;
class FactoryLoader;

class CharacterBodyFactory : public AbstractFactory<BodyPart, CharacterBodyFactory>
{
    public:
        CharacterBodyFactory();
        virtual ~CharacterBodyFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        BodyPart* useFactory(FactoryParameters* params);
        static std::string name()
        {
            return "CharacterBodyFactory";
        }
    protected:
    private:
        AbstractFactoryBase<BodyPart>* bodyFactory;
        AbstractFactoryBase<BodyPart>* wheelFactory;
        AbstractFactoryBase<BodyPart>* jointFactory;
};

#endif // CHARACTERBODYFACTORY_H
