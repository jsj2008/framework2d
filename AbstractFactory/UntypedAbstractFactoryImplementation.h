#ifndef UNTYPEDABSTRACTFACTORYIMPLEMENTATION_H
#define UNTYPEDABSTRACTFACTORYIMPLEMENTATION_H

#include <AbstractFactory/UntypedAbstractFactory.h>
template <typename Product>
class AbstractFactoryBase;

template <typename Product>
class UntypedAbstractFactoryImplementation : public UntypedAbstractFactory
{
    public:
        UntypedAbstractFactoryImplementation(AbstractFactoryBase<Product>* _factory);
        virtual ~UntypedAbstractFactoryImplementation();
        void* use(FactoryParameters* _parameters);
        const std::string& getName();
    protected:
    private:
        AbstractFactoryBase<Product>* factory;
};

/** Implementation
*
*
*/


template <typename Product>
UntypedAbstractFactoryImplementation<Product>::UntypedAbstractFactoryImplementation(AbstractFactoryBase<Product>* _factory)
{
    factory = _factory;
}
template <typename Product>
UntypedAbstractFactoryImplementation<Product>::~UntypedAbstractFactoryImplementation()
{
}
template <typename Product>
void* UntypedAbstractFactoryImplementation<Product>::use(FactoryParameters* _parameters)
{
    return factory->use(_parameters, nullptr);
}
template <typename Product>
const std::string& UntypedAbstractFactoryImplementation<Product>::getName()
{
    return factory->getObjectName();
}
#endif // UNTYPEDABSTRACTFACTORYIMPLEMENTATION_H
