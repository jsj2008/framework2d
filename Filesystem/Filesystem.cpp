#include "Filesystem.h"
#include <Filesystem/OrphanList.h>
#include <Filesystem/Folder.h>

Filesystem::Filesystem()
:GameObject("/", nullptr, false)
{
    //ctor
    orphanList = new OrphanList(this);
    //attachChild(orphanList);
}

Filesystem::~Filesystem()
{
    //dtor
}

Filesystem* Filesystem::global()
{
    static Filesystem* filesystem = new Filesystem;
    return filesystem;
}
void Filesystem::registerActions(GameObjectType* _type)
{
}

void Filesystem::shutdown()
{
    while (getChildren())
    {
        delete getChildren();
    }
}

Folder* Filesystem::makeFolders(const std::string& _address)
{
    GameObjectBase* node = this; /// FIXME this code is duplicated
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
    int next;
    try
    {
        while (true)
        {
            if (_address.size() > iter)
            {
                next = _address.find('/', iter);
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
    }
    catch (int i)
    {
        while (true)
        {
            if (_address.size() > iter)
            {
                next = _address.find('/', iter);
                std::string address = _address.substr(iter, next - iter);
                if (next == -1)
                {
                    Folder* folder = new Folder(address);
                    node->attachChild(folder);
                    node = folder;
                    break;
                }
                else
                {
                    Folder* folder = new Folder(address);
                    node->attachChild(folder);
                    node = folder;
                    iter = next+1;
                }
            } else break;
        }
    }
    assert(dynamic_cast<Folder*>(node));
    return static_cast<Folder*>(node);;
}
