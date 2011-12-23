#ifndef SHAREDCONTENT_H
#define SHAREDCONTENT_H

#define MAX_CONTENT_NAME 16
class SharedContent
{
    public:
        /// These are the reference counting functions
        const char* getName(){return name;}
    protected:
        SharedContent(const char* _name);
        virtual ~SharedContent();
        friend class ContentHandlerBase;
        void grab(); /// ++
        void release(); /// --
        virtual void vGrab(){}
        virtual void vRelease(){}
        virtual void load()=0;
        virtual void unload()=0;
        unsigned short referenceCount;
        char name[MAX_CONTENT_NAME];
    private:
};

class ContentHandlerBase
{
    public:
    protected:
        void grab(){content->grab();}
        void release(){content->release();}
        SharedContent* content;
};
template <typename T>
class ContentHandler: public ContentHandlerBase
{
    public:
        ContentHandler()
        {
            content = 0;
        }
        ContentHandler(T* _content)
        {
            content = _content;
            grab();
        }
        ContentHandler(const ContentHandler<T>& cpy)
        {
            content = cpy.content;
            grab();
        }
        ~ContentHandler()
        {
            if (content != 0)
                release();
        }
        T* operator->(){return (T*)content;}
};

#endif // SHAREDCONTENT_H
