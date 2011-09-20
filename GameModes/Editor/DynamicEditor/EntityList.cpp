#include "EntityList.h"
#include <CEGUI/CEGUI.h>

EntityList::EntityList(const std::string& _windowName)
{
    //ctor
    listBox = dynamic_cast<CEGUI::Combobox*>(CEGUI::System::getSingletonPtr()->getGUISheet()->getChildRecursive(_windowName));
    assert(listBox);
}

EntityList::~EntityList()
{
    //dtor
}

void EntityList::addEntity(Entity* _entity, const std::string& _displayName)
{
    listBox->addItem(new CEGUI::ListboxTextItem(_displayName));
}
