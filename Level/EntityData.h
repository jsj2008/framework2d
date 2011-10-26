#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <Level/LoadedData.h>
class FactoryParameters;

class EntityData : public LoadedData
{
    public:
        EntityData(const char* _type, FactoryParameters* _params, const std::string& _address);
        virtual ~EntityData();
    protected:
    private:
        FactoryParameters* params;
        std::string type;
};

#endif // ENTITYDATA_H
