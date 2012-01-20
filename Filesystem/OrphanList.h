#ifndef ORPHANLIST_H
#define ORPHANLIST_H

#include <GameObject.h>

class OrphanList : public GameObjectBase
{
    public:
        OrphanList();
        virtual ~OrphanList();
        void attachOrphan(GameObjectBase* _node);
        EventHandle* getEventHandle(const std::string& _name){throw -1;}
    protected:
    private:
};

#endif // ORPHANLIST_H
