#ifndef FACTORYDATA_H
#define FACTORYDATA_H

#include <Level/LoadedData.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>
class FactoryParameters;
class AbstractFactories;

class FactoryData : public LoadedData
{
    public:
        FactoryData(const char* _type, const char* _name, FactoryParameters* _params, const std::string& _address);
        virtual ~FactoryData();

        void build(AbstractFactories* _factories);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver);
        CppFactoryLoader loader;
};

#endif // FACTORYDATA_H
