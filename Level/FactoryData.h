#ifndef FACTORYDATA_H
#define FACTORYDATA_H

#include <Level/LoadedData.h>
class FactoryParameters;

class FactoryData : public LoadedData
{
    public:
        FactoryData(const char* _type, const char* _name, FactoryParameters* _params, const std::string& _address);
        virtual ~FactoryData();
    protected:
    private:
        std::string type, name;
        FactoryParameters* params;
};

#endif // FACTORYDATA_H
