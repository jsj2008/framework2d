#include "EntityList.h"
#include <CEGUI/CEGUI.h>
#include <Events/Events.h>
#include <AbstractFactory/FactoryParameters.h>

EntityList::EntityList(const std::string& _windowName)
{
    //ctor
    listBox = dynamic_cast<CEGUI::Combobox*>(CEGUI::System::getSingletonPtr()->getGUISheet()->getChildRecursive(_windowName));
    listBox->setSortingEnabled(true);
    assert(listBox);
    Events::global().registerListener<EntityPlaceEvent>(this,{eReadQueue|eClearQueue|eBlockQueue});
    Events::global().registerListener<EntityRemoveEvent>(this,{eReadQueue|eClearQueue|eBlockQueue});
}

EntityList::~EntityList()
{
    //dtor
}

void EntityList::addEntity(Entity* _entity, const std::string& _displayName)
{
    listBox->addItem(new CEGUI::ListboxTextItem(_displayName));
}

bool EntityList::trigger(EntityPlaceEvent* event)
{
    FactoryParameters params = *event->getParameters(); /// FIXME this shouldn't be necessary
    std::string name = event->getParameters()->get<std::string>("name","");
    if (name == "")
    {
        name = event->getFactoryName();
    }
    else
    {
        name = '\"' + name + '\"';
    }
    listBox->addItem(new CEGUI::ListboxTextItem(name));
    return true;
}
bool EntityList::trigger(EntityRemoveEvent* event)
{
    FactoryParameters params = *event->getParameters(); /// FIXME this shouldn't be necessary
    std::string name = event->getParameters()->get<std::string>("name","");
    if (name == "")
    {
        name = event->getFactoryName();
    }
    else
    {
        name = '\"' + name + '\"';
    }
    listBox->removeItem(listBox->findItemWithText(name, nullptr));
    return true;
}
