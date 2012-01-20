#include "Filesystem.h"
#include <Filesystem/OrphanList.h>

Filesystem g_Filesystem;

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

/*class RootFilesystemIter: public FilesystemIter
{
    public:
        RootFilesystemIter(FilesystemNode* _node){node = _node;}
        ~RootFilesystemIter(){}
        FilesystemNode* get(){return node;}
    private:
        FilesystemNode* node;
};*/
/*FilesystemIter* Filesystem::firstChild()
{
    return new RootFilesystemIter(orphanList);
}
FilesystemIter* Filesystem::nextChild(FilesystemIter* _prevChild)
{
    delete _prevChild;
    return nullptr;
}*/
Filesystem* Filesystem::global()
{
    static Filesystem filesystem;
    return &filesystem;
}
void Filesystem::registerActions(GameObjectType* _type)
{
}

