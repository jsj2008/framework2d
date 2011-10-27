#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <Level/LoadedData.h>
#include <vector>
class EventListData;
class EntityListData;
class FactoryListData;
class Level;

class LevelData : public LoadedData
{
    public:
        LevelData(const std::string& _address);
        virtual ~LevelData();
        Level* build();

        void addEntityList(EntityListData* _list)
            {entityLists.push_back(_list);}
        unsigned int entityListsSize()
            {return entityLists.size();}
        EntityListData* getEntityList(unsigned int _index)
            {return entityLists[_index];}
        void removeEntityList(unsigned int _index); /// Removes from position and items later on in the list get shuffled down

        void addFactoryList(FactoryListData* _list)
            {factoryLists.push_back(_list);}
        unsigned int FactoryListsSize()
            {return factoryLists.size();}
        FactoryListData* getFactoryList(unsigned int _index)
            {return factoryLists[_index];}
        void removeFactoryList(unsigned int _index); /// Removes from position and items later on in the list get shuffled down

        void addEventList(EventListData* _list)
            {eventLists.push_back(_list);}
        unsigned int EventListsSize()
            {return eventLists.size();}
        EventListData* getEventList(unsigned int _index)
            {return eventLists[_index];}
        void removeEventList(unsigned int _index); /// Removes from position and items later on in the list get shuffled down

    protected:
    private:
        void virtualSave(XmlDataSaver* _saver);
        std::vector<EventListData*> eventLists;
        std::vector<EntityListData*> entityLists;
        std::vector<FactoryListData*> factoryLists;
};

#endif // LEVELDATA_H
