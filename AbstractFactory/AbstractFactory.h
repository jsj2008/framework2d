#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <Box2D/Box2D.h>
#include <string>
#include <istream>
class Entity;
class FactoryParameters;

class AbstractFactory
{
    public:
        AbstractFactory();
        virtual ~AbstractFactory();
        virtual Entity* useFactory(FactoryParameters* parameters)=0;
    protected:
        void setMaterial(class Skin* skin,const std::string& materialName);
        b2BodyDef bodyDef;
    private:
};

#endif // ABSTRACTFACTORY_H
