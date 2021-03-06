#ifndef FACTORYDATA_H
#define FACTORYDATA_H

#include <Level/LoadedData.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>
class PropertyBagData;
class AbstractFactories;

class FactoryData : public LoadedData
{
    public:
        FactoryData(const char* _type, const char* _name, const char* _product, PropertyBagData* _propertyBag, const std::vector<FactoryData*>& _childFactories);
        virtual ~FactoryData();

        GameObjectBase* build(AbstractFactories* _factories);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        CppFactoryLoader loader;
        PropertyBagData* propertyBag;
        std::string product;
        std::vector<FactoryData*> childFactories;
};

#endif // FACTORYDATA_H
