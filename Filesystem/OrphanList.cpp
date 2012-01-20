#include "OrphanList.h"

OrphanList::OrphanList()
:GameObjectBase("orphanList", 0)
{
    //ctor
}

OrphanList::~OrphanList()
{
    //dtor
}

void OrphanList::attachOrphan(GameObjectBase* _node)
{
    _node->parent = this;
    _node->parent = this;
    _node->prev = nullptr;
    _node->next = children;
    if (children != nullptr)
    {
        children->prev = _node;
    }
    children = _node;
}
