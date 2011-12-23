#include "EventListData.h"
#include <Level/XmlDataSaver.h>

EventListData::EventListData()
{
    //ctor
}

EventListData::~EventListData()
{
    //dtor
}

void EventListData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{
    TiXmlHandle handle(nullptr);
    if (*_address == address)
    {
        handle = _saver->createElement(*_address, "EventList");
    }
    else
    {
        handle = _saver->createElement(address, "EventListRef");
        TiXmlText* text = new TiXmlText(address);
        handle.Element()->LinkEndChild(text);
    }
}
