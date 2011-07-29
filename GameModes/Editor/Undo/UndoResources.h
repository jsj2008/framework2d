#ifndef UNDORESOURCES_H
#define UNDORESOURCES_H

typedef unsigned int UndoResource;
#include <vector>
#include <map>

class UndoResources
{
    public:
        UndoResources();
        virtual ~UndoResources();
        static UndoResources& global();
        UndoResource createEntry(); /// Adds an entry with null value
        void setValue(UndoResource _resourceId, void* _value); /// Sets the value of the entry, removes the old value from the value map, and adds the new one
        void* getValue(UndoResource _resourceId); /// Returns the value of the entry
        UndoResource getEntry(void* _value); /// Looks up the entry in the value map, fails on non-existance
        UndoResource getEntrySafely(void* _value); /// Looks up the entry in the value map, creates it on non-existance
    protected:
    private:
        std::vector<void*> entries;
        std::map<void*, UndoResource> values;
};

#endif // UNDORESOURCES_H
