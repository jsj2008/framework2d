#include "GraphicalContext.h"
#include <cstring>
#include <iostream>

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
    if (referenceCount != 0 && name[0] != '\0')
    {
        std::cout << "Warning: Graphical context: " << name << " not completely freed" << std::endl;
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
