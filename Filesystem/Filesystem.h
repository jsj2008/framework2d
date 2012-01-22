#ifndef FILESYSTEM_H
#define FILESYSTEM_H

//#include <Filesystem/FilesystemNode.h>
#include <GameObject.h>
class OrphanList;
class Folder;

class Filesystem: public GameObject<Filesystem>
{
    public:
        void shutdown();
        OrphanList* getOrphanList() /// "/dev/orphans"
            {return orphanList;}

        static Filesystem* global(); /// "/"
        static void registerActions(GameObjectType* _type);
        Folder* makeFolders(const std::string& _name); /// Can specify multiple folders with '/' symbol
        /*FilesystemIter* firstChild();
        FilesystemIter* nextChild(FilesystemIter* _prevChild);*/
    protected:
    private:
        Filesystem();
        virtual ~Filesystem();
        OrphanList* orphanList;
};

#endif // FILESYSTEM_H
