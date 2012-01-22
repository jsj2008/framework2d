#include "Folder.h"

Folder::Folder(const std::string& _name)
:GameObject(_name)
{
    //ctor
}

Folder::~Folder()
{
    //dtor
}

void Folder::registerActions(GameObjectType* _type)
{
}
