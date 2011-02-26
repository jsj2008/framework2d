#include "GraphicalContext.h"
#include <cstring>
#include <cassert>

GraphicalContext::GraphicalContext(const char* _name)
{
    if (_name != NULL)
    {
        strcpy(name,_name);
        referenceCount = 0;
    }
    else
    {
        name[0] = '\0';
        referenceCount = 1;
    }
}
GraphicalContext::~GraphicalContext()
{
    //dtor
    assert(referenceCount == 0 || name[0] == '\0');
}

void GraphicalContext::grab()
{
    if (referenceCount == 0)
    {
        load();
    }
    referenceCount++;
    vGrab();
}

void GraphicalContext::release()
{
    referenceCount--;
    if (referenceCount == 0)
    {
        unload();
    }
    vRelease();
}
