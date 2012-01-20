#include "FilesystemNode.h"
#include <Filesystem/Filesystem.h>
#include <Log/Log.h>
/*
FilesystemNode::FilesystemNode()
{
    //ctor
}

FilesystemNode::~FilesystemNode()
{
    //dtor
}
#include <cstring>

FilesystemNode* FilesystemNode::getNode(const std::string& _address)
{
    FilesystemNode* node = this;
    unsigned int iter = 0;
    if (_address[0] == '/')
    {
        node = Filesystem::global();
        iter = 1;
    }
    try
    {
        while (true)
        {
            int next = _address.find('/', iter);
            if (next == -1)
            {
                if (_address.size() > iter)
                    node = node->getIndividualNode(_address.substr(iter, _address.size()));
                break;
            }
            else
            {
                node = node->getIndividualNode(_address.substr(iter, next - iter));
                iter = next+1;
            }
        }
    }
    catch (int i) {}
    return node;
}
FilesystemNode* FilesystemNode::getIndividualNode(const std::string& _address)
{
    FilesystemIter* child = firstChild();
    while (child)
    {
        //if (child->get()->nodeName() == _address)
        if (strcmp(&child->get()->nodeName()[0], &_address[0]) == 0)
        {
            FilesystemNode* ret = child->get();
            delete child;
            return ret;
        }
        child = nextChild(child);
    }
    g_Log.error("No such node: " + _address);
    throw -1;
}

FilesystemIter::FilesystemIter()
{
}
FilesystemIter::~FilesystemIter()
{
}*/
