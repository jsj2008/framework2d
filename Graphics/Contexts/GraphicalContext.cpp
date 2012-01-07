#include "GraphicalContext.h"
#include <cstring>
#include <Log/Log.h>

GraphicalContext::GraphicalContext(const char* _name)
{
    if (_name != nullptr)
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
    if (referenceCount != 0 && name[0] != '\0')
    {
        g_Log.warning(std::string("Graphical context: ") + name + " not completely freed");
    }
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
