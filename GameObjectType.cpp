#include "GameObjectType.h"
#include <GameObject.h>
#include <cassert>

std::unordered_map<std::string,EventHandle*>& GameObjectType::g_EventHandles()
{
    static std::unordered_map<std::string,EventHandle*> handles;
    return handles;
}
std::unordered_map<std::string,ActionHandle*>& GameObjectType::g_ActionHandles()
{
    static std::unordered_map<std::string,ActionHandle*> handles;
    return handles;
}

GameObjectType::GameObjectType(const std::string& _name)
:name(_name)
{
    //ctor
}

GameObjectType::~GameObjectType()
{
    //dtor
}

EventHandle* GameObjectType::createEventHandle(const std::string& _name)
{
    assert(eventHandles.find(_name) == eventHandles.end());
    EventHandle* handle = new EventHandle(eventHandles.size());
    eventHandles[_name] = handle;
    if (g_EventHandles().find(_name) == g_EventHandles().end())
    {
        g_EventHandles()[_name] = handle;
    }
    return handle;
}

unsigned int GameObjectType::eventsSize()
{
    return eventHandles.size();
}

ActionHandle* GameObjectType::getActionHandle(const std::string& _name)
{
    return actionHandles[_name];
}

EventHandle* GameObjectType::staticGetEventHandle(const std::string& _name)
{
    return g_EventHandles()[_name];
}
ActionHandle* GameObjectType::staticGetActionHandle(const std::string& _name)
{
    return g_ActionHandles()[_name];
}

std::string GameObjectType::print(GameObjectBase* _object)
{
    std::string ret;
    ret.append(getName() + ": '" + _object->getObjectName() + "'\n");
    {
        unsigned short numberOfChildren = 0;
        std::string children;
        for (GameObjectBase* child = _object->getChildren(); child; child = child->getNext())
        {
            children.append(child->getType()->getName() + ": '" + child->getObjectName() + "',\n");
            numberOfChildren++;
        }
        std::string buffer;
        buffer.resize(42);
        if (numberOfChildren == 1)
            sprintf(&buffer[0], "%d child:\n", numberOfChildren);
        else
            sprintf(&buffer[0], "%d children:\n", numberOfChildren);
        ret.append(buffer + children);
    }
    {
        unsigned short numberOfEvents = 0;
        std::string events;
        for (auto iter = eventHandles.begin(); iter != eventHandles.end(); iter++)
        {
            events.append(iter->first + ",\n");
            numberOfEvents++;
        }
        std::string buffer;
        buffer.resize(40);
        switch (numberOfEvents)
        {
            case 0:
                sprintf(&buffer[0], "No events\n");
                break;
            case 1:
                sprintf(&buffer[0], "1 event:\n");
                break;
            default:
                sprintf(&buffer[0], "%d events:\n", numberOfEvents);
                break;
        };
        ret.append(buffer + events);
    }
    {
        unsigned short numberOfActions = 0;
        std::string action;
        for (auto iter = actionHandles.begin(); iter != actionHandles.end(); iter++)
        {
            action.append(iter->first + ",\n");
            numberOfActions++;
        }
        std::string buffer;
        buffer.resize(40);
        switch (numberOfActions)
        {
            case 0:
                sprintf(&buffer[0], "No actions\n");
                break;
            case 1:
                sprintf(&buffer[0], "1 action:\n");
                break;
            default:
                sprintf(&buffer[0], "%d actions:\n", numberOfActions);
                break;
        };
        ret.append(buffer + action);
    }
    return ret;
}



























