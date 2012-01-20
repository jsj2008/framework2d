#include "Filesystem.h"
#include <Filesystem/OrphanList.h>

Filesystem g_Filesystem;

Filesystem::Filesystem()
{
    //ctor
    orphanList = new OrphanList;
}

Filesystem::~Filesystem()
{
    //dtor
}

class RootFilesystemIter: public FilesystemIter
{
    public:
        RootFilesystemIter(FilesystemNode* _node){node = _node;}
        ~RootFilesystemIter(){}
        FilesystemNode* get(){return node;}
    private:
        FilesystemNode* node;
};
std::string Filesystem::nodeName()
{
    return "/";
}
FilesystemIter* Filesystem::firstChild()
{
    return new RootFilesystemIter(orphanList);
}
FilesystemIter* Filesystem::nextChild(FilesystemIter* _prevChild)
{
    delete _prevChild;
    return nullptr;
}
