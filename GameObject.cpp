#include "GameObject.h"

GameObjectBase::GameObjectBase(unsigned int _eventsSize)
{
    eventListenerLists.resize(_eventsSize);
    prev = next = children = parent = nullptr;
}
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
    if (prev->children == this)
    {
        prev->children = next;
    }
    else
    {
        prev->next = next;
    }
    if (next != nullptr)
    {
        next->prev = prev;
    }
}

void GameObjectBase::registerBaseActions()
{
    static bool done = false;
    if (!done)
    {
        done = true;
        GameObject<GameObjectBase>::createActionHandle("Kill", &GameObject<GameObjectBase>::killAction);
    }
}

void GameObjectBase::attachChild(GameObjectBase* _child)
{
    _child->prev = this;
    _child->next = children;
    if (children != nullptr)
    {
        children->prev = _child;
    }
    children = _child;
    _child->parent = this;
}

void GameObjectBase::EventHandle::fire(GameObjectBase* _object)
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

void GameObjectBase::killAction(CollisionObject* _object)
{
    delete this;
}
typename GameObject<GameEntity>::EventHandle* GameEntity::coonEvent = createEventHandle("Coon");
