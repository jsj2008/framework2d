#ifndef FACTORYLISTDATA_H
#define FACTORYLISTDATA_H

#include <Level/LoadedData.h>
#include <vector>
class FactoryData;

class FactoryListData : public LoadedData
{
    public:
        FactoryListData(const std::string& _address);
        virtual ~FactoryListData();

        void addFactory(FactoryData* _list)
            {factories.push_back(_list);}
        unsigned int factoriesSize()
            {return factories.size();}
        FactoryData* getFactory(unsigned int _index)
            {return factories[_index];}
        void removeFactory(unsigned int _index); /// Removes from position and items later on in the list get shuffled down
    protected:
    private:
        std::vector<FactoryData*> factories;
};

#endif // FACTORYLISTDATA_H
