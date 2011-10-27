#ifndef ENTITYLISTDATA_H
#define ENTITYLISTDATA_H

#include <Level/LoadedData.h>
#include <vector>
class EntityData;
class AbstractFactories;

class EntityListData : public LoadedData
{
    public:
        EntityListData(const std::string& _address);
        virtual ~EntityListData();

        void addEntity(EntityData* _list)
            {entities.push_back(_list);}
        unsigned int factoriesSize()
            {return entities.size();}
        EntityData* getEntity(unsigned int _index)
            {return entities[_index];}
        void removeEntity(unsigned int _index); /// Removes from position and items later on in the list get shuffled down

        void build(AbstractFactories* _factories);
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver);
        std::vector<EntityData*> entities;
};

#endif // ENTITYLISTDATA_H
