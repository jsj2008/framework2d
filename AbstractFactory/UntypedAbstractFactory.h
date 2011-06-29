#ifndef UNTYPEDABSTRACTFACTORY_H
#define UNTYPEDABSTRACTFACTORY_H

#include <string>
class FactoryParameters;

class UntypedAbstractFactory
{
    public:
        UntypedAbstractFactory();
        virtual ~UntypedAbstractFactory();
        virtual void* use(FactoryParameters* parameters)=0;
        virtual const std::string& getName()=0;
    protected:
    private:
};

#endif // UNTYPEDABSTRACTFACTORY_H
