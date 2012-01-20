#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <string>
class FilesystemNode;

class FilesystemIter
{
    public:
        FilesystemIter();
        virtual ~FilesystemIter();
        virtual FilesystemNode* get()=0;
        FilesystemNode* operator*(){return get();}
};
class FilesystemNode
{
    public:
        FilesystemNode();
        virtual ~FilesystemNode();
        FilesystemNode* getNode(const std::string& _address);
        virtual std::string nodeName()=0;
        virtual FilesystemIter* firstChild()=0; /// Allocates, will not need direct deletion in the usual usage
        virtual FilesystemIter* nextChild(FilesystemIter* _prevChild)=0; /// If this reaches the end it will return nullptr and delete the iterator
    protected:
    private:
        FilesystemNode* getIndividualNode(const std::string& _address);
};

#endif // FILESYSTEMNODE_H
