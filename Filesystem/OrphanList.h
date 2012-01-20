#ifndef ORPHANLIST_H
#define ORPHANLIST_H

#include <GameObject.h>

class OrphanList : public GameObject<OrphanList>
{
    public:
        OrphanList(GameObjectBase* _parent);
        virtual ~OrphanList();
        void attachOrphan(GameObjectBase* _node);
        static void registerActions(GameObjectType* _type);
        EventHandle* getEventHandle(const std::string& _name){throw -1;}
        void print(std::string* _output);
    protected:
    private:
};

#endif // ORPHANLIST_H
