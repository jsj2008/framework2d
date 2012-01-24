#ifndef FACTORYGROUPLISTDATA_H
#define FACTORYGROUPLISTDATA_H

#include <Level/LoadedData.h>
#include <vector>
class AbstractFactories;
class FactoryGroupData;

class FactoryGroupListData : public LoadedData
{
    public:
        FactoryGroupListData();
        virtual ~FactoryGroupListData();
        void build(AbstractFactories* _factories);

        void addFactoryGroup(FactoryGroupData* _list)
            {factoriesGroups.push_back(_list);}
        unsigned int factoryGroupsSize()
            {return factoriesGroups.size();}
        FactoryGroupData* getFactoryGroup(unsigned int _index)
            {return factoriesGroups[_index];}
        void removeFactoryGroup(unsigned int _index);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
        std::vector<FactoryGroupData*> factoriesGroups;
};

#endif // FACTORYGROUPLISTDATA_H
