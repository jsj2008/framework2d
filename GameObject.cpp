#include "GameObject.h"
#include <Filesystem/Filesystem.h>
#include <Filesystem/OrphanList.h>
#include <Log/Log.h>

GameObjectBase::GameObjectBase(GameObjectType* _type, const std::string& _name)
{
    type = _type;
    objectName = _name;
    eventListenerLists.resize(type->eventsSize());
    Filesystem::global()->getOrphanList()->attachOrphan(this);
    children = nullptr;
}
GameObjectBase::GameObjectBase(GameObjectType* _type, const std::string& _name, GameObjectBase* _parent, bool _orphan)
{
    type = _type;
    objectName = _name;
    eventListenerLists.resize(type->eventsSize());
    if (_parent)
    {
      _parent->attachChild(this);
    }
    else if (_orphan)
    {
        Filesystem::global()->getOrphanList()->attachOrphan(this);
    }
    else
    {
    }
}
/*void GameObjectBase::orphaned() FIXME remove old code
{
    Filesystem::global()->getOrphanList()->attachOrphan(this);
}*/
GameObjectBase::~GameObjectBase()
{
    for (auto listeners = eventListenerLists.begin(); listeners != eventListenerLists.end(); listeners++)
    {
        for (auto listener = listeners->begin(); listener != listeners->end(); listener++)
        {
            (*listener)->eventObjectDeleted();
        }
    }
}

void GameObjectBase::registerBaseActions(GameObjectType* _type)
{
    static bool done = false;
    //if (!done)
    {
        done = true;
        _type->createActionHandle("Kill", &GameObject<GameObjectBase>::killAction);
        _type->createActionHandle("KillBy", &GameObject<GameObjectBase>::killActionBy);
        deathEvent = _type->createEventHandle("onDeath");
    }
}

#include <Entities/Entity.h>
#include <Physics/BodyParts/BodyPart.h>

GameObjectType* GameObjectBase::getType()
{
    return type;
}
void EventHandle::fire(GameObjectBase* _object)
{
    std::vector<GameObjectEventListener*>& listeners = _object->eventListenerLists[eventIndex];
    for (auto listener = listeners.begin(); listener != listeners.end(); listener++)
    {
        (*listener)->fire();
    }
}

void GameObjectBase::killAction()
{
    delete this;
}
void GameObjectBase::killActionBy(CollisionObject* _object)
{
    delete this;
}

GameObjectBase* GameObjectBase::getNode(const std::string& _address)
{
  GameObjectBase* node = this;
    unsigned int iter = 0;
    if (_address[0] == '/')
    {
        node = Filesystem::global();
        iter = 1;
    }
    else if (_address[0] == '.')
    {
        iter = 1;
    }
    while (true)
    {
        if (_address.size() > iter)
        {
            int next = _address.find('/', iter);
            std::string address = _address.substr(iter, next - iter);
            if (address == "..")
            {
	      node = node->getParent();
            }
            else
            {
                if (next == -1)
                {
                    node = node->getIndividualNode(address);
                    break;
                }
                else
                {
                    node = node->getIndividualNode(address);
                    iter = next+1;
                }
            }
        } else break;
    }
    return node;
}
#include <cstring>
GameObjectBase* GameObjectBase::getIndividualNode(const std::string& _address)
{
  GameObjectBase* child = getChildren();
    while (child)
    {
        //if (child->get()->nodeName() == _address)
        if (strcmp(&child->getObjectName()[0], &_address[0]) == 0)
        {
            return child;
        }
        child = child->getNext();
    }
    g_Log.error("No such node: " + _address);
    throw -1;
}

EventHandle* GameObjectBase::deathEvent;




























