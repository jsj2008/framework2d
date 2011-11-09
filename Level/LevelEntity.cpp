#include "LevelEntity.h"
#include <Entities/Entity.h>
#include <Events/Events/ShowEntityEvent.h>
#include <GameModes/Editor/DynamicEditor/EntityList.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactories.h>
#include <CEGUI/CEGUI.h>
#include <cassert>

LevelEntity::LevelEntity(EntityList* _entityList, FactoryParameters* _parameters, const std::string& _factoryName)
:parameters(*_parameters)
{
    //ctor
    entity = nullptr;
    listBoxItem = nullptr;
    entityList = _entityList;
    factory = nullptr; /// FIXME AbstractFactories::global().getFactory<Entity>(_factoryName);
    factoryName = _factoryName;
}

LevelEntity::~LevelEntity()
{
    //dtor
    entityList->removeEntity(this);
}

void LevelEntity::show()
{
    if (entity != nullptr)
    {
        ShowEntityEvent event(entity);
        Events::global().triggerEvent(&event);
    }
}
void LevelEntity::activateDisplay(CEGUI::Window* _window)
{
    CEGUI::Window* aliveDisplay = _window->getChild("Root/EntityList/Alive");
    if (entityIsAlive())
        aliveDisplay->setText("Spawned");
    else
        aliveDisplay->setText("Dead");

    CEGUI::Window* factoryNameDisplay = _window->getChild("Root/EntityList/FactoryName");
    factoryNameDisplay->setText(factoryName);

    CEGUI::MultiColumnList* properties = static_cast<CEGUI::MultiColumnList*>(_window->getChild("Root/EntityList/Properties"));
    properties->resetList();
    for (auto i = parameters.begin(); i != parameters.end(); i++)
    {
        unsigned int row = properties->addRow(new CEGUI::ListboxTextItem(i->first), 0);
        properties->setItem(new CEGUI::ListboxTextItem(i->second->getTypeId()),1, row);
        std::stringstream value;
        i->second->output(&value);
        properties->setItem(new CEGUI::ListboxTextItem(value.str()),2, row);
    }

    CEGUI::Window* quitButton = _window->getChild("Root/EntityList/KillButton");
    quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, {&LevelEntity::quitButton, this});
}

bool LevelEntity::isNamed()
{
    const std::string& name = parameters.get<std::string>("name", "");
    return name != "";
}

Entity* LevelEntity::createEntity()
{
    assert(entity == nullptr);
    entity = factory->use(&parameters);
    //entity->registerDeathListener(this);
    entityList->addEntity(this, getName());
    listBoxItem->setTextColours(0xFF00FF00);
    return entity;
}

void LevelEntity::destroyEntity()
{
    assert(entity);
    delete entity;
    assert(entity == nullptr);
    entityList->removeEntity(this);
    listBoxItem->setTextColours(0xFFFF0000);
}

bool LevelEntity::quitButton(const CEGUI::EventArgs& _args)
{
    Entity* entityCache = entity;
    entity = nullptr;
    delete entityCache;
    delete this;
    static_cast<const CEGUI::WindowEventArgs&>(_args).window->removeEvent(CEGUI::PushButton::EventClicked);
    return false; /// FIXME Why doesn't this unsubscribe?
}

std::string LevelEntity::getName()
{
    //return factory->getFactoryName(); /// FIXME make this check for "name"
    const std::string& name = parameters.get<std::string>("name", "");
    if (name != "")
    {
        return '\"' + name + '\"';
    }
    return factoryName;
}

void LevelEntity::output(PropertyBagSerializer* _serializer)
{
    _serializer->startFactory(factoryName);
    parameters.output(_serializer);
    _serializer->endFactory();
}



















