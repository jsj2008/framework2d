#ifndef FILESYSTEM_H
#define FILESYSTEM_H

//#include <Filesystem/FilesystemNode.h>
#include <GameObject.h>
class OrphanList;

class Filesystem: public GameObject<Filesystem>
{
    public:
        Filesystem();
        virtual ~Filesystem();
        OrphanList* getOrphanList() /// "/dev/orphans"
            {return orphanList;}

        static Filesystem* global(); /// "/"
        static void registerActions(GameObjectType* _type);
        /*FilesystemIter* firstChild();
        FilesystemIter* nextChild(FilesystemIter* _prevChild);*/
    protected:
    private:
        OrphanList* orphanList;
};

#endif // FILESYSTEM_H
