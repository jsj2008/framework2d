#include "GameObject.h"
#include <Filesystem/Filesystem.h>
#include <Filesystem/OrphanList.h>

GameObjectBase::GameObjectBase(const std::string& _name, unsigned int _eventsSize)
{
    objectName = _name;
    eventListenerLists.resize(_eventsSize);
    prev = next = children = parent = nullptr;
}
void GameObjectBase::orphaned()
{
    Filesystem::global()->getOrphanList()->attachOrphan(this);
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
    parent->detach(this);
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

class GameObjectFilesystemIter: public FilesystemIter
{
    public:
        GameObjectFilesystemIter(GameObjectBase* _node){node = _node;}
        ~GameObjectFilesystemIter(){}
        FilesystemNode* get(){return node;}
        GameObjectBase* node;
};
FilesystemIter* GameObjectBase::firstChild()
{
    if (children)
        return new GameObjectFilesystemIter(children);
    else
        return nullptr;
}
FilesystemIter* GameObjectBase::nextChild(FilesystemIter* _prevChild)
{
    assert(dynamic_cast<GameObjectFilesystemIter*>(_prevChild));
    GameObjectFilesystemIter* prevChild = static_cast<GameObjectFilesystemIter*>(_prevChild);
    assert(prevChild->node->parent == this);
    if (prevChild->node->next)
    {
        prevChild->node = prevChild->node->next;
        return prevChild;
    }
    else
    {
        delete prevChild;
        return nullptr;
    }
}
typename GameObject<GameEntity>::EventHandle* GameEntity::coonEvent = createEventHandle("Coon");
