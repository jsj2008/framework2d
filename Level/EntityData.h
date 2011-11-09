#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <Level/LoadedData.h>
class FactoryParameters;
class AbstractFactories;

class EntityData : public LoadedData
{
    public:
        EntityData(const char* _type, FactoryParameters* _params);
        virtual ~EntityData();

        void build(AbstractFactories* _factories);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        FactoryParameters* params;
        std::string type;
};

#endif // ENTITYDATA_H
