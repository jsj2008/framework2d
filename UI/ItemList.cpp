#include "ItemList.h"
#include <CEGUI/CEGUI.h>

ItemList::ItemList(const std::string& _listboxWindowName)
{
    //ctor
    listBox = CEGUI::System::getSingletonPtr()->getGUISheet()->getChildRecursive(_listboxWindowName);
}

ItemList::~ItemList()
{
    //dtor
}
