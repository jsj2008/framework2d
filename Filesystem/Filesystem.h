#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <Filesystem/FilesystemNode.h>
class OrphanList;

class Filesystem: public FilesystemNode
{
    public:
        Filesystem();
        virtual ~Filesystem();
        OrphanList* getOrphanList() /// "/dev/orphans"
            {return orphanList;}

        static Filesystem* global() /// "/"
        {
            static Filesystem filesystem;
            return &filesystem;
        }
        std::string nodeName();
        FilesystemIter* firstChild();
        FilesystemIter* nextChild(FilesystemIter* _prevChild);
    protected:
    private:
        OrphanList* orphanList;
};

#endif // FILESYSTEM_H
