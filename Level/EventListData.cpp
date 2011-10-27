#include "EventListData.h"

EventListData::EventListData(const std::string& _address)
:LoadedData(_address)
{
    //ctor
}

EventListData::~EventListData()
{
    //dtor
}

void EventListData::virtualSave(XmlDataSaver* _saver)
{

}
