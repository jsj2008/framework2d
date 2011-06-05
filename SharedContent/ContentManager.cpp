#include "ContentManager.h"
#include "SharedContent.h"
#include <cassert>

ContentManager g_ContentManager;

ContentManager::ContentManager()
{
    //ctor
}

ContentManager::~ContentManager()
{
    //dtor
}

void ContentManager::addSharedContent(SharedContent* content)
{
    assert(contentMap.find(content->getName()) == contentMap.end());
    contentMap[content->getName()] = content;
}
