#include "EntityList.h"
#include <CEGUI/CEGUI.h>
#include <Events/Events.h>
#include <Level/LevelEntity.h>
#include <Entities/Entity.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Types/TextFilePropertyBagSerializer.h>
#include <Types/XmlFilePropertyBagSerializer.h>
#include <Types/XmlPropertyBagLoader.h>
#include <fstream>

EntityList::EntityList(const std::string& _windowName, const std::string& _listFilename)
{
    //ctor
    listBox = dynamic_cast<CEGUI::Combobox*>(CEGUI::System::getSingletonPtr()->getGUISheet()->getChildRecursive(_windowName));
    assert(listBox);
    //selectionDisplay = listBox->getParent()->getChild("Root/EntityList/GroupBox");
    selectionDisplay = listBox->getParent();
    CEGUI::MultiColumnList* properties = static_cast<CEGUI::MultiColumnList*>(selectionDisplay->getChild("Root/EntityList/Properties"));
    properties->addColumn("Property",0,{0.32f,0});
    properties->addColumn("Type",1,{0.33f,0});
    properties->addColumn("Value",2,{0.33f,0});
    CEGUI::Checkbox* filterDeadButton = static_cast<CEGUI::Checkbox*>(selectionDisplay->getChild("Root/EntityList/FilterDead"));
    filterDead = filterDeadButton->isSelected();
    filterDeadButton->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, {&EntityList::filterDeadButton, this});
    listBox->setSortingEnabled(true);
    listBox->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber({&EntityList::eventListSelectionChange, this}));
    listBox->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber({&EntityList::eventListItemSelected, this}));
    //Events::global().registerListener<EntityPlaceEvent>(this,{eReadQueue|eClearQueue|eBlockQueue});
    //Events::global().registerListener<EntityRemoveEvent>(this,{eReadQueue|eClearQueue|eBlockQueue});
    Events::global().registerListener<EntitySelectEvent>(this,{eClearQueue|eBlockQueue});

    loadLevel(_listFilename);
}

EntityList::~EntityList()
{
    //dtor
}
void EntityList::loadLevel(const std::string& _listFileName)
{
    XmlPropertyBagLoader loader("Level.xml");
    int version = loader.getVersion();
    if (version != 1)
    {
        char message[128];
        sprintf(message, "Unknown version number: %d in Level.xml", version);
        g_Log.error(message);
    }
    if (loader.startFactories())
    {
        do
        {
            std::string factory = loader.getFactoryName();
            FactoryParameters params;
            loader.readParameters(&params);
            LevelEntity* entity = new LevelEntity(this, &params, factory);
            Entity* body = entity->createEntity();
            EntityPlaceEvent event(body, factory, &params);
            Events::global().triggerEvent(&event);
        }
        while (loader.next());
    }
    else g_Log.error("Level loading from xml failed");
    loader.endFactories();
}

void EntityList::saveLevel(const std::string& _listFileName)
{
    XmlFilePropertyBagSerializer xml("Level.xml");
    PropertyBagSerializer* serializer = &xml;

    unsigned short size = listBox->getItemCount() + filteredDead.size();
    serializer->startFactories(size, "Entity");
    serializer->setVersion(1);
    for (unsigned short i = 0; i != listBox->getItemCount() ; i++)
    {
        CEGUI::ListboxItem* item = listBox->getListboxItemFromIndex(i);
        LevelEntity* entity = static_cast<LevelEntity*>(item->getUserData());
        entity->output(serializer);
    }
    for (auto i = filteredDead.begin(); i != filteredDead.end(); i++)
    {
        (*i)->output(serializer);
    }
}

void EntityList::addEntity(LevelEntity* _entity, const std::string& _displayName)
{
    if (filterDead)
    {
        filteredDead.insert(_entity);
    }
    else
    {
        CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(_displayName);
        item->setUserData(_entity);
        _entity->setListBoxItem(item);
        listBox->addItem(item);
    }
    assert(_entity->getEntity());
    entityMap[_entity->getEntity()] = _entity;
}
void EntityList::removeEntity(LevelEntity* _entity)
{
    bool wasSelected = listBox->getSelectedItem() == _entity->getListBoxItem();
    listBox->removeItem(_entity->getListBoxItem());
    if (_entity->entityIsAlive())
    {
        entityMap.erase(_entity->getEntity());
        delete _entity->getEntity();
    }
    if (wasSelected)
    {
        //CEGUI::ListboxItem* selectedItem = listBox->getListboxItemFromIndex(0);
        //listBox->setItemSelectState(selectedItem, true);
        //static_cast<LevelEntity*>(listBox->getSelectedItem()->getUserData())->getEntityListDisplay(selectionDisplay);
        CEGUI::MultiColumnList* properties = static_cast<CEGUI::MultiColumnList*>(selectionDisplay->getChild("Root/EntityList/Properties"));
        properties->resetList();
    }
}
void EntityList::entityDied(LevelEntity* _entity)
{
    entityMap.erase(_entity->getEntity());
    if (filterDead)
    {
        CEGUI::ListboxItem* item = _entity->getListBoxItem();
        CEGUI::Window* owner = const_cast<CEGUI::Window*>(item->getOwnerWindow());
        static_cast<CEGUI::Listbox*>(owner)->removeItem(item);
        _entity->setListBoxItem(nullptr);
        filteredDead.insert(_entity);
    }
}
bool EntityList::eventListSelectionChange(const CEGUI::EventArgs& args)
{
    CEGUI::ListboxItem* selectedItem = listBox->getSelectedItem();
    if (selectedItem != nullptr) /// FIXME not sure why this is necessary. Seems to happen while browsing over the selection with the mouse
    {
        static_cast<LevelEntity*>(selectedItem->getUserData())->show();
    }
    return true;
}
bool EntityList::eventListItemSelected(const CEGUI::EventArgs& args)
{
    static_cast<LevelEntity*>(listBox->getSelectedItem()->getUserData())->activateDisplay(selectionDisplay);
    return true;
}
bool EntityList::filterDeadButton(const CEGUI::EventArgs& args) /// CONTINUE here just added this function
{
    bool newFilterDead = static_cast<CEGUI::Checkbox*>(static_cast<const CEGUI::WindowEventArgs&>(args).window)->isSelected();
    assert(filterDead != newFilterDead);
    filterDead = newFilterDead;
    if (filterDead)
    {
        for (unsigned int i = 0; i < listBox->getItemCount(); i++)
        {
            CEGUI::ListboxItem* item = listBox->getListboxItemFromIndex(i);
            LevelEntity* entity = static_cast<LevelEntity*>(item->getUserData());
            if (!entity->entityIsAlive())
            {
                entity->setListBoxItem(nullptr);
                CEGUI::Window* owner = const_cast<CEGUI::Window*>(item->getOwnerWindow());
                static_cast<CEGUI::Listbox*>(owner)->removeItem(item);
                filteredDead.insert(entity);
                i--;
            }
        }
    }
    else
    {
        for (auto i = filteredDead.begin(); i != filteredDead.end(); i++)
        {
            addEntity(*i, (*i)->getName());
            (*i)->getListBoxItem()->setTextColours(0xFFFF0000);
        }
        filteredDead.clear();
    }
    return true;
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
bool EntityList::trigger(EntitySelectEvent* event)
{
    LevelEntity* entity = entityMap[event->getSelectedEntity()];
    if (entity != nullptr)
    {
        CEGUI::ListboxItem* selectedItem = entity->getListBoxItem();
        listBox->setItemSelectState(selectedItem, true);
        entity->activateDisplay(selectionDisplay);
    }
    return true;
}





























