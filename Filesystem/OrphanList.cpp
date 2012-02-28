#include "OrphanList.h"

OrphanList::OrphanList(GameObjectBase* _parent)
:GameObject("orphans", _parent)
{
    //ctor
}

OrphanList::~OrphanList()
{
    //dtor
}

void OrphanList::attachOrphan(GameObjectBase* _node)
{
  attachChild(_node);
}

void OrphanList::registerActions(GameObjectType* _type)
{
}

void OrphanList::print(std::string* _output)
{

}
