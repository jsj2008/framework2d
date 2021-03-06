#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <string>
#include <unordered_map>
#include <SharedContent/SharedContent.h>
typedef std::string ContentIndex;

extern class ContentManager
{
    public:
        ContentManager();
        virtual ~ContentManager();
        template <typename T>
        const ContentHandler<T> getContent(const ContentIndex& name);
        void addSharedContent(SharedContent* content);
    protected:
    private:
        std::unordered_map<std::string, SharedContent*> contentMap;
}g_ContentManager;

#endif // CONTENTMANAGER_H

template <typename T>
const ContentHandler<T> ContentManager::getContent(const ContentIndex& name)
{
    SharedContent* content = contentMap[name];
#ifdef _DEBUG
    assert(content);
    T* dynamicCast = dynamic_cast<T*>(content);
    assert(dynamicCast);
#endif
    T* castedContent = (T*)content;
    return ContentHandler<T>(castedContent);
}
