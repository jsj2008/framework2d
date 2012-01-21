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
        parent = _parent;
        prev = nullptr;
        next = _parent->children;
        if (_parent->children != nullptr)
        {
            _parent->children->prev = this;
        }
        _parent->children = this;
    }
    else if (_orphan)
    {
        Filesystem::global()->getOrphanList()->attachOrphan(this);
    }
    else
    {
        prev = next = parent = nullptr;
    }
    children = nullptr;
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
    GameObjectBase* child = children;
    while (child != nullptr)
    {
        GameObjectBase* prev = child;
        child = child->next;
        delete prev;
    }
    if (prev) /// FIXME remove this
    {
        if (prev->children == this)
        {
            prev->children = next;
        }
        else
        {
            prev->next = next;
        }
    }
    if (next != nullptr)
    {
        next->prev = prev;
    }
    parent->detach(this);
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

void GameObjectBase::attachChild(GameObjectBase* _child)
{
    assert(_child->parent != this);
    _child->parent->detach(_child);
    _child->parent = this;
    _child->prev = nullptr;
    _child->next = children;
    if (children != nullptr)
    {
        children->prev = _child;
    }
    children = _child;
}
#include <Entities/Entity.h>
#include <Physics/BodyParts/BodyPart.h>
void GameObjectBase::detach(GameObjectBase* _child)
{
    if (dynamic_cast<Entity*>(this) && dynamic_cast<BodyPart*>(_child))
    {
        assert(false);
    }
    assert(_child->parent == this);
    if (_child->prev)
        _child->prev->next = _child->next;
    else
        children = _child->next;
    if (_child->next)
        _child->next->prev = _child->prev;
}

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
GameObjectBase* GameObjectBase::getNext()
{
    return next;
}
GameObjectBase* GameObjectBase::getPrev()
{
    return prev;
}
GameObjectBase* GameObjectBase::getChildren()
{
    return children;
}
GameObjectBase* GameObjectBase::getParent()
{
    return parent;
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
            std::string address = _address.substr(iter, _address.size());
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
    GameObjectBase* child = children;
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




























