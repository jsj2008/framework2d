#include "SharedContent.h"
#include <cstring>
#include <cassert>
#include <Log/Log.h>

SharedContent::SharedContent(const char* _name)
{
    if (_name != nullptr)
    {
        size_t len = strlen(_name);
        assert(len < MAX_CONTENT_NAME);
        memcpy(name,_name,len+1);
        referenceCount = 0;
    }
    else
    {
        name[0] = '\0';
        referenceCount = 1;
    }
}
SharedContent::~SharedContent()
{
    //dtor
    if (referenceCount != 0 && name[0] != '\0')
    {
        g_Log.warning(std::string("Shared content: ") + name + " not completely freed");
    }
}

void SharedContent::grab()
{
    if (referenceCount == 0)
    {
        load();
    }
    referenceCount++;
    vGrab();
}

void SharedContent::release()
{
    assert(referenceCount);
    referenceCount--;
    if (referenceCount == 0)
    {
        unload();
    }
    vRelease();
}
